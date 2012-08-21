#include <stdio.h>
#include <string.h>
#include <errno.h>

#define ARRAY_SIZE(__arr) (sizeof(__arr) / sizeof((__arr)[0]))

struct buffer_struct {
    size_t size;
    char *buffer;
    char *rev_ptr;
} /* optional variable list */;

static char *out_buf;
static char *out_ptr;
static size_t out_buf_size;

static char *numbers[] = {
    "bir", "iki", "uc", "dort",
    "bes", "alti", "yedi", "sekiz",
    "dokuz", "on", "yirmi", "otuz",
    "kirk", "elli", "altmis", "yetmis",
    "seksen", "doksan", "yuz", "bin",
    "milyon", "milyar", "trilyon"
};

static int prepend_str(const char *str)
{
    size_t len = strlen(str);
    if (out_ptr - len < out_buf)
        return -ERANGE;

    out_ptr -= len;
    memcpy(out_ptr, str, len);

    return 0;
}

static inline int prepend_char(char ch)
{
    if (out_ptr - 1 < out_buf)
        return -ERANGE;

    --out_ptr;
    *out_ptr = ch;

    return 0;
}

static const char *numstr(int digit, int place_val)
{
    char *ret = NULL;
    long long num = digit * place_val;

    if (num < 11 && num > 0) {
        ret = numbers[num - 1];
        return ret;
    }

    switch (num) {
    case 20:
        ret = numbers[10];
        break;
    case 30:
        ret = numbers[11];
        break;
    case 40:
        ret = numbers[12];
        break;
    case 50:
        ret = numbers[13];
        break;
    case 60:
        ret = numbers[14];
        break;
    case 70:
        ret = numbers[15];
        break;
    case 80:
        ret = numbers[16];
        break;
    case 90:
        ret = numbers[17];
        break;
    case 100:
        ret = numbers[18];
        break;
    case 1000:
        ret = numbers[19];
        break;
    case 1000000:
        ret = numbers[20];
        break;
    case 1000000000:
        ret = numbers[21];
        break;
    case 1000000000000:
        ret = numbers[22];
        break;
    }

    return ret;
}

static int __num_to_words(char *buf, long num, char sep_char);
static inline int _pow(int x, int y);

static int __numstr(int digit, int pos)
{
    int ret = 0;
    const char *str = NULL;
    int triple = pos / 3;
    int place_val = _pow(10, pos % 3);

    switch (pos % 3) {
    case 0:
        if (triple) {
            str = numstr(_pow(10, triple * 3), 1);
            if ((ret = prepend_str(str)) != 0)
                goto err_out;
            if (digit > 1) {
                str = numstr(digit, 1);
                if ((ret = prepend_str(str)) != 0)
                    goto err_out;
            }
        } else {
            str = numstr(digit ,1);
            if ((ret = prepend_str(str)) != 0)
                goto err_out;
        }
        break;
    case 1:
        str = numstr(digit * place_val, 1);
        if ((ret = prepend_str(str)) != 0)
            goto err_out;
        break;
    case 2:
        str = numstr(place_val, 1);
        if ((ret = prepend_str(str)) != 0)
            goto err_out;
        str = numstr(digit, 1);
        break;
    }

err_out:
    return ret;
}

int num_to_words(char *buf, double num, char sep_char)
{
    (void)buf;
    int ret = 0;
    long integer = (long)num;
    long fraction = (num - integer) * 1000;

    printf("integer = %ld, fraction=%ld\n", integer, fraction);
    __num_to_words(NULL, integer, sep_char);

    return ret;
}

static int __num_to_words(char *buf, long num, char sep_char)
{
    (void)buf;
    unsigned char rmost_digit;
    int pos = 0;
    int triple = 0;
    int result = 0;

    char dummy_buf[256];
    out_buf = dummy_buf;
    out_buf_size = ARRAY_SIZE(dummy_buf);
    out_ptr = out_buf + out_buf_size - 1;
    *out_ptr = '\0';

    /* Extract rightmost digit and shift right */
    do {
        rmost_digit = num % 10;
        num /= 10;

        if ((result = __numstr(rmost_digit, pos)))
            break;

        if (num && sep_char)
            if((result = prepend_char(sep_char)))
                break;

        if (pos % 3 == 0)
            ++triple;
        ++pos;
    } while (num);

    printf("buf contains the string = %s, with result: %d\n",
           out_ptr, result);

    return result;
}

static inline int _pow(int x, int y)
{
    int result = 1;
    if (!x)
        return result;

    while (y--)
        result *= x;

    return result;
}
