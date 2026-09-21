// ?_M_copy_state@ios_base@_STL@@IAEXABV12@@Z
// partial score=0.58 date=2026-09-21
// cl: /O2 /Ob0 /MD

// Open-BFME5: _STL::ios_base::_M_copy_state, retail 0x0083F3F0, 432 bytes.
// Called by basic_ios<>::copyfmt (stlport_basic_ios_copyfmt[_w].cpp) which
// already established the ios_base field layout up to the +0x54 pad1
// boundary; this body is what fills that padding in with the locale,
// callback, iarray and parray members and their copy-on-write logic.
// STLport 4.5.3 walks: trivial ints, then the locale (skip if already ==),
// then two more trivial ints, then the callback array (8-byte elements,
// duplicated via the U2 allocator helper), then the iarray and parray
// (4-byte elements each, malloc + BfmeMemMove + free), each array copy
// setting badbit and possibly throwing ios_base::failure on allocation
// failure exactly like STLport's inlined _M_setstate(badbit).

extern "C" __declspec(dllimport) void *__cdecl _malloc(unsigned int bytes);
extern "C" __declspec(dllimport) void __cdecl bfmeFree1035(void *p);
extern "C" __declspec(dllimport) void __cdecl BfmeMemMove(void *dst, const void *src, unsigned int n);

struct Rva00832180Unk
{
	virtual void slot0();
	virtual void addRef();
	virtual void release();
};

class Rva00832180
{
	Rva00832180Unk *m_ptr;

public:
	bool goDSD(void *what);		// retail 0x008366C0, thiscall test
	Rva00832180 &set(Rva00832180Unk *const *src);
};

struct U2Elem8
{
	int m_a;
	int m_b;
};

extern void *Rva0083F3B0Duplicate(const U2Elem8 *src, int count);

extern void *g_global;						// 0x013592F0
extern void (__cdecl *g_call)(void *, void *);		// 0x013593C8

namespace _STL
{

class ios_base
{
public:
	virtual void handle();

protected:
	void _M_copy_state(const ios_base &x);

public:
	int _M_fmtflags;					// +0x04
	int _M_iostate;						// +0x08
	int _M_openmode;					// +0x0C
	int _M_seekdir;						// +0x10
	int _M_exception_mask;					// +0x14
	int _M_precision;					// +0x18
	int _M_width;						// +0x1C
	Rva00832180 _M_locale;					// +0x20
	U2Elem8 *_M_callbacks;					// +0x24
	unsigned int _M_num_callbacks;				// +0x28
	unsigned int _M_callback_index;			// +0x2C
	int *_M_iarray;						// +0x30
	unsigned int _M_iarray_size;				// +0x34
	void **_M_parray;					// +0x38
	unsigned int _M_parray_size;				// +0x3C
	int _M_reserved0;					// +0x40
	int _M_reserved1;					// +0x44
	char m_pad2[0x54 - 0x48];
};

void ios_base::_M_copy_state(const ios_base &x)
{
	_M_fmtflags = x._M_fmtflags;
	_M_openmode = x._M_openmode;
	_M_seekdir = x._M_seekdir;
	_M_precision = x._M_precision;
	_M_width = x._M_width;

	if (_M_locale.goDSD((void *)&x._M_locale))
	{
		_M_locale.set((Rva00832180Unk *const *)&x._M_locale);
		_M_reserved0 = x._M_reserved0;
		_M_reserved1 = x._M_reserved1;
	}

	if (x._M_callbacks)
	{
		U2Elem8 *copy = (U2Elem8 *)Rva0083F3B0Duplicate(x._M_callbacks, x._M_callback_index);
		if (copy)
		{
			bfmeFree1035(_M_callbacks);
			_M_callbacks = copy;
			unsigned int idx = x._M_callback_index;
			_M_callback_index = idx;
			_M_num_callbacks = idx;
		}
		else
		{
			_M_iostate |= 1;
			if (_M_iostate & _M_exception_mask)
				g_call((void *)"ios failure", (char *)g_global + 0x40);
		}
	}

	if (x._M_iarray)
	{
		unsigned int bytes = x._M_iarray_size << 2;
		int *tmp = (int *)_malloc(bytes);
		if (tmp)
		{
			if (bytes)
				BfmeMemMove(tmp, x._M_iarray, bytes);
			bfmeFree1035(_M_iarray);
			_M_iarray = tmp;
			_M_iarray_size = x._M_iarray_size;
		}
		else
		{
			_M_iostate |= 1;
			if (_M_iostate & _M_exception_mask)
				g_call((void *)"ios failure", (char *)g_global + 0x40);
		}
	}

	if (x._M_parray)
	{
		unsigned int bytes = x._M_parray_size << 2;
		void **tmp = (void **)_malloc(bytes);
		if (tmp)
		{
			if (bytes)
				BfmeMemMove(tmp, x._M_parray, bytes);
			bfmeFree1035(_M_parray);
			_M_parray = tmp;
			_M_parray_size = x._M_parray_size;
		}
		else
		{
			_M_iostate |= 1;
			if (_M_iostate & _M_exception_mask)
				g_call((void *)"ios failure", (char *)g_global + 0x40);
		}
	}
}

}
