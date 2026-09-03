// cl: /O1
// Open-BFME5: ATL 7.1 CSimpleArray<HINSTANCE>::operator[].
//
// Ghidra names retail 0x009F6921 "operator[]" and atlcore.h supplies the
// owner: CAtlBaseModule::m_rgResourceInstance is a CSimpleArray<HINSTANCE>.
// Keep the old ATL declarations TU-local; this body only needs the array's
// three pointer-sized members and the checked accessor.

typedef unsigned long DWORD;

extern "C" __declspec(dllimport) void __stdcall RaiseException(
	DWORD code, DWORD flags, DWORD argumentCount, const DWORD *arguments);

namespace ATL
{
inline void __declspec(noreturn) _AtlRaiseException(
	DWORD code, DWORD flags = 1)
{
	RaiseException(code, flags, 0, 0);
}

template <class T>
class CSimpleArrayEqualHelper
{
};

template <class T, class TEqual = CSimpleArrayEqualHelper<T> >
class CSimpleArray
{
public:
	T& operator[](int nIndex)
	{
		if (nIndex < 0 || nIndex >= m_nSize)
			_AtlRaiseException(0xC000008C);
		return m_aT[nIndex];
	}

	T *m_aT;
	int m_nSize;
	int m_nAllocSize;
};

template void *& CSimpleArray<void *, CSimpleArrayEqualHelper<void *> >::operator[](int);
}
