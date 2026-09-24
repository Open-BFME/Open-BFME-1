// ?d_0019b640@@YAXXZ
// partial score=0.15 date=2026-09-24
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /ICode/Libraries/Source/WWVegas/WWLib
// stlport
#include "ascii_string.h"
#include <vector>

class BuildListInfo { public: virtual ~BuildListInfo(); };
class ScriptList { public: virtual ~ScriptList(); };
class Dict { public: void clear(); };
class BfmeRecordCJ { public: void bfmeSwap(BfmeRecordCJ &other); };
class BFMERetailAsciiString : public AsciiString { public: ~BFMERetailAsciiString(); };

class Rva0019B640SideInfo {
public:
    __forceinline void clear() {
        if (m_buildList) delete m_buildList;
        m_buildList = 0;
        m_dict.clear();
        if (m_scripts) delete m_scripts;
        m_scripts = 0;
        m_strings.clear();
    }
private:
    BuildListInfo *m_buildList;
    Dict m_dict;
    ScriptList *m_scripts;
    std::vector<AsciiString> m_strings;
};
class Rva0019B640SidesList {
public:
    void removeSideRecordAt0019B640(int index);
private:
    unsigned char m_prefix[0x28];
    int m_numSides;
    Rva0019B640SideInfo m_sides[32];
};
void Rva0019B640SidesList::removeSideRecordAt0019B640(int index)
{
    if (index < 0 || index >= m_numSides || m_numSides <= 1)
        return;
    for (; index < m_numSides - 1; ++index)
        reinterpret_cast<BfmeRecordCJ *>(&m_sides[index])->bfmeSwap(
            *reinterpret_cast<BfmeRecordCJ *>(&m_sides[index + 1]));
    for (; index < 32; ++index)
        m_sides[index].clear();
    --m_numSides;
}
