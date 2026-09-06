// ?getAllSideStrings@PlayerTemplateStore@@QAEXPAV?$list@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@@Z
// partial score=0.98 date=2026-09-06
// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <algorithm>
#include <list>
#include <string.h>

class AsciiString
{
public:
	AsciiString(const AsciiString &source);
	~AsciiString();
	bool operator==(const AsciiString &other) const
	{
		return strcmp(static_cast<const char *>(m_data) + 4,
			static_cast<const char *>(other.m_data) + 4) == 0;
	}

private:
	void *m_data;
};

template <typename T>
class PlayerTemplateVector
{
public:
	unsigned int size() const
	{
		return static_cast<unsigned int>(m_end - m_begin);
	}

	T *begin() const
	{
		return m_begin;
	}

	T &operator[](int index) const
	{
		return *(begin() + index);
	}

private:
	T *m_begin;
	T *m_end;
};

class PlayerTemplate
{
	public:
	char m_prefix[8];
	AsciiString m_side;
	char m_suffix[0x118];
};

class PlayerTemplateStore
{
public:
	const PlayerTemplate *getNthPlayerTemplate(int index) const
	{
		if (index >= 0 && index < m_playerTemplates.size())
			return &m_playerTemplates[index];
		return 0;
	}

	void getAllSideStrings(std::list<AsciiString> *outStringList);

private:
	char m_prefix[8];
	PlayerTemplateVector<PlayerTemplate> m_playerTemplates;
};

// ?getAllSideStrings@PlayerTemplateStore@@QAEXPAV?$list@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@@Z
void PlayerTemplateStore::getAllSideStrings(std::list<AsciiString> *outStringList)
{
	if (!outStringList)
		return;

	std::list<AsciiString> tmpList;
	int numTemplates = m_playerTemplates.size();
	for (int i = 0; i < numTemplates; ++i)
	{
		const PlayerTemplate *pt = getNthPlayerTemplate(i);
		if (!pt)
			continue;
		if (std::find(tmpList.begin(), tmpList.end(), pt->m_side) == tmpList.end())
			tmpList.push_back(pt->m_side);
	}
	outStringList->splice(outStringList->end(), tmpList);
}
