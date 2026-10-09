// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
#include <fstream>

// Retail RVA 0x0084AF80, 81 bytes, thiscall with two stack arguments and ret 8.
// The body calls the stream buffer's open(name, mode, 0x80), and on failure it
// sets failbit through the virtual-base ios state, the same tail as 0x0084ADA0.
// The stream buffer sits at +0xc and _Filebuf_base at +0x30 (lea edi,[esi+0xc]
// and lea ecx,[edi+0x24]). That pair is exact only with a wide-character owner,
// as probe.py shows, so the owner is a layout view. No caller names the class,
// so the name keeps the address.
struct Rva0084AF80 : _STL::basic_fstream<wchar_t, _STL::char_traits<wchar_t> >
{
    void open(const char *name, int mode);
};

void Rva0084AF80::open(const char *name, int mode)
{
    if (!rdbuf()->open(name, (_STL::ios_base::openmode)mode, 0x80))
        setstate(_STL::ios_base::failbit);
}
