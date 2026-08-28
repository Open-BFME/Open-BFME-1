// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /Ireference/shims/sweep
//
// Win32BIGFile's tenth vtable slot -- a BFME addition Zero Hour's ArchiveFile
// has no declaration for. It splits a path into its last component and the
// directory ahead of it and drops them into the two AsciiStrings getName and
// getPath return, which in Zero Hour are written nowhere at all.
//
// The four-argument openFile calls it -- call dword ptr [eax+0x24] -- on every
// open, with the file being requested, before it looks the entry up. So on BFME
// an archive's getName does not answer with the archive's name; it answers with
// the last file anyone asked the archive for.
//
// Two things here look like slips and are reproduced because the bytes are the
// specification: the truncation lands one character short of the separator
// (buffer[token - str - 1], so "art\textures\x.tga" leaves "art\texture"), and
// the directory that costs a 32K stack buffer to build is then discarded --
// retail assigns m_path from m_name, not from the buffer. Both survive because
// nothing in the shipped game reads the result.
#include <string.h>
#include "string_base.h"

typedef int Int;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	void set( const AsciiString &that )
	{
		((StringBase<char> *)this)->set( *(const StringBase<char> *)&that );
	}

	void set( const char *s, Int len )
	{
		((StringBase<char> *)this)->set( s, len );
	}

	void set( const char *s )
	{
		((StringBase<char> *)this)->set( s, s ? (Int)strlen( s ) : 0 );
	}

	const char *str( void ) const { return m_data ? m_data + 8 : ""; }

private:
	char *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/Win32Device/Common/Win32BIGFile.h
class Win32BIGFile
{
public:
	virtual void setNameAndPath( const AsciiString &filename );

protected:
	char m_opaque[0x20];	// vtable pointer is +0x00; ArchiveFile's members follow
	AsciiString m_name;		// +0x24
	AsciiString m_path;		// +0x28
};

// ?setNameAndPath@Win32BIGFile@@UAEXABVAsciiString@@@Z
void Win32BIGFile::setNameAndPath( const AsciiString &filename )
{
	char buffer[0x8000];

	const char *str = filename.str();
	const char *token = strrchr( str, '\\' );

	if( token != 0 )
	{
		// The reference is load bearing, not style: naming m_name once makes MSVC
		// hoist its address into a callee-saved register ahead of the inlined
		// strlen, which is what costs the register that forces `this` onto the
		// stack and grows the frame by the four bytes retail's chkstk asks for.
		// Writing m_name.set(...) twice instead recomputes the address after the
		// strlen, needs no spill, and allocates four bytes less.
		AsciiString &name = m_name;

		name.set( token + 1 );

		strcpy( buffer, str );
		buffer[token - str - 1] = 0;

		m_path.set( name );
	}
	else
	{
		m_name.set( filename );
		m_path.set( ".", 1 );
	}
}
