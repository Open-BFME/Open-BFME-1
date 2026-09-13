// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// readable body of ?setShellMenuScheme@ShellMenuSchemeManager@@QAEXVAsciiString@@@Z: Code/GameEngine/Source/GameClient/GUI/Shell/ShellMenuScheme.cpp
// Open-BFME: ShellMenuSchemeManager::setShellMenuScheme, retail 0x00581140,
// 262 bytes.
//
// The reference's body unchanged, and the shell twin of
// ControlBarScheme_find.cpp: an empty name clears the current scheme and
// returns, otherwise the list is walked for the first scheme whose name
// matches and that one becomes current.
//
// The list is this+0x00 and the current scheme this+0x04. isEmpty is inlined
// to the null buffer and the zero length at its +4 -- the `cmp word ptr
// [eax+4], cx` -- and the iterator is taken before the name is lower-cased,
// which is the order the reference writes and which the reloaded list header
// after the call preserves.
//
// The compare here is the case-sensitive one, `repe cmpsb` rather than the
// CRT call its control-bar twin makes, and it returns early on a difference.
#define _STLP_NO_EXCEPTIONS 1
#include <list>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef bool Bool;

extern "C" int __cdecl memcmp(const void *buf1, const void *buf2, unsigned int count);

struct BfmeAsciiStringData
{
	UnsignedShort m_refCount;
	UnsignedShort m_numCharsAllocated;
	UnsignedShort m_len;					// this+0x04
	UnsignedShort m_pad;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString(const AsciiString &that);
	~AsciiString();

	void toLower(void);					// retail 0x00887DA0

	Int getLength(void) const { return m_data ? m_data->m_len : 0; }
	const char *str(void) const { return m_data ? (const char *)(m_data + 1) : ""; }

	Bool isEmpty(void) const { return m_data == 0 || m_data->m_len == 0; }

	Int compare(const AsciiString &other) const
	{
		Int lenOther = other.getLength();
		const char *pOther = other.str();
		Int lenThis = getLength();
		const char *pThis = str();
		Int shorter = lenThis < lenOther ? lenThis : lenOther;

		Int diff = memcmp(pThis, pOther, shorter);
		if (diff != 0)
			return diff;

		return lenThis - lenOther;
	}

private:
	BfmeAsciiStringData *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ShellMenuScheme.h
class ShellMenuScheme
{
public:
	AsciiString m_name;					// this+0x00
};

typedef _STL::list<ShellMenuScheme *> ShellMenuSchemeList;
typedef ShellMenuSchemeList::iterator ShellMenuSchemeListIt;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ShellMenuScheme.h
class ShellMenuSchemeManager
{
public:
	void setShellMenuScheme(AsciiString name);

private:
	ShellMenuSchemeList m_schemeList;			// this+0x00
	ShellMenuScheme *m_currentScheme;			// this+0x04
};

void ShellMenuSchemeManager::setShellMenuScheme( AsciiString name )
{
	if(name.isEmpty())
	{
		m_currentScheme = 0;
		return;
	}

	ShellMenuSchemeListIt it;
	it = m_schemeList.begin();
	name.toLower();
	while(it != m_schemeList.end())
	{
		ShellMenuScheme *scheme = *it;
		if(scheme->m_name.compare(name) == 0)
		{
			m_currentScheme = scheme;
			break;
		}
		++it;
	}
}
