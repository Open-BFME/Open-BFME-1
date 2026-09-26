#pragma once
// Minimal dbghelp.h shim for sweeping — debug_stack.cpp uses StackWalk,
// SymGetModuleBase, etc. from DbgHelp.dll for runtime stack traces.
#ifndef SWEEP_DBGHELP_SHIM_H
#define SWEEP_DBGHELP_SHIM_H

#include <windows.h>

typedef struct _IMAGEHLP_LINE {
    DWORD SizeOfStruct;
    void *Key;
    DWORD LineNumber;
    char *FileName;
    DWORD Address;
} IMAGEHLP_LINE, *PIMAGEHLP_LINE;

typedef struct _IMAGEHLP_SYMBOL {
    DWORD SizeOfStruct;
    DWORD Address;
    DWORD Size;
    DWORD Flags;
    DWORD MaxNameLength;
    char Name[1];
} IMAGEHLP_SYMBOL, *PIMAGEHLP_SYMBOL;

typedef struct _IMAGEHLP_MODULE {
    DWORD SizeOfStruct;
    DWORD BaseOfImage;
    DWORD ImageSize;
    DWORD TimeDateStamp;
    DWORD CheckSum;
    DWORD NumSyms;
    unsigned int SymType;
    char ModuleName[32];
    char ImageName[256];
    char LoadedImageName[256];
} IMAGEHLP_MODULE, *PIMAGEHLP_MODULE;

typedef struct _ADDRESS {
    DWORD Offset;
    WORD Segment;
    DWORD Mode;
} ADDRESS, *LPADDRESS;

typedef struct _KDHELP {
    DWORD Thread;
    DWORD ThCallbackStack;
    DWORD ThCallbackBStore;
    DWORD NextCallback;
    DWORD FramePointer;
    DWORD KiCallUserMode;
    DWORD KeUserCallbackDispatcher;
    DWORD SystemRangeStart;
    DWORD Reserved[8];
} KDHELP, *PKDHELP;

typedef struct _STACKFRAME {
    ADDRESS AddrPC;
    ADDRESS AddrReturn;
    ADDRESS AddrFrame;
    ADDRESS AddrStack;
    void *FuncTableEntry;
    DWORD Params[4];
    BOOL Far;
    BOOL Virtual;
    DWORD Reserved[3];
    KDHELP KdHelp;
} STACKFRAME, *LPSTACKFRAME;

#define IMAGE_FILE_MACHINE_I386 0x014c
#define AddrModeFlat 3
#define SYMOPT_UNDNAME 0x00000002

typedef BOOL (CALLBACK *PREAD_PROCESS_MEMORY_ROUTINE)(HANDLE, DWORD, void *, DWORD, LPDWORD);
typedef void * (CALLBACK *PFUNCTION_TABLE_ACCESS_ROUTINE)(HANDLE, DWORD);
typedef DWORD (CALLBACK *PGET_MODULE_BASE_ROUTINE)(HANDLE, DWORD);
typedef DWORD (CALLBACK *PTRANSLATE_ADDRESS_ROUTINE)(HANDLE, DWORD, LPADDRESS);
#define SYMOPT_LOAD_LINES 0x00000010
#define SYMOPT_DEFERRED_LOADS 0x00000004

extern "C" {
__declspec(dllimport) BOOL WINAPI SymInitialize(HANDLE, const char *, BOOL);
__declspec(dllimport) BOOL WINAPI SymCleanup(HANDLE);
__declspec(dllimport) BOOL WINAPI SymSetOptions(DWORD);
__declspec(dllimport) BOOL WINAPI SymGetModuleBase(HANDLE, DWORD);
__declspec(dllimport) BOOL WINAPI SymGetModuleInfo(HANDLE, DWORD, PIMAGEHLP_MODULE);
__declspec(dllimport) BOOL WINAPI SymGetLineFromAddr(HANDLE, DWORD, LPDWORD, PIMAGEHLP_LINE);
__declspec(dllimport) BOOL WINAPI StackWalk(DWORD, HANDLE, HANDLE, LPSTACKFRAME, void *, void *, void *, void *, void *);
}

#endif
