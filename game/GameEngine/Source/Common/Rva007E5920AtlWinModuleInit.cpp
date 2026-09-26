// cl: /O2
// ATL 7.1 AtlWinModuleInit body recovered from the retail 0x007E5920 shape.

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
		return static_cast<HRESULT>(0x80070057L);
	if (pWinModule->cbSize != sizeof(ATL::_ATL_WIN_MODULE70))
		return static_cast<HRESULT>(0x80070057L);
	pWinModule->m_pCreateWndList = 0;
	return pWinModule->m_csWindowCreate.Init();
}
