// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
//
// GameWindowManager::gogoMessageBox (11-argument overload), retail 0x0047DB60,
// 183 bytes (`ret 0x2c` = x/y/w/h + flags + two by-value UnicodeStrings + four
// callbacks). The body forwards to the 13-argument overload at retail vtable
// slot 12 (call [edx+0x30], resolved to 0x0047EF70) with useLogo=FALSE.
//
// Lifted out of GameWindowManager.cpp like its 12-argument sibling: the shared
// sweep shim there puts the gogoMessageBox overloads at slots 13/14 (one extra
// virtual ahead of them), so a forwarder compiled against it calls the 12-arg
// body at +0x34 instead of retail's +0x30. This TU declares the class with the
// overloads at slots 12/13 and pins the UnicodeString copy ctor / releaseBuffer
// the forwarding body needs.

#include <stddef.h>
#include <string.h>
#include "string_base.h"

typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;

#define FALSE false

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString
{
public:
	UnicodeString( const UnicodeString &that )
	{
		((StringBase<wchar_t> *)this)->StringBase<wchar_t>::StringBase(
			*(const StringBase<wchar_t> *)&that );
	}

	~UnicodeString() { ((StringBase<wchar_t> *)this)->releaseBuffer(); }

private:
	wchar_t *m_data;
};

typedef void (*GameWinMsgBoxFunc)( void );

class GameWindow;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindowManager.h
class GameWindowManager
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	// The two overloads share a name, so MSVC lays them out in reverse
	// declaration order: the 13-argument form (declared second) lands at slot
	// 12, which is exactly where the retail forwarder's `call [edx+0x30]` puts
	// it, and the 11-argument forwarder at slot 13.
	virtual GameWindow *gogoMessageBox( Int x, Int y, Int width, Int height,
			UnsignedShort buttonFlags, UnicodeString titleString,
			UnicodeString bodyString, GameWinMsgBoxFunc yesCallback,
			GameWinMsgBoxFunc noCallback, GameWinMsgBoxFunc okCallback,
			GameWinMsgBoxFunc cancelCallback );
	virtual GameWindow *gogoMessageBox( Int x, Int y, Int width, Int height,
			UnsignedShort buttonFlags, UnicodeString titleString,
			UnicodeString bodyString, GameWinMsgBoxFunc yesCallback,
			GameWinMsgBoxFunc noCallback, GameWinMsgBoxFunc okCallback,
			GameWinMsgBoxFunc cancelCallback, Bool useLogo );
};

// ?gogoMessageBox@GameWindowManager@@UAEPAVGameWindow@@HHHHGVUnicodeString@@0P6AXXZ111@Z
GameWindow *GameWindowManager::gogoMessageBox( Int x, Int y, Int width, Int height,
		UnsignedShort buttonFlags, UnicodeString titleString, UnicodeString bodyString,
		GameWinMsgBoxFunc yesCallback, GameWinMsgBoxFunc noCallback,
		GameWinMsgBoxFunc okCallback, GameWinMsgBoxFunc cancelCallback )
{
	return gogoMessageBox(x, y, width, height, buttonFlags, titleString, bodyString,
			yesCallback, noCallback, okCallback, cancelCallback, FALSE);
}
