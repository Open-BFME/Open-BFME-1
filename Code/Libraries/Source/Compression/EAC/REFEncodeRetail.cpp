// cl: /DNDEBUG
// _REF_encode@16
// Clean reconstruction of the retail fb6 encoder wrapper at RVA 0x0081F420.

#include "codex.h"
#include "refcodex.h"

int refcompress(unsigned char *from, int len, unsigned char *dest, int maxback, int quick);

int GCALL REF_encode(void *compresseddata, const void *source, int sourcesize, int *opts)
{
    unsigned int v = (unsigned int)sourcesize;
    unsigned char *d = (unsigned char *)compresseddata;
    unsigned int t = v;
    volatile unsigned char *vd = d;
    int hlen;
    (void)opts;

    if (sourcesize > 0xffffff)
    {
        d[1] = (unsigned char)0xfb;
        t >>= 24;
        vd[0] = (unsigned char)0x90;
        vd[2] = (unsigned char)t;
        t = v >> 16;
        vd[3] = (unsigned char)t;
        t = v >> 8;
        vd[4] = (unsigned char)t;
        vd[5] = (unsigned char)v;
        hlen = 6;
    }
    else
    {
        d[1] = (unsigned char)0xfb;
        t = v >> 16;
        vd[0] = (unsigned char)0x10;
        vd[2] = (unsigned char)t;
        t = v >> 8;
        vd[3] = (unsigned char)t;
        vd[4] = (unsigned char)v;
        hlen = 5;
    }

    typedef int (__cdecl *RefCompressQuick)(unsigned char *, int, unsigned char *, int);
    return hlen + ((RefCompressQuick)refcompress)(
        (unsigned char *)source, sourcesize, d + hlen, 0);
}
