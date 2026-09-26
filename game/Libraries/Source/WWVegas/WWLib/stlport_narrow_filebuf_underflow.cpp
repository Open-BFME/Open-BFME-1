// cl: /O2 /EHsc /MD
// stlport

#include <algorithm>

namespace _STL
{

template <class T>
class char_traits;

template <>
class char_traits<char>
{
public:
	typedef int int_type;

	static int_type eof() { return -1; }
	static int_type to_int_type(const char &c) { return (unsigned char)c; }
};

struct Rva0084B080GetArea
{
	char *ptr;
	int count;
	char *base;
};

class _Filebuf_base
{
private:
	void *m_file;
	void *m_view;
	int m_mode;
	unsigned char m_open;
	unsigned char m_close;
	unsigned char m_regular;
	unsigned char m_pad;

public:
	int _M_read(char *buf, int n);
};

template <class CharT, class Traits>
class basic_streambuf
{
private:
	char m_pad0[4];
	Rva0084B080GetArea *m_get_area;
	char m_pad1[0x54 - 8];

protected:
	void setg(char *begin, char *next, char *end)
	{
		Rva0084B080GetArea *area = m_get_area;
		area->base = begin;
		area->ptr = next;
		area->count = end - next;
	}
};

class codecvt
{
public:
	enum result { ok, partial, error, noconv };

	virtual ~codecvt() {}
	virtual result do_out(int &, const char *, const char *, const char *&, char *, char *, char *&) const = 0;
	virtual result do_in(int &, const char *, const char *, const char *&, char *, char *, char *&) const = 0;

	result in(int &state, const char *from, const char *from_end, const char *&from_next,
		char *to, char *to_end, char *&to_next) const
	{
		return do_in(state, from, from_end, from_next, to, to_end, to_next);
	}
};

template <class CharT, class Traits>
class basic_filebuf : public basic_streambuf<CharT, Traits>
{
private:
	_Filebuf_base m_base;
	unsigned char m_constant_width;
	unsigned char m_always_noconv;
	unsigned char m_int_buf_dynamic;
	unsigned char m_in_input_mode;
	unsigned char m_in_output_mode;
	unsigned char m_in_error_mode;
	unsigned char m_in_putback_mode;
	unsigned char m_pad_mode;
	CharT *m_int_buf;
	CharT *m_int_buf_EOS;
	char *m_ext_buf;
	char *m_ext_buf_EOS;
	char *m_ext_buf_converted;
	char *m_ext_buf_end;
	int m_state;
	int m_end_state;
	void *m_mmap_base;
	int m_mmap_len;
	CharT *m_saved_eback;
	CharT *m_saved_gptr;
	CharT *m_saved_egptr;
	const codecvt *m_codecvt;
	int m_width;
	int m_max_width;
	CharT m_pback_buf[8];

	int _M_input_error();
	int _M_underflow_aux();
};

template <class CharT, class Traits>
int basic_filebuf<CharT, Traits>::_M_underflow_aux()
{
	m_state = m_end_state;

	if (m_ext_buf_end > m_ext_buf_converted)
		m_ext_buf_end = copy(m_ext_buf_converted, m_ext_buf_end, m_ext_buf);
	else
		m_ext_buf_end = m_ext_buf;

	while (true)
	{
		int n = m_base._M_read(m_ext_buf_end, m_ext_buf_EOS - m_ext_buf_end);
		if (n <= 0)
			return Traits::eof();

		m_ext_buf_end += n;
		const char *enext;
		CharT *inext;
		codecvt::result status = m_codecvt->in(m_end_state,
			m_ext_buf, m_ext_buf_end, enext,
			m_int_buf, m_int_buf_EOS, inext);

		if (status == codecvt::noconv)
		{
			m_ext_buf_converted = m_ext_buf_end;
			this->setg(m_ext_buf, m_ext_buf, m_ext_buf_end);
			return Traits::to_int_type(*m_ext_buf);
		}

		if (status == codecvt::error ||
			(inext != m_int_buf && enext == m_ext_buf) ||
			(m_constant_width &&
				(inext - m_int_buf) * m_width != enext - m_ext_buf) ||
			(inext == m_int_buf && enext - m_ext_buf >= m_max_width))
			return _M_input_error();

		if (inext != m_int_buf)
		{
			m_ext_buf_converted = m_ext_buf + (enext - m_ext_buf);
			this->setg(m_int_buf, m_int_buf, inext);
			return Traits::to_int_type(*m_int_buf);
		}
	}
}

template int basic_filebuf<char, char_traits<char> >::_M_underflow_aux();

}
