/* Test driver for tools/component_link.py zlib: exercises the zlib 1.1.4
   objects the link census links, through the public API only. No test
   doubles: every name zlib references must come from zlib's own objects or
   the CRT. argv[1] is a scratch directory the script cross-checks against
   Python's independent zlib (text.z/random.z out, py.z in). */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "zlib.h"

static int failures;

static void check(int ok, const char *what)
{
    printf("%s %s\n", ok ? "PASS" : "FAIL", what);
    if (!ok)
        failures++;
}

static unsigned long lcg = 12345;

static void fill_random(unsigned char *p, unsigned long n)
{
    unsigned long i;
    for (i = 0; i < n; i++) {
        lcg = lcg * 1103515245UL + 12345UL;
        p[i] = (unsigned char)(lcg >> 16);
    }
}

static void fill_text(unsigned char *p, unsigned long n)
{
    static const char words[] = "the ring of power was forged in mount doom by sauron ";
    unsigned long i;
    for (i = 0; i < n; i++)
        p[i] = words[(i * 7 + i / 53) % (sizeof(words) - 1)];
}

static int write_file(const char *dir, const char *name, const unsigned char *p, unsigned long n)
{
    char path[1024];
    FILE *f;
    sprintf(path, "%s/%s", dir, name);
    f = fopen(path, "wb");
    if (!f)
        return 0;
    fwrite(p, 1, n, f);
    fclose(f);
    return 1;
}

static unsigned char *read_file(const char *dir, const char *name, unsigned long *n)
{
    char path[1024];
    FILE *f;
    unsigned char *p;
    sprintf(path, "%s/%s", dir, name);
    f = fopen(path, "rb");
    if (!f)
        return 0;
    fseek(f, 0, SEEK_END);
    *n = ftell(f);
    fseek(f, 0, SEEK_SET);
    p = (unsigned char *)malloc(*n ? *n : 1);
    fread(p, 1, *n, f);
    fclose(f);
    return p;
}

/* compress2 then uncompress one buffer at one level. */
static void round_trip(const char *label, const unsigned char *src, unsigned long n, int level,
                       const char *dir, const char *save)
{
    char what[128];
    uLongf zlen = n + n / 1000 + 12 + 1, olen = n + 1;
    unsigned char *z = (unsigned char *)malloc(zlen), *out = (unsigned char *)malloc(n + 1);
    int rc = compress2(z, &zlen, src, n, level);
    sprintf(what, "compress2 %s level %d (%lu -> %lu)", label, level, n, (unsigned long)zlen);
    check(rc == Z_OK, what);
    rc = uncompress(out, &olen, z, zlen);
    sprintf(what, "uncompress %s level %d", label, level);
    check(rc == Z_OK && olen == n && memcmp(out, src, n) == 0, what);
    if (save)
        check(write_file(dir, save, z, zlen), "write compressed stream for Python cross-check");
    free(z);
    free(out);
}

/* deflate/inflate through tiny input and output windows, so every
   need-more-input and need-more-output path runs. */
static void streaming(const unsigned char *src, unsigned long n, int level, int strategy)
{
    char what[128];
    z_stream d, i;
    unsigned long cap = n + n / 1000 + 64, got = 0;
    unsigned char *z = (unsigned char *)malloc(cap), *out = (unsigned char *)malloc(n + 1);
    int rc;
    memset(&d, 0, sizeof d);
    rc = deflateInit2(&d, level, Z_DEFLATED, MAX_WBITS, 8, strategy);
    d.next_out = z;
    while (rc == Z_OK) {
        unsigned long left = n - d.total_in;
        d.next_in = (Bytef *)src + d.total_in;
        d.avail_in = left < 997 ? (uInt)left : 997;
        d.avail_out = (uInt)(cap - d.total_out < 331 ? cap - d.total_out : 331);
        rc = deflate(&d, left <= 997 ? Z_FINISH : Z_NO_FLUSH);
    }
    sprintf(what, "deflate streaming level %d strategy %d", level, strategy);
    check(rc == Z_STREAM_END && deflateEnd(&d) == Z_OK, what);

    memset(&i, 0, sizeof i);
    rc = inflateInit(&i);
    i.next_in = z;
    i.next_out = out;
    while (rc == Z_OK) {
        i.avail_in = (uInt)(d.total_out - i.total_in < 101 ? d.total_out - i.total_in : 101);
        i.avail_out = (uInt)(n + 1 - i.total_out < 257 ? n + 1 - i.total_out : 257);
        rc = inflate(&i, Z_NO_FLUSH);
    }
    got = i.total_out;
    sprintf(what, "inflate streaming level %d strategy %d", level, strategy);
    check(rc == Z_STREAM_END && got == n && memcmp(out, src, n) == 0 && inflateEnd(&i) == Z_OK, what);
    free(z);
    free(out);
}

static void dictionary(void)
{
    static const char dict[] = "mount doom sauron forged";
    static const char text[] = "sauron forged the ring in mount doom; sauron forged it";
    unsigned char z[256], out[256];
    z_stream d, i;
    int rc;
    memset(&d, 0, sizeof d);
    deflateInit(&d, 9);
    check(deflateSetDictionary(&d, (const Bytef *)dict, sizeof dict - 1) == Z_OK, "deflateSetDictionary");
    d.next_in = (Bytef *)text;
    d.avail_in = sizeof text;
    d.next_out = z;
    d.avail_out = sizeof z;
    check(deflate(&d, Z_FINISH) == Z_STREAM_END, "deflate with dictionary");
    deflateEnd(&d);

    memset(&i, 0, sizeof i);
    inflateInit(&i);
    i.next_in = z;
    i.avail_in = d.total_out;
    i.next_out = out;
    i.avail_out = sizeof out;
    rc = inflate(&i, Z_NO_FLUSH);
    check(rc == Z_NEED_DICT && i.adler == adler32(1, (const Bytef *)dict, sizeof dict - 1),
          "inflate asks for the dictionary by its adler32");
    check(inflateSetDictionary(&i, (const Bytef *)dict, sizeof dict - 1) == Z_OK, "inflateSetDictionary");
    rc = inflate(&i, Z_FINISH);
    check(rc == Z_STREAM_END && i.total_out == sizeof text && memcmp(out, text, sizeof text) == 0,
          "inflate with dictionary");
    inflateEnd(&i);
}

static void copy_params_reset(const unsigned char *src)
{
    unsigned char z1[4096], z2[4096], out[4096];
    uLongf olen;
    z_stream a, b;
    memset(&a, 0, sizeof a);
    deflateInit(&a, 1);
    a.next_in = (Bytef *)src;
    a.avail_in = 1024;
    a.next_out = z1;
    a.avail_out = sizeof z1;
    deflate(&a, Z_NO_FLUSH);
    check(deflateCopy(&b, &a) == Z_OK, "deflateCopy");
    memcpy(z2, z1, a.total_out);
    b.next_out = z2 + a.total_out;
    b.avail_out = sizeof z2 - a.total_out;
    check(deflateParams(&b, 9, Z_DEFAULT_STRATEGY) == Z_OK, "deflateParams");
    b.next_in = (Bytef *)src + 1024;
    b.avail_in = 1024;
    check(deflate(&b, Z_FINISH) == Z_STREAM_END, "deflate on the copied stream");
    olen = sizeof out;
    check(uncompress(out, &olen, z2, b.total_out) == Z_OK && olen == 2048 && memcmp(out, src, 2048) == 0,
          "copied stream inflates to both halves");
    check(deflateReset(&a) == Z_OK && a.total_in == 0 && a.total_out == 0, "deflateReset");
    deflateEnd(&a);
    deflateEnd(&b);
}

static void sync(const unsigned char *src)
{
    unsigned char z[8192], out[4096];
    z_stream d, i;
    int rc;
    memset(&d, 0, sizeof d);
    deflateInit(&d, 6);
    d.next_in = (Bytef *)src;
    d.avail_in = 2048;
    d.next_out = z;
    d.avail_out = sizeof z;
    deflate(&d, Z_FULL_FLUSH);
    d.avail_in = 2048;
    deflate(&d, Z_FINISH);
    deflateEnd(&d);

    memset(&i, 0, sizeof i);
    inflateInit(&i);
    i.next_in = z;
    i.avail_in = 40; /* part of the first block, then garbage to resync over */
    i.next_out = out;
    i.avail_out = sizeof out;
    inflate(&i, Z_SYNC_FLUSH);
    z[40] ^= 0xFF;
    i.avail_in = d.total_out - 40;
    rc = inflateSync(&i);
    check(rc == Z_OK, "inflateSync finds the full-flush point");
    check(inflateReset(&i) == Z_OK, "inflateReset");
    inflateEnd(&i);
}

int main(int argc, char **argv)
{
    static const unsigned char hello_z[] = {0x78, 0x9c, 0xcb, 0x48, 0xcd, 0xc9, 0xc9, 0x07, 0x00,
                                            0x06, 0x2c, 0x02, 0x15};
    const char *dir = argc > 1 ? argv[1] : ".";
    const unsigned long big = 1024UL * 1024UL;
    unsigned char *random = (unsigned char *)malloc(big), *text = (unsigned char *)malloc(big);
    unsigned char z[64], *py, *pyraw, *out;
    uLongf zlen = sizeof z, n, rawn, olen;
    int level;

    fill_random(random, big);
    fill_text(text, big);

    check(strcmp(zlibVersion(), "1.1.4") == 0, "zlibVersion is 1.1.4");
    check(strcmp(zError(Z_DATA_ERROR), "data error") == 0, "zError(Z_DATA_ERROR)");
    check(adler32(0, 0, 0) == 1, "adler32 initial value");
    check(adler32(1, (const Bytef *)"", 0) == 1, "adler32 of empty");
    check(adler32(1, (const Bytef *)"abc", 3) == 0x024d0127UL, "adler32 abc");
    check(adler32(1, (const Bytef *)"Wikipedia", 9) == 0x11E60398UL, "adler32 Wikipedia");
    check(adler32(1, (const Bytef *)"The quick brown fox jumps over the lazy dog", 43) == 0x5BDC0FDAUL,
          "adler32 quick brown fox");
    check(adler32(1, random, big) == adler32(adler32(1, random, 5553), random + 5553, big - 5553),
          "adler32 is chainable over 1 MB");

    check(compress(z, &zlen, (const Bytef *)"hello", 5) == Z_OK && zlen == sizeof hello_z &&
              memcmp(z, hello_z, sizeof hello_z) == 0,
          "compress(\"hello\") is the reference zlib stream 78 9c cb 48 ...");

    round_trip("empty", text, 0, Z_DEFAULT_COMPRESSION, dir, 0);
    round_trip("one byte", text, 1, Z_DEFAULT_COMPRESSION, dir, 0);
    for (level = 0; level <= 9; level += 3)
        round_trip("1 MB text", text, big, level, dir, level == 9 ? "text.z" : 0);
    round_trip("1 MB random", random, big, 1, dir, 0);
    round_trip("1 MB random", random, big, 6, dir, "random.z");
    check(write_file(dir, "text.raw", text, big) && write_file(dir, "random.raw", random, big),
          "write raw buffers for Python cross-check");

    streaming(text, 300000, 6, Z_DEFAULT_STRATEGY);
    streaming(text, 300000, 9, Z_FILTERED);
    streaming(random, 300000, 1, Z_HUFFMAN_ONLY);
    streaming(random, 70000, 0, Z_DEFAULT_STRATEGY);
    dictionary();
    copy_params_reset(text);
    sync(random);

    py = read_file(dir, "py.z", &n);
    pyraw = read_file(dir, "py.raw", &rawn);
    check(py && pyraw, "read Python's stream");
    if (py && pyraw) {
        out = (unsigned char *)malloc(rawn + 1);
        olen = rawn + 1;
        check(uncompress(out, &olen, py, n) == Z_OK && olen == rawn && memcmp(out, pyraw, rawn) == 0,
              "uncompress a stream Python's zlib wrote");
        py[n / 2] ^= 0x55;
        olen = rawn + 1;
        check(uncompress(out, &olen, py, n) != Z_OK, "a corrupted stream is refused");
    }

    printf("%s: %d failure(s)\n", failures ? "FAIL" : "PASS", failures);
    return failures ? 1 : 0;
}
