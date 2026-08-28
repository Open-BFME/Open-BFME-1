// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// readable body of ?openFile@FileSystem@@: Code/GameEngine/Source/Common/System/FileSystem.cpp
//
// FileSystem::openFile retail 0x009C8860 size 394 -- recovered as C++ rather
// than left as 394 emitted bytes.
//
// The naked version could not answer a question the DIR32 consistency check was
// asking, because emitted bytes carry no relocations and so name nothing. That
// is not a tidiness point: this function reads BOTH 0x0134CC50 and 0x0134D060,
// so while it was a byte dump it was the one function that could have settled
// which is which and could not be asked. Disassembled, it settles it outright --
// 0x0134D060 is reached through vtable slot 2 and 0x0134CC50 through slot 5, so
// they are different interfaces, matching what FileSystem_doesFileExist.cpp
// records.
//
// WHAT THE THREE byte_134* GLOBALS ARE. The names encode only the address,
// which is all that is proven; the evidence for what each one holds is:
//
//   byte_134CA48  A char[0x100] path prefix. Its setter is the free function at
//                 0x009C8660 (a plain inlined strcpy into the array, cdecl). Its
//                 only caller is GameEngine::init+291, which builds the argument
//                 with AsciiString::format on the literal "Lang\%s" at
//                 0x010766C0 -- so this is the localisation subdirectory, and
//                 sprintf("%s\\%s", byte_134CA48, filename) below is the
//                 language-specific lookup path.
//
//   byte_134CB50  A second char[0x100] prefix, set by the free function at
//                 0x009C8600. That setter differs from the other two: after the
//                 strcpy it checks the last character and appends "\" (the word
//                 at 0x01075318) unless the string already ends in '\' or '/'.
//                 Its one caller, at 0x00063D5F, passes TheWritableGlobalData
//                 (0x012ED5C8) + 0xDC0 as an AsciiString, immediately after
//                 calling TheArchiveFileSystem vtable slot 9 -- a directory out
//                 of global data, applied only when non-empty.
//
//   byte_134CB4C  A Bool, and NOT a suppressor: it selects the search ORDER.
//                 When it is false the archive block below runs BEFORE the local
//                 one; when it is true the archive block runs AFTER instead. It
//                 has three writers outside this function (0x00061BE2 and
//                 0x00061DE6 are whole one-line setters, 0x00062512 sets it
//                 inline), all of which set it to 1.
//
// A third setter of the same shape sits at 0x009C8680 for byte_134C948, which
// this function does not read.
//
// The access-flag tests are retail's: bit 3 (0x08) suppresses the archive
// lookups and bit 1 (0x02) suppresses the local prefixed lookup.
#include <string.h>

// IAT form of sprintf: call dword ptr [__imp__sprintf]
extern "C" int (__cdecl *__imp__sprintf)(char *, const char *, ...);
static inline int do_sprintf(char *b, const char *f, const char *a, const char *c)
{
	return (*__imp__sprintf)(b, f, a, c);
}

class File;

// Retail's string is StringBase<char>; the two-argument concat stays out of line
// as ?concat@?$StringBase@D@@QAEXPBDH@Z, and the one-argument form that computes
// the length is inlined into the caller -- which is why the strlen loop below
// appears in this function's own bytes, guarded against a null pointer.
template <class T> class StringBase
{
public:
	void concat( const T *s, int len );

protected:
	T *m_data;
};

// Retail AsciiString(const char*) is the thin 0x888BC0 body (not ZH
// ensureUniqueBufferOfSize). Same local shim pattern as Upgrade / DifficultySelect.
class BFMERetailAsciiString : public StringBase<char>
{
public:
	BFMERetailAsciiString( const char *string );
	~BFMERetailAsciiString() { releaseBuffer(); }

	const char *str() const
	{
		return m_data ? m_data + 8 : "";
	}

	void concat( const char *s )
	{
		StringBase<char>::concat( s, s ? (int)strlen( s ) : 0 );
	}

private:
	void releaseBuffer();
};

// Slot layouts stay attached to their call sites, because those are what the
// emitted offsets come from.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ArchiveFileSystem.h
class ArchiveFileSystem
{
public:
	virtual ~ArchiveFileSystem() {}
	virtual void A1() = 0;
	virtual void A2() = 0;
	virtual void A3() = 0;
	virtual void A4() = 0;
	// Declared widest-first: MSVC lays out a run of same-name virtual overloads
	// in reverse declaration order, so this is what puts the two-argument form at
	// slot 5 and the four-argument one at slot 6.
	virtual File *openFile( const char *filename, int access, int a3, int a4 ) = 0;	// slot 6 = +0x18
	virtual File *openFile( const char *filename, int access ) = 0;					// slot 5 = +0x14
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/LocalFileSystem.h
class LocalFileSystem
{
public:
	virtual ~LocalFileSystem() {}
	virtual void L1() = 0;
	virtual File *openFile( const char *filename, int access, int a3, int a4 ) = 0;	// slot 3 = +0x0c
	virtual File *openFile( const char *filename, int access ) = 0;					// slot 2 = +0x08
};

extern ArchiveFileSystem *TheArchiveFileSystem;
extern LocalFileSystem *TheLocalFileSystem;
extern char byte_134CA48[];
extern char byte_134CB50[];
extern bool byte_134CB4C;

class FileSystem
{
public:
	File *openFile( const char *filename, int access );
	File *openFile( const char *filename, int access, int a3, int a4 );
};

// ?openFile@FileSystem@@QAEPAVFile@@PBDH@Z
File *FileSystem::openFile( const char *filename, int access )
{
	char buf[0x200];
	File *file = NULL;

	do_sprintf( buf, "%s\\%s", byte_134CA48, filename );

	if( byte_134CB50[0] )
	{
		BFMERetailAsciiString path( byte_134CB50 );
		path.concat( filename );
		file = TheLocalFileSystem->openFile( path.str(), access );
	}

	if( !byte_134CB4C && file == NULL && TheArchiveFileSystem )
	{
		if( !(access & 8) )
			file = TheArchiveFileSystem->openFile( buf, access );
		if( file == NULL )
			file = TheArchiveFileSystem->openFile( filename, access );
	}

	if( TheLocalFileSystem && file == NULL )
	{
		if( !(access & 2) )
			file = TheLocalFileSystem->openFile( buf, access );
		if( file == NULL )
			file = TheLocalFileSystem->openFile( filename, access );
	}

	if( byte_134CB4C && file == NULL && TheArchiveFileSystem )
	{
		if( !(access & 8) )
		{
			File *f = TheArchiveFileSystem->openFile( buf, access );
			if( f != NULL )
				return f;
		}
		return TheArchiveFileSystem->openFile( filename, access );
	}

	return file;
}

// ?openFile@FileSystem@@QAEPAVFile@@PBDHHH@Z
// BFME's wide form, retail 0x009C89F0, 445 bytes. Structurally the narrow one
// above with two more arguments threaded into every downstream call, and the
// calls go one slot further on: LocalFileSystem slot 3 rather than 2, and
// ArchiveFileSystem slot 6 rather than 5. Nothing in the image says what the two
// extra parameters mean -- Win32LocalFileSystem's narrow forwarder passes them
// as zero -- so they keep positional names.
File *FileSystem::openFile( const char *filename, int access, int a3, int a4 )
{
	char buf[0x200];
	File *file = NULL;

	do_sprintf( buf, "%s\\%s", byte_134CA48, filename );

	if( byte_134CB50[0] )
	{
		BFMERetailAsciiString path( byte_134CB50 );
		path.concat( filename );
		file = TheLocalFileSystem->openFile( path.str(), access, a3, a4 );
	}

	if( !byte_134CB4C && file == NULL && TheArchiveFileSystem )
	{
		if( !(access & 8) )
			file = TheArchiveFileSystem->openFile( buf, access, a3, a4 );
		if( file == NULL )
			file = TheArchiveFileSystem->openFile( filename, access, a3, a4 );
	}

	if( TheLocalFileSystem && file == NULL )
	{
		if( !(access & 2) )
			file = TheLocalFileSystem->openFile( buf, access, a3, a4 );
		if( file == NULL )
			file = TheLocalFileSystem->openFile( filename, access, a3, a4 );
	}

	// Note the test order: the wide form checks TheArchiveFileSystem before
	// file == NULL, where the narrow one above does it the other way round.
	if( byte_134CB4C && TheArchiveFileSystem && file == NULL )
	{
		if( !(access & 8) )
		{
			File *f = TheArchiveFileSystem->openFile( buf, access, a3, a4 );
			if( f != NULL )
				return f;
		}
		return TheArchiveFileSystem->openFile( filename, access, a3, a4 );
	}

	return file;
}
