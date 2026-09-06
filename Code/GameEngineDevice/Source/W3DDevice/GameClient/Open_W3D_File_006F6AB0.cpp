// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// BFME W3D file open helper -- retail 0x006F6AB0, size 188.
//
// Fuzzy twin: 0x006F6BA0 (Open_W3D_File.cpp), r0.929, but that twin is a
// __declspec(naked) __emit lift, not clean C++, so this body is written from
// the disassembly directly rather than ported from the twin's source text.
// The two share the exact same prologue/global-check/local-GameFileClass
// shape; the twin's extra two parameters and its 4-arg FileSystem::openFile
// call are absent here -- this is the plain single-argument form.
//
// Shape (matches d_006f2cc0.asm 0x006F6AB0):
//   if (!g_012F8228 || !TheFileSystem) return NULL;
//   GameFileClass file(filename);          // ??0GameFileClass@@QAE@PBD@Z, matched, W3DFileSystem.cpp
//   if (!file.m_fileExists) return NULL;   // compiler-generated dtor + SEH cleanup
//   File *result = TheFileSystem->openFile(file.m_filePath, 0x41);
//   return result;                          // compiler-generated dtor + SEH cleanup
//
// The local's destructor call is a plain direct call in retail (not a vtable
// dispatch), matching an ordinary automatic-storage RAII local whose scope
// spans both return points -- which is also what produces the two SEH-state
// writes (0 after construction, -1 immediately before each destructor call)
// seen in the dump. reverse/symbols.csv already pins this destructor's
// address (0x00001776) under a placeholder name, "??1Gen_dtor_006f6380@@UAE@XZ",
// with the identity left open; this TU adds a second, additive pin for the
// same address under GameFileClass's real mangled destructor name (see the
// symbols.csv note), which is what lets a normal RAII local -- rather than a
// manual reinterpret_cast call -- reproduce the exact SEH bookkeeping. Nothing
// about the existing placeholder pin is edited or removed.
//
// g_012F8228 is an unnamed/unpinned global read-only as a truth test; no
// other TU references it yet.

class File;

class GameFileClass
{
public:
	GameFileClass( char const *filename );
	virtual ~GameFileClass();

	void   *m_theFile;
	char    m_fileExists;
	char    m_filePath[260];
	char    m_filename[260];
};

class FileSystem
{
public:
	File *openFile( const char *filename, int access );
};

extern int    *g_012F8228;
extern FileSystem *TheFileSystem;

// ?d_006f6ab0@@YAXXZ -- address-derived; real name/signature not recovered.
void *Rva006F6AB0_OpenW3DFile( const char *filename )
{
	if ( !g_012F8228 || !TheFileSystem )
		return 0;

	GameFileClass file( filename );

	if ( !file.m_fileExists )
		return 0;

	File *result = TheFileSystem->openFile( file.m_filePath, 0x41 );
	return (void *)result;
}
