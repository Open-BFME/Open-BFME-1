// ?getPath_UserData@ScreenshotGlobalData@@QBE?AVScreenshotAsciiString@@XZ
// partial score=0.712 date=2026-09-28
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
//
// The pinned ILT at 0x00036D9A and the call in W3DDisplay::saveScreenShot
// identify this body as ScreenshotGlobalData::getPath_UserData.
// The method creates the screenshot path when GlobalData+0x1284 is empty.
// GlobalDataParseDefinition.cpp declares and clears m_userDataDirLegacy at
// this offset. The current retail baseline stores APPDATA:PictureFolder at
// VA 0x0107C670.

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
// same shim shape appears in
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
};

extern GlobalData *TheWritableGlobalData;

// W3DDisplay.cpp declares ScreenshotAsciiString with one pointer to the string.
// Its destructor pin at 0x00887940 names StringBase<char>::releaseBuffer.
// This view inherits AsciiString to reuse the matched copy and release methods.
class ScreenshotAsciiString : private AsciiString
{
public:
	ScreenshotAsciiString(const ScreenshotAsciiString &that)
		: AsciiString((const AsciiString &)that) {}
	~ScreenshotAsciiString() {}
};

class ScreenshotGlobalData
{
public:
	unsigned char m_pad[0x1284];
	ScreenshotAsciiString m_userDataDirLegacy;

	ScreenshotAsciiString getPath_UserData(void) const;
};

ScreenshotAsciiString ScreenshotGlobalData::getPath_UserData(void) const
{
	// Retail loads the buffer pointer directly into EAX, then computes this
	// field's address in ESI. This source uses a raw view at the same offset.
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
