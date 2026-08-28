// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /Ireference/shims/sweep
//
// Win32BIGFileSystem::init, retail 0x009CC590, 111 bytes.
//
// This is the class TheArchiveFileSystem actually points at. Its constructor is
// 0x009CC350: it chains to ArchiveFileSystem's constructor at 0x009CA9E0 (now
// matched) and then installs vtable 0x01143B40, so it derives from
// ArchiveFileSystem, whose own vtable is 0x01143A08. The derived vtable
// overrides the six slots the base leaves pure and inherits slots 5, 6, 8 and 10
// unchanged, which is how the base's openFile/doesFileExist were placed.
//
// The name comes from the body: the literal at 0x0107532C is "*.big", and Zero
// Hour's Win32BIGFileSystem::init is the function that loads "*.big". BFME kept
// only the first half of it -- Zero Hour goes on to read an InstallPath out of
// the registry and load the original Generals assets from there, and none of
// that is here.
//
// loadBigFilesFromDirectory is reached through [eax+0x24], vtable slot 9, which
// is _purecall on the base -- consistent with Zero Hour declaring it pure on
// ArchiveFileSystem and implementing it on this class. It is called through the
// vtable, so it needs no symbol; only the string constructor and the global do.
//
// The two AsciiStrings are passed by value and this function never destroys
// them: MSVC has the callee destroy by-value class parameters. What it does emit
// is the SEH frame and the two state assignments, so that a throw between the
// constructors unwinds the one already built.

#include <stddef.h>
#include "string_base.h"

typedef int Int;
typedef int Bool;

// The delegating shim, as in Win32BIGFileOpenArchived.cpp: the constructor is
// defined here and forwards to StringBase<char>, rather than being left an
// undefined extern. That file matched first try building two of these by value.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString( const char *s )
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase( s );
	}

	~AsciiString()
	{
		((StringBase<char> *)this)->releaseBuffer();
	}

private:
	char *m_data;
};

class LocalFileSystem;
extern LocalFileSystem *TheLocalFileSystem;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/Win32Device/Common/Win32BIGFileSystem.h
class Win32BIGFileSystem
{
public:
	virtual ~Win32BIGFileSystem();										// slot 0
	virtual void init( void );											// slot 1
	virtual void B2() = 0;
	virtual void B3() = 0;
	virtual void B4() = 0;
	virtual void B5() = 0;
	virtual void B6() = 0;
	virtual void B7() = 0;
	virtual void B8() = 0;
	// slot 9 = +0x24
	virtual Bool loadBigFilesFromDirectory( AsciiString dir, AsciiString fileMask,
	                                        Bool overwrite ) = 0;
};

// ?init@Win32BIGFileSystem@@UAEXXZ
//
// This sat at 109 of 111 for a while. The only difference was one instruction
// pair scheduled the other way round, twice:
//
//   retail    push ecx; mov [esp+0xc],esp; mov ecx,esp; push offset "*.big"
//   earlier   push ecx; mov ecx,esp; mov [esp+0xc],esp; push offset "*.big"
//
// The mov [esp+N],esp is MSVC recording the temporary's address for the unwind
// table, and retail emits it before setting the this pointer rather than after.
//
// None of the obvious levers moved it: explicit AsciiString(...) temporaries, a
// declared rather than inline destructor, releaseBuffer public rather than
// private, the third argument defaulted rather than passed, and /GX, /EHa, /Gy,
// /Os, /Ox, /O1, /Oy-, /GF, /Gd and /Og on top of build.py's base. Nor the
// argument order -- MSVC evaluates right-to-left and retail does construct
// "*.big" first.
//
// What fixed it was the AsciiString shim above: defining the constructor inline
// as a delegation to StringBase<char>::StringBase(const char*) instead of
// leaving it an undefined extern. With the extern, the temporary is opaque and
// its unwind record gets scheduled after the receiver; with the delegation the
// compiler can see the construction and orders the pair retail's way. So the
// lever was not how the CALL is written but how the temporary's TYPE is
// declared -- worth remembering, because nothing about the diff pointed at it.
void Win32BIGFileSystem::init( void )
{
	if( TheLocalFileSystem == NULL )
	{
		return;
	}

	loadBigFilesFromDirectory( "", "*.big", 0 );
}
