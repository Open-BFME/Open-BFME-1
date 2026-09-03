// cl: /DNDEBUG /MD /EHsc

namespace _STL
{

class ios_base
{
public:
	enum seekdir { beg = 1, cur = 2, end = 4 };
};

class _Filebuf_base
{
public:
	long _M_seek(long offset, int dir);
	long _M_file_size(void);
	bool __is_open(void) const { return _M_is_open != 0; }

private:
	char m_pad[0x0C];
	unsigned char _M_is_open;
	char m_pad_end[3];
};

template <class CharT>
class char_traits {};

template <class CharT, class Traits>
class basic_filebuf
{
protected:
	virtual long showmanyc(void);

	CharT *gptr(void) const { return _M_gptr; }
	CharT *egptr(void) const { return _M_egptr; }
	bool is_open(void) const { return _M_base.__is_open(); }

private:
	CharT *m_eback;					// +0x04 after vptr
	CharT *_M_gptr;					// +0x08
	CharT *_M_egptr;				// +0x0c
	char m_streambuf_rest[0x24 - 0x10];
	_Filebuf_base _M_base;				// +0x24
	unsigned char _M_constant_width;		// +0x34
	unsigned char _M_always_noconv;			// +0x35
	unsigned char _M_int_buf_dynamic;		// +0x36
	unsigned char _M_in_input_mode;			// +0x37
	unsigned char _M_in_output_mode;		// +0x38
	unsigned char _M_in_error_mode;			// +0x39
	unsigned char _M_in_putback_mode;		// +0x3a
};

template <class CharT, class Traits>
long basic_filebuf<CharT, Traits>::showmanyc(void)
{
	if (!this->is_open() || _M_in_output_mode || _M_in_error_mode)
		return -1;
	else if (_M_in_putback_mode)
		return this->egptr() - this->gptr();
	else if (_M_constant_width) {
		long pos = _M_base._M_seek(0, ios_base::cur);
		long size = _M_base._M_file_size();
		return pos >= 0 && size > pos ? size - pos : 0;
	}
	else
		return 0;
}

template long basic_filebuf<unsigned short, char_traits<unsigned short> >::showmanyc(void);

}
