// The retail body is ATL 7.1's inline CAtlWinModule constructor.  These are
// the relevant declarations and constructor bodies from the VS2003 headers,
// kept TU-local so this one ATL runtime body can be compiled independently.
#include <string.h>

namespace ATL
{
typedef long HRESULT;
typedef unsigned short ATOM;

struct _ATL_WIN_MODULE70;

class CAtlBaseModule
{
public:
	static bool m_bInitFailed;
};

class CComCriticalSection
{
public:
	CComCriticalSection() throw()
	{
		memset(m_sec, 0, sizeof(m_sec));
	}

	HRESULT Init() throw();

	unsigned long m_sec[6];
};

template <class T>
class CSimpleArray
{
public:
	CSimpleArray() : m_aT(0), m_nSize(0), m_nAllocSize(0) {}

	T *m_aT;
	int m_nSize;
	int m_nAllocSize;
};

struct _ATL_WIN_MODULE70
{
	unsigned int cbSize;
	CComCriticalSection m_csWindowCreate;
	void *m_pCreateWndList;
	CSimpleArray<ATOM> m_rgWindowClassAtoms;
};

inline HRESULT __stdcall AtlWinModuleInit(_ATL_WIN_MODULE70 *module)
{
	if (module == 0 || module->cbSize != sizeof(_ATL_WIN_MODULE70))
		return static_cast<HRESULT>(0x80070057L);

	module->m_pCreateWndList = 0;
	return module->m_csWindowCreate.Init();
}

class CAtlWinModule : public _ATL_WIN_MODULE70
{
public:
	CAtlWinModule();
};

CAtlWinModule::CAtlWinModule()
{
	cbSize = sizeof(_ATL_WIN_MODULE70);
	HRESULT hr = AtlWinModuleInit(this);
	if (hr < 0)
		CAtlBaseModule::m_bInitFailed = true;
}
}
