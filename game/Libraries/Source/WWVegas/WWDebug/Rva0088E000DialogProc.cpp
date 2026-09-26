// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c- /Oy-
// Open-BFME: neutral raw-ABI conversion of the 0x0088E000 dialog callback.
// The generated row has no direct named caller; the callback boundary and
// USER32/message relocations are established from the retail body.

typedef int BOOL;
typedef void *HWND;
typedef unsigned int UINT;
typedef unsigned int WPARAM;
typedef long LPARAM;
typedef long LRESULT;

extern "C"
{
	__declspec(dllimport) BOOL __stdcall EndDialog(HWND, int);
	__declspec(dllimport) HWND __stdcall GetDlgItem(HWND, int);
	__declspec(dllimport) BOOL __stdcall ShowWindow(HWND, int);
	__declspec(dllimport) BOOL __stdcall SetWindowTextA(HWND, const char *);
	__declspec(dllimport) LRESULT __stdcall SendDlgItemMessageA(HWND, int, UINT, WPARAM, LPARAM);

	// These are existing parent/current-tree bindings for the two dialog
	// text-pointer relocations.
	extern const char *g_rva0088E000MessageText;
	extern const char *g_rva0088E000WindowText;

	// The caller consumes only AL; use the existing C-linkage spelling for
	// the actual 0x0088EAF0 thunk without adding a new identity pin.
	unsigned char Rva0088EAF0IsDebuggerPresent(void);
}

// ?Rva0088E000DialogProc@@YGHPAXIIJ@Z
int __stdcall Rva0088E000DialogProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM)
{
	switch (uMsg)
	{
	case 0x110:
		if (!Rva0088EAF0IsDebuggerPresent())
			ShowWindow(GetDlgItem(hWnd, 2), 0);
		SetWindowTextA(hWnd, g_rva0088E000WindowText);
		SendDlgItemMessageA(hWnd, 100, 0xC, 0, (LPARAM)g_rva0088E000MessageText);
		return 1;

	case 0x111:
		if ((unsigned short)wParam == 1 || (unsigned short)wParam == 2 ||
			(unsigned short)wParam == 3 || (unsigned short)wParam == 5 ||
			(unsigned short)wParam == 7)
			EndDialog(hWnd, (unsigned short)wParam);
	}

	return 0;
}
