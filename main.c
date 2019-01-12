/*
 * main.c
 *
 * Copyright (c) 2012 Cihangir Akturk
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "numtowords.h"

static int strwords(char *s);

int main(int argc, char *argv[])
{
	char dummy_buf[256];
	char *buf = dummy_buf;
	int result = 0;

	char sep_char, *endptr;
	unsigned long val;

	if (argc < 2) {
		fprintf(stderr, "Usage: %s str [seperator_char]\n",
			argv[0]);
		exit(EXIT_FAILURE);
	}
	/* strwords(argv[1]); */
	/* return 0; */

	val = strtoul(argv[1], &endptr, 10);
	sep_char = (argc > 2) ? (argv[2])[0] : 0x20;

	if (errno == ERANGE) {
		perror("Cannot convert to number");
		exit(EXIT_FAILURE);
	}

	if (endptr == argv[1]) {
		fprintf(stderr, "No digits were found\n");
		exit(EXIT_FAILURE);
	}

	result = num_to_words(&buf, ARRAY_SIZE(dummy_buf), val, sep_char);
	if (!result)
		printf("Num: %lu, Text: <%s>\n", val, buf);
	else
		fprintf(stderr,
			"Supplied number is too large to be converted!\n");

	exit(EXIT_SUCCESS);
}

#define min(a,b) \
	({ typeof (a) _a = (a); \
	 typeof (b) _b = (b); \
	 _a < _b ? _a : _b; })


static int strwords(char *s)
{
	size_t n;
	char *p;

	n = strlen(s);
	p = s + n;

	while (n) {
		size_t m;
		unsigned long val;
		char *endp;

		*p = '\0';
		m = min(n, 3);
		p -= m;
		n -= m;
		val = strtoul(p, &endp, 10);
		/* if (endp == p && !val) */
		/* 	return -errno; */
		printf("s: %s part: %lu\n", p, val);
	}

	return 0;
}
