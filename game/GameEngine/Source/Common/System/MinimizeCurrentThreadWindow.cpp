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

// The callback body at 0x00548D90 is already pinned by its generated-body
// identity. Give that body its real callback type only at this use site.
extern void b_00548d90(void);

void bfmeMinimizeCurrentThreadWindow(void)
{
	HWND window = 0;
	EnumThreadWindows(
		GetCurrentThreadId(),
		reinterpret_cast<BOOL (__stdcall *)(HWND, LPARAM)>(&b_00548d90),
		reinterpret_cast<LPARAM>(&window));

	if (window != 0) {
		ShowWindow(window, 6);
	}
}
