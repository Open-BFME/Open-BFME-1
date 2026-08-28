// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD
//
// Win32BIGFileSystem's two destructors.
//
//   ??1Win32BIGFileSystem@@   0x009CC370, 11 bytes: installs its own vtable
//                             0x01143B40 and tail-jumps to ~ArchiveFileSystem at
//                             0x009CA550, which is matched.
//   ??_GWin32BIGFileSystem@@  0x009CC440, 30 bytes: slot 0 of that same vtable,
//                             and it calls the scalar one above.
//
// The pair confirms itself -- the deleting destructor's call to the scalar one
// is a REL32, which build.py resolves by name and compares against retail, so a
// wrong address for either fails rather than hides. That is worth stating
// because a 30-byte deleting destructor is otherwise the classic unfalsifiable
// row: strip the two relocations and every one of them looks the same.
//
// The base is declared with the vtable slots BFME actually uses, not Zero Hour's
// order -- see docs/filesystem_family.md. Only the count and the destructor
// matter for these two bodies, but getting the count wrong would silently move
// slot 0.

class AsciiString;
class ArchiveFile;
class File;
typedef char Char;
typedef int Int;
typedef int Bool;

class ArchiveFileMapStandIn
{
	void *m_node[4];	// _Rb_tree is 0x10 bytes; only the size matters here
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ArchiveFileSystem.h
class ArchiveFileSystem
{
public:
	virtual ~ArchiveFileSystem();											// slot 0
	virtual void init( void ) = 0;											// slot 1
	virtual ArchiveFile *openArchiveFile( const Char *filename ) = 0;		// slot 2
	virtual void closeArchiveFile( const Char *filename ) = 0;				// slot 3
	virtual void closeAllArchiveFiles( void ) = 0;							// slot 4
	virtual File *openFile( const Char *f, Int a, Int a3, Int a4 ) = 0;		// slot 6
	virtual File *openFile( const Char *f, Int a ) = 0;						// slot 5
	virtual void closeAllFiles( void ) = 0;									// slot 7
	virtual Bool doesFileExist( const Char *filename ) const = 0;			// slot 8
	virtual Bool loadBigFilesFromDirectory( void ) = 0;						// slot 9
	virtual void loadIntoDirectoryTree( void ) = 0;							// slot 10

protected:
	ArchiveFileMapStandIn m_archiveFileMap;	// +0x04
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/Win32Device/Common/Win32BIGFileSystem.h
class Win32BIGFileSystem : public ArchiveFileSystem
{
public:
	virtual ~Win32BIGFileSystem();
};

// ??1Win32BIGFileSystem@@UAE@XZ
Win32BIGFileSystem::~Win32BIGFileSystem()
{
}
