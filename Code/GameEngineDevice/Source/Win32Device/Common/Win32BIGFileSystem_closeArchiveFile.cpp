// cl: /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /GX- /MD /Ireference/shims/ini /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
//
// Win32BIGFileSystem::closeArchiveFile, retail 0x009CD660, 117 bytes -- vtable
// slot 3 of 0x01143B40.
//
// Identified from what the body does rather than from Zero Hour's declaration
// order, which does not apply here: it constructs an AsciiString from the
// argument, runs it through the archive map's _M_find at 0x009C9B70, deletes the
// mapped ArchiveFile through its slot 0 with the delete flag set, and then
// inlines the whole erase -- _Rebalance_for_erase, releaseBuffer on the node's
// key at +0x10, _M_deallocate of 0x18 bytes, and the size decrement at [edi+4].
//
// Zero Hour's version also compares the name against MUSIC_BIG and stops the
// music. None of that is here: there is no string compare and no audio call in
// 117 bytes, so BFME dropped it.
//
// This TU is built WITHOUT exceptions, and that is load-bearing rather than
// incidental: retail has no SEH frame here despite the AsciiString temporary
// having a destructor. loadBigFilesFromDirectory on the same class opens with
// the fs:[0] prologue, so it was built WITH them. Two methods of one class that
// disagree about exceptions cannot have shared a translation unit, which is a
// fact about how retail's sources were split -- worth knowing before adding
// another method here. Anything needing /EHsc belongs in its own file.

#include "Common/AsciiString.h"
#include <map>

// Complete, and with a virtual destructor: retail's delete is the classic
// null-check plus virtual dispatch (mov ecx,[esi+0x14]; test; mov edx,[ecx];
// push 1; call [edx]). On a forward-declared type delete emits a plain
// operator delete instead, which is four bytes shorter and the wrong shape.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ArchiveFile.h
class ArchiveFile
{
public:
	virtual ~ArchiveFile();
};

typedef char Char;

typedef std::map<AsciiString, ArchiveFile *> ArchiveFileMap;


class File;
typedef int Int;
typedef int Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/Win32Device/Common/Win32BIGFileSystem.h
class Win32BIGFileSystem
{
public:
	virtual ~Win32BIGFileSystem();											// slot 0
	virtual void init( void );												// slot 1
	virtual ArchiveFile *openArchiveFile( const Char *filename ) = 0;		// slot 2
	virtual void closeArchiveFile( const Char *filename );					// slot 3
	virtual void closeAllArchiveFiles( void ) = 0;							// slot 4
	virtual File *openFile( const Char *filename, Int access, Int a3, Int a4 ) = 0;	// slot 6
	virtual File *openFile( const Char *filename, Int access ) = 0;			// slot 5
	virtual void closeAllFiles( void );										// slot 7

protected:
	ArchiveFileMap m_archiveFileMap;	// +0x04
};

// ?closeArchiveFile@Win32BIGFileSystem@@UAEXPBD@Z
void Win32BIGFileSystem::closeArchiveFile( const Char *filename )
{
	ArchiveFileMap::iterator it = m_archiveFileMap.find( filename );
	if (it == m_archiveFileMap.end()) {
		return;
	}

	delete it->second;
	m_archiveFileMap.erase( it );
}
