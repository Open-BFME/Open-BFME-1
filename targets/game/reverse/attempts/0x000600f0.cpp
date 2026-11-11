// _WinMain@16
// partial score=0.9727 date=2026-11-12
// cl: /DNDEBUG /MD /EHsc /I. /Iinputs/toolchains/vs2003/PROG~FBU/MICR~2RR.NET/Vc7/atlmfc/include /Iinputs/toolchains/vs2003/PROG~FBU/MICR~2RR.NET/Vc7/PlatformSDK/Include
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#pragma push_macro("lstrcmpi")
#undef lstrcmpi
extern "C" __declspec(dllimport) int __stdcall lstrcmpi(const char *, const char *);
#pragma push_macro("GetStringTypeExWFake")
#pragma push_macro("CompareStringWFake")
#pragma push_macro("GetStringTypeExA")
#pragma push_macro("lstrcmpiA")
#define GetStringTypeExWFake GetStringTypeExWFakeCStringT
#define CompareStringWFake CompareStringWFakeCStringT
#define GetStringTypeExA GetStringTypeA
#define lstrcmpiA lstrcmpi
#include <atlimage.h>
#pragma pop_macro("lstrcmpiA")
#pragma pop_macro("GetStringTypeExA")
#pragma pop_macro("CompareStringWFake")
#pragma pop_macro("GetStringTypeExWFake")
#pragma pop_macro("lstrcmpi")
#include "game/Libraries/Source/WWVegas/WWLib/ascii_string.h"
#include "game/Libraries/Source/WWVegas/WWLib/unicode_string.h"
typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
#include "inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/version.h"
AsciiString GetRegistryLanguage();
class DebugStackwalk { public: class Signature { public: static void GetSymbol(unsigned int,char*,unsigned int); }; };
class CopyProtect { public: static bool isLauncherRunning(); static bool notifyLauncher(); static void shutdown(); };
class WW3D { public: static bool Shutdown(); };
class GameEngine;
extern GameEngine *TheGameEngine;
class GlobalData;
extern GlobalData *TheWritableGlobalData;
class Rva0006B610 { public: void apply(); };
void bfmeBootBZ(void*,void*);
extern char g_Va012ED270CommandLine[];
extern bool g_Va012ED23CWindowed;
extern HBITMAP g_Va012ED24CBitmap;
typedef bool WindowedFlag;
inline UnicodeString::~UnicodeString() { reinterpret_cast<StringBase<unsigned short> *>(this)->~StringBase(); }
// ?nextParam@@YAPADPAD0@Z
// The Zero Hour WinMain tokenizer names this body. Retail stores its static
// cursor at 0x012ED264 and loads strpbrk through 0x013594C4.
#include <string.h>

typedef char *(__cdecl *StrpbrkFunction)(const char *, const char *);
extern "C" StrpbrkFunction _imp__strpbrk;

char *nextParam(char *newSource, char *seps)
{
	static char *source = NULL;
	if (newSource)
	{
		source = newSource;
	}
	if (!source)
	{
		return NULL;
	}

	char *first = source;
	if (first)
	{
		StrpbrkFunction find = _imp__strpbrk;
		char *firstSep = find(first, seps);
		char firstChar[2] = {0, 0};
		if (firstSep == first)
		{
			firstChar[0] = *first;
			while (*first == firstChar[0]) first++;
		}

		char *end;
		if (firstChar[0])
			end = find(first, firstChar);
		else
			end = find(first, seps);

		if (end)
		{
			source = end+1;
			*end = 0;
			if (!*source)
				source = NULL;
		}
		else
		{
			source = NULL;
		}

		if (first && !*first)
			first = NULL;
	}

	return first;
}

// strtrim ====================================================================
/** Trim leading and trailing whitespace from a character string (in place). */
// Zero Hour WinMain's file-static; retail 0x0005D5B0 sits beside nextParam and
// takes buffer in EAX through VC7.1's private static convention. WWLib's
// trim.cpp owns the plain name (0x009E7EB0), so this copy takes the twin namespace.
//=============================================================================
namespace Rva0005D5B0Twin {
static char* strtrim(char* buffer)
{
	if (buffer != NULL) {
		//	Strip leading white space from the string.
		char * source = buffer;
		while ((*source != 0) && ((unsigned char)*source <= 32))
		{
			source++;
		}

		if (source != buffer)
		{
			strcpy(buffer, source);
		}

		//	Clip trailing white space from the string.
		for (int index = strlen(buffer)-1; index >= 0; index--)
		{
			if ((*source != 0) && ((unsigned char)buffer[index] <= 32))
			{
				buffer[index] = '\0';
			}
			else
			{
				break;
			}
		}
	}

	return buffer;
}
}

class BfmeAwakenDebug
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3C();
	virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual void slot4C();
	virtual void slot50(); virtual void slot54(); virtual void slot58(); virtual void slot5C();
	virtual void slot60(); virtual void slot64(); virtual void slot68(); virtual void slot6C();
	virtual void slot70(); virtual void slot74(); virtual void slot78(); virtual void slot7C();
	virtual void slot80(); virtual void slot84(); virtual void slot88(); virtual void slot8C();
	virtual void slot90(); virtual void slot94(); virtual void slot98(); virtual void slot9C();
	virtual void slotA0(Bool value);
};

// Retail 0x01336E5C is ?g_Rva00F36E5C@@3PAXA (data_rows.csv,
// debug/Rva00F36E5C.cpp); TheBfmeAwakenDebug was only a pin.
extern void *g_Rva00F36E5C;
#define TheBfmeAwakenDebug ( *(BfmeAwakenDebug **)&g_Rva00F36E5C )
UnicodeString getBfmeDisplayName();

void *ApplicationHInstance = 0;
extern void *ApplicationHWnd;
Bool g_Va012ED248Initializing = false;
Bool g_Va012A6514 = true;

// ?applicationInstance@@YAAAPAXXZ absent-from-retail
static void *&applicationInstance()
{
	return ApplicationHInstance;
}

// ?applicationWindow@@YAAAPAXXZ absent-from-retail
static void *&applicationWindow()
{
	return ApplicationHWnd;
}

// ?initializing@@YAAA_NXZ absent-from-retail
static Bool &initializing()
{
	return g_Va012ED248Initializing;
}

// ?doPaint@@YAAA_NXZ absent-from-retail
static Bool &doPaint()
{
	return g_Va012A6514;
}

extern const wchar_t g_Va01073048[] =
	L"E99E8455-CC9B-488a-BA22-0E8A8F74F9FA";
const wchar_t *g_Va012A6504WindowClassName = g_Va01073048;

// ?Rva0005F2B0InitializeAppWindows@@YA_NPAXH_N@Z
static Bool Rva0005F2B0InitializeAppWindows(
	void *hInstance, Int nCmdShow, WindowedFlag runWindowed)
{
	DWORD windowStyle;
	Int startWidth = 800;
	Int startHeight = 600;
	WindowedFlag debugFlag = runWindowed;
	TheBfmeAwakenDebug->slotA0(debugFlag);
	WNDCLASSW wndClass = { CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS,
		(WNDPROC)0x0043206A, 0, 0, (HINSTANCE)hInstance,
		(HICON)LoadImageA((HINSTANCE)hInstance, "lotrbfme.ico", IMAGE_ICON, 0, 0,
		LR_LOADFROMFILE | LR_DEFAULTSIZE),
		NULL, (HBRUSH)GetStockObject(BLACK_BRUSH), NULL, g_Va012A6504WindowClassName };
	RegisterClassW(&wndClass);

	windowStyle = WS_POPUP | WS_VISIBLE;
	if (runWindowed)
		windowStyle |= WS_DLGFRAME | WS_CAPTION | WS_SYSMENU;
	else
		windowStyle |= WS_EX_TOPMOST | WS_SYSMENU;

	RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = startWidth;
	rect.bottom = startHeight;
	AdjustWindowRect(&rect, windowStyle, FALSE);
	if (runWindowed)
	{
		startWidth = 800;
		startHeight = 600;
	}

	initializing() = TRUE;

	HWND hWnd = CreateWindowExW(
		0, g_Va012A6504WindowClassName, getBfmeDisplayName().str(), windowStyle,
		(GetSystemMetrics(SM_CXSCREEN) / 2) - (startWidth / 2),
		(GetSystemMetrics(SM_CYSCREEN) / 2) - (startHeight / 2) - 32,
		rect.right - rect.left, rect.bottom - rect.top,
		0, 0, (HINSTANCE)hInstance, 0);

	if (!runWindowed)
		SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
	else
		SetWindowPos(hWnd, HWND_TOP, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
	SetFocus(hWnd);
	SetForegroundWindow(hWnd);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	applicationInstance() = hInstance;
	applicationWindow() = hWnd;
	initializing() = FALSE;
	if (!runWindowed)
		doPaint() = FALSE;
	return TRUE;
}


extern "C" int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,char *lpCmdLine,int nCmdShow)
{
 HMODULE imm=LoadLibraryA("IMM32.dll");
 if(imm) {
  FARPROC disable=GetProcAddress(imm,"ImmDisableTextFrameService");
  if(disable) ((BOOL (WINAPI *)(DWORD))disable)(-1);
  FreeLibrary(imm);
 }
 strcpy(g_Va012ED270CommandLine,lpCmdLine);
 try {
  char buffer[260];
  GetModuleFileNameA(0,buffer,sizeof(buffer));
  char *pEnd=buffer+strlen(buffer);
  while(pEnd!=buffer) {
   if(*pEnd=='\\') { *pEnd=0; break; }
   pEnd--;
  }
  SetCurrentDirectoryA(buffer);
  int argc=1;
  char *argv[20];
  argv[0]=0;
  char *token=nextParam(g_Va012ED270CommandLine,"\" ");
  while(argc<20 && token) {
   if((unsigned char)*token==0x96) *token='-';
   argv[argc++]=Rva0005D5B0Twin::strtrim(token);
   if(_strcmpi(token,"-win")==0) g_Va012ED23CWindowed=true;
   _strcmpi(token,"-automatch");
   token=nextParam(0,"\" ");
  }
  if(argc>2 && strcmp(argv[1],"-DX")==0) {
   for(int i=2;i<argc;i++) {
    unsigned int address=strtoul(argv[i],0,16);
    char name[256];
    DebugStackwalk::Signature::GetSymbol(address,name,sizeof(name));
   }
   return 0;
  }
  {
   ATL::CImage splashImage;
   char filePath[260];
   sprintf(filePath,"%sSplash.jpg",GetRegistryLanguage().str());
   if(splashImage.Load(filePath)<0) {
    sprintf(filePath,"%sSplash.bmp",GetRegistryLanguage().str());
    splashImage.Load(filePath);
   }
   g_Va012ED24CBitmap=splashImage;
   HANDLE gameMutex=CreateMutexW(0,FALSE,g_Va012A6504WindowClassName);
   if(GetLastError()==ERROR_ALREADY_EXISTS) {
    HWND runningWindow=FindWindowW(g_Va012A6504WindowClassName,0);
    if(runningWindow) { SetForegroundWindow(runningWindow);ShowWindow(runningWindow,SW_RESTORE); }
    if(gameMutex) CloseHandle(gameMutex);
    delete TheVersion;TheVersion=0;
    return 0;
   }
   if(!Rva0005F2B0InitializeAppWindows(hInstance,nCmdShow,g_Va012ED23CWindowed)) return 0;
  }
  TheVersion=new Version;
  TheVersion->setVersion(1,3,0,13,AsciiString("rtsbuild"),AsciiString("EALA-RTS-BUILD5"),AsciiString("17:15:10"),AsciiString("Nov 28 2005"));
  if(!CopyProtect::isLauncherRunning()) { delete TheVersion;TheVersion=0;return 0; }
  if(!CopyProtect::notifyLauncher()) { delete TheVersion;TheVersion=0;return 0; }
  bfmeBootBZ((void*)argc,argv);
  CopyProtect::shutdown();
  delete TheVersion;TheVersion=0;
  if(*((const unsigned char*)TheWritableGlobalData+0xD04)) {
   if(TheGameEngine) { ((Rva0006B610*)TheGameEngine)->apply();TheGameEngine=0; }
  } else WW3D::Shutdown();
 } catch(...) {}
 return 0;
}
