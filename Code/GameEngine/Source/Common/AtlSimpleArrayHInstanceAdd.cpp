// cl: /O1
// Open-BFME5: ATL 7.1 CSimpleArray<HINSTANCE>::Add.
//
// Ghidra names retail 0x009F6A90 "Add".  The implementation is the pristine
// VS2003 atlsimpcoll.h growth path for a pointer element.  InternalSetAtIndex
// is already represented by the exact indexed pointer-slot body at
// 0x009F6948, so this TU calls that recovered body by its landed source name.

typedef void *HINSTANCE;
typedef int BOOL;

#define FALSE 0
#define TRUE 1
#define NULL 0

extern "C" void *__cdecl realloc(void *memory, unsigned int size);
extern "C" void *__cdecl memmove(void *destination, const void *source,
	unsigned int bytes);

class Rva009F6948Array
{
public:
	void setAt(int index, void *const &value);
};

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
	BOOL Add(const T& t)
	{
		if (m_nSize == m_nAllocSize)
		{
			T* aT;
			int nNewAllocSize = (m_nAllocSize == 0) ? 1 : (m_nSize * 2);
			aT = (T*)realloc(m_aT, nNewAllocSize * sizeof(T));
			if (aT == NULL)
				return FALSE;
			m_nAllocSize = nNewAllocSize;
			m_aT = aT;
		}
		((Rva009F6948Array *)this)->setAt(m_nSize, t);
		m_nSize++;
		return TRUE;
	}

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

template BOOL CSimpleArray<HINSTANCE>::Add(const HINSTANCE& t);
template int CSimpleArray<void *, CSimpleArrayEqualHelper<void *> >::RemoveAt(int);
}
