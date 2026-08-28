// cl: /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /MD /EHsc /Ireference/shims/ini /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
//
// Win32BIGFileSystem::closeAllArchiveFiles, retail 0x009CD780, 261 bytes --
// vtable slot 4 of 0x01143B40.
//
// Its own translation unit because it needs exceptions: it opens with the
// fs:[0] prologue, where closeArchiveFile next door has no SEH frame at all.
// Two methods of one class cannot disagree about that inside a TU.
//
// Zero Hour's closeAllArchiveFiles is an empty body -- BFME wrote this one. The
// shape is readable straight off the disassembly: walk the archive map calling
// ArchiveFile slot 5 (getName, which returns by value, hence the return-slot
// push at 0x009CD7C5), collect the names into a vector, then walk the vector
// calling this->slot 3 with each -- and slot 3 is closeArchiveFile, matched next
// door. Collecting first is not incidental: closeArchiveFile erases from the map
// it would otherwise be iterating.

#include "Common/AsciiString.h"
#include <map>
#include <vector>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ArchiveFile.h
class ArchiveFile
{
public:
	virtual ~ArchiveFile();							// slot 0
	virtual void A1() = 0;
	virtual void A2() = 0;
	virtual void A3() = 0;
	virtual void A4() = 0;
	// slot 5 = +0x14
	virtual AsciiString getName( void ) = 0;
};

typedef char Char;
typedef int Int;
typedef int Bool;

typedef std::map<AsciiString, ArchiveFile *> ArchiveFileMap;

class File;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/Win32Device/Common/Win32BIGFileSystem.h
class Win32BIGFileSystem
{
public:
	virtual ~Win32BIGFileSystem();											// slot 0
	virtual void init( void );												// slot 1
	virtual ArchiveFile *openArchiveFile( const Char *filename ) = 0;		// slot 2
	virtual void closeArchiveFile( const Char *filename ) = 0;				// slot 3
	virtual void closeAllArchiveFiles( void );								// slot 4

protected:
	ArchiveFileMap m_archiveFileMap;	// +0x04
};

// ?closeAllArchiveFiles@Win32BIGFileSystem@@UAEXXZ
void Win32BIGFileSystem::closeAllArchiveFiles( void )
{
	std::vector<AsciiString> names;

	ArchiveFileMap::iterator it = m_archiveFileMap.begin();
	while (it != m_archiveFileMap.end()) {
		names.push_back( it->second->getName() );
		++it;
	}

	std::vector<AsciiString>::iterator n = names.begin();
	while (n != names.end()) {
		closeArchiveFile( n->str() );
		++n;
	}
}
