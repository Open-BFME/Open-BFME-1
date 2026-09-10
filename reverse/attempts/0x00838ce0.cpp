// ?d_00838ce0@@YAXXZ
// partial score=0.25 date=2026-09-10
// cl: /O2 /MD /D_STLP_USE_STATIC_LIB /EHsc
// stlport
// STLport 4.5.3 num_get<char, istreambuf_iterator<char>>::do_get(bool&) at
// 0x00838CE0 (704B). Identity confirmed from retail bytes: the boolalpha
// test reads ios_base+4 bit 0x100 (_M_fmtflags), the facet pointer comes
// from ios_base+0x44 (_M_cached_numpunct), and the two direct calls into
// the shared SlotForward COMDATs land on numpunct<char>'s do_truename and
// do_falsename vtable slots (0x10, 0x14, counting facet's own dtor and
// do_decimal_point/do_thousands_sep/do_grouping ahead of them). bfmeGoSG
// is istreambuf_iterator<char,...>::_M_getc (already matched at 0x00832940)
// and j_0001f433 is the already-matched sbumpc thunk.

#include "stlport_prefix.h"
#include <stl/_string.h>
#include <stl/_ios.h>
#include <stl/_locale.h>

class BfmeThingSG
{
public:
	void bfmeGoSG();
};

void j_0001f433();

class Rva00838FA0SlotForward
{
public:
	void *forward(void *p);
};

class Rva00838FC0SlotForward
{
public:
	void *forward(void *p);
};

_STLP_BEGIN_NAMESPACE

template <class CharT, class Traits>
class istreambuf_iterator
{
public:
	istreambuf_iterator(basic_streambuf<CharT, Traits> * = 0);
	__declspec(noinline) bool equal(const istreambuf_iterator &other) const;

	CharT operator*() const
	{
		((BfmeThingSG *)this)->bfmeGoSG();
		return m_c;
	}
	istreambuf_iterator &operator++()
	{
		j_0001f433();
		m_have_c = 0;
		return *this;
	}

	basic_streambuf<CharT, Traits> *m_buf;
	mutable CharT m_c;
	mutable unsigned char m_eof;
	mutable unsigned char m_have_c;
};

template <class CharT, class InputIter>
class num_get : public locale::facet
{
protected:
	virtual InputIter do_get(InputIter in, InputIter end, ios_base &str,
		ios_base::iostate &err, bool &value) const
	{
		if (str.flags() & ios_base::boolalpha)
		{
			locale loc = str.getloc();
			void *facet = (void *)str._M_numpunct_facet();

			unsigned char truenameBuf[12];
			unsigned char falsenameBuf[12];
			((Rva00838FA0SlotForward *)facet)->forward(truenameBuf);
			((Rva00838FC0SlotForward *)facet)->forward(falsenameBuf);
			basic_string<CharT> &truename = *(basic_string<CharT> *)truenameBuf;
			basic_string<CharT> &falsename = *(basic_string<CharT> *)falsenameBuf;

			bool trueOk = true;
			bool falseOk = true;
			size_t n = 0;
			for (; !in.equal(end); ++in)
			{
				CharT c = *in;
				trueOk = trueOk && (c == truename[n]);
				falseOk = falseOk && (c == falsename[n]);
				++n;

				if ((!trueOk && !falseOk) ||
					(trueOk && n >= truename.size()) ||
					(falseOk && n >= falsename.size()))
				{
					++in;
					break;
				}
			}
			if (trueOk && n < truename.size())
				trueOk = false;
			if (falseOk && n < falsename.size())
				falseOk = false;

			if (trueOk || falseOk)
			{
				err = ios_base::goodbit;
				value = trueOk;
			}
			else
				err = ios_base::failbit;

			if (in.equal(end))
				err |= ios_base::eofbit;

			falsename.~basic_string<CharT>();
			truename.~basic_string<CharT>();

			return in;
		}
		else
		{
			long lx;
			InputIter tmp = this->do_get(in, end, str, err, lx);
			if (!(err & ios_base::failbit))
			{
				if (lx == 0)
					value = false;
				else if (lx == 1)
					value = true;
				else
					err |= ios_base::failbit;
			}
			return tmp;
		}
	}

	virtual InputIter do_get(InputIter in, InputIter end, ios_base &str,
		ios_base::iostate &err, long &value) const;
};

typedef istreambuf_iterator<char, char_traits<char> > NarrowIterator;
template class num_get<char, NarrowIterator>;

_STLP_END_NAMESPACE
