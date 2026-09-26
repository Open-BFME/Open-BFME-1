// cl: /O2 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
// STLport 4.5.3 basic_filebuf<char>::_M_seek_return with outlined exit.

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

struct Rva00841B90GetArea
{
	char *eback;
	char *gptr;
	char *egptr;
};

struct Rva00841B90PutArea
{
	char *pbase;
	char *pptr;
	char *epptr;
};

template <class CharT, class Traits>
class basic_filebuf
{
private:
	fpos<mbstate_t> _M_seek_return(long off, mbstate_t state);

	void _M_exit_input_mode();

	void *m_vptr;
	Rva00841B90GetArea * volatile m_get;
	Rva00841B90PutArea * volatile m_put;
	char m_pad[0x67 - 0x0C];
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
		// Retail loads get-area into eax BEFORE clearing the four mode flags.
		Rva00841B90GetArea *get = m_get;
		_M_in_input_mode = 0;
		_M_in_output_mode = 0;
		_M_in_putback_mode = 0;
		_M_in_error_mode = 0;
		get->egptr = 0;
		get->eback = 0;
		get->gptr = 0;
		Rva00841B90PutArea *put = m_put;
		put->epptr = 0;
		put->pbase = 0;
		put->pptr = 0;
	}
	fpos<mbstate_t> result(off);
	result.state(state);
	return result;
}

template fpos<mbstate_t>
basic_filebuf<char, char_traits<char> >::_M_seek_return(long, mbstate_t);

} // namespace _STL
