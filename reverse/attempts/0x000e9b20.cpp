// ?d_000e9b20@@YAXXZ
// partial score=0.86 date=2026-08-30
// cl: /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

#include <map>
#include <string.h>

struct BfmeScoreStringData {
    unsigned short references;
    unsigned short allocated;
    unsigned short length;
    unsigned short padding;
    char text[1];
};

class BfmeScoreString {
public:
    bool equals(const BfmeScoreString &other) const;

private:
    BfmeScoreStringData *m_data;
};

bool BfmeScoreString::equals(const BfmeScoreString &other) const
{
    unsigned int leftLength = m_data ? m_data->length : 0;
    const char *left = m_data ? m_data->text : "";
    unsigned int rightLength = other.m_data ? other.m_data->length : 0;
    const char *right = other.m_data ? other.m_data->text : "";
    unsigned int commonLength = leftLength < rightLength ? leftLength : rightLength;
    int comparison = memcmp(right, left, commonLength);
    if (comparison == 0)
        comparison = rightLength - leftLength;
    return comparison == 0;
}

struct BfmeScoreTemplate {
    char padding[0x20];
    BfmeScoreString name;
};

typedef _STL::map<const BfmeScoreTemplate *, int> BfmeScoreMap;

class ScoreKeeper {
public:
    int bfmeGetTotalDestroyed(const BfmeScoreString &name) const;

private:
    char padding[0x150];
    BfmeScoreMap m_destroyed[32];
};

int ScoreKeeper::bfmeGetTotalDestroyed(const BfmeScoreString &name) const
{
    int count = 0;
    for (int player = 0; player < 32; ++player) {
        for (BfmeScoreMap::const_iterator it = m_destroyed[player].begin();
             it != m_destroyed[player].end(); ++it) {
            const BfmeScoreTemplate *thingTemplate = it->first;
            if (thingTemplate && name.equals(thingTemplate->name))
                count += it->second;
        }
    }
    return count;
}
