// ?openArchiveFile@Win32BIGFileSystem@@UAEPAVArchiveFile@@PBD@Z
// partial score=0.91 date=2026-09-19
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /Ireference/shims/sweep
//
// Win32BIGFileSystem::openArchiveFile, retail 0x009CC710, 832 bytes -- vtable
// slot 2 of 0x01143B40.
//
// Written from the disassembly rather than adapted from Zero Hour, because the
// two are structured differently in three ways:
//
//   * Zero Hour reads the header in three four-byte reads; retail reads sixteen
//     bytes in one call and checks the return equals 16.
//   * Zero Hour recognises one identifier; retail tries the tag against both
//     "BIGF" (0x012D9030) and "BIG4" (0x012D9034) with strncmp and accepts
//     either.
//   * Zero Hour walks the directory entry by entry, issuing a read per field and
//     a byte-at-a-time loop per name. Retail allocates one buffer with
//     operator new[] of archiveFileSize - 0x10, reads the WHOLE directory into
//     it in a single read, and then parses it in memory. The parse loop does no
//     file I/O, which is why it slices names with the private three-argument
//     StringBase constructor instead of building them a character at a time.
//
// ntohl is expanded inline in registers on both the header fields and every
// entry's offset and size, so there is no call for it.
//
// STATE: compiles to 832 bytes against retail's 832, NOT claimed. The prologue,
// epilogue, every call target and every constant agree; what is left is a
// handful of codegen idioms and the register assignment.
//
// Fixed since the first attempt, each of which moved it:
//   * the separator scan runs backwards from the end of the name, as retail
//     does (mov al,[esi+ebp]; cmp; dec ebp; jns), not forwards tracking the
//     last hit;
//   * two index variables rather than one -- retail's frame is four bytes
//     larger, and a single `sep` is four bytes short of it;
//   * the byte-swap written as (v>>24) | ((v>>8)&0xFF00) | ((v<<8)&0xFF0000) |
//     (v<<24).
//
// Still different:
//   * the operator-new null check. Retail stores the pointer to a stack slot in
//     BOTH arms (mov [esp+0x10],edi / mov [esp+0x10],ebx) where this keeps it
//     only in a register, which makes retail's skip 0x0f bytes against 0x0b.
//   * the fp == NULL test. Retail branches over a short inline early-return
//     block (jne +0x28); here the compiler merges that return with the later
//     ones and jumps far (je +0xdd). Retail's three returns evidently are not
//     all interchangeable -- probably they clean up different amounts.
//   * register assignment on top of both: fp in edi where retail has ebp.
//
// Things tried that do NOT help: hoisting archiveFileSize - 0x10 into a local,
// moving the m_archiveFilename set inside the loop, and declaring
// archiveFileName before fp.

#include <stddef.h>
#include <string.h>
#include "string_base.h"

// Declared, not inherited from a header: without these in scope MSVC lowers
// `new char[n]` to the scalar operator new, while retail calls operator new[].
extern void * __cdecl operator new[](size_t size);
extern void __cdecl operator delete[](void *p);

typedef char Char;
typedef int Int;
typedef int Bool;
typedef unsigned int UnsignedInt;

// The delegating shim: the constructor is defined here and forwards to
// StringBase<char> rather than being left an undefined extern. Left as an
// extern the temporary is opaque and its unwind record is scheduled after the
// receiver, which costs two bytes per by-value temporary -- see the note in
// Win32BIGFileSystem_init.cpp.
class AsciiString
{
public:
	AsciiString() : m_data( 0 ) { }

	AsciiString( const char *s )
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase( s );
	}

	AsciiString( const AsciiString &src, int start, int len )
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&src, start, len );
	}

	~AsciiString()
	{
		((StringBase<char> *)this)->releaseBuffer();
	}

	void set( const char *s, int len ) { ((StringBase<char> *)this)->set( s, len ); }
	void set( const AsciiString &s )   { ((StringBase<char> *)this)->set( *(const StringBase<char> *)&s ); }
	void toLower()                     { ((StringBase<char> *)this)->toLower(); }

private:
	char *m_data;
};

// ntohl, expanded. Retail has no call for it -- the swap is done in registers
// on both header fields and on every entry's offset and size.
static inline Int ntohl_inline( Int v )
{
	// Sum rather than or, and an unsigned high shift: retail folds the two low
	// terms into ((v << 16) + (v & 0xff00)) << 8 and uses shr, which it can only
	// do for + on an unsigned value.
	unsigned int u = (unsigned int)v;
	return (Int)((u << 24) + ((u << 8) & 0xFF0000) + (u >> 24) + ((u >> 8) & 0xFF00));
}

struct ArchivedFileInfo
{
	AsciiString m_filename;			// +0x00
	AsciiString m_archiveFilename;	// +0x04
	Int m_offset;					// +0x08
	Int m_size;						// +0x0c

	ArchivedFileInfo();
};

class ArchiveFile
{
public:
	virtual ~ArchiveFile();								// slot 0
	virtual void A1();
	virtual void A2();
	virtual void A3();
	virtual void A4();
	virtual void A5();
	virtual void A6();
	virtual void A7();
	virtual void A8();
	// slot 9 = +0x24; named by Win32BIGFile's vtable at 0x01143BE8
	virtual void setNameAndPath( const AsciiString &nameAndPath );

	void addFile( const AsciiString &path, const ArchivedFileInfo *info );
	void attachFile( class File *file );
};

// Complete: retail allocates with operator new and then calls
// ??0Win32BIGFile@@QAE@XZ, which is already matched, so the type has to be real
// enough for `new` to find a constructor.
class Win32BIGFile : public ArchiveFile
{
public:
	Win32BIGFile();

private:
	// Retail allocates 0x2c bytes for one of these -- `push 0x2c` before
	// operator new at 0x009CC77A -- so the object is 44 bytes: the vptr plus
	// forty of members this function never touches.
	char m_opaque[40];
};

class File
{
public:
	enum { READ = 0x01, BINARY = 0x40 };
	virtual ~File();											// slot 0
	virtual Bool open( const Char *filename, Int access );		// slot 1
	virtual void close( void );									// slot 2
	virtual Int read( void *buffer, Int bytes );				// slot 3
};

class LocalFileSystem
{
public:
	virtual ~LocalFileSystem();
	virtual void L1() = 0;
	// slot 2 = +0x08
	virtual File *openFile( const Char *filename, Int access ) = 0;
};

extern LocalFileSystem *TheLocalFileSystem;

// The two accepted container tags.
extern const char *TheBigfIdentifier;	// 0x012D9030 -> "BIGF"
extern const char *TheBig4Identifier;	// 0x012D9034 -> "BIG4"

class Win32BIGFileSystem
{
public:
	virtual ~Win32BIGFileSystem();											// slot 0
	virtual void init( void );												// slot 1
	virtual ArchiveFile *openArchiveFile( const Char *filename );			// slot 2
};

// ?openArchiveFile@Win32BIGFileSystem@@UAEPAVArchiveFile@@PBD@Z present-unmatched
ArchiveFile *Win32BIGFileSystem::openArchiveFile( const Char *filename )
{
	File *fp = TheLocalFileSystem->openFile( filename, File::READ | File::BINARY );

	AsciiString archiveFileName;
	archiveFileName.set( filename, filename ? (int)strlen( filename ) : 0 );
	archiveFileName.toLower();

	ArchiveFile *archiveFile = (ArchiveFile *)new Win32BIGFile;
	archiveFile->setNameAndPath( AsciiString( filename ) );

	if (fp == NULL) {
		return NULL;
	}

	// Only the null-file case returns NULL. A short read or an unrecognised
	// magic falls through to attachFile and hands back the empty archive --
	// that is why retail has one inline epilogue for fp == NULL at 0x009CC7D6
	// and sends both header failures to the shared tail at 0x009CCA20.
	char header[16];
	if (fp->read( header, 16 ) == 16 &&
		(strncmp( TheBigfIdentifier, header, 4 ) == 0 ||
		 strncmp( TheBig4Identifier, header, 4 ) == 0)) {

	ArchivedFileInfo fileInfo;

	// +12, not +4: retail allocates and reads the directory-table size at
	// header+0x0c (it loads [esp+0x48] against a header base of [esp+0x3c]),
	// while +4 is the whole-archive size, which it never uses.
	Int archiveFileSize = ntohl_inline( *(Int *)(header + 12) );
	// Unsigned: retail's loop guard is `test edi,edi / je`, not jle.
	UnsignedInt numLittleFiles = (UnsignedInt)ntohl_inline( *(Int *)(header + 8) );

	char *table = new char[archiveFileSize];
	if (fp->read( table, archiveFileSize - 0x10 ) == archiveFileSize - 0x10) {

	char *p = table;
	for (UnsignedInt i = numLittleFiles; i != 0; --i) {
		// invariant, but retail has it here: MSVC hoists it into the preheader
		// after the loop-count init, which is where retail's call lands.
		fileInfo.m_archiveFilename.set( archiveFileName );
		fileInfo.m_offset = ntohl_inline( *(Int *)p );
		fileInfo.m_size   = ntohl_inline( *(Int *)(p + 4) );

		const char *name = p + 8;

		// Backwards from the end, which is what retail does: mov al,[esi+ebp];
		// cmp against the two separators; dec ebp; jns.
		Int sep = (Int)strlen( name );
		while (sep >= 0 && name[sep] != '\\' && name[sep] != '/') {
			--sep;
		}

		const char *base = name + sep + 1;
		fileInfo.m_filename.set( base, base ? (int)strlen( base ) : 0 );
		fileInfo.m_filename.toLower();

		// A temporary, not a named local: retail destroys the full name right
		// after path is built and before addFile, which is end-of-full-expression.
		AsciiString path( AsciiString( name ), 0, sep + 1 );

		archiveFile->addFile( path, &fileInfo );

		// strlen again rather than reusing the scan's start: addFile can write
		// through the pointers, so retail recomputes it here too.
		p += (Int)strlen( name ) + 9;
	}
	}

	delete[] table;
	}

	archiveFile->attachFile( fp );

	return archiveFile;
}

