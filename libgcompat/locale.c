#include <dlfcn.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include "alias.h" /* alias */
#include "internal.h"

struct glibc_locale {
	/* hopefully nobody pokes at this */
	void *__locales[13];

	const unsigned short int *__ctype_b;
	const int *__ctype_tolower;
	const int *__ctype_toupper;

	char *__names[13];
};

typedef locale_t (*newlocale_t)(int mask, const char *name, locale_t base);

const unsigned short **__ctype_b_loc(void);
const int32_t **__ctype_tolower_loc(void);
const int32_t **__ctype_toupper_loc(void);

struct glibc_locale *__newlocale(int mask, const char *name, locale_t base) {
	struct glibc_locale *ret = (void*)base;
	if(ret == NULL) {
		ret = calloc(1, sizeof(struct glibc_locale));
		if(ret == NULL) return NULL;
		mask = 0x7fffffff;
	}

	/* relies on sizeof(*locale_t) <= sizeof(ret.__locales) */
	newlocale_t real_newlocale = (newlocale_t)dlsym(RTLD_NEXT, "__newlocale");
	real_newlocale(mask, name, (void*)ret);

	ret->__ctype_b = *__ctype_b_loc();
	ret->__ctype_tolower = *__ctype_tolower_loc();
	ret->__ctype_toupper = *__ctype_toupper_loc();

	ret->__names[0] = "C";
	for(int i = 1; i < 13; i++) ret->__names[i] = ret->__names[0];

	return ret;
}

alias(__newlocale, newlocale);

void *__duplocale(struct glibc_locale *loc) {
	struct glibc_locale *ret = malloc(sizeof *ret);
	if(!ret) return NULL;
	*ret = *loc;
	return ret;
}

alias(__duplocale, duplocale);
