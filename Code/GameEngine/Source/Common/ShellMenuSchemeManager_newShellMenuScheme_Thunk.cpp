// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// readable body of ?newShellMenuScheme@ShellMenuSchemeManager@@QAEPAVShellMenuScheme@@VAsciiString@@@Z: Code/GameEngine/Source/GameClient/GUI/Shell/ShellMenuScheme.cpp
// Open-BFME5: convert ShellMenuSchemeManager::newShellMenuScheme to clean C++.

#define _STLP_NO_EXCEPTIONS 1
#include <list>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;

extern "C" int __cdecl memcmp(const void *buf1, const void *buf2, unsigned int count);

struct BfmeAsciiStringData
{
	UnsignedShort m_refCount;
	UnsignedShort m_numCharsAllocated;
	UnsignedShort m_len;
	UnsignedShort m_pad;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString(const AsciiString &that);
	~AsciiString();

	void toLower(void);                         // retail 0x00887DA0
	void set(const AsciiString &that);          // retail 0x00887C90

	Int getLength(void) const { return m_data ? m_data->m_len : 0; }
	const char *str(void) const { return m_data ? (const char *)(m_data + 1) : ""; }

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

class ShellMenuSchemeLine;
class ShellMenuSchemeImage;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ShellMenuScheme.h
class ShellMenuScheme
{
public:
	ShellMenuScheme(void);
	~ShellMenuScheme(void);

	AsciiString m_name;
	typedef _STL::list<ShellMenuSchemeImage *> ShellMenuSchemeImageList;
	ShellMenuSchemeImageList m_imageList;
	typedef _STL::list<ShellMenuSchemeLine *> ShellMenuSchemeLineList;
	ShellMenuSchemeLineList m_lineList;
};

typedef _STL::list<ShellMenuScheme *> ShellMenuSchemeList;
typedef ShellMenuSchemeList::iterator ShellMenuSchemeListIt;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ShellMenuScheme.h
class ShellMenuSchemeManager
{
public:
	ShellMenuScheme *newShellMenuScheme(AsciiString name);

private:
	ShellMenuSchemeList m_schemeList;
	ShellMenuScheme *m_currentScheme;
};

ShellMenuScheme *ShellMenuSchemeManager::newShellMenuScheme(AsciiString name)
{
	ShellMenuSchemeListIt it;
	it = m_schemeList.begin();
	name.toLower();
	while (it != m_schemeList.end())
	{
		ShellMenuScheme *scheme = *it;
		if (scheme->m_name.compare(name) == 0)
		{
			m_schemeList.erase(it);
			delete scheme;
			break;
		}
		else
			++it;
	}

	ShellMenuScheme *newScheme = new ShellMenuScheme;
	newScheme->m_name.set(name);
	m_schemeList.push_back(newScheme);
	return newScheme;
}
