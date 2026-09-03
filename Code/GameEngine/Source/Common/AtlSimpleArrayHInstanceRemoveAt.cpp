// cl: /O1
// Open-BFME5: ATL 7.1 CSimpleArray<HINSTANCE>::RemoveAt.
//
// Retail 0x009F6883 is Ghidra's RemoveAt body for the array named by
// _ATL_BASE_MODULE70::m_rgResourceInstance in atlcore.h.  The declarations
// are deliberately TU-local: this instantiation only needs the ATL array
// layout and the VS2003 memmove call used for pointer elements.

typedef int BOOL;

extern "C" void *__cdecl memmove(void *destination, const void *source,
	unsigned int bytes);

namespace ATL
{
template <class T>
class CSimpleArrayEqualHelper
{
};

template <class T, class TEqual = CSimpleArrayEqualHelper<T> >
class CSimpleArray
{
public:
	BOOL RemoveAt(int nIndex)
	{
		if (nIndex < 0 || nIndex >= m_nSize)
			return 0;
		if (nIndex != (m_nSize - 1))
			memmove(m_aT + nIndex, m_aT + nIndex + 1,
				(m_nSize - (nIndex + 1)) * sizeof(T));
		m_nSize--;
		return 1;
	}

	T *m_aT;
	int m_nSize;
	int m_nAllocSize;
};

template int CSimpleArray<void *, CSimpleArrayEqualHelper<void *> >::RemoveAt(int);
}
