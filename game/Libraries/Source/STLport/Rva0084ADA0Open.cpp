// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
#include <fstream>

// Retail 0x0084ADA0: stream buffer at +0xc, _Filebuf_base at +0x54,
// followed by virtual-base ios state and exception-mask handling.
// The character specialization is a layout view, not a proven identity.
struct Rva0084ADA0Owner : _STL::basic_fstream<char, _STL::char_traits<char> >
{
    void rva0084ADA0OpenLog(const char *name, int mode);
};

void Rva0084ADA0Owner::rva0084ADA0OpenLog(const char *name, int mode)
{
    if (!rdbuf()->open(name, (_STL::ios_base::openmode)mode, 0x80))
        setstate(_STL::ios_base::failbit);
}
