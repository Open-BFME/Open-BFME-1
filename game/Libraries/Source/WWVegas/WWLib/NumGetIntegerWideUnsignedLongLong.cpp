// cl: /O2 /MD
// STLport 4.5.3 wide unsigned __int64 __get_integer at retail 0x00834010.
// BFME's wchar_t ABI is unsigned short; this is the __false_type overflow
// parser reached by the wide num_get integer facet.

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

		bool empty() const { return _M_start == _M_finish; }
		const CharT *data() const { return _M_start; }
		unsigned int size() const
		{
			return (unsigned int)(_M_finish - _M_start);
		}
	};

	typedef basic_string<char, char_traits<char>, allocator<char> > string;

	template <class CharT, class Traits>
	class basic_streambuf
	{
	public:
		unsigned short sbumpc();
	};

	template <class CharT, class Traits>
	class istreambuf_iterator
	{
	public:
		bool equal(const istreambuf_iterator &other) const
		{
			if (_M_buf)
				_M_getc();
			if (other._M_buf)
				other._M_getc();
			return _M_eof == other._M_eof;
		}

		void _M_getc() const;

		CharT operator*() const
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

	struct __false_type
	{
	};

	template <class Integer>
	struct numeric_limits;

	template <>
	struct numeric_limits<unsigned __int64>
	{
		static unsigned __int64 max()
		{
			return 0xffffffffffffffffui64;
		}
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
		const string &grouping, const __false_type &)
	{
		bool overflow = false;
		Integer result = 0;
		bool is_group = !grouping.empty();
		char group_sizes[64];
		int current_group_size = 0;
		char *group_sizes_end = group_sizes;
		Integer over_base = (numeric_limits<Integer>::max)() / (Integer)base;

		for (; first != last; ++first)
		{
			const char c = (char)*first;
			if (is_group && c == separator)
			{
				*group_sizes_end = (char)current_group_size;
				++group_sizes_end;
				current_group_size = 0;
				continue;
			}

			int digit = __get_digit_from_table(c);
			if (digit >= base)
				break;

			++got;
			++current_group_size;
			if (result > over_base)
				overflow = true;
			else
			{
				Integer next = (Integer)(base * result + digit);
				if (result != 0)
					overflow = overflow || next <= result;
				result = next;
			}
		}

		if (is_group && group_sizes_end != group_sizes)
			*group_sizes_end++ = (char)current_group_size;
		if (got > 0)
			value = overflow ? (numeric_limits<Integer>::max)()
				: (negative ? (Integer)-result : result);
		return (got > 0 && !overflow) &&
			(is_group == 0 || __valid_grouping(group_sizes, group_sizes_end,
				grouping.data(), grouping.data() + grouping.size()));
	}

	template bool __get_integer<WideIterator, unsigned __int64>(
		WideIterator &, WideIterator &, int, unsigned __int64 &, int, bool, char,
		const string &, const __false_type &);
}
