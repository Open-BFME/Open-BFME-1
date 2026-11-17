// cl: /O2 /EHsc /MD /D__BUILDING_STLPORT
// stlport
#include <string>
#include <stl/_locale.h>
// Only locale declarations are needed; <locale> also instantiates unrelated
// stream facets against the library-internal locale constructors below.
#include <clocale>

// _STL::locale::global, STLport 4.6 src/locale_impl.cpp, retail 0x008366E0
// (362 bytes; linked but uncalled).  Built as STLport's own library source:
// __BUILDING_STLPORT exposes the node allocator, so the first temporary
// string's release inlines the locked free-list push while the second calls
// the out-of-line destructor, as in retail.  The same TU sees the inline
// default/copy constructors and destructor that retail expands here.

class Gen_00C70CC0Target;
// Retail 0x0130BCB4: STLport's "*" nameless-locale string, recorded under
// this opaque name (C6D8B0 constructs it, C70CC0 destroys it).
extern Gen_00C70CC0Target TheBfmeObject_00C70CC0;

namespace _STL {

class _Locale_impl
{
public:
	virtual void _bfme_slot0();
	virtual void incr();
	virtual void decr();
};

// The global locale implementation and the spin lock that guards it.
extern _Locale_impl *_Bfme_classic_locale;
extern _STLP_mutex g_Va0130BCA4;

static _Locale_impl *_bfme_acquire(_Locale_impl *impl)
{
	impl->incr();
	return impl;
}

inline locale::locale() : _M_impl(0)
{
	_M_impl = _bfme_acquire(_Bfme_classic_locale);
}

// Same statement order as retail's copy constructor (0x00832150, 32 bytes):
// the exported COMDAT this TU emits must be byte-identical to it.
inline locale::locale(const locale &L) : _M_impl(0)
{
	_Locale_impl *impl = L._M_impl;
	impl->incr();
	_M_impl = impl;
}

inline locale::~locale()
{
	_M_impl->decr();
}

// ?global@locale@_STL@@SA?AV12@ABV12@@Z
locale _STLP_CALL locale::global(const locale &L)
{
	locale old;

	L._M_impl->incr();
	{
		_STLP_auto_lock lock(g_Va0130BCA4);
		_Bfme_classic_locale->decr();
		_Bfme_classic_locale = L._M_impl;
	}

	if (L.name() != reinterpret_cast<const string &>(TheBfmeObject_00C70CC0))
		setlocale(LC_ALL, L.name().c_str());

	return old;
}

} // namespace _STL
