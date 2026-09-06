// cl: /O2 /MD
// STLport 4.5.3 signed-long __get_integer<wchar_t> @ 0x00834F50 (404B).

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
		typedef unsigned int size_type;

		CharT *_M_start;
		CharT *_M_finish;
		CharT *_M_end_of_storage;

		bool empty() const { return _M_start == _M_finish; }
		const CharT *data() const { return _M_start; }
		size_type size() const { return (size_type)(_M_finish - _M_start); }
	};

	typedef basic_string<char, char_traits<char>, allocator<char> > string;

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

		bool equal(const istreambuf_iterator &other) const
		{
			if (_M_buf)
				_M_getc();
			if (other._M_buf)
				other._M_getc();
			return _M_eof == other._M_eof;
		}

		void _M_getc() const;

		char_type operator*() const
		{
			_M_getc();
			return _M_c;
		}

		istreambuf_iterator &operator++()
		{
			_M_buf->sbumpc();
			_M_have_c = 0;
			return *this;
		}

		basic_streambuf<CharT, Traits> *_M_buf;
		mutable CharT _M_c;
		mutable unsigned char _M_eof;
		mutable unsigned char _M_have_c;
	};

	template <class CharT, class Traits>
	inline bool operator!=(const istreambuf_iterator<CharT, Traits> &left,
		const istreambuf_iterator<CharT, Traits> &right)
	{
		return !left.equal(right);
	}

	struct __true_type
	{
	};

	template <class Integer>
	struct numeric_limits;

	template <>
	struct numeric_limits<long>
	{
		static long min() { return -2147483647L - 1; }
		static long max() { return 2147483647L; }
	};

	extern const unsigned char __digit_val_table[];

	inline int __get_digit_from_table(unsigned int index)
	{
		return index > 127 ? 0xff : __digit_val_table[index];
	}

	bool __valid_grouping(const char *, const char *, const char *, const char *);

	typedef istreambuf_iterator<unsigned short,
		char_traits<unsigned short> > WideIterator;

	template <class InputIter, class Integer>
	bool __get_integer(InputIter &first, InputIter &last, int base,
		Integer &value, int got, bool negative, char separator,
		const string &grouping, const __true_type &)
	{
		bool overflow = false;
		Integer result = 0;
		bool is_group = !grouping.empty();
		char group_sizes[64];
		int current_group_size = 0;
		char *group_sizes_end = group_sizes;
		Integer over_base = (numeric_limits<Integer>::min)() / (Integer)base;

		for (; first != last; ++first)
		{
			const char c = (char)*first;
			if (is_group && c == separator)
			{
				*group_sizes_end++ = (char)current_group_size;
				current_group_size = 0;
				continue;
			}

			int digit = __get_digit_from_table(c);
			if (digit >= base)
				break;

			++got;
			++current_group_size;
			if (result < over_base)
				overflow = true;
			else
			{
				Integer next = (Integer)(base * result - digit);
				if (result != 0)
					overflow = overflow || next >= result;
				result = next;
			}
		}

		if (is_group && group_sizes_end != group_sizes)
			*group_sizes_end++ = (char)current_group_size;
		if (got > 0)
			value = overflow ? (negative ? (numeric_limits<Integer>::min)()
				: (numeric_limits<Integer>::max)())
				: (negative ? result : (Integer)-result);
		return (got > 0 && !overflow) &&
			(is_group == 0 || __valid_grouping(group_sizes, group_sizes_end,
				grouping.data(), grouping.data() + grouping.size()));
	}

	template bool __get_integer<WideIterator, long>(
		WideIterator &, WideIterator &, int, long &, int, bool, char,
		const string &, const __true_type &);
}
