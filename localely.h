/* Author: Richard James Howe
 * License: The Unlicense
 * Email: howe.r.j.89@gmail.com
 * Repo: https://github.com/howerj/localely
 *
 * As you may know, "locale.h" should be avoided, for a good
 * reason why, see:
 *
 * <https://github.com/mpv-player/mpv/commit/1e70e82baa9193f6f027338b0fab0f5078971fbe>.
 *
 * The functions in <ctype.h> are locale dependent. This means you can
 * get unexpected behavior with those functions (especially if some random
 * library goes and uses "setlocale" within your program).
 *
 * If you want a set of portable isX() functions in C that does not
 * depend on the locale, look no further, or look further if you want
 * super highly optimized code. 
 *
 * We could add a few other functions for printing and scanning numbers.
 *
 * Ideally we would also make a set of printf/scanf functions that were
 * also locale independent as well, but those functions are are quite
 * complex. 
 *
 * This library deals with ASCII/Bytes, not UTF-8 or anything else. 
 *
 * This is a header only library that should compile under C and C++.
 *
 * The following #define directives might be useful to you:
 *
 * #define LOCALELY_API
 * #define LOCALELY_IMPLEMENTATION
 * #define LOCALELY_UNIT_TESTS
 * #define LOCALELY_DEFINE_MAIN
 * #define NDEBUG
 *
 * You can use these to make a version of this library that define
 * the isX functions that are; just declarations, instances with
 * external linkage, instances that are static (and static inline).
 * You can also instantiate a set of unit tests and even an instance
 * of "main()" that runs the unit tests.
 *
 * By default:
 *
 * - The library behaves like an ordinary header with declarations
 *   of the functions that are to be exported.
 * - Unit tests are off.
 * - "main()" is not defined.
 *
 * To use this library you will need to do one of the following depending
 * on your use case:
 *
 * 1) Include the header file in your C file and create another C
 * file to link with that includes this header and defines
 * "LOCALELY_IMPLEMENTATION" before the header is included.
 * 2) Include the header file in your C file, and before that
 * inclusion define "LOCALELY_IMPLEMENTATION" and define LOCALELY_API 
 * as "static inline".
 * 3) Define "LOCALELY_IMPLEMENTATION", "LOCALELY_UNIT_TESTS" and
 * "LOCALELY_DEFINE_MAIN" before the header file inclusion in another C 
 * file which includes this header to make a program that runs the 
 * unit tests and exits.
 *
 * The header only depends on <assert.h> unless unit tests are needed. The
 * unit tests do what I complain about earlier, being some random library
 * that uses "setlocale", you should not need to call them in your program
 * however as they are just an aid for development, so I will allow my
 * own hypocrisy. */
#ifndef LOCALELY_H
#define LOCALELY_H
#ifdef __cplusplus
extern "C" {
#endif

#include <assert.h>

#ifndef LOCALELY_API
#define LOCALELY_API
#endif

#ifndef LOCALELY_IMPLEMENTATION

extern int C_isascii(const int ch);
extern int C_isspace(const int ch);
extern int C_iscntrl(const int ch);
extern int C_isprint(const int ch);
extern int C_isblank(const int ch);
extern int C_isgraph(const int ch);
extern int C_isupper(const int ch);
extern int C_islower(const int ch);
extern int C_isalpha(const int ch);
extern int C_isdigit(const int ch);
extern int C_isalnum(const int ch);
extern int C_ispunct(const int ch);
extern int C_isxdigit(const int ch);

#else

static inline void C_assert_char_range(const int ch) { assert(ch >= -1 && ch <= 255); }
static inline int C_assert_return(const int r) { assert(r == 0 || r == 1); return r; }
LOCALELY_API int C_isascii(const int ch) { C_assert_char_range(ch); return C_assert_return(ch < 128 && ch >= 0); }
LOCALELY_API int C_isspace(const int ch) { C_assert_char_range(ch); return C_assert_return((ch >= 9 && ch <= 13) || ch == 32); }
LOCALELY_API int C_iscntrl(const int ch) { C_assert_char_range(ch); return C_assert_return((ch < 32 || ch == 127) && C_isascii(ch)); }
LOCALELY_API int C_isprint(const int ch) { C_assert_char_range(ch); return C_assert_return(!C_iscntrl(ch) && C_isascii(ch)); }
LOCALELY_API int C_isblank(const int ch) { C_assert_char_range(ch); return C_assert_return(ch == 32 || ch == 9); }
LOCALELY_API int C_isgraph(const int ch) { C_assert_char_range(ch); return C_assert_return(ch > 32 && ch < 127); }
LOCALELY_API int C_isupper(const int ch) { C_assert_char_range(ch); return C_assert_return(ch >= 65 && ch <= 90); }
LOCALELY_API int C_islower(const int ch) { C_assert_char_range(ch); return C_assert_return(ch >= 97 && ch <= 122); }
LOCALELY_API int C_isalpha(const int ch) { C_assert_char_range(ch); return C_assert_return(C_islower(ch) || C_isupper(ch)); }
LOCALELY_API int C_isdigit(const int ch) { C_assert_char_range(ch); return C_assert_return(ch >= 48 && ch <= 57); }
LOCALELY_API int C_isalnum(const int ch) { C_assert_char_range(ch); return C_assert_return(C_isalpha(ch) || C_isdigit(ch)); }
LOCALELY_API int C_ispunct(const int ch) { C_assert_char_range(ch); return C_assert_return((ch >= 33 && ch <= 47) || (ch >= 58 && ch <= 64) || (ch >= 91 && ch <= 96) || (ch >= 123 && ch <= 126)); }
LOCALELY_API int C_isxdigit(const int ch) { C_assert_char_range(ch); return C_assert_return((ch >= 65 && ch <= 70) || (ch >= 97 && ch <= 102) || C_isdigit(ch)); }

#endif

#ifdef LOCALELY_UNIT_TESTS
#include <locale.h>
#include <ctype.h>

#define BOOLINATOR(X) (!!(X))

#ifndef LOCALELY_IMPLEMENTATION

extern int localely_unit_tests(void); /* returns zero on success, negative on failure */

#else

LOCALELY_API int localely_unit_tests(void) {
	if (!setlocale(LC_ALL, "C"))
		return -1;
	for (int ch = -1; ch < 256; ch++) {
		if (C_isspace(ch) != BOOLINATOR(isspace(ch))) return -2;
		if (C_iscntrl(ch) != BOOLINATOR(iscntrl(ch))) return -3;
		if (C_isprint(ch) != BOOLINATOR(isprint(ch))) return -4;
		if (C_isblank(ch) != BOOLINATOR(isblank(ch))) return -5;
		if (C_isgraph(ch) != BOOLINATOR(isgraph(ch))) return -6;
		if (C_isupper(ch) != BOOLINATOR(isupper(ch))) return -7;
		if (C_islower(ch) != BOOLINATOR(islower(ch))) return -8;
		if (C_isalpha(ch) != BOOLINATOR(isalpha(ch))) return -9;
		if (C_isdigit(ch) != BOOLINATOR(isdigit(ch))) return -10;
		if (C_isalnum(ch) != BOOLINATOR(isalnum(ch))) return -11;
		if (C_ispunct(ch) != BOOLINATOR(ispunct(ch))) return -12;
		if (C_isxdigit(ch) != BOOLINATOR(isxdigit(ch))) return -13;
	}
	return 0;
}
#endif

#undef BOOLINATOR

#ifdef LOCALELY_DEFINE_MAIN
#include <stdio.h>

int main(void) {
	int r = localely_unit_tests();
	if (printf("Localely Unit Test Results: %d %s\n", r, r ? "[FAIL]" : "[PASS]") < 0)
		return 2;
	return r == 0 ? 0 : 1;
}

#endif /* LOCALELY_UNIT_TESTS */
#endif /* LOCALELY_DEFINE_MAIN */
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* LOCALELY_H */
