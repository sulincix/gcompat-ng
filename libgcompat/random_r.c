/*
 * -------------------------------------------------------------------
 * Copyright © 2005-2020 Rich Felker, et al.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * -------------------------------------------------------------------
 */

/* This is an adaptation of musl's random() implementation, adding
 * random_data buffers to make reentrant variants
 */

#include <stddef.h>	/* NULL, size_t */
#include <stdint.h>	/* int32_t, uint32_t */
#include <errno.h>	/* errno */

/* This code uses the same lagged fibonacci generator as the
 * original bsd random implementation except for the seeding
 * which was broken in the original
 */

/* This must use the same struct layout as used by glibc
 * and specified in LSB
 * ref: https://refspecs.linuxfoundation.org/LSB_5.0.0/LSB-Core-generic/LSB-Core-generic/libc-ddefs.html
 */
struct random_data {
	int32_t *x;		/* int32_t *fptr */
	int32_t *unused_1;	/* int32_t *rptr */
	int32_t *unused_2;	/* int32_t *state */
	int n;			/* int rand_type */
	int i;			/* int rand_deg */
	int j;			/* int rand_sep */
	int32_t *unused_3;	/* int32_t *end_ptr */
};

static uint32_t lcg31(uint32_t x) {
	return (1103515245*x + 12345) & 0x7fffffff;
}

static uint64_t lcg64(uint64_t x) {
	return 6364136223846793005ull*x + 1;
}

static void savestate_r(struct random_data *buf) {
	buf->x[-1] = (buf->n<<16)|(buf->i<<8)|buf->j;
}

static void loadstate_r(uint32_t *state, struct random_data *buf) {
	buf->x = (int32_t *)state + 1;
	buf->n = buf->x[-1]>>16;
	buf->i = (buf->x[-1]>>8)&0xff;
	buf->j = buf->x[-1]&0xff;
}

int srandom_r(unsigned seed, struct random_data *buf) {
	int k;
	uint64_t s = seed;

	if (buf == NULL) {
		return -1;
	}

	if (buf->n > 63) {
		return -1;
	} else if (buf->n == 0) {
		buf->x[0] = s;
		return 0;
	}
	buf->i = buf->n == 31 || buf->n == 7 ? 3 : 1;
	buf->j = 0;
	for (k = 0; k < buf->n; k++) {
		s = lcg64(s);
		buf->x[k] = s>>32;
	}
	/* make sure x contains at least one odd number */
	buf->x[0] |= 1;

	return 0;
}

int initstate_r(unsigned seed, char *restrict state, size_t size,
		struct random_data *restrict buf) {
	if (size < 8) {
		errno = EINVAL;
		return -1;
	}

	savestate_r(buf);
	if (size < 32) {
		buf->n = 0;
	} else if (size < 64) {
		buf->n = 7;
	} else if (size < 128) {
		buf->n = 15;
	} else if (size < 256) {
		buf->n = 31;
	} else {
		buf->n = 63;
	}
	buf->x = (int32_t*)state + 1;
	srandom_r(seed, buf);
	savestate_r(buf);
	return 0;
}

int setstate_r(char *restrict state, struct random_data *restrict buf) {
	if (!state || !buf) {
		errno = EINVAL;
		return -1;
	}

	savestate_r(buf);
	loadstate_r((uint32_t*)state, buf);
	return 0;
}

int random_r(struct random_data *restrict buf, int32_t *restrict result) {
	long k;

	if (result == NULL || buf == NULL) {
		errno = EINVAL;
		return -1;
	}

	if (buf->n == 0) {
		k = buf->x[0] = lcg31(buf->x[0]);
		goto end;
	}
	buf->x[buf->i] += buf->x[buf->j];
	k = buf->x[buf->i]>>1;
	if (++(buf->i) == buf->n) {
		buf->i = 0;
	} if (++(buf->j) == buf->n) {
		buf->j = 0;
	}
end:
	*result = k;
	return 0;
}
