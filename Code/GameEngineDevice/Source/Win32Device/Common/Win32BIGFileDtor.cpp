// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /Ireference/shims/sweep
//
// Win32BIGFile::~Win32BIGFile and the scalar deleting thunk the vtable's first
// slot actually holds.
//
// The body is empty in the source sense -- everything retail does is compiler
// generated: reinstall the vtable, destroy the two AsciiString members in
// reverse declaration order, chain to ~ArchiveFile. It nonetheless cannot live
// in Win32BIGFile.cpp, for the same reason getName and getPath could not: Zero
// Hour's Common/AsciiString.h inlines the destructor's refcount work into the
// caller, while retail makes two plain calls to WWLib's private
// StringBase<char>::releaseBuffer at 0x00887940. So this file uses the same
// delegating AsciiString the sibling Win32BIGFileNames.cpp does.
//
// It is split from that sibling rather than appended to it because the
// destructor needs ArchiveFile to be a real base class -- retail's last call is
// ~ArchiveFile at 0x009D0BD0 -- whereas getName and getPath only need the two
// member offsets and take the base as opaque padding. Giving that file a base
// class would rewrite the layout its two matched rows were proven under for no
// gain.
//
// The base is opaque because the destructor never touches its fields: retail's
// ~ArchiveFile closes m_file at +0x04 through its own vtable and destroys the
// archived-directory tree at +0x08, all inside 0x009D0BD0. All this file needs
// is for the base to be 0x24 bytes with a virtual destructor, which puts m_name
// at +0x24 and m_path at +0x28 and makes the object 0x2C bytes -- exactly what
// Win32BIGFile's already-matched constructor at 0x009D14E0 allocates and zeroes.
#include "string_base.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString() { m_text = 0; }

	~AsciiString()
	{
		((StringBase<char> *)this)->releaseBuffer();
	}

private:
	char *m_text;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ArchiveFile.h
class ArchiveFile
{
public:
	virtual ~ArchiveFile();

protected:
	char m_opaque[0x20];	// vtable pointer is +0x00; ArchiveFile's own fields follow
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/Win32Device/Common/Win32BIGFile.h
class Win32BIGFile : public ArchiveFile
{
public:
	virtual ~Win32BIGFile();

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
