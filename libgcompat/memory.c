#include <wchar.h>
#include <string.h>

wchar_t *
__wmemcpy_chk (wchar_t *s1, const wchar_t *s2, size_t n, size_t ns1)
{
  return (wchar_t *) mempcpy ((void *) s1, (void *) s2, n * sizeof (wchar_t));
}

wchar_t *
__wmemmove_chk (wchar_t *s1, const wchar_t *s2, size_t n, size_t ns1)
{
  return (wchar_t *) memmove ((void *) s1, (void *) s2, n * sizeof (wchar_t));
}
