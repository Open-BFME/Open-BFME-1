// cl: /O2 /EHsc /MD /D_STLP_USE_STATIC_LIB
// STLport 4.5.3

// The vtable at VA 0x0112FB8C carries an RTTI complete object locator whose
// type descriptor spells `.?AV?$messages@D@_STL@@`, and 0x0112FBB8 spells
// `.?AV?$messages@G@_STL@@`.  inputs/vendor/stlport/stl/_messages_facets.h declares
// the protected virtuals of both specializations as the destructor, do_open,
// do_get and do_close in that order, so slot 1 of each table is do_open.
// Slot 2 is do_get and slot 3 is do_close for the same reason.  Each body loads
// the owned _Messages from offset 0x0C and reaches one of its virtuals: do_open
// at slot 0, do_close at slot 3, and do_get at slot 2 for the narrow facet and
// slot 1 for the wide one, which is the reverse declaration order MSVC 7.1 gives
// an overload set.  The _Messages member names below are placeholders that fix
// the slot order, since retail names none of them.

typedef unsigned short wchar_t;

namespace _STL
{

template <class CharT> class char_traits;
template <class T> class allocator;
template <class CharT, class Traits, class Alloc>
class basic_string
{
public:
	basic_string(const basic_string &other);
	~basic_string();

	CharT *m_start;
	CharT *m_finish;
	CharT *m_endOfStorage;
	void *m_allocator;
};

typedef basic_string<char, char_traits<char>, allocator<char> > string;
typedef basic_string<wchar_t, char_traits<wchar_t>, allocator<wchar_t> > wstring;

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
	virtual wstring do_get_wide(int c, int set, int msgid,
		const wstring &dfault) const;
	virtual string do_get_narrow(int c, int set, int msgid,
		const string &dfault) const;
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
public:
	typedef string string_type;

protected:
	~messages();
	virtual catalog do_open(const string &fn, const locale &loc) const;
	virtual string_type do_get(catalog c, int set, int msgid,
		const string_type &dfault) const;
	virtual void do_close(catalog c) const;

private:
	_Messages *_M_impl;
};

template <>
class messages<wchar_t> : public locale::facet, public messages_base
{
public:
	typedef wstring string_type;

protected:
	~messages();
	virtual catalog do_open(const string &fn, const locale &loc) const;
	virtual string_type do_get(catalog c, int set, int msgid,
		const string_type &dfault) const;
	virtual void do_close(catalog c) const;

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

messages<char>::string_type messages<char>::do_get(catalog c, int set,
	int msgid, const string_type &dfault) const
{
	return _M_impl->do_get_narrow(c, set, msgid, dfault);
}

messages<wchar_t>::string_type messages<wchar_t>::do_get(catalog c, int set,
	int msgid, const string_type &dfault) const
{
	return _M_impl->do_get_wide(c, set, msgid, dfault);
}

void messages<char>::do_close(catalog c) const
{
	_M_impl->do_close(c);
}

void messages<wchar_t>::do_close(catalog c) const
{
	_M_impl->do_close(c);
}

} // namespace _STL
