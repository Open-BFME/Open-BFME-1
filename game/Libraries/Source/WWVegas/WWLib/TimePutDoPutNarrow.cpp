// ?do_put@?$time_put@DV?$ostreambuf_iterator@DV?$char_traits@D@_STL@@@_STL@@@_STL@@MBE?AV?$ostreambuf_iterator@DV?$char_traits@D@_STL@@@2@V32@AAVios_base@2@DPBUtm@@DD@Z
// cl: /O2 /MD /D_STLP_USE_STATIC_LIB
// stlport

struct tm
{
	int tm_sec;
	int tm_min;
	int tm_hour;
	int tm_mday;
	int tm_mon;
	int tm_year;
	int tm_wday;
	int tm_yday;
	int tm_isdst;
};

namespace _STL
{

template <class CharT>
class char_traits
{
};

template <class CharT, class Traits>
class basic_streambuf
{
};

class ios_base
{
};

class locale
{
public:
	class facet
	{
	};
};

class time_base
{
};

class _Time_Info
{
};

template <class CharT, class Traits>
class ostreambuf_iterator
{
public:
	typedef CharT char_type;
	typedef basic_streambuf<CharT, Traits> streambuf_type;

	ostreambuf_iterator &operator=(char_type);
	ostreambuf_iterator &operator*()
	{
		return *this;
	}
	ostreambuf_iterator &operator++()
	{
		return *this;
	}
	ostreambuf_iterator &operator++(int)
	{
		return *this;
	}

private:
	streambuf_type *_M_buf;
	bool _M_ok;
};

template <class CharT, class OutputIterator>
class time_put : public locale::facet, public time_base
{
public:
	typedef OutputIterator iter_type;

protected:
	virtual iter_type do_put(
		iter_type, ios_base &, CharT, const tm *, char, char) const;
	_Time_Info _M_timeinfo;
};

char *__cdecl __write_formatted_time(
	char *, char, char, const _Time_Info &, const tm *);

typedef ostreambuf_iterator<char, char_traits<char> > NarrowIterator;

template <>
NarrowIterator
time_put<char, NarrowIterator>::do_put(
	NarrowIterator out, ios_base &, char,
	const tm *value, char format, char modifier) const
{
	NarrowIterator result = out;
	char buffer[64];
	char *end = __write_formatted_time(
		buffer, format, modifier, *reinterpret_cast<const _Time_Info *>(
			reinterpret_cast<const char *>(this) + 0x0C), value);
	char *p = buffer;
	int count = (int)(end - buffer);
	if (count > 0)
	{
		for (; count > 0; --count)
		{
			*result = *p;
			++p;
			++result;
		}
	}
	return result;
}

}
