// cl: /DNDEBUG /MD /EHsc
// Readable C++ for ?Reset_D3D_Device@@YAXH@Z, an upstream free function whose
// BFME twin adds a W3DRadarResetGuard lock and a clipCursorToClient() call
// around the ZH logic.
// upstream: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplay.cpp

void __cdecl W3DRadarResetLock(void);
char __cdecl bfmeUnlock1179(void);
void clipCursorToClient(void);

class W3DRadarResetGuard
{
public:
	W3DRadarResetGuard(void)
	{
		W3DRadarResetLock();
	}

	~W3DRadarResetGuard(void)
	{
		bfmeUnlock1179();
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Display.h
// BFME's Display has three more virtuals ahead of getWidth than ZH's, so
// getWidth/getHeight/getBitDepth/getWindowed land at +0x2c/+0x30/+0x38/+0x40
// (proven by the landed W3DDisplaySetDisplayMode.cpp sibling).
class Display
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void setWidth(unsigned int width);
	virtual void setHeight(unsigned int height);
	virtual unsigned int getWidth();
	virtual unsigned int getHeight();
	virtual void setBitDepth(unsigned int bitDepth);
	virtual unsigned int getBitDepth();
	virtual void setWindowed(bool windowed);
	virtual bool getWindowed();
};

extern Display *TheDisplay;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/w3derr.h
enum WW3DErrorType
{
	WW3D_ERROR_OK = 0,
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/ww3d.h
class WW3D
{
public:
	static bool Is_Initted(void) { return IsInitted; }
	static int Get_Render_Device(void);
	static WW3DErrorType Set_Render_Device(int dev = -1, int resx = -1, int resy = -1, int bits = -1, int windowed = -1, bool resize_window = false, bool reset_device = false, bool restore_assets = true);
	static void _Invalidate_Textures();

private:
	static bool IsInitted;
};

// GetVersionExA: KERNEL32 import, same idiom as the neighbouring
// W3DDisplayClipCursor.cpp (no manual IAT pin needed for a standard import).
struct BfmeOsVersionInfo
{
	unsigned long dwOSVersionInfoSize;
	unsigned long dwMajorVersion;
	unsigned long dwMinorVersion;
	unsigned long dwBuildNumber;
	unsigned long dwPlatformId;
	char szCSDVersion[128];
};

#define BFME_VER_PLATFORM_WIN32_WINDOWS 1

extern "C" __declspec(dllimport) int __stdcall GetVersionExA(BfmeOsVersionInfo *lpVersionInformation);

// ?Reset_D3D_Device@@YAXH@Z
void Reset_D3D_Device(bool active)
{
	if (TheDisplay && WW3D::Is_Initted() && !TheDisplay->getWindowed())
	{
		W3DRadarResetGuard lock;

		if (active)
		{
			// switch back to desired mode when user alt-tabs back into game
			if (WW3D_ERROR_OK != (char)WW3D::Set_Render_Device(WW3D::Get_Render_Device(), TheDisplay->getWidth(), TheDisplay->getHeight(), TheDisplay->getBitDepth(), TheDisplay->getWindowed(), true, true))
			{
				BfmeOsVersionInfo osvi;
				osvi.dwOSVersionInfoSize = sizeof(BfmeOsVersionInfo);
				if (GetVersionExA(&osvi))
				{
					// check if we're running Win9x variant since they have buggy alt-tab
					// that requires reloading all textures.
					if (osvi.dwPlatformId == BFME_VER_PLATFORM_WIN32_WINDOWS)
					{
						WW3D::_Invalidate_Textures();
					}
				}

				clipCursorToClient();
			}
		}
		else
		{
			// switch to windowed mode whenever the user alt-tabs out of game.
			// Don't restore assets after reset since we'll do it when returning.
			WW3D::Set_Render_Device(WW3D::Get_Render_Device(), TheDisplay->getWidth(), TheDisplay->getHeight(), TheDisplay->getBitDepth(), TheDisplay->getWindowed(), true, true, false);
		}
	}
}
