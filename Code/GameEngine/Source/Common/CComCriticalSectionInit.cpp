// ATL 7.1 CComCriticalSection::Init recovered at retail RVA 0x007E5860.

typedef long HRESULT;

extern "C" __declspec(dllimport) void __stdcall InitializeCriticalSection(
	void *section);
extern "C" unsigned long __cdecl _exception_code(void);

#define GetExceptionCode _exception_code

#define STATUS_NO_MEMORY ((unsigned long)0xC0000017)
#define E_OUTOFMEMORY ((HRESULT)0x8007000E)
#define E_FAIL ((HRESULT)0x80004005)

namespace ATL
{
class CComCriticalSection
{
public:
	HRESULT Init() throw();

	unsigned long m_sec[6];
};

HRESULT CComCriticalSection::Init() throw()
{
	HRESULT hRes = 0;
	__try
	{
		InitializeCriticalSection(m_sec);
	}
	__except (1)
	{
		if (STATUS_NO_MEMORY == GetExceptionCode())
			hRes = E_OUTOFMEMORY;
		else
			hRes = E_FAIL;
	}
	return hRes;
}
}
