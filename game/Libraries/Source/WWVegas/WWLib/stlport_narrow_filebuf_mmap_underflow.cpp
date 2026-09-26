// cl: /O2 /EHsc /MD
// stlport

// STLport 4.5.3 specialized narrow-file underflow helper, retail 0x0084B210.

#include <windows.h>

typedef long streamoff;

namespace _STL
{

class ios_base
{
public:
	 enum seekdir { beg = 0, cur = 1, end = 2 };
};

template <class CharT>
class char_traits;

template <>
class char_traits<char>
{
public:
	typedef int int_type;

	static int_type eof() { return -1; }
	static int_type to_int_type(const char &c) { return (unsigned char)c; }
};

struct Rva0084B210GetArea
{
	typedef char *_File_ptr_type;
	_File_ptr_type _ptr;
	int _cnt;
	_File_ptr_type _base;
};

inline char *_FILE_I_begin(const Rva0084B210GetArea *file)
{
	return (char *)file->_base;
}

inline char *_FILE_I_next(const Rva0084B210GetArea *file)
{
	return (char *)file->_ptr;
}

inline char *_FILE_I_end(const Rva0084B210GetArea *file)
{
	return (char *)file->_ptr + file->_cnt;
}

inline void _FILE_I_set(Rva0084B210GetArea *file, char *begin,
	char *next, char *end)
{
	file->_base = (Rva0084B210GetArea::_File_ptr_type)begin;
	file->_ptr = (Rva0084B210GetArea::_File_ptr_type)next;
	file->_cnt = end - next;
}

class _Filebuf_base
{
public:
	bool __regular_file(void) const { return m_regular_file != 0; }
	bool _M_in_binary_mode(void) const { return (m_openmode & 4) != 0; }
	static unsigned int __page_size(void) { return _M_page_size; }

	streamoff _M_seek(streamoff offset, ios_base::seekdir dir)
	{
		streamoff result = -1;
		int whence;

		switch (dir)
		{
		case ios_base::beg:
			if (offset < 0)
				return streamoff(-1);
			whence = FILE_BEGIN;
			break;
		case ios_base::cur:
			whence = FILE_CURRENT;
			break;
		case ios_base::end:
			if (-offset > _M_file_size())
				return streamoff(-1);
			whence = FILE_END;
			break;
		default:
			return streamoff(-1);
		}

		LARGE_INTEGER li;
		li.QuadPart = offset;
		li.LowPart = SetFilePointer(_M_file_id, li.LowPart, &li.HighPart, whence);
		if (li.LowPart == (DWORD)-1 && GetLastError() != 0)
			result = -1;
		else
			result = li.QuadPart;

		return result;
	}

	void _M_unmap(void *base, long len);
	long _M_file_size(void);
	void *_M_mmap(streamoff offset, streamoff len);

private:
	void *_M_file_id;
	void *_M_view_id;
	int m_openmode;
	unsigned char m_is_open;
	unsigned char m_should_close;
	unsigned char m_regular_file;
	unsigned char m_pad;

	static unsigned int _M_page_size;
};

template <class CharT, class Traits>
class basic_streambuf
{
	private:
	char m_pad0[4];
	Rva0084B210GetArea *m_get;
	Rva0084B210GetArea *m_put;
	char m_pad[0x54 - 0x0c];

	protected:
	void setg(char *begin, char *next, char *end)
	{
		_FILE_I_set(m_get, begin, next, end);
	}

	char *gptr(void) const { return _FILE_I_next(m_get); }
	char *egptr(void) const { return _FILE_I_end(m_get); }
};

template <class CharT, class Traits>
class _Underflow;

template <class CharT, class Traits>
class basic_filebuf;

template <>
class _Underflow<char, char_traits<char> >
{
public:
	typedef char_traits<char>::int_type int_type;
	typedef char_traits<char> traits_type;

	static int _M_doit(basic_filebuf<char, traits_type> *self);
};

template <class CharT, class Traits>
class basic_filebuf : public basic_streambuf<CharT, Traits>
{
public:
	typedef basic_streambuf<CharT, Traits> streambuf_type;

private:
	friend class _Underflow<CharT, Traits>;

	_Filebuf_base _M_base;
	unsigned char _M_constant_width;
	unsigned char _M_always_noconv;
	unsigned char _M_int_buf_dynamic;
	unsigned char _M_in_input_mode;
	unsigned char _M_in_output_mode;
	unsigned char _M_in_error_mode;
	unsigned char _M_in_putback_mode;
	unsigned char _M_pad_mode;
	CharT *_M_int_buf;
	CharT *_M_int_buf_EOS;
	char *_M_ext_buf;
	char *_M_ext_buf_EOS;
	char *_M_ext_buf_converted;
	char *_M_ext_buf_end;
	int _M_state;
	int _M_end_state;
	void *_M_mmap_base;
	int _M_mmap_len;
	CharT *_M_saved_eback;
	CharT *_M_saved_gptr;
	CharT *_M_saved_egptr;
	void *_M_codecvt;
	int _M_width;
	int _M_max_width;
	CharT _M_pback_buf[8];

	bool _M_switch_to_input_mode(void);
	int _M_underflow_aux(void);

	void _M_exit_putback_mode(void)
	{
		this->setg((char *)_M_saved_eback, (char *)_M_saved_gptr,
			(char *)_M_saved_egptr);
		_M_in_putback_mode = false;
	}
};

// ?_M_doit@?$_Underflow@DV?$char_traits@D@_STL@@@_STL@@SAGPAV?$basic_filebuf@DV?$char_traits@D@_STL@@@2@@Z
#define MMAP_CHUNK 0x100000UL

int _Underflow<char, char_traits<char> >::_M_doit(
	basic_filebuf<char, char_traits<char> > *self)
{
	typedef char_traits<char> traits_type;
	typedef traits_type::int_type int_type;

	if (!self->_M_in_input_mode) {
		if (!self->_M_switch_to_input_mode())
			return traits_type::eof();
	}
	else if (self->_M_in_putback_mode) {
		self->_M_exit_putback_mode();
		if (self->gptr() != self->egptr()) {
			int_type c = traits_type::to_int_type(*self->gptr());
			return c;
		}
	}

	if (self->_M_base.__regular_file()
		&& self->_M_always_noconv
		&& self->_M_base._M_in_binary_mode()) {
		if (self->_M_mmap_base)
			self->_M_base._M_unmap(self->_M_mmap_base, self->_M_mmap_len);
		self->_M_mmap_base = 0;
		self->_M_mmap_len = 0;

		streamoff cur = self->_M_base._M_seek(0, ios_base::cur);
		streamoff size = self->_M_base._M_file_size();
		if (size > 0 && cur >= 0 && cur < size) {
			unsigned int page_size = self->_M_base.__page_size();
			streamoff offset = (cur / page_size) * page_size;
			streamoff remainder = cur - offset;

			self->_M_mmap_len = size - offset;
			if (self->_M_mmap_len > MMAP_CHUNK)
				self->_M_mmap_len = MMAP_CHUNK;

			if ((self->_M_mmap_base = self->_M_base._M_mmap(
				offset, self->_M_mmap_len)) != 0) {
				self->setg((char *)self->_M_mmap_base,
					(char *)self->_M_mmap_base + (int)remainder,
					(char *)self->_M_mmap_base + self->_M_mmap_len);
				return traits_type::to_int_type(*self->gptr());
			}
		}
		else {
			self->_M_mmap_base = 0;
			self->_M_mmap_len = 0;
		}
	}

	return self->_M_underflow_aux();
}

}
