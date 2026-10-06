// cl: /O2 /Ob0

// STLport 4.5.3 locale copy constructor, retail 0x00832150 (src/locale.cpp):
// clear _M_impl, take a reference on the source's implementation through its
// second virtual slot, then store it.  The callers are the locale-returning
// imbue/pubimbue/getloc bodies (basic_ios<char>::imbue 0x0053F690,
// ios_base::imbue 0x0083EC50, both basic_streambuf pubimbue and getloc), which
// return their locale by copy.  Only the implementation's vtable layout is
// declared here, as game/stlport/LocaleImplDeletingDestructor.cpp gives it
// (RTTI vtable 0x0112EB34): its destructor, then the reference increment.

namespace _STL
{

class _Locale_impl
{
public:
	virtual ~_Locale_impl();
	virtual void incrementReference() = 0;
};

class locale
{
public:
	locale(const locale &L);

private:
	_Locale_impl *_M_impl;
};

locale::locale(const locale &L) : _M_impl(0)
{
	_Locale_impl *impl = L._M_impl;
	impl->incrementReference();
	_M_impl = impl;
}

}
