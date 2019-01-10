/*
 * main.c
 *
 * Copyright (c) 2012 Cihangir Akturk
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "numtowords.h"

int main(int argc, char *argv[])
{
	char dummy_buf[256];
	char *buf = dummy_buf;
	int result = 0;

	char sep_char, *endptr;
	double val;

	if (argc < 2) {
		fprintf(stderr, "Usage: %s str [seperator_char]\n",
			argv[0]);
		exit(EXIT_FAILURE);
	}

	val = strtod(argv[1], &endptr);
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
		printf("Num: %f, Text: <%s>\n", val, buf);
	else
		fprintf(stderr,
			"Supplied number is too large to be converted!\n");


	exit(EXIT_SUCCESS);
}
