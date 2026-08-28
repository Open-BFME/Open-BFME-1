// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Win32BIGFileSystem::closeAllFiles, retail 0x009CC3B0 -- vtable slot 7 of
// 0x01143B40, and one byte, a bare ret.
//
// Be clear about what carries this row: a bare ret matches every empty function
// in the image, so the bytes prove nothing and the vtable is the whole evidence.
// That vtable is pinned hard, though. Its constructor at 0x009CC350 chains to
// ArchiveFileSystem's at 0x009CA9E0 and installs 0x01143B40; slot 1 holds the
// "*.big" literal that names the class; slot 9 is what slot 1 calls through
// [eax+0x24]; and slots 5, 6, 8 and 10 are inherited unchanged from the base,
// three of which are matched functions reached by matched callers.
//
// Slot 7 is _purecall on the base and one byte here, which is exactly what Zero
// Hour has -- its Win32BIGFileSystem::closeAllFiles is an empty body. So the
// vtable and the reference agree, which is as much corroboration as a one-byte
// function can carry.
//
// The slot numbering is BFME's, not Zero Hour's. BFME's ArchiveFileSystem runs
// dtor, init, openArchiveFile, closeArchiveFile, closeAllArchiveFiles, openFile,
// openFile-wide, closeAllFiles, doesFileExist, loadBigFilesFromDirectory,
// loadIntoDirectoryTree. Zero Hour declares init/update/reset/postProcessLoad
// first and openFile ninth, so reading the slots off the header gets them wrong.

class File;
class ArchiveFile;
class AsciiString;
typedef int Int;
typedef int Bool;
typedef char Char;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/Win32Device/Common/Win32BIGFileSystem.h
class Win32BIGFileSystem
{
public:
	virtual ~Win32BIGFileSystem();											// slot 0
	virtual void init( void );												// slot 1
	virtual ArchiveFile *openArchiveFile( const Char *filename ) = 0;		// slot 2
	virtual void closeArchiveFile( const Char *filename ) = 0;				// slot 3
	virtual void closeAllArchiveFiles( void ) = 0;							// slot 4
	virtual File *openFile( const Char *filename, Int access, Int a3, Int a4 ) = 0;	// slot 6
	virtual File *openFile( const Char *filename, Int access ) = 0;			// slot 5
	virtual void closeAllFiles( void );										// slot 7
};

// ?closeAllFiles@Win32BIGFileSystem@@UAEXXZ
void Win32BIGFileSystem::closeAllFiles( void )
{
}
