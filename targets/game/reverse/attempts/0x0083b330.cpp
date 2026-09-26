// ?bfmeTwoTB@@YAPAXXZ
// partial score=0.21585903083700442 date=2026-09-25
// cl: /O2 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME5: classic STLport locale initializer at retail 0x0083B330.

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

	__forceinline _Locale_impl(const char *name) : m_bfmeName(name) {}

	locale::facet **m_bfmeFacets;
	unsigned int m_bfmeCount;
	string m_bfmeName;
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

static _STL::locale::facet **bfmeClassicFacets()
{
	return reinterpret_cast<_STL::locale::facet **>(0x012C7388);
}

static unsigned int bfmeClassicFacetCount()
{
	return *reinterpret_cast<unsigned int *>(0x012C7428);
}

void *bfmeTwoTB()
{
	_STL::_Locale_impl *impl = new (reinterpret_cast<void *>(0x0130B2A0)) _STL::_Locale_impl("C");
	impl->m_bfmeCount = bfmeClassicFacetCount();
	impl->m_bfmeFacets = bfmeClassicFacets();

	(reinterpret_cast<_STL::ctype<char> *>(0x0130BC78))->_STL::ctype<char>::ctype(0, false, 1);
	(reinterpret_cast<_STL::collate<char> *>(0x0130BC90))->_STL::collate<char>::collate(1);
	(reinterpret_cast<_STL::codecvt<char, char, mbstate_t> *>(0x0130B7E0))->_STL::codecvt<char, char, mbstate_t>::codecvt(1);

	(reinterpret_cast<_STL::time_get<char, BfmeNarrowInput> *>(0x0130BA50))->_STL::time_get<char, BfmeNarrowInput>::time_get(1);
	(reinterpret_cast<_STL::time_put<char, BfmeNarrowOutput> *>(0x0130B570))->_STL::time_put<char, BfmeNarrowOutput>::time_put(1);

	(reinterpret_cast<BfmeChannelPair847EF0 *>(0x0130BA28))->BfmeChannelPair847EF0::BfmeChannelPair847EF0(reinterpret_cast<void *>(1));
	(reinterpret_cast<BfmeChannelPair847F90 *>(0x0130B538))->BfmeChannelPair847F90::BfmeChannelPair847F90(reinterpret_cast<void *>(1));

	(reinterpret_cast<_STL::numpunct<char> *>(0x0130B270))->_STL::numpunct<char>::numpunct(1);
	(reinterpret_cast<_STL::money_get<char, BfmeNarrowInput> *>(0x0130BA18))->_STL::money_get<char, BfmeNarrowInput>::money_get(1);
	(reinterpret_cast<_STL::money_put<char, BfmeNarrowOutput> *>(0x0130BA40))->_STL::money_put<char, BfmeNarrowOutput>::money_put(1);
	(reinterpret_cast<BfmeE1124 *>(0x0130B290))->BfmeE1124::BfmeE1124(reinterpret_cast<BfmeSubE1124 *>(0x0130BCAC));

	(reinterpret_cast<_STL::collate<wchar_t> *>(0x0130B798))->_STL::collate<wchar_t>::collate(1);
	(reinterpret_cast<_STL::ctype<wchar_t> *>(0x0130B280))->_STL::ctype<wchar_t>::ctype(1);
	(reinterpret_cast<_STL::codecvt<wchar_t, char, mbstate_t> *>(0x0130B550))->_STL::codecvt<wchar_t, char, mbstate_t>::codecvt(1);
	(reinterpret_cast<BfmeChannelPair848030 *>(0x0130B2F8))->BfmeChannelPair848030::BfmeChannelPair848030(reinterpret_cast<void *>(1));
	(reinterpret_cast<BfmeChannelPair8480D0 *>(0x0130B7C8))->BfmeChannelPair8480D0::BfmeChannelPair8480D0(reinterpret_cast<void *>(1));
	(reinterpret_cast<_STL::numpunct<wchar_t> *>(0x0130B560))->_STL::numpunct<wchar_t>::numpunct(1);
	(reinterpret_cast<_STL::num_get<wchar_t, BfmeWideInput> *>(0x0130B7A8))->_STL::num_get<wchar_t, BfmeWideInput>::num_get(1);
	(reinterpret_cast<_STL::num_put<wchar_t, BfmeWideOutput> *>(0x0130B2C8))->_STL::num_put<wchar_t, BfmeWideOutput>::num_put(1);

	(reinterpret_cast<_STL::time_get<wchar_t, BfmeWideInput> *>(0x0130B310))->_STL::time_get<wchar_t, BfmeWideInput>::time_get(1);
	(reinterpret_cast<_STL::time_put<wchar_t, BfmeWideOutput> *>(0x0130B7F0))->_STL::time_put<wchar_t, BfmeWideOutput>::time_put(1);

	(reinterpret_cast<BfmeF1124 *>(0x0130B260))->BfmeF1124::BfmeF1124(reinterpret_cast<BfmeSubF1124 *>(0x0130BCAC));
	(reinterpret_cast<BfmeChannelPair848030 *>(0x0130B2F8))->BfmeChannelPair848030::BfmeChannelPair848030(reinterpret_cast<void *>(1));
	(reinterpret_cast<BfmeChannelPair8480D0 *>(0x0130B7C8))->BfmeChannelPair8480D0::BfmeChannelPair8480D0(reinterpret_cast<void *>(1));
	*reinterpret_cast<unsigned int *>(0x0130B2DC) = 1;
	*reinterpret_cast<unsigned char *>(0x0130B2E0) = 0;
	*reinterpret_cast<unsigned int *>(0x0130B2D8) = 0x0112E9D8;
	*reinterpret_cast<unsigned int *>(0x0130B7BC) = 1;
	*reinterpret_cast<unsigned char *>(0x0130B7C0) = 0;
	*reinterpret_cast<unsigned int *>(0x0130B7B8) = 0x0112E9E8;

	return reinterpret_cast<void *>(0x0130B2A0);
}
