// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: _STL::basic_filebuf<wchar>::_M_allocate_buffers, retail
// 0x008420B0, 188 bytes. The body carried only a machine byte-dump row;
// targets/game/reverse/reloc_names.csv holds the name with identity=real. It is also the
// callee _M_switch_to_input_mode at 0x00843680 folds its no-argument sibling
// into, so the two bodies now meet.
//
// The offsets extend the layout that body already fixed: the internal buffer
// at +0x3C with its dynamic flag at +0x36 and its end at +0x40, the external
// buffer at +0x44 with its end at +0x48, and the codecvt at +0x70.
//
// The external size is max(n * max(encoding(), 1), max_length()), and both
// STLport maxes are the reference-returning kind: the body stores each
// candidate to the stack and selects an address with lea, rather than moving
// values. max_length() -- virtual slot 0x1C -- is called before encoding() at
// slot 0x10, which is the argument order of the outer max.
//
// malloc is loaded from the import table once, into ebx, and used for both
// allocations.

extern "C" __declspec(dllimport) void *__cdecl malloc(unsigned int size);

namespace _STL
{

template <class T>
class char_traits {};

class _Filebuf_base
{
protected:
	void *_M_file_id;					// +0x00
	void *_M_view_id;					// +0x04
	int _M_openmode;					// +0x08
	unsigned char _M_is_open;				// +0x0C
	unsigned char _M_should_close;				// +0x0D
	unsigned char _M_regular_file;				// +0x0E
};

class BfmeCodecvt
{
public:
	virtual void _bfme_slot0(void) = 0;
	virtual void _bfme_slot1(void) = 0;
	virtual void _bfme_slot2(void) = 0;
	virtual void _bfme_slot3(void) = 0;
	virtual int encoding(void) const = 0;			// slot 4, +0x10
	virtual void _bfme_slot5(void) = 0;
	virtual void _bfme_slot6(void) = 0;
	virtual int max_length(void) const = 0;			// slot 7, +0x1C
};

template <class T>
inline const T &max(const T &a, const T &b)
{
	return a < b ? b : a;
}

template <class CharT, class Traits>
class basic_filebuf
{
private:
	bool _M_allocate_buffers(CharT *buf, int n);

	void _M_deallocate_buffers(void);			// retail 0x00842170

	char m_bfmeStreambuf[0x24];
	_Filebuf_base _M_base;					// +0x24
	char m_bfmePad0[0x36 - 0x34];
	unsigned char _M_int_buf_dynamic;			// +0x36
	unsigned char _M_in_input_mode;				// +0x37
	unsigned char _M_in_output_mode;			// +0x38
	unsigned char _M_in_error_mode;				// +0x39
	char m_bfmePad1[0x3C - 0x3A];
	CharT *_M_int_buf;					// +0x3C
	CharT *_M_int_buf_EOS;					// +0x40
	char *_M_ext_buf;					// +0x44
	char *_M_ext_buf_EOS;					// +0x48
	char m_bfmePad2[0x70 - 0x4C];
	BfmeCodecvt *_M_codecvt;				// +0x70
};

// ?_M_allocate_buffers@?$basic_filebuf@GV?$char_traits@G@_STL@@@_STL@@AAE_NPAGH@Z
template <class CharT, class Traits>
bool basic_filebuf<CharT, Traits>::_M_allocate_buffers(CharT *buf, int n)
{
	if (buf == 0)
	{
		_M_int_buf = (CharT *)malloc(n * sizeof(CharT));
		if (!_M_int_buf)
			return false;
		_M_int_buf_dynamic = true;
	}
	else
	{
		_M_int_buf = buf;
		_M_int_buf_dynamic = false;
	}

	unsigned int ebufsiz = (max)(n * (max)(_M_codecvt->encoding(), 1),
		(int)_M_codecvt->max_length());

	_M_ext_buf = (char *)malloc(ebufsiz);
	if (!_M_ext_buf)
	{
		_M_deallocate_buffers();
		return false;
	}

	_M_int_buf_EOS = _M_int_buf + n;
	_M_ext_buf_EOS = _M_ext_buf + ebufsiz;
	return true;
}

template bool basic_filebuf<unsigned short, char_traits<unsigned short> >::_M_allocate_buffers(unsigned short *, int);

}
