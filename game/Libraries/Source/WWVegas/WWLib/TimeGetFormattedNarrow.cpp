// cl: /O2 /MD /D_STLP_USE_STATIC_LIB
// STLport 4.5.3 __get_formatted_time narrow iterator instantiation.

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

template <class CharT>
class allocator
{
};

template <class CharT, class Traits, class Alloc>
class basic_string
{
public:
	CharT *_M_start;
	CharT *_M_finish;
	CharT *_M_end_of_storage;
};

typedef basic_string<char, char_traits<char>, allocator<char> > string;

class ios_base
{
public:
	typedef int iostate;
	enum
	{
		goodbit = 0x00,
		badbit = 0x01,
		eofbit = 0x02,
		failbit = 0x04
	};
};

class _Time_Info
{
public:
	string _M_dayname[14];
	string _M_monthname[24];
	string _M_am_pm[2];
	string _M_time_format;
	string _M_date_format;
	string _M_date_time_format;
	string _M_long_date_format;
	string _M_long_date_time_format;
};

template <class CharT, class Traits>
class basic_streambuf
{
public:
	int sbumpc();
};

template <class CharT, class Traits>
class istreambuf_iterator
{
public:
	typedef CharT char_type;

	bool equal(const istreambuf_iterator &) const;
	void _M_getc() const;

	char_type operator*() const
	{
		_M_getc();
		return _M_c;
	}

	istreambuf_iterator &operator++()
	{
		_M_bumpc();
		return *this;
	}

	istreambuf_iterator operator++(int)
	{
		istreambuf_iterator result = *this;
		_M_bumpc();
		_M_have_c = false;
		return result;
	}

private:
	void _M_bumpc()
	{
		_M_buf->sbumpc();
		_M_have_c = false;
	}

	basic_streambuf<CharT, Traits> *_M_buf;
	mutable CharT _M_c;
	mutable unsigned char _M_eof;
	mutable unsigned char _M_have_c;
};

template <class CharT, class Traits>
inline bool operator!=(
	const istreambuf_iterator<CharT, Traits> &left,
	const istreambuf_iterator<CharT, Traits> &right)
{
	return !left.equal(right);
}

template <class InputIt, class RandomIt, class Difference>
RandomIt __match(
	InputIt &, InputIt &, RandomIt, RandomIt, Difference *);

template <class InputIt, class RandomIt>
RandomIt __match(
	InputIt &first, InputIt &last, RandomIt name, RandomIt name_end)
{
	return __match(
		(InputIt &)first, (InputIt &)last, name, name_end, (long *)0);
}

template <class InputIt, class Integer>
bool __get_decimal_integer(
	InputIt &first, InputIt &last, Integer &value);

template <class InputIt, class FormatIt>
FormatIt __get_formatted_time(
	InputIt first, InputIt last,
	FormatIt format, FormatIt format_end,
	const _Time_Info &table, ios_base::iostate &error, tm *value)
{
	while (first != last && format != format_end)
	{
		if (*format == '%')
		{
			++format;
			char c = *format;
			switch (c)
			{
			case 'a':
			{
				const string *result = __match(
					first, last,
					(string *)table._M_dayname,
					(string *)table._M_dayname + 7);
				if (result == (string *)table._M_dayname + 7)
					return format;
				value->tm_wday = (int)(result - (string *)table._M_dayname);
				break;
			}

			case 'A':
			{
				const string *result = __match(
					first, last,
					(string *)table._M_dayname + 7,
					(string *)table._M_dayname + 14);
				if (result == (string *)table._M_dayname + 14)
					return format;
				value->tm_wday =
					(int)(result - (string *)table._M_dayname - 7);
				break;
			}

			case 'b':
			{
				const string *result = __match(
					first, last,
					(string *)table._M_monthname,
					(string *)table._M_monthname + 12);
				if (result == (string *)table._M_monthname + 12)
					return format;
				value->tm_mon =
					(int)(result - (string *)table._M_monthname);
				break;
			}

			case 'B':
			{
				const string *result = __match(
					first, last,
					(string *)table._M_monthname + 12,
					(string *)table._M_monthname + 24);
				if (result == (string *)table._M_monthname + 24)
					return format;
				value->tm_mon =
					(int)(result - (string *)table._M_monthname - 12);
				break;
			}

			case 'd':
			{
				bool result = __get_decimal_integer(
					first, last, value->tm_mday);
				if (!result || value->tm_mday < 1 || value->tm_mday > 31)
				{
					error |= ios_base::failbit;
					return format;
				}
				break;
			}

			case 'H':
			case 'I':
			{
				bool result = __get_decimal_integer(
					first, last, value->tm_hour);
				if (!result)
					return format;
				break;
			}

			case 'j':
			{
				bool result = __get_decimal_integer(
					first, last, value->tm_yday);
				if (!result)
					return format;
				break;
			}

			case 'm':
			{
				bool result = __get_decimal_integer(
					first, last, value->tm_mon);
				--value->tm_mon;
				if (!result || value->tm_mon < 0 || value->tm_mon > 11)
				{
					error |= ios_base::failbit;
					return format;
				}
				break;
			}

			case 'M':
			{
				bool result = __get_decimal_integer(
					first, last, value->tm_min);
				if (!result)
					return format;
				break;
			}

			case 'p':
			{
				const string *result = __match(
					first, last,
					(string *)table._M_am_pm,
					(string *)table._M_am_pm + 2);
				if (result == (string *)table._M_am_pm + 2)
					return format;
				if (result == (string *)table._M_am_pm + 1)
					value->tm_hour += 12;
				break;
			}

			case 'S':
			{
				bool result = __get_decimal_integer(
					first, last, value->tm_sec);
				if (!result)
					return format;
				break;
			}

			case 'y':
			{
				bool result = __get_decimal_integer(
					first, last, value->tm_year);
				if (!result)
					return format;
				break;
			}

			case 'Y':
			{
				bool result = __get_decimal_integer(
					first, last, value->tm_year);
				value->tm_year -= 1900;
				if (!result)
					return format;
				break;
			}

			default:
				break;
			}
		}
		else
		{
			if (*first++ != *format)
				break;
		}

		++format;
	}

	return format;
}

typedef istreambuf_iterator<char, char_traits<char> > NarrowTimeIterator;

template const char *__get_formatted_time<NarrowTimeIterator, const char *>(
	NarrowTimeIterator, NarrowTimeIterator,
	const char *, const char *, const _Time_Info &,
	ios_base::iostate &, tm *);

} // namespace _STL
