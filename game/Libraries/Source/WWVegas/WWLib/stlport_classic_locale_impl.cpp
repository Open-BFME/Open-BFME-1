// ?bfmeTwoTB@@YAPAXXZ
// cl: /O2 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
// Retail 0x0083B330, 908 bytes: STLport's classic-locale builder. Both matched
// callers (bfmeOnceWE and BfmeThingTB::bfmeGoTB) call it and store the result
// in _Bfme_classic_locale (0x0130BCA0). It placement-constructs the "C"
// _Locale_impl and every standard facet into static storage, one new-expression
// each, so each throwing constructor gets its own unwind state. The storage
// objects have no recovered names and keep their addresses. The body name stays
// the existing address-derived pin.

#include <locale>
#include <new>

namespace _STL
{

class _Locale_impl
{
public:
	virtual ~_Locale_impl();
	virtual void _bfme_incr(void);
	virtual void _bfme_decr(void);

	__forceinline _Locale_impl(const char *name) : m_name(name) {}

	locale::facet **m_facets;
	unsigned int m_bfmeCount;
	string m_name;
};

}

class BfmeChannelPair847EF0
{
public:
	BfmeChannelPair847EF0(void *source);
	char m_bfmeStorage[20];
};

class BfmeChannelPair847F90
{
public:
	BfmeChannelPair847F90(void *source);
	char m_bfmeStorage[20];
};

class BfmeChannelPair848030
{
public:
	BfmeChannelPair848030(void *source);
	char m_bfmeStorage[20];
};

class BfmeChannelPair8480D0
{
public:
	BfmeChannelPair8480D0(void *source);
	char m_bfmeStorage[20];
};

struct BfmeSubE1124
{
	char m_bfmePad[4];
	char m_bfme04;
};

class BfmeE1124
{
public:
	BfmeE1124(BfmeSubE1124 *source);
	char m_bfmeStorage[16];
};

struct BfmeSubF1124
{
	char m_bfmePad[4];
	char m_bfme04;
};

class BfmeF1124
{
public:
	BfmeF1124(BfmeSubF1124 *source);
	char m_bfmeStorage[16];
};

typedef _STL::istreambuf_iterator<char, _STL::char_traits<char> > BfmeNarrowInput;
typedef _STL::ostreambuf_iterator<char, _STL::char_traits<char> > BfmeNarrowOutput;
typedef _STL::istreambuf_iterator<wchar_t, _STL::char_traits<wchar_t> > BfmeWideInput;
typedef _STL::ostreambuf_iterator<wchar_t, _STL::char_traits<wchar_t> > BfmeWideOutput;

extern _STL::_Locale_impl g_classic0130B2A0;
extern _STL::ctype<char> g_classic0130BC78;
extern _STL::collate<char> g_classic0130BC90;
extern _STL::codecvt<char, char, mbstate_t> g_classic0130B7E0;
extern _STL::numpunct<char> g_classic0130B270;
extern _STL::num_get<char, BfmeNarrowInput> g_classic0130B2B8;
extern _STL::num_put<char, BfmeNarrowOutput> g_classic0130B2E8;
extern _STL::time_get<char, BfmeNarrowInput> g_classic0130BA50;
extern _STL::time_put<char, BfmeNarrowOutput> g_classic0130B570;
extern BfmeChannelPair847EF0 g_classic0130BA28;
extern BfmeChannelPair847F90 g_classic0130B538;
extern _STL::money_get<char, BfmeNarrowInput> g_classic0130BA18;
extern _STL::money_put<char, BfmeNarrowOutput> g_classic0130BA40;
extern BfmeE1124 g_classic0130B290;
extern _STL::ctype<wchar_t> g_classic0130B280;
extern _STL::collate<wchar_t> g_classic0130B798;
extern _STL::codecvt<wchar_t, char, mbstate_t> g_classic0130B550;
extern _STL::numpunct<wchar_t> g_classic0130B560;
extern _STL::num_get<wchar_t, BfmeWideInput> g_classic0130B7A8;
extern _STL::num_put<wchar_t, BfmeWideOutput> g_classic0130B2C8;
extern _STL::time_get<wchar_t, BfmeWideInput> g_classic0130B310;
extern _STL::time_put<wchar_t, BfmeWideOutput> g_classic0130B7F0;
extern BfmeF1124 g_classic0130B260;
extern BfmeChannelPair848030 g_classic0130B2F8;
extern BfmeChannelPair8480D0 g_classic0130B7C8;
extern _STL::money_get<wchar_t, BfmeWideInput> g_classic0130B2D8;
extern _STL::money_put<wchar_t, BfmeWideOutput> g_classic0130B7B8;
extern _STL::locale::facet *g_classicFacets012C7388[];
extern unsigned int g_classicFacetCount012C7428;
extern BfmeSubE1124 g_classicMessagesImpl0130BCAC;

void *bfmeTwoTB()
{
	void *buffer = &g_classic0130B2A0;
	_STL::_Locale_impl *classic = new (buffer) _STL::_Locale_impl("C");
	classic->m_bfmeCount = g_classicFacetCount012C7428;
	classic->m_facets = g_classicFacets012C7388;

	new (&g_classic0130BC78) _STL::ctype<char>(0, false, 1);
	new (&g_classic0130BC90) _STL::collate<char>(1);
	new (&g_classic0130B7E0) _STL::codecvt<char, char, mbstate_t>(1);
	new (&g_classic0130B270) _STL::numpunct<char>(1);
	new (&g_classic0130B2B8) _STL::num_get<char, BfmeNarrowInput>(1);
	new (&g_classic0130B2E8) _STL::num_put<char, BfmeNarrowOutput>(1);
	new (&g_classic0130BA50) _STL::time_get<char, BfmeNarrowInput>(1);
	new (&g_classic0130B570) _STL::time_put<char, BfmeNarrowOutput>(1);
	new (&g_classic0130BA28) BfmeChannelPair847EF0(reinterpret_cast<void *>(1));
	new (&g_classic0130B538) BfmeChannelPair847F90(reinterpret_cast<void *>(1));
	new (&g_classic0130BA18) _STL::money_get<char, BfmeNarrowInput>(1);
	new (&g_classic0130BA40) _STL::money_put<char, BfmeNarrowOutput>(1);
	new (&g_classic0130B290) BfmeE1124(&g_classicMessagesImpl0130BCAC);

	new (&g_classic0130B280) _STL::ctype<wchar_t>(1);
	new (&g_classic0130B798) _STL::collate<wchar_t>(1);
	new (&g_classic0130B550) _STL::codecvt<wchar_t, char, mbstate_t>(1);
	new (&g_classic0130B560) _STL::numpunct<wchar_t>(1);
	new (&g_classic0130B7A8) _STL::num_get<wchar_t, BfmeWideInput>(1);
	new (&g_classic0130B2C8) _STL::num_put<wchar_t, BfmeWideOutput>(1);
	new (&g_classic0130B310) _STL::time_get<wchar_t, BfmeWideInput>(1);
	new (&g_classic0130B7F0) _STL::time_put<wchar_t, BfmeWideOutput>(1);
	new (&g_classic0130B260) BfmeF1124(reinterpret_cast<BfmeSubF1124 *>(&g_classicMessagesImpl0130BCAC));
	new (&g_classic0130B2F8) BfmeChannelPair848030(reinterpret_cast<void *>(1));
	new (&g_classic0130B7C8) BfmeChannelPair8480D0(reinterpret_cast<void *>(1));
	new (&g_classic0130B2D8) _STL::money_get<wchar_t, BfmeWideInput>(1);
	new (&g_classic0130B7B8) _STL::money_put<wchar_t, BfmeWideOutput>(1);

	return classic;
}
