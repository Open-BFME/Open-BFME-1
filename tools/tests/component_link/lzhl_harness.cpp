// Test driver for tools/component_link.py lzhl: LZH-Light 1.0 (CompLibSource)
// and EA's NoxCompress wrappers, through the functions retail calls. The tree
// has no public LZHL header, so the prototypes are declared here exactly as
// NoxCompress.cpp declares them; the link proves the names. argv[1] is a
// scratch directory for the CompressFile/DecompressFile pair.
//
// TEST DOUBLES, the only ones: LZHL's new/delete are retail's own operators
// (WWLib/mem_ops.cpp, linked as part of the component), which call through
// two memory-manager pointers the game fills in at run time. Nothing in the
// component defines them, so this driver does, pointing them at malloc/free.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *LZHLCreateCompressor();
unsigned int LZHLCompress(void *, void *, void *, unsigned int);
void LZHLDestroyCompressor(void *);
unsigned int LZHLCompressorCalcMaxBuf(unsigned);
void *LZHLCreateDecompressor();
int LZHLDecompress(void *, unsigned char *, unsigned int *, const unsigned char *, unsigned int *);
void LZHLDestroyDecompressor(void *);
bool CompressMemory(void *, int, void *, int &);
bool DecompressMemory(void *, int, void *, int &);
bool CompressFile(char *, char *);
bool DecompressFile(char *, char *);

typedef void *(__cdecl *GameAllocFn)(size_t, int);
typedef void(__cdecl *GameFreeFn)(void *, int);
static int allocs, frees;
static void *__cdecl test_alloc(size_t n, int) { allocs++; return malloc(n); }
static void __cdecl test_free(void *p, int) { frees++; free(p); }
extern "C" GameAllocFn __gameMemAllocPtr = test_alloc;  // TEST DOUBLE
extern "C" GameFreeFn __gameMemFreePtr = test_free;     // TEST DOUBLE

static int failures;

static void check(bool ok, const char *what)
{
    printf("%s %s\n", ok ? "PASS" : "FAIL", what);
    if (!ok)
        failures++;
}

static void fill_random(unsigned char *p, unsigned int n, unsigned long seed)
{
    for (unsigned int i = 0; i < n; i++) {
        seed = seed * 1103515245UL + 12345UL;
        p[i] = (unsigned char)(seed >> 16);
    }
}

static void fill_text(unsigned char *p, unsigned int n)
{
    static const char words[] = "one does not simply walk into mordor its black gates are guarded ";
    for (unsigned int i = 0; i < n; i++)
        p[i] = words[(i * 5 + i / 61) % (sizeof(words) - 1)];
}

// Compress `n` bytes in blocks of `block` through one compressor, then
// decompress the whole stream with one decompressor, as DecompressMemory does.
static void round_trip(const char *label, const unsigned char *src, unsigned int n, unsigned int block)
{
    char what[160];
    unsigned int cap = LZHLCompressorCalcMaxBuf(n) + 64 * (n / (block ? block : 1) + 1);
    unsigned char *z = (unsigned char *)malloc(cap), *out = (unsigned char *)malloc(n + 16);
    unsigned int zn = 0;
    void *c = LZHLCreateCompressor();
    for (unsigned int at = 0; at < n || (n == 0 && at == 0); at += block) {
        unsigned int len = n - at < block ? n - at : block;
        zn += LZHLCompress(c, z + zn, (void *)(src + at), len);
        if (n == 0)
            break;
    }
    LZHLDestroyCompressor(c);
    sprintf(what, "LZHLCompress %s (%u -> %u, block %u)", label, n, zn, block);
    check(zn <= cap && (n == 0 || zn > 0), what);

    void *d = LZHLCreateDecompressor();
    unsigned int dst = n + 16, srcLeft = zn;
    int ok = 1, calls = 0;
    while (ok && srcLeft > 0 && calls < 100000) {
        ok = LZHLDecompress(d, out + (n + 16 - dst), &dst, z + (zn - srcLeft), &srcLeft);
        calls++;
    }
    LZHLDestroyDecompressor(d);
    // EA's decoder returns FALSE, without writing back the sizes, when the
    // input ends with the end-of-block symbol already in its bit buffer (see
    // end_quirk). The bytes are written either way, and DecompressMemory
    // relies on exactly that: it ignores the result.
    sprintf(what, "LZHLDecompress %s (%d calls, returned %s)", label, calls,
            ok ? "TRUE" : "FALSE on the last block, end symbol buffered");
    check(memcmp(out, src, n) == 0 && (ok ? n + 16 - dst == n : srcLeft > 0), what);
    free(z);
    free(out);
}

static void memory_api(const char *label, const unsigned char *src, int n)
{
    char what[160];
    int zn = LZHLCompressorCalcMaxBuf(n) + 1024, on = n;
    unsigned char *z = (unsigned char *)malloc(zn), *out = (unsigned char *)malloc(n);
    sprintf(what, "CompressMemory %s", label);
    check(CompressMemory((void *)src, n, z, zn) && zn > 0, what);
    sprintf(what, "DecompressMemory %s (%d -> %d)", label, zn, on);
    check(DecompressMemory(z, zn, out, on) && on == n && memcmp(out, src, n) == 0, what);
    free(z);
    free(out);
}

static bool same_file(const char *a, const char *b)
{
    FILE *fa = fopen(a, "rb"), *fb = fopen(b, "rb");
    bool same = fa && fb;
    while (same) {
        int x = fgetc(fa), y = fgetc(fb);
        same = x == y;
        if (x == EOF)
            break;
    }
    if (fa)
        fclose(fa);
    if (fb)
        fclose(fb);
    return same;
}

// Pins retail's decoder behaviour at an exact end of input: 500000 bytes of
// this text compress to a stream whose end symbol lands in the bit buffer, so
// decompress returns FALSE with every byte written; one more input byte lets
// the top-tested loop run once more and it returns TRUE.
static void end_quirk(const unsigned char *text)
{
    const unsigned int n = 500000;
    unsigned int cap = LZHLCompressorCalcMaxBuf(n) + 64;
    unsigned char *z = (unsigned char *)calloc(cap + 1, 1), *out = (unsigned char *)malloc(n + 16);
    void *c = LZHLCreateCompressor();
    unsigned int zn = LZHLCompress(c, z, (void *)text, n);
    LZHLDestroyCompressor(c);
    int result[2];
    bool written[2];
    for (int pad = 0; pad < 2; pad++) {
        memset(out, 0xCC, n + 16);
        void *d = LZHLCreateDecompressor();
        unsigned int dst = n + 16, left = zn + pad;
        result[pad] = LZHLDecompress(d, out, &dst, z, &left);
        LZHLDestroyDecompressor(d);
        written[pad] = memcmp(out, text, n) == 0;
    }
    check(!result[0] && written[0] && result[1] && written[1],
          "EA decoder: FALSE at an exact end with the end symbol buffered, TRUE given one byte more; data intact");
    free(z);
    free(out);
}

int main(int argc, char **argv)
{
    const char *dir = argc > 1 ? argv[1] : ".";
    const unsigned int big = 1024 * 1024;
    unsigned char *random = (unsigned char *)malloc(big), *text = (unsigned char *)malloc(big);
    fill_random(random, big, 12345);
    fill_text(text, big);

    check(LZHLCompressorCalcMaxBuf(1000) > 1000, "LZHLCompressorCalcMaxBuf bounds expansion");
    round_trip("empty", text, 0, 1);
    round_trip("one byte", text, 1, 1);
    round_trip("1 MB text", text, big, big);
    round_trip("1 MB text", text, big, 4096);
    round_trip("1 MB random", random, big, big);
    round_trip("1 MB random", random, big, 65536);

    // Two fresh compressors on the same input produce the same stream.
    {
        unsigned int cap = LZHLCompressorCalcMaxBuf(65536);
        unsigned char *a = (unsigned char *)malloc(cap), *b = (unsigned char *)malloc(cap);
        void *c1 = LZHLCreateCompressor(), *c2 = LZHLCreateCompressor();
        unsigned int na = LZHLCompress(c1, a, text, 65536), nb = LZHLCompress(c2, b, text, 65536);
        LZHLDestroyCompressor(c1);
        LZHLDestroyCompressor(c2);
        check(na == nb && memcmp(a, b, na) == 0, "LZHLCompress is deterministic");
        free(a);
        free(b);
    }

    end_quirk(text);
    memory_api("1 MB text", text, big);
    memory_api("1 MB random", random, big);
    memory_api("5 bytes", (const unsigned char *)"gimli", 5);
    {
        int n = 16;
        unsigned char z[16];
        check(!CompressMemory(text, 3, z, n), "CompressMemory refuses fewer than 4 bytes");
    }

    char in[1024], packed[1024], back[1024];
    sprintf(in, "%s/lzhl.raw", dir);
    sprintf(packed, "%s/lzhl.lzh", dir);
    sprintf(back, "%s/lzhl.back", dir);
    FILE *f = fopen(in, "wb");
    fwrite(text, 1, 700000, f);  // more than one 500000-byte block
    fwrite(random, 1, 300000, f);
    fclose(f);
    check(CompressFile(in, packed), "CompressFile");
    check(DecompressFile(packed, back), "DecompressFile");
    check(same_file(in, back), "file round trip is byte-identical");

    check(allocs > 0 && allocs == frees, "every allocation went through retail's operator new and was freed");
    printf("%s: %d failure(s)\n", failures ? "FAIL" : "PASS", failures);
    return failures ? 1 : 0;
}
