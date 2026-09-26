// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: _STL::locale::locale(), retail 0x00832120, 30 bytes. The body
// carried only a machine byte-dump row; targets/game/reverse/reloc_names.csv holds the name
// with identity=real.
//
// It stores a null over the one member, loads the classic-locale impl from the
// global at 0x0130BCA0, calls virtual slot 1 on it -- the reference count that
// STLport takes before handing the impl out -- and only then writes it into the
// member. The null store is separate from the final store, so the member is
// assigned twice rather than initialised once.
//
// The acquire step is a helper that returns the pointer rather than a bare
// call. Written as a call followed by a store, MSVC loads the global straight
// into the callee-saved register and pushes it before the load; retail loads it
// into ecx, uses ecx for the vtable fetch, and only then saves a copy -- which
// is the allocation you get when the pointer is a return value that has to
// survive the call. Same thirty bytes either way, different order.

namespace _STL
{

class _Locale_impl
{
public:
	virtual void _bfme_slot0(void) = 0;
	virtual void _bfme_incr(void) = 0;			// vtable slot 1

};

extern _Locale_impl *_Bfme_classic_locale;		// 0x0130BCA0 (pinned)

class locale
{
public:
	locale(void);

private:
	_Locale_impl *_M_impl;
};

static _Locale_impl *_bfme_acquire(_Locale_impl *impl)
{
	impl->_bfme_incr();
	return impl;
}

// ??0locale@_STL@@QAE@XZ
locale::locale(void)
{
	_M_impl = 0;
	_M_impl = _bfme_acquire(_Bfme_classic_locale);
}

}
