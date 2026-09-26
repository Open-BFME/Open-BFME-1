// ?d_0005f2b0@@YAXXZ
// partial score=0.23 date=2026-09-20
// Probe reconstruction for the BFME application-window initializer.
// The integration caller is intentionally absent from retail.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/stringinline /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main

#include <windows.h>
#include "StringInline.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int WindowedFlag;

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
	virtual void slotA0(void *value);
};

#define TheBfmeAwakenDebug (*(BfmeAwakenDebug **)0x01336E5C)
UnicodeString getBfmeDisplayName();

static HINSTANCE &applicationInstance()
{
	return *reinterpret_cast<HINSTANCE *>(0x012ED234);
}

static HWND &applicationWindow()
{
	return *reinterpret_cast<HWND *>(0x012ED238);
}

static Bool &initializing()
{
	return *reinterpret_cast<Bool *>(0x012ED248);
}

static Bool &doPaint()
{
	return *reinterpret_cast<Bool *>(0x012A6514);
}

static const wchar_t *windowClassName()
{
	return *reinterpret_cast<const wchar_t *const *>(0x012A6504);
}

__forceinline const unsigned short *UnicodeString::str() const
{
	return m_data ? m_data->m_text : reinterpret_cast<const unsigned short *>(0x0107388C);
}

static Bool Rva0005F2B0InitializeAppWindows(
	HINSTANCE hInstance, volatile Int nCmdShow, WindowedFlag runWindowed)
{
	DWORD windowStyle;
	Int startWidth = 800;
	Int startHeight = 600;
	WindowedFlag debugFlag = runWindowed;
	TheBfmeAwakenDebug->slotA0((void *)(ULONG_PTR)debugFlag);
	WNDCLASSW wndClass = { CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS,
		(WNDPROC)0x0043206A, 0, 0, hInstance,
		(HICON)LoadImageA(hInstance, "lotrbfme.ico", IMAGE_ICON, 0, 0,
		LR_LOADFROMFILE | LR_DEFAULTSIZE),
		NULL, (HBRUSH)GetStockObject(BLACK_BRUSH), NULL, windowClassName() };
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
	UnicodeString displayName = getBfmeDisplayName();
	const unsigned short *title = displayName.str();
	if (title == NULL)
		title = reinterpret_cast<const unsigned short *>(0x0107388C);

	HWND hWnd = CreateWindowExW(
		0, windowClassName(), title, windowStyle,
		(GetSystemMetrics(SM_CXSCREEN) / 2) - (startWidth / 2),
		(GetSystemMetrics(SM_CYSCREEN) / 2) - (startHeight / 2),
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

Bool Rva0005F2B0ProbeCaller(HINSTANCE hInstance, Int nCmdShow, Bool runWindowed)
{
	return Rva0005F2B0InitializeAppWindows(hInstance, nCmdShow, runWindowed);
}
