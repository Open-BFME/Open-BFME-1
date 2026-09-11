// cl: /O2 /MD
// stlport
// STLport 4.5.3 __get_monetary_value for the narrow istreambuf iterator.
// The helper is called by money_get<char>::do_get(string&) and follows the
// adjacent narrow mismatch specialization at retail 0x0083D6A0.
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
		typedef CharT value_type;
		typedef unsigned int size_type;

		CharT *m_start;
		CharT *m_finish;
		CharT *m_end_of_storage;

		size_type size() const { return (size_type)(m_finish - m_start); }
		const CharT *data() const { return m_start; }
		void push_back(CharT);
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

		bool equal(const istreambuf_iterator &) const;
		void _M_getc() const;

		char_type operator*() const
		{
			_M_getc();
			return m_c;
		}

		istreambuf_iterator &operator++()
		{
			m_buf->sbumpc();
			m_have_c = 0;
			return *this;
		}

		istreambuf_iterator operator++(int)
		{
			istreambuf_iterator old = *this;
			++*this;
			return old;
		}

		basic_streambuf<CharT, Traits> *m_buf;
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

	class ctype_base
	{
	public:
		typedef unsigned int mask;
		enum { digit = 4 };
	};

	template <class CharT>
	class ctype : public ctype_base
	{
	public:
		bool is(mask value, CharT c) const
		{
			return (m_table[(unsigned char)c] & value) != 0;
		}

	private:
		unsigned char m_prefix[0x0c];
		const mask *m_table;
	};

	template <class Container>
	class back_insert_iterator
	{
	public:
		typedef back_insert_iterator<Container> self;

		explicit back_insert_iterator(Container &container) : m_container(&container) {}
		self &operator=(typename Container::value_type value)
		{
			m_container->push_back(value);
			return *this;
		}
		self &operator*() { return *this; }
		self &operator++() { return *this; }
		self operator++(int) { return *this; }

	private:
		Container *m_container;
	};

	bool __valid_grouping(const char *, const char *, const char *, const char *);

	template <class InIt, class OutIt, class CharT>
	bool __get_monetary_value(InIt &first, InIt last, OutIt out,
		const ctype<CharT> &ctype_value, CharT point, int frac_digits,
		CharT separator, const string &grouping, bool &syntax_ok)
	{
		if (first == last || !ctype_value.is(ctype_base::digit, *first))
			return false;

		char group_sizes[128];
		char *group_sizes_end = grouping.size() == 0 ? 0 : group_sizes;
		char current_group_size = 0;

		while (first != last)
		{
			if (ctype_value.is(ctype_base::digit, *first))
			{
				++current_group_size;
				*out++ = *first++;
			}
			else if (group_sizes_end)
			{
				if (*first == separator)
				{
					*group_sizes_end++ = current_group_size;
					current_group_size = 0;
					++first;
				}
				else
					break;
			}
			else
				break;
		}

		if (grouping.size() == 0)
			syntax_ok = true;
		else
		{
			if (group_sizes_end != group_sizes)
				*group_sizes_end++ = current_group_size;

			syntax_ok = __valid_grouping(group_sizes, group_sizes_end,
				grouping.data(), grouping.data() + grouping.size());

			if (first == last || *first != point)
			{
				for (int digits = 0; digits != frac_digits; ++digits)
					*out++ = CharT('0');
				return true;
			}
		}

		++first;
		unsigned int digits = 0;
		while (first != last && ctype_value.is(ctype_base::digit, *first))
		{
			*out++ = *first++;
			++digits;
		}

		syntax_ok = syntax_ok && (digits == (unsigned int)frac_digits);
		return true;
	}

	typedef istreambuf_iterator<char, char_traits<char> > NarrowIterator;
	typedef back_insert_iterator<string> NarrowBackInserter;

	template bool __get_monetary_value<NarrowIterator, NarrowBackInserter, char>(
		NarrowIterator &, NarrowIterator, NarrowBackInserter,
		const ctype<char> &, char, int, char, const string &, bool &);
}
