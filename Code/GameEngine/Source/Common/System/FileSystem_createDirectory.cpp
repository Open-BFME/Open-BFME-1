// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/ini /Ireference/shims/iniexception /Ireference/shims/ini_noinline /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
// readable body of ?createDirectory@FileSystem@@: Code/GameEngine/Source/Common/System/FileSystem.cpp
//
// FileSystem::createDirectory, recovered as C++ rather than left as 144 emitted
// bytes. The body is Zero Hour's unchanged: null-check the local file system and
// forward the directory name to it.
//
// Worth recording while it is fresh: the naked version could not answer the
// question the DIR32 consistency check was asking about ?TheLocalFileSystem@@,
// because emitted bytes carry no relocations and so name nothing. Disassembled,
// this function loads 0x0134D060 -- which reverse/symbols.csv already names
// TheLocalFileSystem -- so it is not the source of that conflict. That is a
// thing the C++ says and the byte dump could not.
//
// createDirectory is virtual slot 7 on LocalFileSystem, reached at +0x1c.
#include "PreRTS.h"
#include "Common/AsciiString.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/LocalFileSystem.h
class LocalFileSystem
{
public:
	virtual void _bfme_slot0( void ) = 0;
	virtual void _bfme_slot1( void ) = 0;
	virtual void _bfme_slot2( void ) = 0;
	virtual void _bfme_slot3( void ) = 0;
	virtual void _bfme_slot4( void ) = 0;
	virtual void _bfme_slot5( void ) = 0;
	virtual void _bfme_slot6( void ) = 0;
	virtual Bool createDirectory( AsciiString directory ) = 0;	// slot 7, +0x1c
};

extern LocalFileSystem *TheLocalFileSystem;

class FileSystem
{
public:
	Bool createDirectory( AsciiString directory );
};

Bool FileSystem::createDirectory( AsciiString directory )
{
	if( TheLocalFileSystem != NULL )
	{
		return TheLocalFileSystem->createDirectory( directory );
	}
	return FALSE;
}
