// cl: /O2
// ATL 7.1 CAtlWinModule destructor (out of line in retail at 0x007E8600).
// Evidence: ~CAtlWinModule() calls Term(), i.e. AtlWinModuleTerm(this,
// _AtlBaseModule.m_hInst) (stdcall, this + the global at 0x0134FB4C), then the
// m_rgWindowClassAtoms CSimpleArray member dtor inlines RemoveAll: free m_aT
// at +0x20 and zero m_aT/m_nSize/m_nAllocSize (+0x20/+0x24/+0x28), matching
// the 44-byte _ATL_WIN_MODULE70 layout the 0x007E85A0 ctor builds. The
// 0x00C6C770 initializer constructs the global at 0x0130A45C with that ctor
// and its atexit forwarder (0x00C70C00) reaches this body through ILT 0xEAFC.

extern "C" __declspec(dllimport) void __cdecl free(void *block);

void __stdcall rva007e8530_bar(void *self, void *g);

void *g_rva007e8530;

namespace ATL
{
class CAtlWinModule
{
public:
	~CAtlWinModule();

private:
	char m_pad[0x20];
	void *m_20;
	int m_24;
	int m_28;
};

CAtlWinModule::~CAtlWinModule()
{
	rva007e8530_bar(this, g_rva007e8530);
	int z = 0;
	if (m_20 != 0)
	{
		free(m_20);
		m_20 = (void *)z;
	}
	m_24 = z;
	m_28 = z;
}
}
