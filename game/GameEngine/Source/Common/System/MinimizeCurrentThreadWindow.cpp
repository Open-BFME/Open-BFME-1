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

// Retail 0x00948D90 (?b_00548d90@@YAXXZ): the thunk retail's
// EnumThreadWindows callers reference; the body below stays rowed at 0x00548D90.
extern void b_00548d90();

// Retail 0x00548D90, 15 bytes, right before its one user below: Zero Hour's
// debug EnumThreadWndProc (stores the first window and stops enumerating).
BOOL __stdcall bfmeEnumThreadWndProc(HWND window, LPARAM context)
{
	HWND *found = reinterpret_cast<HWND *>(context);
	*found = window;
	return 0;
}

void bfmeMinimizeCurrentThreadWindow(void)
{
	HWND window = 0;
	EnumThreadWindows(
		GetCurrentThreadId(),
		(BOOL (__stdcall *)(HWND, LPARAM))&b_00548d90,
		reinterpret_cast<LPARAM>(&window));

	if (window != 0) {
		ShowWindow(window, 6);
	}
}
