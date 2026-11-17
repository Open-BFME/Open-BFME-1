// cl: /O1 /G6 /MT /DNDEBUG
// Independent C++ reconstruction of the Summer2003 DXErr9 DXTraceA.
// Microsoft DXUT Core/dxerr.cpp supplies the readable structure (MIT, copyright
// Microsoft Corporation; see license.dxut.txt). The Summer2003 ABI, buffer sizes,
// literals and worker/API calls come independently from the original dxerr9.lib
// member and retail: targets/game/reverse/identity_evidence/dxerr9-summer2003-dxtracea.md
//
// Frame lever. The member was built by MSVC 13.00.9178, which biased this frame
// (`lea ebp,[esp-0x64]` ... `add ebp,0x64`). 13.10.3077 biases a frame only when
// three references hit a frame slot based below -0x80, and the 128-byte line buffer
// sits at exactly -0x80 (attempt_support/dxerr9-summer2003/tracea-bias-model-20261117.md).
// frameBiasSlot is never written, so 13.10 packs it with strBufferLine into one
// 132-byte slot based at -0x84; the line buffer stays at [ebp-0x80] and its three
// references now bias the frame. The slot's lowest four bytes are the last four of
// the 260-byte file buffer, declared 256 so that every buffer keeps its retail
// address, and frameBiasSlot[37] is the hr argument at [ebp+0x10]: returning hr
// through it is the slot's one reference and costs no instruction.
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
    long frameBiasSlot[33];
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
        char strBufferFile[256];
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
    return frameBiasSlot[37];
}
