// cl: /O2 /Ob0 /EHsc /MD

// Open-BFME5: _STL::ios_base::imbue, retail 0x0083EC50, 163 bytes.
// STLport 4.5.3 copies the prior locale, assigns the new one, walks the
// callback array backwards with imbue_event (fn/index locals -> call ecx),
// then returns the prior locale.

namespace _STL
{

class locale
{
public:
	locale(const locale &x);
	~locale();
	locale &operator=(const locale &x);

private:
	void *_M_impl;
};

class ios_base
{
public:
	enum event { erase_event = 0, imbue_event = 1, copyfmt_event = 2 };
	typedef void (*event_callback)(event, ios_base &, int);

	locale imbue(const locale &loc);

protected:
	virtual void handle();

	int _M_fmtflags;					// +0x04
	int _M_iostate;						// +0x08
	int _M_openmode;					// +0x0C
	int _M_seekdir;						// +0x10
	int _M_exception_mask;					// +0x14
	int _M_precision;					// +0x18
	int _M_width;						// +0x1C
	locale _M_locale;					// +0x20
	struct Callback
	{
		event_callback fn;
		int index;
	};
	Callback *_M_callbacks;					// +0x24
	unsigned int _M_num_callbacks;				// +0x28
	unsigned int _M_callback_index;				// +0x2C
};

locale ios_base::imbue(const locale &loc)
{
	locale previous = _M_locale;
	_M_locale = loc;

	for (unsigned int i = _M_callback_index; i > 0; --i)
	{
		event_callback f = _M_callbacks[i - 1].fn;
		int n = _M_callbacks[i - 1].index;
		f(imbue_event, *this, n);
	}

	return previous;
}

}
