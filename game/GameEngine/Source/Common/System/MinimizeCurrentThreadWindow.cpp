// cl: /DNDEBUG /MD /O2 /Ob2

typedef void *HWND;
typedef long LPARAM;
typedef int BOOL;
typedef unsigned long DWORD;

extern "C" __declspec(dllimport) DWORD __stdcall GetCurrentThreadId(void);
extern "C" __declspec(dllimport) BOOL __stdcall EnumThreadWindows(
	DWORD threadId,
	BOOL (__stdcall *callback)(HWND, LPARAM),
	LPARAM context);
extern "C" __declspec(dllimport) BOOL __stdcall ShowWindow(HWND window, int command);

// The callback at 0x00548D90 is pinned as bfmeEnumThreadWndProc.
extern BOOL __stdcall bfmeEnumThreadWndProc(HWND window, LPARAM context);

void bfmeMinimizeCurrentThreadWindow(void)
{
	HWND window = 0;
	EnumThreadWindows(
		GetCurrentThreadId(),
		&bfmeEnumThreadWndProc,
		reinterpret_cast<LPARAM>(&window));

	if (window != 0) {
		ShowWindow(window, 6);
	}
}
