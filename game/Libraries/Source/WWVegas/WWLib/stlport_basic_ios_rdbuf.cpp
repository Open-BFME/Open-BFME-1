// cl: /O2 /MD

// _STL::basic_ios<char>::rdbuf(basic_streambuf *), retail 0x00538A30, 39 bytes.
// STLport 4.5.3 (stl/_ios.c): swap _M_streambuf, then the inline clear()
// sets _M_iostate to goodbit or badbit and tests the exception mask, whose
// no-exception _M_throw_failure is the fputs("ios failure", stderr) body at
// 0x0083E8F0. Identity: the matched STLport ios_base::sync_with_stdio calls it
// on cin/cout/cerr/clog through ILT 0x00031FE3 with the new streambufs.
// Previously held under the placeholder name BfmeThingVIM::bfmeSetVIM.

namespace _STL
{

class ios_base
{
public:
	enum { goodbit = 0, badbit = 1 };

protected:
	void _M_throw_failure();
	void _M_clear_nothrow(int state) { _M_iostate = state; }
	void _M_check_exception_mask()
	{
		if (_M_iostate & _M_exception_mask)
			_M_throw_failure();
	}

	void *m_vtable;						// +0x00
	int _M_fmtflags;					// +0x04
	int _M_iostate;						// +0x08
	int _M_openmode;					// +0x0C
	int _M_seekdir;						// +0x10
	int _M_exception_mask;					// +0x14
	char m_bfmePad[0x54 - 0x18];
};

template <class T>
class char_traits {};

template <class CharT, class Traits>
class basic_streambuf;

template <class CharT, class Traits>
class basic_ios : public ios_base
{
public:
	basic_streambuf<CharT, Traits> *rdbuf() const { return _M_streambuf; }
	basic_streambuf<CharT, Traits> *rdbuf(basic_streambuf<CharT, Traits> *buf);
	void clear(int state = goodbit)
	{
		_M_clear_nothrow(this->rdbuf() ? state : (state | badbit));
		_M_check_exception_mask();
	}

private:
	CharT _M_fill;						// +0x54
	basic_streambuf<CharT, Traits> *_M_streambuf;		// +0x58
	void *_M_tied_ostream;					// +0x5C
};

template <class CharT, class Traits>
basic_streambuf<CharT, Traits> *basic_ios<CharT, Traits>::rdbuf(basic_streambuf<CharT, Traits> *buf)
{
	basic_streambuf<CharT, Traits> *tmp = _M_streambuf;
	_M_streambuf = buf;
	this->clear();
	return tmp;
}

template basic_streambuf<char, char_traits<char> > *basic_ios<char, char_traits<char> >::rdbuf(basic_streambuf<char, char_traits<char> > *);

}
