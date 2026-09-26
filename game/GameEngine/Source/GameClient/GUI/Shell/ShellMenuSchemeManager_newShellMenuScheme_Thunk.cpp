// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// readable body of ?newShellMenuScheme@ShellMenuSchemeManager@@QAEPAVShellMenuScheme@@VAsciiString@@@Z: game/GameEngine/Source/GameClient/GUI/Shell/ShellMenuScheme.cpp
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

#include "ascii_string.h"

class ShellMenuSchemeLine;
class ShellMenuSchemeImage;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ShellMenuScheme.h
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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ShellMenuScheme.h
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
