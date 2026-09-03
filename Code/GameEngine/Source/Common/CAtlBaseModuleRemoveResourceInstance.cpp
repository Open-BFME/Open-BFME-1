// cl: /O1 /Oy-
// Open-BFME5: ATL 7.1 CAtlBaseModule::RemoveResourceInstance.
//
// The implementation and member layout are recovered from the pristine
// VS2003 ATL sources in build/toolchains/vs2003/.../atlbase.cpp and
// atlcore.h.  These declarations stay TU-local so this one retail body can be
// converted without changing the shared headers.

typedef void *HINSTANCE;
typedef long HRESULT;
typedef int BOOL;

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
	// Retail keeps this cleanup as a separate COMDAT call from the body.
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
	BOOL RemoveAt(int nIndex);

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
	bool RemoveResourceInstance(HINSTANCE hInst) throw();
};

bool CAtlBaseModule::RemoveResourceInstance(HINSTANCE hInst) throw()
{
	CComCritSecLock<CComCriticalSection> lock(m_csResource, false);
	if (FAILED(lock.Lock()))
	{
		// ATLTRACE and ATLASSERT are compiled out by the retail NDEBUG build.
		return false;
	}
	for (int i = 0; i < m_rgResourceInstance.GetSize(); i++)
	{
		if (m_rgResourceInstance[i] == hInst)
		{
			m_rgResourceInstance.RemoveAt(i);
			return true;
		}
	}
	return false;
}
}
