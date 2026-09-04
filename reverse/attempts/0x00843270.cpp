// ?overflow@?$basic_filebuf@DU?$char_traits@D@_STL@@@_STL@@MAEHH@Z
// partial score=0.92 date=2026-09-04
// ?overflow@?$basic_filebuf@DU?$char_traits@D@_STL@@@_STL@@MAEHH@Z
// partial score=0.92 date=2026-09-03
// cl: /O2 /EHsc /MD
// stlport
// STLport 4.5.3 basic_filebuf<char>::overflow (stl/_fstream.c).
// probe 297/297 register-mirror: eax=EOS/ecx=Area vs ours ecx=EOS/eax=Area
// through setp; tail from +0x3F exact. TU-flag wall per lessons.md.

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

template <class CharT> struct char_traits {};

template <>
struct char_traits<char> {
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

class basic_streambuf {
public:
	virtual ~basic_streambuf() {}

protected:
	struct Area {
		char *next;
		int n;
		char *base;
	};

	void *_M_locale;
	Area *_M_put;
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

	char *eos = _M_int_buf_EOS;
	Area *area = _M_put;
	char *iend = area->next;
	--eos;
	char *ibegin = _M_int_buf;
	area->n = eos - ibegin;
	area->base = ibegin;
	area->next = ibegin;
	if (c != traits_type::eof())
		*iend++ = traits_type::to_char_type(c);

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
