// _Rva0088DC30DialogProc@16
// partial score=0.85 date=2026-09-02
// cl: /DNDEBUG /MD /EHs-c- /Oy-
// Open-BFME: dialog proc. WM_INITDIALOG falls through; WM_COMMAND with
// IDOK (1) or IDRETRY (4) calls EndDialog. Unused 0x48-byte frame.

typedef void *HWND;
typedef unsigned int UINT;
typedef unsigned int WPARAM;
typedef long LPARAM;
typedef int INT_PTR;

extern "C" __declspec(dllimport) INT_PTR __stdcall EndDialog(HWND hDlg, INT_PTR nResult);

enum
{
	WM_INITDIALOG = 0x0110,
	WM_COMMAND = 0x0111
};

// _Rva0088DC30DialogProc@16
extern "C" INT_PTR __stdcall Rva0088DC30DialogProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM)
{
	switch (msg)
	{
	case WM_INITDIALOG:
		return 0;
	case WM_COMMAND:
	{
		unsigned short id = (unsigned short)wParam;
		if (id == 1 || id == 4)
			EndDialog(hDlg, id);
		return 0;
	}
	default:
		return 0;
	}
}
