// cl: /DNDEBUG /DBFME_STLP_NODE_ALLOC /D_STLP_NO_EXCEPTIONS /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/stlp_nodealloc /Ireference/shims/sweep /ICode/Libraries/Source/WWVegas/WWLib /Ireference/shims/asciistring_downloadmanager /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport

#define __PLACEMENT_VEC_NEW_INLINE
#include "PreRTS.h"

class Rva00080B60AsciiStringLess
{
public:
	bool operator()(const AsciiString &lhs, const AsciiString &rhs) const
	{
		return lhs.compare(rhs) < 0;
	}
};

namespace _STL
{
	template <>
	struct less<AsciiString> : public Rva00080B60AsciiStringLess
	{
	};
}

#include "Common/STLTypedefs.h"
#include "Common/Registry.h"

extern const char g_Rva0107301CEmptyString[];

typedef std::list<AsciiString> AsciiStringList;

class Rva00080B60GameSpyLoginPreferences
{
public:
	AsciiStringList getEmails(void);

private:
	typedef std::map<AsciiString, AsciiStringList> NickMap;
	unsigned char m_prefix[0x20];
	NickMap m_emailNickMap;
};

// ?getEmails@GameSpyLoginPreferences@@QAE?AV?$list@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@XZ
AsciiStringList Rva00080B60GameSpyLoginPreferences::getEmails(void)
{
	AsciiStringList theList;
	NickMap::iterator it = m_emailNickMap.begin();
	while (it != m_emailNickMap.end())
	{
		theList.push_back(it->first);
		++it;
	}
	if (theList.size() == 0)
	{
		AsciiString memberName;
		GetStringFromRegistry(g_Rva0107301CEmptyString, AsciiString("MemberName"), memberName);
		theList.push_back(memberName);
	}
	return theList;
}
