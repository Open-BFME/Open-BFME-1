// cl: /O2 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
// STLport 4.5.3 wide ostreambuf_iterator num_put::do_put(bool), retail
// 0x0083AEA0. Minimal canonical ABI declarations retain the wide string
// destructor inlining emitted by the original translation unit.

namespace _STL
{

typedef int ptrdiff_t;
typedef int streamsize;
typedef unsigned short BfmeWchar;

class BfmeCanonicalLocaleImpl
{
public:
	virtual void slot0() = 0;
	virtual void increment() = 0;
	virtual void decrement() = 0;
};

class locale
{
public:
	class facet {};
	~locale() { m_impl->decrement(); }

private:
	BfmeCanonicalLocaleImpl *m_impl;
};

class ios_base
{
public:
	typedef int fmtflags;
	enum {
		left = 1,
		right = 2,
		internal = 4,
		adjustfield = left | right | internal,
		boolalpha = 0x100
	};

	virtual ~ios_base();
	fmtflags flags() const { return m_flags; }
	streamsize width(streamsize value)
	{
		streamsize old = m_width;
		m_width = value;
		return old;
	}
	locale getloc() const;
	const locale::facet *_M_numpunct_facet() const { return m_numpunct; }

private:
	fmtflags m_flags;
	char m_before_width[0x14];
	streamsize m_width;
	char m_before_numpunct[0x24];
	const locale::facet *m_numpunct;
};

template <bool Threads, int Inst>
class __node_alloc
{
public:
	static void __declspec(nothrow) deallocate(void *, unsigned int);
};

template <class T> class allocator {};
template <class CharT> class char_traits {};

template <class CharT, class Traits>
class ostreambuf_iterator
{
private:
	void *m_buffer;
	int m_ok;
};

template <class CharT, class Traits, class Alloc>
class basic_string
{
public:
	basic_string(const basic_string &);
	~basic_string()
	{
		deallocate(m_start, (unsigned int)(m_end - m_start));
	}

	const CharT *c_str() const { return m_start; }
	ptrdiff_t size() const { return m_finish - m_start; }

private:
	static void deallocate(CharT *pointer, unsigned int count)
	{
		if (pointer != 0)
			__node_alloc<true, 0>::deallocate(pointer,
				count * sizeof(CharT));
	}

	CharT *m_start;
	CharT *m_finish;
	CharT *m_end;
};

template <class CharT>
class numpunct
{
public:
	basic_string<CharT, char_traits<CharT>, allocator<CharT> >
		truename() const;
	basic_string<CharT, char_traits<CharT>, allocator<CharT> >
		falsename() const;
};

template <class CharT, class OutputIter>
class num_put
{
protected:
	virtual ~num_put();
	virtual OutputIter do_put(OutputIter, ios_base &, CharT, bool) const;
	virtual OutputIter do_put(OutputIter, ios_base &, CharT, long) const;
	virtual OutputIter do_put(OutputIter, ios_base &, CharT, unsigned long) const;
	virtual OutputIter do_put(OutputIter, ios_base &, CharT, double) const;
	virtual OutputIter do_put(OutputIter, ios_base &, CharT, long double) const;
	virtual OutputIter do_put(OutputIter, ios_base &, CharT, __int64) const;
	virtual OutputIter do_put(OutputIter, ios_base &, CharT,
		unsigned __int64) const;
	virtual OutputIter do_put(OutputIter, ios_base &, CharT,
		const void *) const;
};

template <class CharT, class OutputIter>
OutputIter __cdecl __copy_integer_and_fill(const CharT *, ptrdiff_t,
	OutputIter, ios_base::fmtflags, streamsize, CharT, CharT, CharT);

typedef ostreambuf_iterator<BfmeWchar, char_traits<BfmeWchar> >
	BfmeWidePutIterator;

template <>
BfmeWidePutIterator
num_put<BfmeWchar, BfmeWidePutIterator>::do_put(
	BfmeWidePutIterator output, ios_base &stream, BfmeWchar fill,
	bool value) const
{
	if (!(stream.flags() & ios_base::boolalpha))
		return this->do_put(output, stream, fill, (long)value);

	locale loc = stream.getloc();
	const numpunct<BfmeWchar> &punct =
		*(const numpunct<BfmeWchar> *)stream._M_numpunct_facet();
	basic_string<BfmeWchar, char_traits<BfmeWchar>, allocator<BfmeWchar> > text =
		value ? punct.truename() : punct.falsename();

	ios_base::fmtflags flags = stream.flags();
	if ((flags & ios_base::adjustfield) == ios_base::internal)
		flags = (flags & ~ios_base::adjustfield) | ios_base::right;

	return __copy_integer_and_fill(text.c_str(), text.size(), output,
		flags, stream.width(0), fill, (BfmeWchar)0, (BfmeWchar)0);
}

} // namespace _STL
