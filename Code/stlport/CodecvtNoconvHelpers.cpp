// cl: /EHsc
// stlport

#include <algorithm>

typedef int T2MbState;

#define BFME_NOCONV_CODECVT(CLASS_NAME)                                  \
    struct CLASS_NAME                                                    \
    {                                                                    \
        int unshift(T2MbState *, char *, char *, char **);               \
        int out(T2MbState *, const char *, const char *,                 \
            const char **, char *, char *, char **);                     \
        int length(T2MbState *, const char *, const char *,              \
            unsigned int);                                               \
    };                                                                   \
    int CLASS_NAME::unshift(T2MbState *, char *to, char *,               \
        char **to_next) { *to_next = to; return 3; }                     \
    int CLASS_NAME::out(T2MbState *, const char *from, const char *,     \
        const char **from_next, char *to, char *, char **to_next)        \
        { *from_next = from; *to_next = to; return 3; }                  \
    int CLASS_NAME::length(T2MbState *, const char *from,                \
        const char *from_end, unsigned int max)                          \
        { const unsigned int avail = (unsigned int)(from_end - from);    \
          return (int)(_STL::min)(avail, max); }

BFME_NOCONV_CODECVT(T2NoconvCodecvt)
BFME_NOCONV_CODECVT(T2NoconvCodecvtWide)

unsigned int __stdcall t2_hash_narrow_range(const char *first,
                                               const char *last)
{
    unsigned int h = 0;
    while (first < last)
    {
        h = h * 5 + *first;
        ++first;
    }
    return h;
}

unsigned int __stdcall t2_hash_wide_range(const unsigned short *first,
                                             const unsigned short *last)
{
    unsigned int h = 0;
    while (first < last)
    {
        h = h * 5 + *first;
        ++first;
    }
    return h;
}
