#pragma once
// Minimal winsock2 shim for GeneralsMD sweep files that only need byte-order helpers.
extern "C" {
__declspec(dllimport) unsigned long __stdcall htonl(unsigned long);
__declspec(dllimport) unsigned short __stdcall htons(unsigned short);
__declspec(dllimport) unsigned long __stdcall ntohl(unsigned long);
__declspec(dllimport) unsigned short __stdcall ntohs(unsigned short);
}
