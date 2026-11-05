// ?getPath00083DD0@ScreenshotGlobalData@@QBE?AVScreenshotAsciiString@@XZ
// Retail RVA 0x00083DD0, 401 bytes.
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
//
// W3DDisplay::saveScreenShot reaches this body through the ILT at 0x00036D9A.
// Its real name is unproven: GlobalData::getPath_UserData is the separate
// matched body at 0x00083D70, and retail's thunk order contradicts that
// spelling here, so the method keeps an address-derived name.
// The method creates the screenshot path when GlobalData+0x1284 is empty.
// GlobalDataParseDefinition.cpp declares and clears m_userDataDirLegacy at
// this offset. The current retail baseline stores APPDATA:PictureFolder at
// VA 0x0107C670.

#include <string.h>
#include "ascii_string.h"
#include "unicode_string.h"

// Retail inlines ~UnicodeString at every scope exit and calls
// StringBase<unsigned short>::releaseBuffer (0x008881D0) directly, never
// the 0x0005EEA0 jmp body the out-of-line declaration would bind to.
inline UnicodeString::~UnicodeString() { ((StringBase<unsigned short> *)this)->releaseBuffer(); }

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
// Retail keeps no distinct ScreenshotAsciiString dtor body: the destructor pin
// at 0x00887940 names StringBase<char>::releaseBuffer.  The out-of-line
// declaration plus the alternatename below route every scope exit to the
// matched releaseBuffer row instead of emitting a non-retail copy here, as
// W3DDisplay.cpp already assumes.
#pragma comment(linker, "/alternatename:??1ScreenshotAsciiString@@QAE@XZ=?releaseBuffer@?$StringBase@D@@AAEXXZ")
class ScreenshotAsciiString : private AsciiString
{
public:
	ScreenshotAsciiString(const ScreenshotAsciiString &that)
		: AsciiString((const AsciiString &)that) {}
	~ScreenshotAsciiString();
};

class ScreenshotGlobalData
{
public:
	unsigned char m_pad[0x1284];
	ScreenshotAsciiString m_userDataDirLegacy;

	ScreenshotAsciiString getPath00083DD0(void) const;
};

ScreenshotAsciiString ScreenshotGlobalData::getPath00083DD0(void) const
{
	// Retail reads the header before retaining the member address for the return.
	const char *dataPtr = *(const char *const *)((const char *)this + 0x1284);
	if ((dataPtr == 0 || *(const unsigned short *)(dataPtr + 4) == 0) && TheGameText)
	{
		char temp[MAX_PATH];
		if (SHGetSpecialFolderPathA(0, temp, 0x27, TRUE))
		{
			// Retail constructs and translates the leaf before inspecting the separator.
			AsciiString leaf;
			leaf.translate(TheGameText->fetch("APPDATA:PictureFolder"));

			if (temp[strlen(temp) - 1] != '\\')
				strcat(temp, "\\");

			strcat(temp, leaf.str());
			strcat(temp, "\\");

			CreateDirectoryA(temp, 0);
			TheWritableGlobalData->m_userDataDirLegacy = temp;
		}
	}
	return m_userDataDirLegacy;
}
