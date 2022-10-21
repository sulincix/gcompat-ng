==========================
 Changelog for libgcompat
==========================
:Author:
  * **A. Wilcox**, documentation writer
  * **Contributors**, code
:Copyright:
  © 2016-2020 Adélie Software and contributors.  NCSA open source license.


1.1 (202?-??-??)
================

For detailed contributor information, see the gcompat Git repository.

error
-----

* Always append a newline when error() is called, bringing behaviour in
  line with glibc.

gnulib
------

* Add __fdelt_warn as an alias of __fdelt_chk.

locale
------

* Redesign newlocale, courtesy of rcombs.

misc
----

* Add a __libc_single_threaded stub.  Currently it always says we are MT.

pthread
-------

* Add pthread_mutexattr_(get/set)kind_np, non-portable aliases of the
  pthread_mutexattr_(get/set)type function.

pwd
---

* Fix an issue where fgetpwent_r may infinitely recurse.

random
------

* New module, containing re-entrant random functions.

stdio
-----

* Add __dprintf_chk, using vdprintf as a backing function.

* Hook fopen to intercept attempts at opening /proc/self/exe.  Issue #349.

string
------

* Add historical, non-POSIX strerror_r definition.

* Add __explicit_bzero_chk.

sysctl
------

* Add __getauxval alias.

unistd
------

* Fix behaviour of execvp when called with a non-/proc/self/exe argument.

wchar
-----

* Add __mbrlen alias for mbrlen.


1.0.0 (2020-09-27)
==================

loader
------

* Fix crash on AArch64, courtesy of Ariadne Conill.

math
----

* Fix __*_finite math functions, courtesy of George Matsumura.

pthread
-------

* Add pthread_yield from Hal G.

* Add __sched_cpualloc and __sched_cpufree from Érico Nogueira.

readlink, unistd
----------------

* Update for AArch64 fix.

socket
------

* Fix inverted logic in __poll_chk.

wchar
-----

* Add the following functions from Michal Kazior:

  * __fwprintf_chk

  * __vfwprintf_chk

  * wcstod_l

  * wcstol_l

  * wcstoul_l


0.9.0 (2020-07-06)
==================

locale
------

* New module.

* Add newlocale and freelocale, which provide a glibc-compatible locale_t ABI.
  This is necessary for software using the libstdc++ <locale>/<ctype> modules.

time
----

* New module.

* Add __strftime_l.

unistd
------

* Add execv/execve/execvp family of functions to catch exec of /proc/self/exe.

wchar
-----

* Add __wcscpy_chk.


0.4.0 (2019-05-03)
==================

Build system
------------

* Allow building against libobstack.
* Fix compatibility with Linux 4.17 and newer.
* Travis CI is now used.

Documentation
-------------

* README rewritten to conform to Adélie project standards.

malloc
------

* Add mtrace and muntrace.

pthread
-------

* Add pthread_getname_np.

string
------

* Add __strdup.

wchar
-----

* Add __wcstol_internal.



0.3.0 (2018-09-21)
==================

Build system
------------

* Allow building against libucontext.

ctype
-----

* Add __ctype_b.


cxx_thread
----------

* Add __cxa_thread_atexit_impl.


math
----

* Add most __*_finite functions, courtesy of Elizabeth Myers.


readlink/realpath
-----------------

* Intercept realpath as well as readlink.
* Report EIO on /proc read failure.
* Report ENOSYS on dlsym failure.


resolv
------

* Add __res_search -> res_search alias.


socket
------

* Add __poll_chk


stdlib
------

* Add secure_getenv alias to __secure_getenv.


string
------

* Add __strcspn_c2.
* Add memfrob.
* Add strfry.

unistd
------

* Add __open_2/__open64_2.


malloc
------

* Add malloc_trim


0.2.0 (2018-02-20)
==================

Build system
------------

* Ensure correct compilation on GCC 4.x.


Loader
------

* Catch attempts to exec the loader itself and handle gracefully.

* Fix problems caught by valgrind memcheck.


malloc
------

* Add __sbrk.


socket
------

* Add __cmsg_nxthdr.


sysctl
------

* Don't build where SYS__sysctl is not defined (at least aarch64), credit to
  Michael Gehring of VoidLinux for finding this error.


Thanks to Samuel Holland for all of the following improvements and additions,
along with documentation improvements and other contributions:


error
-----

* Implement error().


execinfo
--------

* Implement backtrace_symbols_fd.

* Fix return value in backtrace.


grp
---

* Implement fgetgrent_r/getgrent_r.


Loader
------

* Handle programs that have a DT_NEEDED entry for glibc's ld.so.

* Handle when LD_PRELOAD is already set.

* Use the --argv0 option to properly set argv[0] in the target program.

* Ensure the the argument list is terminated with a NULL sentinel.

* Document the details of the loader's implementation.

* Intercept readlink("/proc/self/exe") to return the executable's absolute
  path, instead of musl's path.


math
----

* Add finite() variants.

* Add remaining long double variants of existing functions.


misc
----

* New module.

* Adds __chk_fail, __cxa_at_quick_exit, gnu_dev_major, gnu_dev_makedev,
  and gnu_dev_minor.


netdb
-----

* New module.

* Adds re-entrant (_r) versions of getprotoby[name,number], getprotoent,
  and getservent.


pwd
---

* Correctly implement fgetpwent_r/getpwent_r.


signal
------

* New module.

* Adds __xpg_sigpause.


socket
------

* New module.

* Adds __recv_chk and __recvfrom_chk.


stdio
-----

* Add all (non-wchar) stdio functions from LSB, plus those found in use
  in other applications. Document those functions from LSB as such.

* Use a consistent structure and paramater names for all functions.

* flag == 0 means FORTIFY_SOURCE=1, so the implemented checks should be
  unconditional.

* Add all possible checks without parsing the format string.

* Move functions from wchar.h to their own appropriately-named file.


stdlib
------

* Fix prototype of __realpath_chk.

* Add all strto* functions from LSB, plus the ones that were previously
  incorrectly in string.c.


string
------

* Add all checked string functions from LSB, plus those found in use
  in other applications. Document those functions from LSB as such.

* Use a consistent structure and paramater names for all functions.

* Fix multiple off-by-one errors.

* Use a less hacky and more optimized rawmemchr.


syslog
------

* New module.

* Adds __syslog_chk and __vsyslog_chk.


unistd
------

* New module.

* Adds __confstr_chk, __getcwd_chk, __getgroups_chk, __gethostname_chk,
  __getlogin_r_chk, __getpagesize, __getpgid, __pread_chk, __pread64_chk,
  __readlink_chk, __sysconf, __ttyname_r_chk, and group_member.


utmp
----

* New module.

* Adds stub getutent_r.




0.1.0 (2017-10-15)
==================

ucontext
--------
* new module

* Adds getcontext(), which always sets errno to ENOSYS and returns -1.


resolv
------
* new module

* Adds res_ninit and res_nclose methods which wrap around standard
  res_init and res_close.


string
------
* Adds strtoll_l and strtoull_l 'locale-aware' methods.  Currently, these
  do nothing but call the non-locale-aware versions as musl does not implement
  `LC_NUMERIC`.


malloc
------
* Adds __libc_memalign which is a thin shim to musl's __memalign.

* Adds __libc_malloc, __libc_calloc, __libc_realloc, and __libc_free which are
  used by some system-level software.  These just call directly to musl's free
  and malloc/calloc/realloc.


math
----
* Adds non-prefixed isinf, isinff, isnan, and isnanf, needed since these are
  implemented as macros in musl.


Build system
------------
* A patch from Daniel James of VoidLinux has been applied, which allows use of
  CC instead of hard-coding `gcc`.


Documentation
-------------
* Updates the README.

* Adds contribution guide, a copy of the license, and this changelog.


pthread
-------
* Adds __pthread_register_cancel and __pthread_unregister_cancel stubs, which
  do nothing because they are not relevant to musl's pthread implementation.

* Adds __register_atfork stub.

* Removes pthread_setname_np since musl now provides it.


pwd
---
* new module

* Adds getpwent_r and fgetpwent_r.


sysctl
------
* new module

* Adds sysctl.
