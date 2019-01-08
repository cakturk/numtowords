/*
 * numtowords.c
 *
 * Copyright (c) 2012 Cihangir Akturk
 *
 */

#ifndef NUMTOWORDS_H
#define NUMTOWORDS_H
#ifdef __cplusplus
extern "C" {
#endif

#define ARRAY_SIZE(__arr) (sizeof(__arr) / sizeof((__arr)[0]))
	extern int num_to_words(char **buffer, size_t size,
				double num, char sep_char);

#ifdef __cplusplus
}
#endif
#endif				// NUMTOWORDS_H
