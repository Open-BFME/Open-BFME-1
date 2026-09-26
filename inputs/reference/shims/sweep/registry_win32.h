#ifndef SWEEP_REGISTRY_WIN32_H
#define SWEEP_REGISTRY_WIN32_H

#include <windows.h>

#define REG_BINARY 3
#define RegEnumValue RegEnumValueA
#define RegDeleteValue RegDeleteValueA
#define RegDeleteKey RegDeleteKeyA
#define RegEnumKeyEx RegEnumKeyExA
#define RegQueryInfoKey RegQueryInfoKeyA

extern "C" {
__declspec(dllimport) LONG WINAPI RegEnumValueA(HKEY, DWORD, LPSTR, LPDWORD, LPDWORD, LPDWORD, LPBYTE, LPDWORD);
__declspec(dllimport) LONG WINAPI RegDeleteValueA(HKEY, LPCSTR);
__declspec(dllimport) LONG WINAPI RegDeleteKeyA(HKEY, LPCSTR);
__declspec(dllimport) LONG WINAPI RegEnumKeyExA(HKEY, DWORD, LPSTR, LPDWORD, LPDWORD, LPSTR, LPDWORD, LPFILETIME);
__declspec(dllimport) LONG WINAPI RegQueryInfoKeyA(HKEY, LPSTR, LPDWORD, LPDWORD, LPDWORD, LPDWORD, LPDWORD, LPDWORD, LPDWORD, LPDWORD, LPDWORD, LPFILETIME);
__declspec(dllimport) LONG WINAPI RegQueryValueExW(HKEY, LPCWSTR, LPDWORD, LPDWORD, LPBYTE, LPDWORD);
__declspec(dllimport) LONG WINAPI RegSetValueExW(HKEY, LPCWSTR, DWORD, DWORD, const BYTE *, DWORD);
}

#include <RAWFILE.H>
#include <INI.H>

#endif
