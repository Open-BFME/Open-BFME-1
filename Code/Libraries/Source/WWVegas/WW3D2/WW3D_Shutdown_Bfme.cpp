// cl: /DNDEBUG /MD /EHsc
// Retail 0x008FD6E0: BFME WW3D teardown.  The retail object lifetime around
// the reset lock is kept explicit so MSVC emits the same EH state transitions.

class DX8Wrapper
{
public:
	static void Shutdown();
};

class DefaultStaticSortListClass
{
public:
	virtual void slot00(int);
};

extern void W3DRadarResetLock(void);
extern char bfmeUnlock1179(void);

struct BfmeRadarResetGuard
{
	BfmeRadarResetGuard(void) { W3DRadarResetLock(); }
	~BfmeRadarResetGuard(void) { bfmeUnlock1179(); }
};

extern DefaultStaticSortListClass *g_WW3D_DefaultStaticSortList;
extern void (__stdcall *g_WW3D_ShutdownTextures)(int);
extern DefaultStaticSortListClass *g_WW3D_SecondaryResource;
extern unsigned char g_WW3D_SkipDeviceShutdown;

class WW3D
{
public:
	static bool Shutdown(void);
	// First block is inlined Stop_Movie_Capture: 0x133f42a is IsCapturing, not IsInitted.
	static bool IsInitted;
	static bool IsCapturing;
};

bool WW3D::Shutdown(void)
{
	if (IsCapturing)
	{
		DefaultStaticSortListClass *list = g_WW3D_DefaultStaticSortList;
		IsCapturing = 0;
		if (list)
			list->slot00(1);
		g_WW3D_DefaultStaticSortList = 0;
	}
	g_WW3D_ShutdownTextures(1);
	if (!g_WW3D_SkipDeviceShutdown)
	{
		BfmeRadarResetGuard guard;
		DX8Wrapper::Shutdown();
	}
	if (g_WW3D_SecondaryResource)
	{
		g_WW3D_SecondaryResource->slot00(1);
	}
	IsInitted = 0;
	return true;
}
