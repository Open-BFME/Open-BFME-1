// ?rva00893230StatusRelease@@YA_NPAX@Z
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Returns whether the object type dword at +8 is 4, then drops the object
// when the refcount at +0 hits zero. The barrier keeps the second null test
// that MSVC 7.1 would otherwise fold into the flag computation.

class Rva00894D90Accessor
{
public:
	static unsigned int decrement(unsigned int *value);
};

__declspec(noinline) void bfmeDropA(void *p);

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

bool rva00893230StatusRelease(void *p)
{
	bool flag = p && *((int *)p + 2) == 4;
	_ReadWriteBarrier();
	if (p)
	{
		if (Rva00894D90Accessor::decrement((unsigned int *)p) == 0)
			bfmeDropA(p);
	}
	return flag;
}
