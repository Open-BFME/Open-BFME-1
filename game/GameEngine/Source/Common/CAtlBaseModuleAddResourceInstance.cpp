// cl: /O1 /Oy-
// Open-BFME5: ATL 7.1 CAtlBaseModule::AddResourceInstance.

typedef void *HINSTANCE;
typedef long HRESULT;
typedef int BOOL;

#define FAILED(hr) ((hr) < 0)
#define FALSE 0

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
	BOOL Add(const T& t);

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
	bool AddResourceInstance(HINSTANCE hInst) throw();
};

bool CAtlBaseModule::AddResourceInstance(HINSTANCE hInst) throw()
{
	CComCritSecLock<CComCriticalSection> lock(m_csResource, false);
	if (FAILED(lock.Lock()))
		return false;
	return m_rgResourceInstance.Add(hInst) != FALSE;
}
}
