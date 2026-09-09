// cl: /O2 /MD
// STLport 4.5.3 signed integer _M_do_get_integer<wchar_t> specializations.
// The __int64 body is at retail 0x00834250; the signed-long body is at
// 0x00834E50 and calls the exact parser at 0x00834F50.
// BFME's wchar_t ABI is unsigned short.  RTTI/vtable evidence: this body is
// the slot-2 implementation reached by the wide num_get facet.  The helper
// uses __alldiv and the value destination is eight bytes wide.

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

	template <class CharT, class Traits>
	class istreambuf_iterator
	{
	public:
		istreambuf_iterator(void * = 0);

		bool equal(const istreambuf_iterator &other) const
		{
			if (m_buf)
				_M_getc();
			if (other.m_buf)
				other._M_getc();
			return m_eof == other.m_eof;
		}

		void _M_getc() const;

		void *m_buf;
		mutable CharT m_c;
		mutable unsigned char m_eof;
		mutable unsigned char m_have_c;
	};

	template <class CharT, class Traits>
	inline bool operator==(const istreambuf_iterator<CharT, Traits> &left,
		const istreambuf_iterator<CharT, Traits> &right)
	{
		return left.equal(right);
	}

	template <class CharT, class Traits>
	inline bool operator!=(const istreambuf_iterator<CharT, Traits> &left,
		const istreambuf_iterator<CharT, Traits> &right)
	{
		return !left.equal(right);
	}

	struct __true_type
	{
	};

	template <class CharT>
	class numpunct
	{
	public:
		CharT thousands_sep() const { return do_thousands_sep(); }

	protected:
		virtual ~numpunct();
		virtual CharT do_decimal_point() const;
		virtual CharT do_thousands_sep() const;
	};

	class ios_base
	{
	public:
		typedef int iostate;
		static const iostate goodbit = 0;
		static const iostate eofbit = 2;
		static const iostate failbit = 4;

		const void *_M_numpunct_facet() const
		{
			return *(const void **)((const char *)this + 0x44);
		}

		const string &_M_grouping() const
		{
			return *(const string *)((const char *)this + 0x48);
		}
	};

	typedef istreambuf_iterator<unsigned short,
		char_traits<unsigned short> > WideIterator;

	template <class InputIter, class CharT>
	int _M_get_base_or_zero(InputIter &, InputIter &, ios_base &, CharT *);

	template <class InputIter, class Integer>
	bool __get_integer(InputIter &, InputIter &, int, Integer &, int,
		bool, char, const string &, const __true_type &);

	template <class InputIter, class Integer, class CharT>
	InputIter _M_do_get_integer(InputIter &in, InputIter &end,
		ios_base &str, ios_base::iostate &err, Integer &val, CharT *pc)
	{
		const numpunct<CharT> &punct = *(const numpunct<CharT> *)
			str._M_numpunct_facet();
		const string &grouping = str._M_grouping();
		const int base_or_zero = _M_get_base_or_zero(in, end, str, pc);
		const int got = base_or_zero & 1;
		bool result;

		if (in == end)
		{
			if (got > 0)
			{
				val = 0;
				result = true;
			}
			else
				result = false;
		}
		else
		{
			const bool negative = (base_or_zero & 2) != 0;
			const int base = base_or_zero >> 2;
			result = __get_integer(in, end, base, val, got, negative,
				punct.thousands_sep(), grouping, __true_type());
		}

		err = (ios_base::iostate)(result ? ios_base::goodbit : ios_base::failbit);
		if (in == end)
			err = (ios_base::iostate)(err | ios_base::eofbit);
		return in;
	}

	template istreambuf_iterator<unsigned short, char_traits<unsigned short> >
	_M_do_get_integer<WideIterator, __int64, unsigned short>(
		WideIterator &, WideIterator &, ios_base &, ios_base::iostate &,
		__int64 &, unsigned short *);

	template istreambuf_iterator<unsigned short, char_traits<unsigned short> >
	_M_do_get_integer<WideIterator, long, unsigned short>(
		WideIterator &, WideIterator &, ios_base &, ios_base::iostate &,
		long &, unsigned short *);
}
