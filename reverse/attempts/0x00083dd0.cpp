// ?rva0083DD0@GlobalData@@QBE?AVAsciiString@@XZ
// partial score=0.25 date=2026-09-21
// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
//
// Retail 0x00083DD0, 401 bytes. Reached from W3DDisplay::saveScreenShot only
// through the pinned thunk 0x00036D9A (symbols.csv:
// ?getPath_UserData@ScreenshotGlobalData@@QBE?AVScreenshotAsciiString@@XZ),
// which jmp's straight here. Lazily builds the "legacy" (My Pictures based)
// user-data directory the first time anyone asks for it: GlobalData+0x1284
// is m_userDataDirLegacy, a real member already proven by the landed
// Code/GameEngine/Source/Common/GlobalDataParseDefinition.cpp, which declares
// the identical GlobalData padding layout up to +0x1290 and clears this same
// field. The label string fetched from TheGameText, "APPDATA:PictureFolder",
// was read directly out of mods/dist/lotrbfme.exe's .rdata at VA 0x0107C670.

#include <string.h>
#include "ascii_string.h"
#include "unicode_string.h"

typedef int BOOL;
typedef void *HWND;
typedef char *LPSTR;
#define MAX_PATH 260
#define TRUE 1

extern "C" __declspec(dllimport) BOOL __stdcall CreateDirectoryA(const char *path, void *sa);
extern "C" __declspec(dllimport) BOOL __stdcall SHGetSpecialFolderPathA(HWND hwnd, LPSTR path, int csidl, BOOL create);

// GameTextInterface's vtable: ten unnamed base-class/earlier-overload slots
// (SubsystemInterface plus GameTextInterface's own destructor) precede
// fetch(const Char *, Bool *), matching the target's `call [edx+0x28]`; the
// same shim shape is already landed in
// Code/GameEngine/Source/Common/OnlineHomeRankText.cpp.
class GameTextInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual UnicodeString fetch(const char *label, bool *exists = 0) = 0;
};

extern GameTextInterface *TheGameText;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
// (BFME-only members past m_userDataDir; offsets proven by
// GlobalDataParseDefinition.cpp, which this file's layout matches exactly.)
class GlobalData
{
public:
	unsigned char m_bfme_pad[0x1284];
	AsciiString m_userDataDirLegacy;

	AsciiString rva0083DD0(void) const;
};

extern GlobalData *TheWritableGlobalData;

AsciiString GlobalData::rva0083DD0(void) const
{
	// Retail inlines the emptiness check as a single `mov eax,[this+1284]`
	// (the AsciiString's raw m_text pointer, laid directly at +0x1284 of
	// GlobalData) rather than materialising &m_userDataDirLegacy first and
	// loading through that address; a this-relative raw view gets the same
	// one-instruction field load.
	const char *dataPtr = *(const char *const *)((const char *)this + 0x1284);
	if ((dataPtr == 0 ||
		*(const unsigned short *)(dataPtr + 4) == 0) && TheGameText)
	{
		char temp[MAX_PATH];
		if (SHGetSpecialFolderPathA(0, temp, 0x27, TRUE))
		{
			if (temp[strlen(temp) - 1] != '\\')
				strcat(temp, "\\");

			AsciiString leaf;
			leaf.translate(TheGameText->fetch("APPDATA:PictureFolder"));
			strcat(temp, leaf.str());
			strcat(temp, "\\");

			CreateDirectoryA(temp, 0);
			TheWritableGlobalData->m_userDataDirLegacy = temp;
		}
	}
	return m_userDataDirLegacy;
}
