// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/shims/sweep
//
// Win32BIGFile string ownership: destructor and name/path accessors.
// The matched constructor at 0x009D14E0 establishes a 0x24-byte ArchiveFile
// base followed by m_name (+0x24) and m_path (+0x28), sizeof 0x2c.
// Retail uses WWLib StringBase calls for these members; the separate
// Win32BIGFile.cpp compiles against ZH headers with different inline bodies.
// Keep this shared BFME layout and canonical string headers together.

#include "string_base.h"

#include "ascii_string.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ArchiveFile.h
class ArchiveFile
{
public:
	virtual ~ArchiveFile();

protected:
	char m_opaque[0x20];	// vtable pointer is +0x00; ArchiveFile's own fields follow
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/Win32Device/Common/Win32BIGFile.h
class Win32BIGFile : public ArchiveFile
{
public:
	virtual ~Win32BIGFile();
	virtual AsciiString getName( void );
	virtual AsciiString getPath( void );

protected:
	AsciiString m_name;		// +0x24
	AsciiString m_path;		// +0x28
};

// Claiming this brings ??_GWin32BIGFile@@UAEPAXI@Z with it: the vtable's first
// slot holds the scalar deleting thunk, not the destructor itself.
// ??1Win32BIGFile@@UAE@XZ
Win32BIGFile::~Win32BIGFile()
{
}

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
