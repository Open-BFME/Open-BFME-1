// cl: /O2
// ATL 7.1 AtlWinModuleTerm from atlbase.h, TU-local so this one ATL runtime
// body can compile independently of the shared headers.

typedef long HRESULT;
typedef unsigned short ATOM;
typedef unsigned long DWORD;

extern "C" __declspec(dllimport) void __cdecl free(void *block);
extern "C" __declspec(dllimport) int __stdcall UnregisterClassA(const char *name, void *hInst);
extern "C" __declspec(dllimport) void __stdcall DeleteCriticalSection(void *cs);
extern "C" __declspec(dllimport) void __stdcall RaiseException(DWORD code, DWORD flags, DWORD nArgs, const DWORD *args);

inline void __declspec(noreturn) AtlRaiseException(DWORD code, DWORD flags = 1)
{
	RaiseException(code, flags, 0, 0);
}

struct AtlWinCritSec
{
	HRESULT Term()
	{
		DeleteCriticalSection(m_sec);
		return 0;
	}

	unsigned long m_sec[6];
};

struct AtlWinAtomArray
{
	int GetSize() const
	{
		return m_nSize;
	}

	ATOM &operator[](int nIndex)
	{
		if (nIndex < 0 || nIndex >= m_nSize)
			AtlRaiseException(0xC000008C);
		return m_aT[nIndex];
	}

	void RemoveAll()
	{
		if (m_aT != 0)
		{
			free(m_aT);
			m_aT = 0;
		}
		m_nSize = 0;
		m_nAllocSize = 0;
	}

	ATOM *m_aT;
	int m_nSize;
	int m_nAllocSize;
};

struct AtlWinModule
{
	unsigned int cbSize;
	AtlWinCritSec m_csWindowCreate;
	void *m_pCreateWndList;
	AtlWinAtomArray m_rgWindowClassAtoms;
};

extern "C" HRESULT __stdcall AtlWinModuleTerm(AtlWinModule *pWinModule, void *hInst)
{
	if (pWinModule == 0)
		return static_cast<HRESULT>(0x80070057L);
	if (pWinModule->cbSize == 0)
		return 0;
	if (pWinModule->cbSize != sizeof(AtlWinModule))
		return static_cast<HRESULT>(0x80070057L);

	for (int i = 0; i < pWinModule->m_rgWindowClassAtoms.GetSize(); i++)
		UnregisterClassA((const char *)pWinModule->m_rgWindowClassAtoms[i], hInst);
	pWinModule->m_rgWindowClassAtoms.RemoveAll();
	pWinModule->m_csWindowCreate.Term();
	pWinModule->cbSize = 0;
	return 0;
}
