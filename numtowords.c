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

    printf("buf = %u, ptr = %u, len = %u\n",
            (unsigned long)out_buf,
            (unsigned long)out_ptr, len);

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

static int __num_to_words(char *buf, long num);
static inline int _pow(int x, int y);

static const char *__numstr(int digit, int pos)
{
    const char *ret = NULL;
    int triple = pos / 3;
    int place_val = _pow(10, pos % 3);

    switch (pos % 3) {
    case 0:
        if (triple) {
            ret = numstr(_pow(10, triple * 3), 1);
            if (prepend_str(ret) != 0)
                goto err_out;
            printf("new = %s\n", ret);
            if (digit > 1) {
                ret = numstr(digit, 1);
                if (prepend_str(ret) != 0)
                    goto err_out;
                printf("new = %s\n", numstr(digit, 1));
            }
        } else {
            ret = numstr(digit ,1);
            if (prepend_str(ret) != 0)
                goto err_out;
            printf("new = %s\n", ret);
        }
        break;
    case 1:
        ret = numstr(digit * place_val, 1);
        printf("new = %s\n", ret);
        if (prepend_str(ret) != 0)
            goto err_out;
        break;
    case 2:
        ret = numstr(place_val, 1);
        if (prepend_str(ret) != 0)
            goto err_out;
        printf("new = %s\n", ret);
        ret = numstr(digit, 1);
        printf("new = %s\n", ret);
        break;
    }

err_out:
    return ret;
}

int num_to_words(char *buf, double num)
{
    (void)buf;
    int ret = 0;
    long integer = (long)num;
    long fraction = (num - integer) * 1000;

    printf("integer = %ld, fraction=%ld\n", integer, fraction);
    __num_to_words(NULL, integer);

    return ret;
}

static int __num_to_words(char *buf, long num)
{
    (void)buf;
    unsigned char rmost_digit;
    int pos = 0;
    int triple = 0;

    char dummy_buf[256];
    out_buf = dummy_buf;
    out_buf_size = ARRAY_SIZE(dummy_buf);
    out_ptr = out_buf + out_buf_size - 1;
    *out_ptr = '\0';

    /* Extract rightmost digit and shift right */
    do {
        rmost_digit = num % 10;
        __numstr(rmost_digit, pos);

        if (pos % 3 == 0)
            ++triple;
        ++pos;

        /* TODO: numstr(digit, place_value, triple) */
       // printf("rightmost = %d, val = %s, place_val = %d, triple = %d\n",
       //         rmost_digit, numstr(rmost_digit ,place_value),
       //         place_value, triple);
    } while (num /= 10);

    printf("buf contains the string = %s\n", out_ptr);

    return 0;
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
