// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// Evidence: targets/game/reverse/identity_evidence/0005f2b0-window-initializer-abi.md

#include <windows.h>
#include "../Libraries/Source/WWVegas/WWLib/unicode_string.h"

inline UnicodeString::~UnicodeString()
{
	reinterpret_cast<StringBase<unsigned short> *>(this)->~StringBase();
}

typedef bool Bool;
typedef int Int;
typedef bool WindowedFlag;

typedef LRESULT (CALLBACK *WNDPROC)(HWND, UINT, WPARAM, LPARAM);
typedef unsigned short ATOM;
typedef struct tagWNDCLASSW {
	UINT style;
	WNDPROC lpfnWndProc;
	int cbClsExtra;
	int cbWndExtra;
	HINSTANCE hInstance;
	HICON hIcon;
	HCURSOR hCursor;
	HBRUSH hbrBackground;
	LPCWSTR lpszMenuName;
	LPCWSTR lpszClassName;
} WNDCLASSW;

#define CS_HREDRAW 0x0002
#define CS_VREDRAW 0x0001
#define CS_DBLCLKS 0x0008
#define IMAGE_ICON 1
#define LR_LOADFROMFILE 0x00000010
#define LR_DEFAULTSIZE 0x00000040
#define BLACK_BRUSH 4
#define WS_POPUP 0x80000000L
#define WS_VISIBLE 0x10000000L
#define WS_DLGFRAME 0x00400000L
#define WS_SYSMENU 0x00080000L
#define WS_EX_TOPMOST 0x00000008L
#define SM_CXSCREEN 0
#define SM_CYSCREEN 1

extern "C" {
__declspec(dllimport) HANDLE WINAPI LoadImageA(HINSTANCE, LPCSTR, UINT, int, int, UINT);
__declspec(dllimport) HGDIOBJ WINAPI GetStockObject(int);
__declspec(dllimport) ATOM WINAPI RegisterClassW(const WNDCLASSW *);
__declspec(dllimport) int WINAPI GetSystemMetrics(int);
__declspec(dllimport) HWND WINAPI CreateWindowExW(DWORD, LPCWSTR, LPCWSTR, DWORD, int, int, int, int, HWND, HMENU, HINSTANCE, LPVOID);
__declspec(dllimport) HWND WINAPI SetFocus(HWND);
__declspec(dllimport) BOOL WINAPI SetForegroundWindow(HWND);
__declspec(dllimport) BOOL WINAPI UpdateWindow(HWND);
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

extern BfmeAwakenDebug *TheBfmeAwakenDebug;
UnicodeString getBfmeDisplayName();

extern HINSTANCE ApplicationHInstance;
extern HWND ApplicationHWnd;
extern Bool g_Va012ED248Initializing;
extern Bool g_Va012A6514;

// ?applicationInstance@@YAAAPAXXZ absent-from-retail
static HINSTANCE &applicationInstance()
{
	return ApplicationHInstance;
}

// ?applicationWindow@@YAAAPAXXZ absent-from-retail
static HWND &applicationWindow()
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

extern const wchar_t *g_Va012A6504WindowClassName;

// ?Rva0005F2B0InitializeAppWindows@@YA_NPAXH_N@Z
static Bool Rva0005F2B0InitializeAppWindows(
	HINSTANCE hInstance, Int nCmdShow, WindowedFlag runWindowed)
{
	DWORD windowStyle;
	Int startWidth = 800;
	Int startHeight = 600;
	WindowedFlag debugFlag = runWindowed;
	TheBfmeAwakenDebug->slotA0(debugFlag);
	WNDCLASSW wndClass = { CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS,
		(WNDPROC)0x0043206A, 0, 0, hInstance,
		(HICON)LoadImageA(hInstance, "lotrbfme.ico", IMAGE_ICON, 0, 0,
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
		0, 0, hInstance, 0);

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

// ?Rva0005F2B0ProbeCaller@@YA_NPAXH_N@Z absent-from-retail
// The support caller preserves the decoded EDI and two-stack-argument ABI.
Bool Rva0005F2B0ProbeCaller(HINSTANCE hInstance, Int nCmdShow, Bool runWindowed)
{
	return Rva0005F2B0InitializeAppWindows(hInstance, nCmdShow, runWindowed);
}
