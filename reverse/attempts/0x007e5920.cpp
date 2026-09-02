// _AtlWinModuleInit@4
// partial score=0.9 date=2026-09-02
// cl: /O2
// ATL 7.1 AtlWinModuleInit from atlbase.inl. TU-local so this one ATL runtime
// body can compile independently of the shared headers.

typedef long HRESULT;

namespace ATL
{
class CComCriticalSection
{
public:
	HRESULT Init() throw();
	unsigned long m_sec[6];
};

struct _ATL_WIN_MODULE70
{
	unsigned int cbSize;
	CComCriticalSection m_csWindowCreate;
	void *m_pCreateWndList;
	void *m_aT;
	int m_nSize;
	int m_nAllocSize;
};
}

extern "C" HRESULT __stdcall AtlWinModuleInit(ATL::_ATL_WIN_MODULE70 *pWinModule)
{
	if (pWinModule == 0)
		goto error;
	if (pWinModule->cbSize == sizeof(ATL::_ATL_WIN_MODULE70))
		goto success;
error:
	return static_cast<HRESULT>(0x80070057L);
success:
	pWinModule->m_pCreateWndList = 0;
	return pWinModule->m_csWindowCreate.Init();
}
