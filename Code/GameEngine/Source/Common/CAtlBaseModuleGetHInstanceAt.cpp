// cl: /O1 /Oy-
// Open-BFME5: ATL 7.1 CAtlBaseModule::GetHInstanceAt.
//
// Ghidra identifies retail 0x009F6A42 as GetHInstanceAt.  Its member layout
// and lock lifetime come from the pristine VS2003 atlcore.h/atlbase.cpp; the
// TU-local declarations preserve the existing ATL helper calls without a
// shared-header change.

typedef void *HINSTANCE;
typedef long HRESULT;

#define FAILED(hr) ((hr) < 0)

extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(void *cs);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void *cs);

namespace ATL
{
class CComCriticalSection
{
public:
	HRESULT Lock() throw()
	{
		EnterCriticalSection(m_sec);
		return 0;
	}
	HRESULT Unlock() throw()
	{
		LeaveCriticalSection(m_sec);
		return 0;
	}
	unsigned long m_sec[6];
};

template <class TLock>
class CComCritSecLock
{
public:
	CComCritSecLock(TLock& cs, bool bInitialLock = true) : m_cs(cs), m_bLocked(false)
	{
		if (bInitialLock)
		{
			HRESULT hr = Lock();
			if (FAILED(hr))
				return;
		}
	}
	__declspec(noinline) ~CComCritSecLock() throw();
	HRESULT Lock() throw()
	{
		HRESULT hr = m_cs.Lock();
		if (FAILED(hr))
			return hr;
		m_bLocked = true;
		return 0;
	}
	void Unlock() throw()
	{
		m_cs.Unlock();
		m_bLocked = false;
	}

private:
	TLock& m_cs;
	bool m_bLocked;
};

template <class TLock>
CComCritSecLock<TLock>::~CComCritSecLock() throw()
{
	if (m_bLocked)
		Unlock();
}

template <class T>
class CSimpleArrayEqualHelper
{
};

template <class T, class TEqual = CSimpleArrayEqualHelper<T> >
class CSimpleArray
{
public:
	int GetSize() const { return m_nSize; }
	T& operator[](int nIndex);

	T *m_aT;
	int m_nSize;
	int m_nAllocSize;
};

struct _ATL_BASE_MODULE70
{
	unsigned int cbSize;
	HINSTANCE m_hInst;
	HINSTANCE m_hInstResource;
	bool m_bNT5orWin98;
	unsigned long dwAtlBuildVer;
	const void *pguidVer;
	CComCriticalSection m_csResource;
	CSimpleArray<HINSTANCE> m_rgResourceInstance;
};

class CAtlBaseModule : public _ATL_BASE_MODULE70
{
public:
	HINSTANCE GetHInstanceAt(int i) throw();
};

HINSTANCE CAtlBaseModule::GetHInstanceAt(int i) throw()
{
	CComCritSecLock<CComCriticalSection> lock(m_csResource, false);
	if (FAILED(lock.Lock()))
		return 0;
	if (i > m_rgResourceInstance.GetSize() || i < 0)
		return 0;
	if (i == m_rgResourceInstance.GetSize())
		return m_hInstResource;
	return m_rgResourceInstance[i];
}
}
