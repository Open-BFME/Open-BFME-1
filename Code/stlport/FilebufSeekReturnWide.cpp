// cl: /O2 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
// STLport 4.5.3 basic_filebuf<unsigned short>::_M_seek_return — inline get/put slots.

typedef int mbstate_t;

namespace _STL {

template <class T> class char_traits {};
template <class StateT> class fpos
{
public:
	fpos(long off = 0) : _Off(off), _State(0) {}
	void state(mbstate_t s) { _State = s; }
	mbstate_t state() const { return _State; }
	long _Off;
	mbstate_t _State;
};

template <class CharT, class Traits>
class basic_filebuf
{
private:
	fpos<mbstate_t> _M_seek_return(long off, mbstate_t state);

	void _M_exit_input_mode();

	void *m_vptr;
	CharT *m_eback;
	CharT *m_gptr;
	CharT *m_egptr;
	CharT *m_pbase;
	CharT *m_pptr;
	CharT *m_epptr;
	char m_pad[0x37 - 0x1C];
	volatile unsigned char _M_in_input_mode;
	volatile unsigned char _M_in_output_mode;
	volatile unsigned char _M_in_error_mode;
	volatile unsigned char _M_in_putback_mode;
};

template <class CharT, class Traits>
fpos<mbstate_t> basic_filebuf<CharT, Traits>::_M_seek_return(long off, mbstate_t state)
{
	if (off != -1)
	{
		if (_M_in_input_mode)
			_M_exit_input_mode();
		_M_in_input_mode = 0;
		_M_in_output_mode = 0;
		_M_in_putback_mode = 0;
		_M_in_error_mode = 0;
		m_eback = 0;
		m_gptr = 0;
		m_egptr = 0;
		m_pbase = 0;
		m_pptr = 0;
		m_epptr = 0;
	}
	fpos<mbstate_t> result(off);
	result.state(state);
	return result;
}

template fpos<mbstate_t>
basic_filebuf<unsigned short, char_traits<unsigned short> >::_M_seek_return(long, mbstate_t);

} // namespace _STL
