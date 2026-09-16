// cl: /O2 /EHsc /MD /D_STLP_USE_STATIC_LIB
// STLport 4.5.3

// The vtable at VA 0x0112FB8C carries an RTTI complete object locator whose
// type descriptor spells `.?AV?$messages@D@_STL@@`, and 0x0112FBB8 spells
// `.?AV?$messages@G@_STL@@`.  vendor/stlport/stl/_messages_facets.h declares
// the protected virtuals of both specializations as the destructor, do_open,
// do_get and do_close in that order, so slot 1 of each table is do_open.
// Both bodies load the owned _Messages from offset 0x0C and tail-jump to its
// first virtual, which is _Messages::do_open at 0x00848AD0.

typedef unsigned short wchar_t;

namespace _STL
{

template <class CharT> class char_traits;
template <class T> class allocator;
template <class CharT, class Traits, class Alloc> class basic_string;

typedef basic_string<char, char_traits<char>, allocator<char> > string;

class locale
{
public:
	class facet
	{
	protected:
		virtual ~facet();
		int _M_ref_count;
		bool _M_delete;
	};
};

class _Messages
{
public:
	virtual int do_open(const string &fn, const locale &loc) const;
	virtual void *do_get_c() const;
	virtual void *do_get_w() const;
	virtual void do_close(int c) const;
};

class messages_base
{
public:
	typedef int catalog;
};

template <class CharT> class messages {};

template <>
class messages<char> : public locale::facet, public messages_base
{
protected:
	~messages();
	virtual catalog do_open(const string &fn, const locale &loc) const;

private:
	_Messages *_M_impl;
};

template <>
class messages<wchar_t> : public locale::facet, public messages_base
{
protected:
	~messages();
	virtual catalog do_open(const string &fn, const locale &loc) const;

private:
	_Messages *_M_impl;
};

messages<char>::catalog messages<char>::do_open(const string &fn, const locale &loc) const
{
	return _M_impl->do_open(fn, loc);
}

messages<wchar_t>::catalog messages<wchar_t>::do_open(const string &fn, const locale &loc) const
{
	return _M_impl->do_open(fn, loc);
}

} // namespace _STL
