/*
 * numtowords.c
 *
 * Copyright (c) 2012 Cihangir Akturk
 *
 */

#include <stdio.h>
#include <string.h>
#include <errno.h>

static char *out_buf;
static char *out_ptr;
static size_t out_buf_size;

static const char *nums[] = {
	"sifir", "bir", "iki", "uc", "dort", "bes", "alti",
	"yedi", "sekiz", "dokuz"
};
static const char *tens[] = {
	"", "on", "yirmi", "otuz", "kirk", "elli",
	"altmis", "yetmis", "seksen", "doksan"
};
static const char *tri_nums[] = {
	"", "bin", "milyon", "milyar", "trilyon", "katrilyon", "kentilyon",
};

static int prepend_str(const char *str)
{
	size_t len = strlen(str);
	if (out_ptr - len - 1 < out_buf)
		return -ERANGE;

	if (*out_ptr != '\0') {
		out_ptr--;
		*out_ptr = ' ';
	}
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

static int __num_to_words(long num, char sep_char);

int num_to_words(char **buf, size_t size, double num, char sep_char)
{
	int ret = 0;
	long integer = (long) num;
	long fraction = (num - integer) * 1000;
	(void) fraction;

	out_buf = *buf;
	out_buf_size = size;
	out_ptr = out_buf + out_buf_size - 1;
	*out_ptr = '\0';

	ret = __num_to_words(integer, sep_char);
	*buf = out_ptr;

	return ret;
}

static void hundred(int num, int nth_tri, char sep)
{
	int pos = 0, n = num;

	do {
		int digit;

		digit = n % 10;
		n = n / 10;

		switch (pos) {
		case 0:
			if (nth_tri > 1) {
				if (digit > 0)
					prepend_str(nums[digit]);
			} else if (nth_tri > 0) {
				if (digit > 1)
					prepend_str(nums[digit]);
			} else {
				prepend_str(nums[digit]);
			}
			break;

		case 1:
			if (digit > 0)
				prepend_str(tens[digit]);
			break;

		case 2:
			prepend_str("yuz");
			if (digit > 1)
				prepend_str(nums[digit]);
			break;

		default:
			printf("error\n");
			/* error? */
			break;
		}
		pos++;
	} while (n);
}

static int __num_to_words(long num, char sep_char)
{
	int triple = 0, ret = 0, pos = 0;

	if (!num) {
		prepend_str(nums[num]);
		return 0;
	}

	/* Extract rightmost 3 digit and shift right */
	do {
		triple = num % 1000;
		num /= 1000;

		/* bin, milyon, etc.. */
		if (pos > 0 && triple)
			prepend_str(tri_nums[pos]);
		hundred(triple, pos, sep_char);

		pos++;
	} while (num);

	return ret;
}
