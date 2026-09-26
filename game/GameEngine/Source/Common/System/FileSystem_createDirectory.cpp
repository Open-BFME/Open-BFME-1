// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/ini /Iinputs/reference/shims/iniexception /Iinputs/reference/shims/ini_noinline /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
// readable body of ?createDirectory@FileSystem@@: game/GameEngine/Source/Common/System/FileSystem.cpp
//
// FileSystem::createDirectory, recovered as C++ rather than left as 144 emitted
// bytes. The body is Zero Hour's unchanged: null-check the local file system and
// forward the directory name to it.
//
// Worth recording while it is fresh: the naked version could not answer the
// question the DIR32 consistency check was asking about ?TheLocalFileSystem@@,
// because emitted bytes carry no relocations and so name nothing. Disassembled,
// this function loads 0x0134D060 -- which targets/game/reverse/symbols.csv already names
// TheLocalFileSystem -- so it is not the source of that conflict. That is a
// thing the C++ says and the byte dump could not.
//
// createDirectory is virtual slot 7 on LocalFileSystem, reached at +0x1c.
#include "PreRTS.h"
#include "Common/AsciiString.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/LocalFileSystem.h
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
