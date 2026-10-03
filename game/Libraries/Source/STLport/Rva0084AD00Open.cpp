// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// Opaque STLport file-stream `open(name, mode)` members at 0x0084AD00
// (84 B, narrow ofstream), 0x0084AE40 (84 B, wide ifstream) and 0x0084AEE0
// (84 B, wide ofstream). Each body pushes the retail default protection
// 0x80, ORs the direction bit the owner already implies (in=8 for the
// ifstream, out=0x10 for the ofstreams), opens the stream buffer through
// _Filebuf_base::_M_open(name, mode, 0x80) and runs the shared failbit tail
// (`neg al / sbb eax,eax / test edi,eax / jne`, then the locator-driven
// flag update ending in the `process` tail call at 0x0083E8F0).
//
// The direction bit is witnessed by `probe.py --shape`: the 0x10 spelling
// is EXACT at 0x0084AD00 and 0x0084AEE0, the 8 spelling is EXACT at
// 0x0084AE40, and each is off by exactly that `or` byte at the other two.
// The owner width is witnessed the same way: the edi/ecx pair
// (`lea edi,[esi+4] / lea ecx,[edi+0x54]` narrow, `lea edi,[esi+8] /
// `lea ecx,[edi+0x24]` wide) is EXACT only with the matching CharT, off
// by exactly those two bytes otherwise.
//
// IDENTITY IS NOT RECOVERED beyond the stream family: no caller, string or
// vtable names the holder, so every class name is derived from its own
// address. The layout is the STLport file-stream one (virtual-base
// locator at +0, sub-object at +4/+8, filebuf with _M_base at +0x54/+0x24
// past it); `char`/`unsigned short` are layout views here, since the body
// only calls the non-template _M_open and the `process` tail.

// Use the internal class header directly: the public wrapper adds a TU-local
// _Loc_init static even though these matched methods only need the stream
// declarations.  Its ctor/dtor have no linked provider in this build.
#include <stl/_fstream.h>

struct Rva0084AD00 : _STL::basic_ofstream<char, _STL::char_traits<char> >
{
    void open(const char *name, _STL::ios_base::openmode mode);
};

void Rva0084AD00::open(const char *name, _STL::ios_base::openmode mode)
{
    if (!rdbuf()->open(name, mode | 0x10, 0x80))
        setstate(0x04);
}

struct Rva0084AE40 : _STL::basic_ifstream<unsigned short, _STL::char_traits<unsigned short> >
{
    void open(const char *name, _STL::ios_base::openmode mode);
};

void Rva0084AE40::open(const char *name, _STL::ios_base::openmode mode)
{
    if (!rdbuf()->open(name, mode | 0x08, 0x80))
        setstate(0x04);
}

struct Rva0084AEE0 : _STL::basic_ofstream<unsigned short, _STL::char_traits<unsigned short> >
{
    void open(const char *name, _STL::ios_base::openmode mode);
};

void Rva0084AEE0::open(const char *name, _STL::ios_base::openmode mode)
{
    if (!rdbuf()->open(name, mode | 0x10, 0x80))
        setstate(0x04);
}
