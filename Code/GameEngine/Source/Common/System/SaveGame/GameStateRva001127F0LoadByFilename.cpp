// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
//
// Retail 0x001127F0, 254 bytes through the int3 run at +0xFE; Ghidra split it
// at the success arm (+0xAE).  It resolves the leaf name to its path in the
// save directory, fills an AvailableGameInfo (ZH layout: filename, a 0x30-byte
// SaveGameInfo, next/prev) from that file, and loads it by value through the
// loadGame body behind ILT 0x00016716; 1 when the file yields no save info.
// Nothing calls it directly, so the method keeps the address.
//
// Retail opens no EH state between the filename and the SaveGameInfo
// constructor, which a throw() constructor reproduces, and zeroes next/prev
// only after the filename is assigned.  The loadGame call is spelled through
// the name pinned on that ILT; the ledger's GameState::loadGame row sits at a
// different address (0x001109CF).

#include "ascii_string.h"

typedef bool Bool;
typedef int Int;

enum SaveCode { SC_INVALID = -1, SC_OK, SC_NO_FILE_AVAILABLE };

class SaveGameInfo
{
public:
	SaveGameInfo() throw();
	~SaveGameInfo();
private:
	char m_unmodelled00[ 0x30 ];
};

struct AvailableGameInfo
{
	AvailableGameInfo() {}
	AvailableGameInfo( const AvailableGameInfo &that );
	~AvailableGameInfo();

	AsciiString filename;
	SaveGameInfo saveGameInfo;
	AvailableGameInfo *next;
	AvailableGameInfo *prev;
};

class BfmePopupSaveGameState
{
public:
	SaveCode loadGame( AvailableGameInfo gameInfo );
};

class GameState
{
public:
	AsciiString getFilePathInSaveDirectory( const AsciiString &leaf ) const;
	Bool getSaveGameInfoFromFile( AsciiString filename, SaveGameInfo *saveGameInfo );
	SaveCode rva001127F0( const AsciiString &filename );
};

SaveCode GameState::rva001127F0( const AsciiString &filename )
{
	AsciiString filepath = getFilePathInSaveDirectory( filename );
	AvailableGameInfo info;
	info.filename = filename;
	info.next = 0;
	info.prev = 0;
	if( getSaveGameInfoFromFile( filepath, &info.saveGameInfo ) == false )
		return SC_NO_FILE_AVAILABLE;

	return ( (BfmePopupSaveGameState *)this )->loadGame( info );
}
