// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Open-BFME: copyReplay, retail 0x004E1090, 760 bytes; deleteReplay, retail
// 0x004E2100, 623 bytes. Converted from gen-dump d_004e1090.asm. ZH twin is
// ReplayMenu.cpp's copyReplay/deleteReplay; this TU keeps its own statics
// (listboxReplayFiles, callCopy, callDelete) rather than sharing
// ReplayMenuInit.cpp's, since DIR32 relocations are patched to the real
// retail address independently of which C++ symbol names them.
// getReplayDir() compiles as a plain static call (no TheRecorder deref).
// GetReplayFilenameFromListbox is ReplayMenuGetReplayFilenameFromListbox.cpp's
// matched twin; only its prototype is needed here.

#include "../../../../../Include/Common/ScalarTypes.h"

typedef unsigned short WideChar;

#include "ascii_string.h"
#include "unicode_string.h"
#include <string.h>

// The retail wide lifetimes call StringBase directly, as the canonical
// message-box caller does.
inline UnicodeString::UnicodeString() : m_text(0) {}
inline UnicodeString::UnicodeString(const UnicodeString &that)
{
    ((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(
        *(const StringBase<unsigned short> *)&that);
}
inline UnicodeString::~UnicodeString()
{
    ((StringBase<unsigned short> *)this)->releaseBuffer();
}

class GameWindow;

// ?GetReplayFilenameFromListbox@@YA?AVUnicodeString@@PAVGameWindow@@H@Z
UnicodeString GetReplayFilenameFromListbox( GameWindow *listbox, Int index );

// ?GadgetListBoxGetSelected@@YAXPAVGameWindow@@PAH@Z
void GadgetListBoxGetSelected( GameWindow *listbox, Int *selected );

// ?GadgetListBoxReset@@YAXPAVGameWindow@@@Z
void GadgetListBoxReset( GameWindow *listbox );
void PopulateReplayFileListbox( GameWindow *listbox );

class GameTextInterface
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual UnicodeString fetch( const char *label, Bool *exists = 0 );
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Recorder.h
class RecorderClass
{
public:
	static AsciiString getReplayDir();
};

extern GameTextInterface *TheGameText;

GameWindow *MessageBoxOk( UnicodeString title, UnicodeString body, void ( *callback )( void ) );

extern "C" __declspec(dllimport) int __stdcall DeleteFileA( const char *fileName );
extern "C" __declspec(dllimport) int __stdcall CopyFileA( const char *existing, const char *newFile, int failIfExists );
extern "C" __declspec(dllimport) unsigned long __stdcall GetLastError();
extern "C" __declspec(dllimport) unsigned long __stdcall FormatMessageA(
	unsigned long flags, const void *source, unsigned long messageId, unsigned long languageId,
	char *buffer, unsigned long size, void *args );
extern "C" __declspec(dllimport) unsigned long __stdcall FormatMessageW(
	unsigned long flags, const void *source, unsigned long messageId, unsigned long languageId,
	WideChar *buffer, unsigned long size, void *args );
extern "C" __declspec(dllimport) int __stdcall SHGetSpecialFolderLocation( void *hwndOwner, int folder, void *pidl );
extern "C" __declspec(dllimport) int __stdcall SHGetPathFromIDListA( void *pidl, char *path );
#pragma comment(lib, "shell32.lib")

enum
{
	CSIDL_DESKTOPDIRECTORY = 0x10,
	FORMAT_MESSAGE_FROM_SYSTEM = 0x1000
};

static GameWindow *listboxReplayFiles = 0;
static Bool callCopy = false;
static Bool callDelete = false;

// ?copyReplay@@YAXXZ
void copyReplay( void )
{
	callCopy = false;
	Int selected;
	GadgetListBoxGetSelected( listboxReplayFiles, &selected );
	if ( selected < 0 )
	{
		MessageBoxOk( TheGameText->fetch( "GUI:NoFileSelected" ), TheGameText->fetch( "GUI:PleaseSelectAFile" ), 0 );
		return;
	}

	AsciiString filename, translate;
	filename = RecorderClass::getReplayDir();
	translate.translate( GetReplayFilenameFromListbox( listboxReplayFiles, selected ) );
	filename.StringBase<char>::concat( translate.str(), translate.StringBase<char>::getLength() );

	char path[ 1024 ];
	void *pidl;
	SHGetSpecialFolderLocation( 0, CSIDL_DESKTOPDIRECTORY, &pidl );
	SHGetPathFromIDListA( pidl, path );
	AsciiString newFilename;
	newFilename.StringBase<char>::set( path, (Int)strlen(path) );
	newFilename.StringBase<char>::concat( "\\", 1 );
	newFilename.StringBase<char>::concat( translate.str(), translate.StringBase<char>::getLength() );

	if ( CopyFileA( filename.str(), newFilename.str(), 0 ) == 0 )
	{
		WideChar buffer[ 1024 ];
		FormatMessageW( FORMAT_MESSAGE_FROM_SYSTEM, 0, GetLastError(), 0, buffer, sizeof( buffer ), 0 );
		UnicodeString errorStr;
		((StringBase<unsigned short> *)&errorStr)->set( buffer, (Int)wcslen(buffer) );
		((StringBase<unsigned short> *)&errorStr)->trim();
		MessageBoxOk( TheGameText->fetch( "GUI:Error" ), errorStr, 0 );
	}
}

// ?deleteReplay@@YAXXZ
void deleteReplay( void )
{
	callDelete = false;
	Int selected;
	GadgetListBoxGetSelected( listboxReplayFiles, &selected );
	if ( selected < 0 )
	{
		MessageBoxOk( TheGameText->fetch( "GUI:NoFileSelected" ), TheGameText->fetch( "GUI:PleaseSelectAFile" ), 0 );
		return;
	}

	AsciiString filename, translate;
	filename = RecorderClass::getReplayDir();
	translate.translate( GetReplayFilenameFromListbox( listboxReplayFiles, selected ) );
	filename.StringBase<char>::concat( translate.str(), translate.StringBase<char>::getLength() );

	if ( DeleteFileA( filename.str() ) == 0 )
	{
		char buffer[ 1024 ];
		FormatMessageA( FORMAT_MESSAGE_FROM_SYSTEM, 0, GetLastError(), 0, buffer, sizeof( buffer ), 0 );
		UnicodeString errorStr;
		translate.StringBase<char>::set( buffer, (Int)strlen(buffer) );
		errorStr.translate( translate );
		MessageBoxOk( TheGameText->fetch( "GUI:Error" ), errorStr, 0 );
	}

	GadgetListBoxReset( listboxReplayFiles );
	PopulateReplayFileListbox( listboxReplayFiles );
}
