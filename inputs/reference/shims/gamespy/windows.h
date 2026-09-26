#pragma once
// <windows.h> stand-in for the vendored GameSpy SDK, which is C -- the sweep
// shim next door is C++-only (it declares `struct IDispatch` and an
// `operator==(const GUID&, const GUID&)`), so a C translation unit cannot use it.
// Scoped to the GameSpy TUs through -Ireference/shims/gamespy in their `// cl:`
// banner, so it can never shadow <windows.h> for anything else in the tree.
// Declarations mirror the real PlatformSDK (dllimport + __stdcall, exact struct
// layouts); equivalence is not assumed, it is proven -- building the SDK against
// this reproduces the identical whole-function image hits, at identical RVAs and
// sizes, that the real PlatformSDK headers produce.
#ifndef GAMESPY_WINDOWS_SHIM_H
#define GAMESPY_WINDOWS_SHIM_H

#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned short WORD;
typedef unsigned long DWORD;
typedef unsigned char BYTE;
typedef int BOOL;
typedef long LONG;
typedef unsigned long ULONG;
typedef unsigned int UINT;
typedef char CHAR;
typedef wchar_t WCHAR;
typedef char *LPSTR;
typedef const char *LPCSTR;
typedef WCHAR *LPWSTR;
typedef const WCHAR *LPCWSTR;
typedef void *LPVOID;
typedef const void *LPCVOID;
typedef void *HANDLE;
typedef DWORD *LPDWORD;
typedef BYTE *LPBYTE;
typedef long *PLONG;
typedef unsigned long ULONG_PTR;

#define WINAPI __stdcall
#define TRUE 1
#define FALSE 0
#define MAX_PATH 260
#define INFINITE 0xFFFFFFFF
#define INVALID_HANDLE_VALUE ((HANDLE)(long)-1)

typedef union _LARGE_INTEGER {
	struct { DWORD LowPart; LONG HighPart; };
	struct { DWORD LowPart; LONG HighPart; } u;
	__int64 QuadPart;
} LARGE_INTEGER;

typedef struct _SECURITY_ATTRIBUTES {
	DWORD nLength;
	LPVOID lpSecurityDescriptor;
	BOOL bInheritHandle;
} SECURITY_ATTRIBUTES, *LPSECURITY_ATTRIBUTES;

typedef struct _SYSTEMTIME {
	WORD wYear, wMonth, wDayOfWeek, wDay, wHour, wMinute, wSecond, wMilliseconds;
} SYSTEMTIME, *LPSYSTEMTIME;

typedef DWORD(__stdcall *LPTHREAD_START_ROUTINE)(LPVOID);

/* Exact RTL layout: the 2007 SDK embeds one of these in GSICriticalSection, so
   its size participates in the struct offsets its callers compile against. */
typedef struct _RTL_CRITICAL_SECTION {
	void *DebugInfo;
	LONG LockCount;
	LONG RecursionCount;
	HANDLE OwningThread;
	HANDLE LockSemaphore;
	ULONG_PTR SpinCount;
} CRITICAL_SECTION, *LPCRITICAL_SECTION;

/* Registry: nonport.c's GOAGetUniqueID reads the GameSpy 3D registration key. */
struct HKEY__;
typedef struct HKEY__ *HKEY;
typedef HKEY *PHKEY;
typedef LONG LSTATUS;

#define HKEY_CLASSES_ROOT   ((HKEY)(ULONG_PTR)((LONG)0x80000000))
#define HKEY_CURRENT_USER   ((HKEY)(ULONG_PTR)((LONG)0x80000001))
#define HKEY_LOCAL_MACHINE  ((HKEY)(ULONG_PTR)((LONG)0x80000002))

#define ERROR_SUCCESS 0L
#define KEY_QUERY_VALUE 0x0001
#define KEY_SET_VALUE 0x0002
#define KEY_CREATE_SUB_KEY 0x0004
#define KEY_READ 0x20019
#define KEY_WRITE 0x20006
#define KEY_ALL_ACCESS 0xF003F
#define REG_NONE 0
#define REG_SZ 1
#define REG_BINARY 3
#define REG_DWORD 4
#define REG_OPTION_NON_VOLATILE 0

#define CP_ACP 0
#define CP_UTF8 65001

#ifdef __cplusplus
extern "C" {
#endif

__declspec(dllimport) DWORD __stdcall GetTickCount(void);
__declspec(dllimport) void __stdcall Sleep(DWORD);
__declspec(dllimport) BOOL __stdcall QueryPerformanceCounter(LARGE_INTEGER *);
__declspec(dllimport) BOOL __stdcall QueryPerformanceFrequency(LARGE_INTEGER *);
__declspec(dllimport) void __stdcall GetSystemTime(LPSYSTEMTIME);
__declspec(dllimport) void __stdcall GetLocalTime(LPSYSTEMTIME);
__declspec(dllimport) DWORD __stdcall GetLastError(void);
__declspec(dllimport) DWORD __stdcall GetCurrentThreadId(void);
__declspec(dllimport) HANDLE __stdcall GetCurrentThread(void);
__declspec(dllimport) BOOL __stdcall CloseHandle(HANDLE);
__declspec(dllimport) HANDLE __stdcall CreateThread(LPSECURITY_ATTRIBUTES, DWORD,
                                                    LPTHREAD_START_ROUTINE, LPVOID,
                                                    DWORD, LPDWORD);
__declspec(dllimport) void __stdcall ExitThread(DWORD);
__declspec(dllimport) BOOL __stdcall TerminateThread(HANDLE, DWORD);
__declspec(dllimport) DWORD __stdcall WaitForSingleObject(HANDLE, DWORD);
__declspec(dllimport) void __stdcall InitializeCriticalSection(LPCRITICAL_SECTION);
__declspec(dllimport) void __stdcall EnterCriticalSection(LPCRITICAL_SECTION);
__declspec(dllimport) void __stdcall LeaveCriticalSection(LPCRITICAL_SECTION);
__declspec(dllimport) void __stdcall DeleteCriticalSection(LPCRITICAL_SECTION);
__declspec(dllimport) HANDLE __stdcall CreateSemaphoreA(LPSECURITY_ATTRIBUTES, LONG, LONG, LPCSTR);
__declspec(dllimport) BOOL __stdcall ReleaseSemaphore(HANDLE, LONG, PLONG);
__declspec(dllimport) LONG __stdcall InterlockedIncrement(PLONG);
__declspec(dllimport) LONG __stdcall InterlockedDecrement(PLONG);
__declspec(dllimport) int __stdcall MultiByteToWideChar(UINT, DWORD, LPCSTR, int, LPWSTR, int);
__declspec(dllimport) int __stdcall WideCharToMultiByte(UINT, DWORD, LPCWSTR, int, LPSTR,
                                                        int, LPCSTR, BOOL *);
__declspec(dllimport) DWORD __stdcall GetModuleFileNameA(HANDLE, LPSTR, DWORD);
__declspec(dllimport) BOOL __stdcall GetComputerNameA(LPSTR, LPDWORD);

__declspec(dllimport) LSTATUS __stdcall RegOpenKeyExA(HKEY, LPCSTR, DWORD, DWORD, PHKEY);
__declspec(dllimport) LSTATUS __stdcall RegCreateKeyExA(HKEY, LPCSTR, DWORD, LPSTR, DWORD,
                                                        DWORD, LPSECURITY_ATTRIBUTES,
                                                        PHKEY, LPDWORD);
__declspec(dllimport) LSTATUS __stdcall RegQueryValueExA(HKEY, LPCSTR, LPDWORD, LPDWORD,
                                                         LPBYTE, LPDWORD);
__declspec(dllimport) LSTATUS __stdcall RegSetValueExA(HKEY, LPCSTR, DWORD, DWORD,
                                                        const BYTE *, DWORD);
__declspec(dllimport) LSTATUS __stdcall RegCloseKey(HKEY);

#ifdef __cplusplus
}
#endif

#endif
