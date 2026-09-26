// cl: /O2 /Ob0 /MD

// Open-BFME5: _STL::basic_ios<char>::copyfmt, retail 0x0083F5A0, 107 bytes.
// STLport 4.5.3 walks the callback array backwards with erase_event, copies
// ios_base state plus fill and tie, walks it again with copyfmt_event, then
// copies the exception mask.

namespace _STL
{

class ios_base
{
public:
	enum event { erase_event = 0, imbue_event = 1, copyfmt_event = 2 };
	typedef void (*event_callback)(event, ios_base &, int);

protected:
	void _M_copy_state(const ios_base &x);
	virtual void handle();

	int _M_fmtflags;					// +0x04
	int _M_iostate;						// +0x08
	int _M_openmode;					// +0x0C
	int _M_seekdir;						// +0x10
	int _M_exception_mask;					// +0x14
	char m_pad0[0x24 - 0x18];
	struct Callback
	{
		event_callback fn;
		int index;
	};
	Callback *_M_callbacks;					// +0x24
	unsigned int _M_num_callbacks;				// +0x28
	unsigned int _M_callback_index;				// +0x2C
	char m_pad1[0x54 - 0x30];
};

template <class T>
class char_traits {};

template <class CharT, class Traits>
class basic_ios : public ios_base
{
public:
	basic_ios &copyfmt(const basic_ios &x);

private:
	CharT _M_fill;						// +0x54
	void *_M_streambuf;					// +0x58
	void *_M_tied_ostream;					// +0x5C
};

template <class CharT, class Traits>
basic_ios<CharT, Traits> &basic_ios<CharT, Traits>::copyfmt(const basic_ios &x)
{
	unsigned int n = _M_callback_index;
	if (n > 0)
	{
		do
		{
			Callback *slot = _M_callbacks + n;
			slot[-1].fn(erase_event, *this, slot[-1].index);
			--n;
		}
		while (n);
	}

	_M_copy_state(x);
	_M_fill = x._M_fill;
	_M_tied_ostream = x._M_tied_ostream;

	n = _M_callback_index;
	if (n > 0)
	{
		do
		{
			Callback *slot = _M_callbacks + n;
			slot[-1].fn(copyfmt_event, *this, slot[-1].index);
			--n;
		}
		while (n);
	}

	_M_exception_mask = x._M_exception_mask;
	return *this;
}

template basic_ios<char, char_traits<char> > &basic_ios<char, char_traits<char> >::copyfmt(const basic_ios<char, char_traits<char> > &);

}
