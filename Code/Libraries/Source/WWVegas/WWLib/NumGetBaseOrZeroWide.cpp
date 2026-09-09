// cl: /O2 /MD

// STLport 4.5.3 _M_get_base_or_zero for
// istreambuf_iterator<unsigned short, char_traits<unsigned short> >.
//
// The retail body at 0x00833DE0 is the wide instantiation of the vendor
// _M_get_base_or_zero template in vendor/stlport/stl/_num_get.c.  This build
// uses the non-owning iostream path: the ctype facet is obtained from the
// temporary locale returned by ios_base::getloc(), and that locale is released
// immediately after _M_use_facet returns.  BFME's wchar_t ABI is an unsigned
// short, and the iterator's Traits::int_type is the same unsigned short.  The
// narrow instantiation at 0x00832970 uses the corresponding narrow ctype ABI.

namespace _STL
{
	template <class CharT>
	class char_traits
	{
	};

	class _Locale_impl
	{
	public:
		virtual void slot_0();
		virtual void add_reference();
		virtual void release_reference();
	};

	class locale
	{
	public:
		class facet
		{
		public:
			virtual ~facet();
		};

		class id
		{
		public:
			unsigned int index;
		};

		facet *_M_use_facet(const id &) const;

		~locale() __declspec(nothrow)
		{
			_M_impl->release_reference();
		}

	private:
		_Locale_impl *_M_impl;
	};

	template <class CharT>
	class ctype : public locale::facet
	{
	public:
		const char *widen(const char *low, const char *high,
			CharT *to) const
		{
			return do_widen(low, high, to);
		}

	protected:
		// The STLport wide ctype table's vftable is the range-first variant
		// proved at 0x00D2EA54.  Keep all preceding slots in the declaration;
		// this TU only dispatches through the existing facet and emits no table.
		virtual const CharT *is_range(const CharT *, const CharT *,
			unsigned int *) const;
		virtual bool is_one(unsigned int, CharT) const;
		virtual const CharT *scan_is(unsigned int, const CharT *,
			const CharT *) const;
		virtual const CharT *scan_not(unsigned int, const CharT *,
			const CharT *) const;
		virtual const CharT *toupper_range(CharT *, CharT *) const;
		virtual CharT toupper_one(unsigned int) const;
		virtual const CharT *tolower_range(CharT *, CharT *) const;
		virtual CharT tolower_one(unsigned int) const;
		virtual const char *do_widen(const char *, const char *,
			CharT *) const;
	};

	// STLport's narrow ctype has four virtual range/conversion slots before
	// do_widen; the wide ctype above has eight.  Keeping this ABI-local view is
	// what makes the narrow parser dispatch at vtable offset +0x14.
	template <>
	class ctype<char> : public locale::facet
	{
	public:
		const char *widen(const char *low, const char *high,
			char *to) const
		{
			return do_widen(low, high, to);
		}

	protected:
		virtual char do_toupper(char) const;
		virtual char do_tolower(char) const;
		virtual const char *do_toupper(char *, const char *) const;
		virtual const char *do_tolower(char *, const char *) const;
		virtual const char *do_widen(const char *, const char *,
			char *) const;
	};

	template <class CharT>
	const ctype<CharT> &use_ctype_facet(const locale &loc)
	{
		return *(const ctype<CharT> *)loc._M_use_facet(
			*(const locale::id *)0x012C7450);
	}

	template <>
	const ctype<char> &use_ctype_facet<char>(const locale &loc)
	{
		return *(const ctype<char> *)loc._M_use_facet(
			*(const locale::id *)0x012C7430);
	}

	class ios_base
	{
	public:
		typedef unsigned int fmtflags;

		static const fmtflags dec = 0x0008;
		static const fmtflags hex = 0x0010;
		static const fmtflags oct = 0x0020;
		static const fmtflags basefield = dec | hex | oct;

		virtual ~ios_base();

		fmtflags flags() const
		{
			return _M_fmtflags;
		}

		locale getloc() const;

	private:
		fmtflags _M_fmtflags;
	};

	template <class CharT, class Traits>
	class basic_streambuf
	{
	public:
		// VC7 STLport's wide Traits::int_type is unsigned short.
		unsigned short sbumpc();
	};

	template <class Traits>
	class basic_streambuf<char, Traits>
	{
	public:
		// The narrow Traits::int_type is int in this retail build.
		int sbumpc();
	};

	template <class CharT, class Traits>
	class istreambuf_iterator
	{
	public:
		typedef CharT char_type;

		istreambuf_iterator(basic_streambuf<CharT, Traits> * = 0);

		__forceinline bool equal(const istreambuf_iterator &other) const
		{
			if (_M_buf)
				_M_getc();
			if (other._M_buf)
				other._M_getc();
			return _M_eof == other._M_eof;
		}

	public:
		void _M_getc() const;

		char_type operator*() const
		{
			_M_getc();
			return _M_c;
		}

		__forceinline istreambuf_iterator &operator++()
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
	__forceinline bool operator!=(const istreambuf_iterator<CharT, Traits> &left,
		const istreambuf_iterator<CharT, Traits> &right)
	{
		return !left.equal(right);
	}

	typedef istreambuf_iterator<unsigned short,
		char_traits<unsigned short> > WideIterator;
	typedef istreambuf_iterator<char, char_traits<char> > NarrowIterator;

	// The vendor's __narrow_atoms is the five-byte table beginning at this
	// independently read retail VA ("+x0123456789abcdef...").
	static const char *const __narrow_atoms =
		(const char *)0x0112F430;

	template <class InputIter, class CharT>
	__declspec(nothrow) int _M_get_base_or_zero(InputIter &in, InputIter &end,
		ios_base &str, CharT *)
	{
		CharT atoms[5];
		const ctype<CharT> &c_type =
			use_ctype_facet<CharT>(str.getloc());

		c_type.widen(__narrow_atoms, __narrow_atoms + 5, atoms);

		bool negative = false;
		CharT c = *in;

		if (c == atoms[1])
		{
			negative = true;
			++in;
		}
		else if (c == atoms[0])
			++in;

		int base;
		int valid_zero = 0;
		ios_base::fmtflags basefield = str.flags() & ios_base::basefield;

		switch (basefield)
		{
		case ios_base::oct:
			base = 8;
			break;
		case ios_base::dec:
			base = 10;
			break;
		case ios_base::hex:
			base = 16;
			if (in != end && *in == atoms[2])
			{
				++in;
				if (in != end &&
					(*in == atoms[3] || *in == atoms[4]))
					++in;
				else
					valid_zero = 1;
			}
			break;
		default:
			if (in != end && *in == atoms[2])
			{
				++in;
				if (in != end &&
					(*in == atoms[3] || *in == atoms[4]))
				{
					++in;
					base = 16;
				}
				else
				{
					base = 8;
					valid_zero = 1;
				}
			}
			else
				base = 10;
			break;
		}

		return (base << 2) | ((int)negative << 1) | valid_zero;
	}

	template int _M_get_base_or_zero<WideIterator, unsigned short>(
		WideIterator &, WideIterator &, ios_base &, unsigned short *);

	template int _M_get_base_or_zero<NarrowIterator, char>(
		NarrowIterator &, NarrowIterator &, ios_base &, char *);
}
