// _REF_encode@16
// partial score=0.99 date=2026-09-03
// cl: /DNDEBUG
// partial stash for REF_encode @ 0x0081F420 (108B)
// Size exact; sole residue is adjacent swap of `mov edx,ecx` vs `mov byte [eax+1],0xfb`.
// Identity: _REF_encode@16; callee refcompress 4-arg (maxback DCE'd); fb6 header.
// Volatile stores fix 0x90/0x10 scheduling; 4-arg cast matches call site.

#include "codex.h"
#include "refcodex.h"

// Declared only for the stash compile shape; real body lives in refencode.cpp.
static int refcompress(unsigned char *from, int len, unsigned char *dest, int maxback, int quick);

int GCALL REF_encode(void *compresseddata, const void *source, int sourcesize, int *opts)
{
    unsigned char *d = (unsigned char *)compresseddata;
    volatile unsigned char *vd = d;
    unsigned int v = (unsigned int)sourcesize;
    unsigned int t;
    int hlen;
    (void)opts;

    vd[1] = (unsigned char)0xfb;
    if (sourcesize > 0xffffff)
    {
        t = v >> 24;
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
        t = v >> 16;
        vd[0] = (unsigned char)0x10;
        vd[2] = (unsigned char)t;
        t = v >> 8;
        vd[3] = (unsigned char)t;
        vd[4] = (unsigned char)v;
        hlen = 5;
    }
    {
        typedef int (__cdecl *RefCompressQuick)(unsigned char *, int, unsigned char *, int);
        return hlen + ((RefCompressQuick)refcompress)(
            (unsigned char *)source, sourcesize, d + hlen, 0);
    }
}
