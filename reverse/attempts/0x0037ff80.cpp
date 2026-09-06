// ?findLevel@ExperienceLevelSystem@@QAEPAVBfmeExperienceLevelDefinition@@ABVAsciiString@@@Z
// partial score=0.9 date=2026-09-05
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /D_STLP_USE_STATIC_LIB /EHsc
// stlport
// Open-BFME5: clean C++ lift of ExperienceLevelSystem::findLevel.
// The iterator temporary preserves the retail stack layout.

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
#include <list>

typedef unsigned short UnsignedShort;

extern const char g_bfmeEmptyAscii[];
extern "C" int __cdecl memcmp(const void *, const void *, unsigned int);
#pragma intrinsic(memcmp)

struct BfmeAsciiStringData
{
	int m_refCount;
	UnsignedShort m_length;
	UnsignedShort m_capacity;
	char m_text[1];
};

class AsciiString
{
public:
    BfmeAsciiStringData *m_data;

    int compare(const AsciiString &other) const
    {
        const int otherLength = other.m_data ? other.m_data->m_length : 0;
        const char *otherText = other.m_data ? other.m_data->m_text : g_bfmeEmptyAscii;
        const int length = m_data ? m_data->m_length : 0;
        const char *text = m_data ? m_data->m_text : g_bfmeEmptyAscii;
        const int result = memcmp(text, otherText,
            (unsigned int)(length < otherLength ? length : otherLength));
        if (result != 0)
            return result;
        return length - otherLength;
    }
};

inline bool operator==(const AsciiString &left, const AsciiString &right)
{
    return left.compare(right) == 0;
}

class Overridable
{
public:
    Overridable *friend_getFinalOverride(void);

	char m_bfmeHead[4];
    Overridable *m_nextOverride;
};

class BfmeExperienceLevelDefinition : public Overridable
{
public:
    int m_level;
    AsciiString m_name;
};

typedef _STL::list<BfmeExperienceLevelDefinition> BfmeExperienceLevelList;
typedef _STL::hash_map<int, BfmeExperienceLevelList> BfmeExperienceLevelMap;

class ExperienceLevelSystem
{
public:
	BfmeExperienceLevelDefinition *findLevel(const AsciiString &name);

private:
	char m_bfmeHead[8];
	BfmeExperienceLevelMap m_levels;
};

// ?findLevel@ExperienceLevelSystem@@QAEPAVBfmeExperienceLevelDefinition@@ABVAsciiString@@@Z
BfmeExperienceLevelDefinition *ExperienceLevelSystem::findLevel(const AsciiString &name)
{
    BfmeExperienceLevelMap::iterator mapBegin = m_levels.begin();
    for (BfmeExperienceLevelMap::iterator mapIt = mapBegin;
        mapIt != m_levels.end(); ++mapIt)
	{
		BfmeExperienceLevelList &levels = (*mapIt).second;
		for (BfmeExperienceLevelList::iterator levelIt = levels.begin();
			levelIt != levels.end(); ++levelIt)
		{
            if ((*levelIt).m_name == name)
            {
                BfmeExperienceLevelDefinition *level = &(*levelIt);
                Overridable *next = level->m_nextOverride;
                if (next != 0)
                {
                    Overridable *final = next->m_nextOverride;
                    if (final == 0)
                        return 0;
                    return (BfmeExperienceLevelDefinition *)final->friend_getFinalOverride();
                }
                return level;
            }
		}
	}

	return 0;
}
