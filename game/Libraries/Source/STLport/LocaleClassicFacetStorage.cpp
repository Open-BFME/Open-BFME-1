// cl: /O2 /EHsc /MD /D_STLP_USE_STATIC_LIB
// STLport 4.5.3 classic-locale facet storage. Retail VA 0x0130B550 is the wide
// codecvt facet buffer the classic-locale builder
// (game/Libraries/Source/WWVegas/WWLib/stlport_classic_locale_impl.cpp)
// placement-constructs at its line 178: new (&g_classic0130B550)
// _STL::codecvt<wchar_t, char, mbstate_t>(1). That builder TU only declares the
// buffer, so this data TU owns it, and it owns it as raw storage: retail reads
// 16 zero bytes at 0x0130B550 in .data, and the buffer is inert until the
// builder constructs the facet into it.
//
// Extent: the neighbouring named objects bound it exactly. BfmeChannelPair847F90
// (the buffer at 0x0130B538) ends at 0x0130B550, and g_classic0130B560
// (_STL::numpunct<wchar_t>) begins at 0x0130B560, so 0x10 bytes is the whole
// allocation with no gap.
//
// STLport's own codecvt<wchar_t, char, mbstate_t> cannot back this definition:
// its destructor is protected (input/vendor/stlport/stl/_codecvt.h:142, C2248 on
// a namespace-scope object), so the facet type is shadowed here as POD storage.
// The TU deliberately includes no STLport header: a codecvt template shadow would
// collide with <locale>'s declaration in any TU that pulls stl/_codecvt.h. The
// builtin spelling reproduces the same mangled type encoding the builder's
// extern declaration emits, because STLport's wchar_t is an unsigned short and
// its mbstate_t is an int here (unsigned short = G, char = D, int = H).
namespace _STL {
template <class _InternT, class _ExternT, class _StateT>
class codecvt
{
public:
	char m_bfmeStorage[0x10];
};
}

// Matched data owner: ?g_classic0130B550@@3V?$codecvt@GDH@_STL@@A at VA 0x0130B550.
_STL::codecvt<unsigned short, char, int> g_classic0130B550;
