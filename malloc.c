/* struct mallinfo pulled from mallinfo.3:
 *
 * Copyright (c) 2012 by Michael Kerrisk <mtk.manpages@gmail.com>
 * 
 * Permission is granted to make and distribute verbatim copies of this
 * manual provided the copyright notice and this permission notice are
 * preserved on all copies.
 * 
 * Permission is granted to copy and distribute modified versions of this
 * manual under the conditions for verbatim copying, provided that the
 * entire resulting derived work is distributed under the terms of a
 * permission notice identical to this one.
 * 
 * Since the Linux kernel and libraries are constantly changing, this
 * manual page may be incorrect or out-of-date.  The author(s) assume no
 * responsibility for errors or omissions, or for damages resulting from
 * the use of the information contained herein.  The author(s) may not
 * have taken the same level of care in the production of this manual,
 * which is licensed free of charge, as they might when working
 * professionally.
 * 
 * Formatted or processed versions of this manual, if unaccompanied by
 * the source, must acknowledge the copyright and authors of this work.
 */

#include <string.h>	/* memset */

struct mallinfo {
	int arena;     /* Non-mmapped space allocated (bytes) */
	int ordblks;   /* Number of free chunks */
	int smblks;    /* Number of free fastbin blocks */
	int hblks;     /* Number of mmapped regions */
	int hblkhd;    /* Space allocated in mmapped regions (bytes) */
	int usmblks;   /* Maximum total allocated space (bytes) */
	int fsmblks;   /* Space in freed fastbin blocks (bytes) */
	int uordblks;  /* Total allocated space (bytes) */
	int fordblks;  /* Total free space (bytes) */
	int keepcost;  /* Top-most, releasable space (bytes) */
};

struct mallinfo mallinfo(void)
{
	struct mallinfo my_info;
	memset(&my_info, 0, sizeof(struct mallinfo));
	return my_info;
}