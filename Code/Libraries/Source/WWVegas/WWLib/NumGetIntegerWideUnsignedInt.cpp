// cl: /O2 /MD
// STLport 4.5.3 narrow and wide unsigned integer _M_do_get_integer
// specializations. The narrow unsigned-long body is at 0x00833170 and calls
// its digit parser at 0x00833270.
// The unsigned-long body is at 0x00834610 and calls its digit parser at
// 0x00834710. The unsigned-int body is at 0x008348D0 and calls its digit parser
// at 0x008349D0. The unsigned-short body is at 0x00834B90 and calls the exact
// parser at 0x00834C90. Their adjacent 47-byte num_get wrappers establish the
// three specializations independently.

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
		CharT *m_start;
		CharT *m_finish;
		CharT *m_end_of_storage;

		bool empty() const { return m_start == m_finish; }
		const CharT *data() const { return m_start; }
		unsigned int size() const
		{
			return (unsigned int)(m_finish - m_start);
		}
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

		CharT operator*() const
		{
			_M_getc();
			return m_c;
		}

		istreambuf_iterator &operator++()
		{
			m_have_c = 0;
			return *this;
		}

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

	struct __false_type
	{
	};

	template <class CharT>
	class numpunct
	{
	public:
		virtual void slot_0() const;
		virtual void slot_1() const;
		virtual CharT thousands_sep() const;
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
	typedef istreambuf_iterator<char, char_traits<char> > NarrowIterator;

	template <class InputIter, class CharT>
	int _M_get_base_or_zero(InputIter &, InputIter &, ios_base &,
		CharT *);

	template <class InputIter, class Integer>
	bool __get_integer(InputIter &, InputIter &, int, Integer &, int,
		bool, char, const string &, const __false_type &);

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
					punct.thousands_sep(), grouping, __false_type());
		}

		err = (ios_base::iostate)(result ? ios_base::goodbit : ios_base::failbit);
		if (in == end)
			err = (ios_base::iostate)(err | ios_base::eofbit);
		return in;
	}

	template istreambuf_iterator<unsigned short, char_traits<unsigned short> >
	_M_do_get_integer<WideIterator, unsigned long, unsigned short>(
		WideIterator &, WideIterator &, ios_base &, ios_base::iostate &,
		unsigned long &, unsigned short *);

	template istreambuf_iterator<char, char_traits<char> >
	_M_do_get_integer<NarrowIterator, unsigned long, char>(
		NarrowIterator &, NarrowIterator &, ios_base &, ios_base::iostate &,
		unsigned long &, char *);

	template istreambuf_iterator<unsigned short, char_traits<unsigned short> >
	_M_do_get_integer<WideIterator, unsigned int, unsigned short>(
		WideIterator &, WideIterator &, ios_base &, ios_base::iostate &,
		unsigned int &, unsigned short *);

	template istreambuf_iterator<unsigned short, char_traits<unsigned short> >
	_M_do_get_integer<WideIterator, unsigned short, unsigned short>(
		WideIterator &, WideIterator &, ios_base &, ios_base::iostate &,
		unsigned short &, unsigned short *);
}
