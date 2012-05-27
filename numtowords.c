#include <stdio.h>

#define ARRAY_SIZE(__arr) (sizeof(__arr) / sizeof((__arr)[0]))

static char *numbers[] = {
    "bir", "iki", "uc", "dort",
    "bes", "alti", "yedi", "sekiz",
    "dokuz", "on", "yirmi", "otuz",
    "kirk", "elli", "altmis", "yetmis",
    "seksen", "doksan", "yuz", "bin",
    "milyon", "milyar", "trilyon"
};

static const char *numstr(int num)
{
    char *ret = NULL;

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
        ret = numbers[13];
        break;
    case 50:
        ret = numbers[14];
        break;
    case 60:
        ret = numbers[15];
        break;
    case 70:
        ret = numbers[16];
        break;
    case 80:
        ret = numbers[17];
        break;
    case 90:
        ret = numbers[18];
        break;
    case 100:
        ret = numbers[19];
        break;
    case 1000:
        ret = numbers[20];
        break;
    }

    return ret;
}

static int __num_to_words(char *buf, long num);
static inline int _pow(int x, int y);

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
    int place_value;
    int triple = 0;

    /* Extract rightmost digit and shift right */
    do {
        rmost_digit = num % 10;
        place_value = _pow(10, pos % 3);
        if (pos % 3 == 0)
            ++triple;
        ++pos;

        printf("rightmost = %d, val = %s, place_val = %d\n",
                rmost_digit, numstr(rmost_digit), place_value);
    } while (num /= 10);

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
