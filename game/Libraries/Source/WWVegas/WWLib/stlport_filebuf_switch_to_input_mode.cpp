// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: _STL::basic_filebuf<wchar>::_M_switch_to_input_mode, retail
// 0x00843680, 96 bytes. The body carried only a machine byte-dump row;
// targets/game/reverse/reloc_names.csv holds the name with identity=real.
//
// The offsets confirm the layout STLport's own header describes and the
// _Filebuf_base constructor at 0x00849F40 already fixed: _M_base sits at
// basic_filebuf+0x24, so its openmode lands at +0x2C and its open flag at
// +0x30. Past it are the three mode flags at +0x37, +0x38 and +0x39, the
// internal buffer at +0x3C, the external buffer at +0x44 with its converted
// and end cursors at +0x4C and +0x50, and the two conversion states at +0x54
// and +0x58.
//
// The no-argument _M_allocate_buffers folds in rather than being called: the
// page size is read once into a register and rounded up with the
// ((page + 4095) / page) * page that STLport spells out, then handed to the
// two-argument form with a null buffer. The __forceinline is a shaping lever,
// not evidence: at this project's optimisation level MSVC leaves the helper
// out of line, and the twenty-four bytes it would cost are exactly the gap.
//
// The buffer size is an int rather than a long: the ledger already pins the
// two-argument helper at 0x008420B0 under a name whose second parameter is H.

namespace _STL
{

template <class CharT>
class char_traits {};

class _Filebuf_base
{
public:
	bool __is_open(void) const { return _M_is_open != 0; }
	int __o_mode(void) const { return (int)_M_openmode; }
	static unsigned int __page_size(void) { return _M_page_size; }

protected:
	static unsigned int _M_page_size;			// 0x012C7ED0

	void *_M_file_id;					// +0x00
	void *_M_view_id;					// +0x04
	int _M_openmode;					// +0x08
	unsigned char _M_is_open;				// +0x0C
	unsigned char _M_should_close;				// +0x0D
	unsigned char _M_regular_file;				// +0x0E
};

enum { bfme_ios_base_in = 8 };

template <class CharT, class Traits>
class basic_filebuf
{
public:
	bool is_open(void) const { return _M_base.__is_open(); }

private:
	bool _M_switch_to_input_mode(void);
	bool _M_allocate_buffers(CharT *buf, int n);
	bool _M_allocate_buffers(void);

	char m_bfmeStreambuf[0x24];
	_Filebuf_base _M_base;					// +0x24
	char m_bfmePad0[0x37 - 0x34];
	unsigned char _M_in_input_mode;				// +0x37
	unsigned char _M_in_output_mode;			// +0x38
	unsigned char _M_in_error_mode;				// +0x39
	char m_bfmePad1[0x3C - 0x3A];
	CharT *_M_int_buf;					// +0x3C
	char m_bfmePad2[0x44 - 0x40];
	char *_M_ext_buf;					// +0x44
	char m_bfmePad3[0x4C - 0x48];
	char *_M_ext_buf_converted;				// +0x4C
	char *_M_ext_buf_end;					// +0x50
	int _M_state;						// +0x54
	int _M_end_state;					// +0x58
};

template <class CharT, class Traits>
__forceinline bool basic_filebuf<CharT, Traits>::_M_allocate_buffers(void)
{
	// Choose a buffer that's at least 4096 characters long and that's a
	// multiple of the page size.
	int defaultBufsiz = (int)
		(((_Filebuf_base::__page_size() + 4095UL) / _Filebuf_base::__page_size())
			* _Filebuf_base::__page_size());
	return _M_allocate_buffers(0, defaultBufsiz);
}

// ?_M_switch_to_input_mode@?$basic_filebuf@GV?$char_traits@G@_STL@@@_STL@@AAE_NXZ
template <class CharT, class Traits>
bool basic_filebuf<CharT, Traits>::_M_switch_to_input_mode(void)
{
	if (is_open() && ((_M_base.__o_mode() & bfme_ios_base_in) != 0)
		&& (_M_in_output_mode == 0) && (_M_in_error_mode == 0))
	{
		if (!_M_int_buf && !_M_allocate_buffers())
			return false;

		_M_ext_buf_converted = _M_ext_buf;
		_M_ext_buf_end = _M_ext_buf;

		_M_end_state = _M_state;

		_M_in_input_mode = true;
		return true;
	}
	else
		return false;
}

template bool basic_filebuf<unsigned short, char_traits<unsigned short> >::_M_switch_to_input_mode(void);

}
