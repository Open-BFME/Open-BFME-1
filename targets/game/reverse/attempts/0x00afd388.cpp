// _DXTraceA@20
// partial score=0.246 date=2026-11-17
// cl: /O1 /G6 /MT /DNDEBUG
// DXTraceA, Summer 2003 DXErr9 (dxerr9.obj built by 13.00.9178).
// Structure: Microsoft DXUT Core/dxerr.cpp (MIT, license.dxut.txt); ABI, buffer
// sizes, literals and worker/API calls independently BFME 1-proven (see
// attempt_support/dxerr9-summer2003/tracea-blocked.md). Under MSVC 13.10.3077
// this is retail minus the 0x64 EBP bias: 369 B unbiased vs 374 B biased; the
// bias normalisation equals all 374 retail bytes and 22 relocations. 13.10's
// bias heuristic never fires for this frame (strBufferLine at exactly -0x80);
// see attempt_support/dxerr9-summer2003/tracea-bias-heuristic-20261117.md.
struct HWND__;
typedef HWND__* HWND;
extern "C" {
__declspec(dllimport) void __stdcall OutputDebugStringA(const char*);
__declspec(dllimport) int __stdcall MessageBoxA(HWND, const char*, const char*, unsigned int);
__declspec(dllimport) void __stdcall DebugBreak();
const char* __stdcall DXGetErrorString9A(long);
}
long __cdecl StringCchPrintfA(char*, unsigned int, const char*, ...);
long __stdcall StringCopyWorkerA(char*, unsigned int, const char*);

extern "C" long __stdcall DXTraceA(const char* strFile, unsigned long dwLine,
                                    long hr, const char* strMsg, int bPopMsgBox)
{
    char strBufferLine[128];
    char strBufferError[256];
    char strBuffer[3000];
    StringCchPrintfA(strBufferLine, 128, "%ld", dwLine);
    if (strFile) {
        StringCchPrintfA(strBuffer, 3000, "%s(%s): ", strFile, strBufferLine);
        OutputDebugStringA(strBuffer);
    }
    if (strMsg)
        OutputDebugStringA(strMsg);
    StringCchPrintfA(strBufferError, 256, "%s (0x%0.8x)", DXGetErrorString9A(hr), hr);
    StringCchPrintfA(strBuffer, 3000, " (hr=%s)", strBufferError);
    OutputDebugStringA(strBuffer);
    OutputDebugStringA("\n");
    if (bPopMsgBox) {
        char strBufferFile[260];
        StringCopyWorkerA(strBufferFile, 260, "");
        if (strFile)
            StringCopyWorkerA(strBufferFile, 260, strFile);
        char strBufferMsg[1024];
        StringCopyWorkerA(strBufferMsg, 1024, "");
        if (strMsg)
            StringCopyWorkerA(strBufferMsg, 1024, strMsg);
        StringCchPrintfA(strBuffer, 3000,
            "File: %s\nLine: %s\nError Code: %s\nCalling: %s\nDo you want to debug the application?",
            strBufferFile, strBufferLine, strBufferError, strBufferMsg);
        if (MessageBoxA(0, strBuffer, "Unexpected error encountered", 0x14) == 6)
            DebugBreak();
    }
    return hr;
}
