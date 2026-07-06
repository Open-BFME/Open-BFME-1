#pragma once
// Minimal declarations for the Win32 lstr* string helpers rendobj.cpp calls.
// Retail links these from kernel32 (IAT imports); we only need declarations to
// compile to object. Signatures match <winbase.h> so codegen (stdcall IAT call)
// is identical.
#ifndef WINBASE_SHIM_H
#define WINBASE_SHIM_H
extern "C" __declspec(dllimport) char * __stdcall lstrcpyA(char *, const char *);
extern "C" __declspec(dllimport) int    __stdcall lstrlenA(const char *);
extern "C" __declspec(dllimport) int    __stdcall lstrcmpiA(const char *, const char *);
#define lstrcpy  lstrcpyA
#define lstrlen  lstrlenA
#define lstrcmpi lstrcmpiA
#endif
