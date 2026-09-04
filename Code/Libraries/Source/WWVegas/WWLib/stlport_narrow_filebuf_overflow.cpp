// cl: /O2 /EHsc /MD
// stlport

// Open-BFME5: _STL::basic_filebuf<char>::overflow @ 0x00843270 (297B)
// STLport 4.5.3 basic_filebuf<char>::overflow (stl/_fstream.c).

namespace _STL {

class codecvt {
public:
	enum result { ok, partial, error, noconv };

	virtual ~codecvt() {}

	result out(int &state,
		const char *from, const char *from_end, const char *&from_next,
		char *to, char *to_end, char *&to_next) const
	{
		return do_out(state, from, from_end, from_next, to, to_end, to_next);
	}

protected:
	virtual result do_out(int &state,
		const char *from, const char *from_end, const char *&from_next,
		char *to, char *to_end, char *&to_next) const = 0;
};

template <class CharT> class char_traits {};

template <>
class char_traits<char> {
	public:
	typedef int int_type;
	static int_type eof() { return -1; }
	static int_type not_eof(int_type c) { return c == -1 ? 0 : c; }
	static int eq_int_type(int_type a, int_type b) { return a == b; }
	static char to_char_type(int_type c) { return (char)c; }
};

class _Filebuf_base {
public:
	bool _M_write(char *buf, int n);

private:
	void *_M_file_id;
	void *_M_view_id;
	int _M_openmode;
	unsigned char _M_is_open;
	unsigned char _M_should_close;
	unsigned char _M_regular_file;
	unsigned char _M_pad;
};

struct BfmeFileBuf {
	char *ptr;
	int cnt;
	char *base;
};

inline char *_FILE_I_begin(BfmeFileBuf *f) { return f->base; }
inline char *_FILE_I_next(BfmeFileBuf *f) { return f->ptr; }
inline char *_FILE_I_end(BfmeFileBuf *f) { return f->ptr + f->cnt; }
inline int _FILE_I_avail(BfmeFileBuf *f) { return f->cnt; }
inline void _FILE_I_set(BfmeFileBuf *f, char *begin, char *next, char *end)
{
	f->base = begin;
	f->ptr = next;
	f->cnt = (int)(end - next);
}

class basic_streambuf {
public:
	virtual ~basic_streambuf() {}

protected:
	void *_M_locale;
	BfmeFileBuf *_M_put;
	char _M_sb_pad[0x54 - 0x0C];
};

template <class CharT, class Traits>
class basic_filebuf {};

template <>
class basic_filebuf<char, char_traits<char> > : public basic_streambuf {
public:
	typedef char_traits<char> traits_type;
	typedef traits_type::int_type int_type;

protected:
	virtual int_type overflow(int_type c);

	private:
	bool _M_switch_to_output_mode();
	int_type _M_output_error();

private:
	_Filebuf_base _M_base;
	unsigned char _M_constant_width;
	unsigned char _M_always_noconv;
	unsigned char _M_int_buf_dynamic;
	unsigned char _M_in_input_mode;
	unsigned char _M_in_output_mode;
	unsigned char _M_in_error_mode;
	unsigned char _M_in_putback_mode;
	unsigned char _M_pad_mode;
	char *_M_int_buf;
	char *_M_int_buf_EOS;
	char *_M_ext_buf;
	char *_M_ext_buf_EOS;
	char *_M_ext_buf_converted;
	char *_M_ext_buf_end;
	int _M_state;
	int _M_end_state;
	void *_M_mmap_base;
	int _M_mmap_len;
	char *_M_saved_eback;
	char *_M_saved_gptr;
	char *_M_saved_egptr;
	const codecvt *_M_codecvt;
	int _M_width;
	int _M_max_width;
	char _M_pback_buf[8];

};

basic_filebuf<char, char_traits<char> >::int_type
basic_filebuf<char, char_traits<char> >::overflow(int_type c)
{
	if (!_M_in_output_mode)
		if (!_M_switch_to_output_mode())
			return traits_type::eof();

	char *ibegin = _M_int_buf;
	char *iend = _FILE_I_next(_M_put);
	_FILE_I_set(_M_put, ibegin, ibegin, _M_int_buf_EOS - 1);
	if (!traits_type::eq_int_type(c, traits_type::eof()))
		*iend++ = c;

	while (ibegin != iend) {
		const char *inext = ibegin;
		char *enext = _M_ext_buf;
		codecvt::result status = _M_codecvt->out(_M_state, ibegin, iend, inext,
			_M_ext_buf, _M_ext_buf_EOS, enext);
		if (status == codecvt::noconv) {
			return _M_base._M_write(ibegin, (int)(iend - ibegin))
				? traits_type::not_eof(c)
				: _M_output_error();
		}
		else if (status != codecvt::error &&
			(((inext == iend) &&
				 (enext - _M_ext_buf == _M_width * (int)(iend - ibegin))) ||
				(!_M_constant_width && inext != ibegin))) {
			int n = (int)(enext - _M_ext_buf);
			if (_M_base._M_write(_M_ext_buf, n))
				ibegin += inext - ibegin;
			else
				return _M_output_error();
		}
		else
			return _M_output_error();
	}

	return traits_type::not_eof(c);
}

} // namespace _STL
