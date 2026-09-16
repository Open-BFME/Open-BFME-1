// ?d_00838ce0@@YAXXZ
// partial score=0.91 date=2026-09-16
// cl: /O2 /MD /D_STLP_USE_STATIC_LIB /EHsc
// stlport
// STLport 4.5.3 num_get<char, istreambuf_iterator<char>>::do_get(bool&).
// The vtable at 0x0112E97C identifies the narrow num_get overload slot;
// The vtable overloads are declared in STLport source order; MSVC 7.1 lays
// this virtual family out in reverse declaration order, putting bool at +0x2c.

#include "stlport_prefix.h"
#include <stl/_string.h>
#include <stl/_ios.h>
#include <stl/_locale.h>
#include <stl/_numpunct.h>

class BfmeThingSG
{
public:
	void bfmeGoSG();
};

namespace _STL
{

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

class Rva0001F433Streambuf
{
public:
	int sbumpc();
};

#pragma comment(linker, "/alternatename:?sbumpc@Rva0001F433Streambuf@_STL@@QAEHXZ=?j_0001f433@@YAXXZ")

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
		((Rva0001F433Streambuf *)m_buf)->sbumpc();
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
			BfmeInlineLocale loc = ((BfmeIosLocaleView &)str).getloc();
			const numpunct<CharT> &punct =
				*(const numpunct<CharT> *)str._M_numpunct_facet();
			const basic_string<CharT> truename = punct.truename();
			const basic_string<CharT> falsename = punct.falsename();

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
	virtual InputIter do_get(InputIter in, InputIter end, ios_base &str,
		ios_base::iostate &err, unsigned short &value) const;
	virtual InputIter do_get(InputIter in, InputIter end, ios_base &str,
		ios_base::iostate &err, unsigned int &value) const;
	virtual InputIter do_get(InputIter in, InputIter end, ios_base &str,
		ios_base::iostate &err, unsigned long &value) const;
	virtual InputIter do_get(InputIter in, InputIter end, ios_base &str,
		ios_base::iostate &err, float &value) const;
	virtual InputIter do_get(InputIter in, InputIter end, ios_base &str,
		ios_base::iostate &err, double &value) const;
	virtual InputIter do_get(InputIter in, InputIter end, ios_base &str,
		ios_base::iostate &err, void *&value) const;
	virtual InputIter do_get(InputIter in, InputIter end, ios_base &str,
		ios_base::iostate &err, long double &value) const;
	virtual InputIter do_get(InputIter in, InputIter end, ios_base &str,
		ios_base::iostate &err, __int64 &value) const;
	virtual InputIter do_get(InputIter in, InputIter end, ios_base &str,
		ios_base::iostate &err, unsigned __int64 &value) const;
};

typedef istreambuf_iterator<char, char_traits<char> > NarrowIterator;
template class num_get<char, NarrowIterator>;

} // namespace _STL
