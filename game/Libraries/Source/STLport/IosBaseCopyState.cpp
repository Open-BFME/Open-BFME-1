// cl: /O2 /MD
// stlport
// STLport 4.5.3 ios_base::_M_copy_state and _Stl_copy_array (src/ios.cpp).

#include <algorithm>
#include <cstdlib>
#include <stdio.h>

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
	bool goDSD(void *what);		// retail 0x008366C0, thiscall locale inequality test
	Rva00832180 &set(Rva00832180Unk *const *src);
};

#pragma comment(linker, "/alternatename:?goDSD@Rva00832180@@QAE_NPAX@Z=?bfmeGoDSD@@YG_NPAX@Z")

struct U2Elem8
{
	int m_a;
	int m_b;
};

extern void *Rva0083F3B0Duplicate(const U2Elem8 *src, int count);

namespace _STL
{

// malloc N elements and copy the source array into them; null on failure.
template <class PODType>
PODType *_Stl_copy_array(const PODType *array, size_t N)
{
	PODType *result = (PODType *)malloc(N * sizeof(PODType));
	if (result)
		copy(array, array + N, result);
	return result;
}

class ios_base
{
public:
	virtual void handle();

protected:
	void _M_copy_state(const ios_base &x);
	void _M_setstate_nothrow(int state) { _M_iostate |= state; }
	void _M_check_exception_mask()
	{
		if (_M_iostate & _M_exception_mask)
			fputs("ios failure", stderr);
	}

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
		U2Elem8 *tmp = (U2Elem8 *)Rva0083F3B0Duplicate(x._M_callbacks, x._M_callback_index);
		if (tmp)
		{
			free(_M_callbacks);
			_M_callbacks = tmp;
			_M_num_callbacks = _M_callback_index = x._M_callback_index;
		}
		else
		{
			_M_setstate_nothrow(1);
			_M_check_exception_mask();
		}
	}

	if (x._M_iarray)
	{
		int *tmp = _Stl_copy_array(x._M_iarray, x._M_iarray_size);
		if (tmp)
		{
			free(_M_iarray);
			_M_iarray = tmp;
			_M_iarray_size = x._M_iarray_size;
		}
		else
		{
			_M_setstate_nothrow(1);
			_M_check_exception_mask();
		}
	}

	if (x._M_parray)
	{
		void **tmp = _Stl_copy_array(x._M_parray, x._M_parray_size);
		if (tmp)
		{
			free(_M_parray);
			_M_parray = tmp;
			_M_parray_size = x._M_parray_size;
		}
		else
		{
			_M_setstate_nothrow(1);
			_M_check_exception_mask();
		}
	}
}

}
