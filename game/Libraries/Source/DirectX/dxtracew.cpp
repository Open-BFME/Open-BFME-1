// cl: /O1 /G6 /MT /DNDEBUG
// Independent C++ reconstruction of the Summer2003 DXErr9 DXTraceW.
// Microsoft DXUT Core/dxerr.cpp supplies the readable structure (MIT, copyright
// Microsoft Corporation; see license.dxut.txt). The Summer2003 ABI, buffer sizes,
// literals and worker/API calls come independently from the original dxerr9.lib
// member and retail: targets/game/reverse/identity_evidence/dxerr9-summer2003-dxtracew.md
#include <stddef.h>

struct HWND__;
typedef HWND__* HWND;
extern "C" {
__declspec(dllimport) void __stdcall OutputDebugStringW(const wchar_t*);
__declspec(dllimport) int __stdcall MessageBoxW(HWND, const wchar_t*, const wchar_t*, unsigned int);
__declspec(dllimport) void __stdcall DebugBreak();
const wchar_t* __stdcall DXGetErrorString9W(long);
}
long __cdecl StringCchPrintfW(wchar_t*, unsigned int, const wchar_t*, ...);
long __stdcall StringCopyWorkerA(char*, unsigned int, const char*);
long __stdcall StringCopyWorkerW(wchar_t*, unsigned int, const wchar_t*);

// Summer2003 keeps the file name narrow in the wide entry point: it is copied with
// the narrow worker and shown with %S, but the debug-output line formats it with %s
// exactly as the shipped literal does.
extern "C" long __stdcall DXTraceW(const char* strFile, unsigned long dwLine,
                                    long hr, const wchar_t* strMsg, int bPopMsgBox)
{
    wchar_t strBufferLine[128];
    wchar_t strBufferError[256];
    wchar_t strBuffer[3000];
    StringCchPrintfW(strBufferLine, 128, L"%ld", dwLine);
    if (strFile) {
        StringCchPrintfW(strBuffer, 3000, L"%s(%s): ", strFile, strBufferLine);
        OutputDebugStringW(strBuffer);
    }
    if (strMsg)
        OutputDebugStringW(strMsg);
    StringCchPrintfW(strBufferError, 256, L"%s (0x%0.8x)", DXGetErrorString9W(hr), hr);
    StringCchPrintfW(strBuffer, 3000, L" (hr=%s)", strBufferError);
    OutputDebugStringW(strBuffer);
    OutputDebugStringW(L"\n");
    if (bPopMsgBox) {
        char strBufferFile[260];
        StringCopyWorkerA(strBufferFile, 260, "");
        if (strFile)
            StringCopyWorkerA(strBufferFile, 260, strFile);
        wchar_t strBufferMsg[1024];
        StringCopyWorkerW(strBufferMsg, 1024, L"");
        if (strMsg)
            StringCopyWorkerW(strBufferMsg, 1024, strMsg);
        StringCchPrintfW(strBuffer, 3000,
            L"File: %S\nLine: %s\nError Code: %s\nCalling: %s\nDo you want to debug the application?",
            strBufferFile, strBufferLine, strBufferError, strBufferMsg);
        if (MessageBoxW(0, strBuffer, L"Unexpected error encountered", 0x14) == 6)
            DebugBreak();
    }
    return hr;
}
