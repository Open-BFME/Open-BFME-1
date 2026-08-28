// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /Ireference/shims/sweep
//
// Win32BIGFile::getName and ::getPath, which return an archive's two AsciiString
// members by value. They live here rather than in Win32BIGFile.cpp because that
// file compiles against Zero Hour's Common/AsciiString.h, whose copy constructor
// is inline: it emits the refcount bump straight into the caller
// (mov eax,[ecx+0x24] / test / mov [esi],eax / InterlockedIncrement). Retail
// instead makes one out-of-line call to WWLib's StringBase<char> copy
// constructor at 0x00887B60 -- already byte-matched from
// Code/Libraries/Source/WWVegas/WWLib/string_base.cpp -- so the two shapes can
// never agree. Same divergence, and same fix, as the NameKeyGenerator shim:
// delegate to StringBase<char> from an in-header wrapper so the compiler inlines
// the wrapper and leaves the real call behind.
//
// Splitting into a sibling translation unit rather than switching Win32BIGFile
// .cpp's header wholesale keeps that file's eight already-matched rows compiling
// against the headers they matched under, the same split used for
// GameWindowFields.cpp and LocomotorAccessors.cpp.
//
// The class is a TU-local skeleton, not the real Win32BIGFile: only the member
// offsets matter here, and both are proven by retail's own instruction stream --
// getName reads this+0x24 and getPath reads this+0x28. Everything before that is
// the vtable pointer plus ArchiveFile's members, which these two functions never
// touch, so it is opaque padding. Win32BIGFile's constructor (0x009D14E0, already
// matched) zeroes exactly those two words after chaining to ArchiveFile's, which
// is what makes them Win32BIGFile's own rather than the base's, and it allocates
// 0x2C bytes -- the two AsciiStrings are the last thing in the object.
#include "string_base.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString() { m_text = 0; }

	// The one shape this file exists for: a direct call to
	// ??0?$StringBase@D@@AAE@ABV0@@Z rather than an inlined refcount bump.
	AsciiString( const AsciiString &that )
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase( *(const StringBase<char> *)&that );
	}

	~AsciiString()
	{
		((StringBase<char> *)this)->releaseBuffer();
	}

private:
	char *m_text;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/Win32Device/Common/Win32BIGFile.h
class Win32BIGFile
{
public:
	virtual AsciiString getName( void );
	virtual AsciiString getPath( void );

protected:
	char m_opaque[0x20];	// vtable pointer is +0x00; ArchiveFile's members follow
	AsciiString m_name;		// +0x24
	AsciiString m_path;		// +0x28
};

// ?getName@Win32BIGFile@@UAE?AVAsciiString@@XZ
AsciiString Win32BIGFile::getName( void )
{
	return m_name;
}

// ?getPath@Win32BIGFile@@UAE?AVAsciiString@@XZ
AsciiString Win32BIGFile::getPath( void )
{
	return m_path;
}
