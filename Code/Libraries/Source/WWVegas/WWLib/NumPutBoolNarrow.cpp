// cl: /O2 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
// STLport 4.5.3 narrow ostreambuf_iterator num_put::do_put(bool), retail
// 0x00838FE0.
// The boolalpha branch obtains the cached narrow numpunct true/false name and
// writes it with the stream's requested field width.  Without boolalpha the
// standard delegates to the signed-long virtual overload.

#include "stlport_prefix.h"
#include <stl/_string.h>
#include <stl/_ios.h>
#include <stl/_numpunct.h>
#include <stl/_num_put.h>
#include <stl/_ostreambuf_iterator.h>

_STLP_BEGIN_NAMESPACE

class BfmeLocaleImpl
{
public:
	virtual void slot0() = 0;
	virtual void increment() = 0;
	virtual void decrement() = 0;
};

class BfmeInlineLocale
{
public:
	~BfmeInlineLocale() { m_impl->decrement(); }

private:
	BfmeLocaleImpl *m_impl;
};

class BfmeIosLocaleView
{
public:
	BfmeInlineLocale getloc() const;
};

#pragma comment(linker, "/alternatename:?getloc@BfmeIosLocaleView@_STL@@QBE?AVBfmeInlineLocale@2@XZ=?getloc@ios_base@_STL@@QBE?AVlocale@2@XZ")

template <class CharT, class OutputIter>
OutputIter _STLP_CALL __copy_integer_and_fill(const CharT *, ptrdiff_t,
	OutputIter, ios_base::fmtflags, streamsize, CharT, CharT, CharT);

typedef ostreambuf_iterator<char, char_traits<char> > BfmeNarrowPutIterator;

template <>
BfmeNarrowPutIterator
num_put<char, BfmeNarrowPutIterator>::do_put(BfmeNarrowPutIterator output,
	ios_base &stream,
	char fill, bool value) const
{
	if (!(stream.flags() & ios_base::boolalpha))
		return this->do_put(output, stream, fill, (long)value);

	BfmeInlineLocale loc = ((BfmeIosLocaleView &)stream).getloc();
	const numpunct<char> &punct =
		*(const numpunct<char> *)stream._M_numpunct_facet();
	basic_string<char> text = value ? punct.truename() : punct.falsename();

	ios_base::fmtflags flags = stream.flags();
	if ((flags & ios_base::adjustfield) == ios_base::internal)
		flags = (flags & ~ios_base::adjustfield) | ios_base::right;

	return __copy_integer_and_fill(text.c_str(), text.size(), output,
		flags, stream.width(0), fill, (char)0, (char)0);
}

_STLP_END_NAMESPACE
