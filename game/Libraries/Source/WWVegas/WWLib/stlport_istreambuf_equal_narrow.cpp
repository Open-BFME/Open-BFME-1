// cl: /O2 /MD

// Open-BFME5: _STL::istreambuf_iterator<char>::equal, retail 0x00838820, 126 bytes.
// Fully inlines _M_getc on both sides (buffer peek or sgetc at vtable+0x1C),
// then compares eof flags via setz-style equality.

namespace _STL
{

template <class CharT>
class char_traits {};

template <class CharT, class Traits>
class basic_streambuf
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual int sgetc();					// vtable +0x1C
};

struct BfmeSbPointers
{
	char *gptr;
	int remaining;
};

template <class CharT, class Traits>
class istreambuf_iterator
{
public:
	bool equal(const istreambuf_iterator &other) const;

private:
	basic_streambuf<CharT, Traits> *_M_buf;			// +0x00
	mutable CharT _M_c;					// +0x04
	mutable unsigned char _M_eof;				// +0x05
	mutable unsigned char _M_have_c;			// +0x06
};

template <class CharT, class Traits>
bool istreambuf_iterator<CharT, Traits>::equal(const istreambuf_iterator &other) const
{
	if (_M_buf)
	{
		if (!_M_have_c)
		{
			basic_streambuf<CharT, Traits> *buf = _M_buf;
			BfmeSbPointers *ptrs = *(BfmeSbPointers **)((char *)buf + 4);
			int c;
			if (ptrs->remaining > 0)
				c = (unsigned char)*ptrs->gptr;
			else
				c = buf->sgetc();
			_M_c = (CharT)c;
			_M_eof = (unsigned char)(c == -1);
			_M_have_c = 1;
		}
	}
	if (other._M_buf)
	{
		if (!other._M_have_c)
		{
			basic_streambuf<CharT, Traits> *buf = other._M_buf;
			BfmeSbPointers *ptrs = *(BfmeSbPointers **)((char *)buf + 4);
			int c;
			if (ptrs->remaining > 0)
				c = (unsigned char)*ptrs->gptr;
			else
				c = buf->sgetc();
			other._M_c = (CharT)c;
			other._M_eof = (unsigned char)(c == -1);
			other._M_have_c = 1;
		}
	}
	return _M_eof == other._M_eof;
}

template bool istreambuf_iterator<char, char_traits<char> >::equal(
	const istreambuf_iterator<char, char_traits<char> > &) const;

}
