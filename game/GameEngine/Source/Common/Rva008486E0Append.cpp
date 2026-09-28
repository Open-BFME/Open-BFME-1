// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// Opaque wide-string push-back wrapper at 0x008486E0 (26 B). The body reads
// one incoming word pointer, zero-extends its first word, and forwards it
// as the character argument of the wide basic_string push_back at
// 0x00839530 (still a gen-tgrid dump; emitted by the vendored explicit
// instantiation here). `mov eax,esi` at the end returns the holder, not
// the string: the probe returning `m_s` instead misses by exactly that
// byte.
//
// IDENTITY IS NOT RECOVERED: no caller, string or vtable names the holder,
// so the class name is derived from its own address.

#include <string>

struct Rva008486E0
{
    _STL::basic_string<unsigned short, _STL::char_traits<unsigned short>,
                       _STL::allocator<unsigned short> > *m_s;
    Rva008486E0 *add(const unsigned short *p);
};

// ?add@Rva008486E0@@QAEPAU1@PBG@Z
Rva008486E0 *Rva008486E0::add(const unsigned short *p)
{
    unsigned short ch = *p;
    m_s->push_back(ch);
    return this;
}
