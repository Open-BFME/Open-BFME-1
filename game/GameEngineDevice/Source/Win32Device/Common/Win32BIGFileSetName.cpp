// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/shims/sweep
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

#include "../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

template<> inline void StringBase<char>::set(const char *str) { set(str, str ? strlen(str) : 0); }

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/Win32Device/Common/Win32BIGFile.h
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
		// Writing m_name.StringBase<char>::set(...) twice instead recomputes the address after the
		// strlen, needs no spill, and allocates four bytes less.
		AsciiString &name = m_name;

		name.StringBase<char>::set( token + 1 );

		strcpy( buffer, str );
		buffer[token - str - 1] = 0;

		m_path.StringBase<char>::set( name );
	}
	else
	{
		m_name.StringBase<char>::set( filename );
		m_path.StringBase<char>::set( ".", 1 );
	}
}
