// cl: /O2 /MD
// STLport 4.5.3 __get_integer<char *, long double> at retail 0x00837840.
// The x87 accumulator, DBL_MAX/base threshold, qword result store, and direct
// one-byte pointer increment make this the narrow twin of the raw wide-pointer
// long-double helper at 0x008396D0.  The queued istreambuf_iterator/long name
// does not describe this body's ABI, so the source keeps the honest pointer and
// result types visible in its emitted identity.

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

		CharT *m_start;
		CharT *m_finish;
		CharT *m_end_of_storage;

		bool empty() const { return m_start == m_finish; }
		const CharT *data() const { return m_start; }
		size_type size() const { return (size_type)(m_finish - m_start); }
	};

	typedef basic_string<char, char_traits<char>, allocator<char> > string;

	struct __false_type
	{
	};

	template <class Integer>
	struct numeric_limits;

	template <>
	struct numeric_limits<long double>
	{
		static long double max()
		{
			return 1.7976931348623157e+308;
		}
	};

	extern const unsigned char __digit_val_table[];

	inline int __get_digit_from_table(unsigned int index)
	{
		return index > 127 ? 0xff : __digit_val_table[index];
	}

	bool __valid_grouping(const char *, const char *, const char *, const char *);

	typedef char * NarrowPointer;

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
		Integer over_base = (numeric_limits<Integer>::max)() /
			(Integer)base;

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

	template bool __get_integer<NarrowPointer, long double>(
		NarrowPointer &, NarrowPointer &, int, long double &, int, bool, char,
		const string &, const __false_type &);
}
