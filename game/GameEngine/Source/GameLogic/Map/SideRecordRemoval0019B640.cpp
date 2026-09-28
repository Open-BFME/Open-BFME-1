// RVA 0x0019B640: side-record removal called by prepareForMP_or_Skirmish.
// Keep the address-qualified identity: the descriptive removeSide pin is disputed.
// Retail uses a 0x18-byte record at +0x2C and count at +0x28.
// Retaining ScriptList::deleteInstance with its internal null guard reproduces
// the hoisted EBP zero and the vector cleanup base register.
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#include "ascii_string.h"
#include <vector>

class BuildListInfo { public: virtual ~BuildListInfo(); void deleteInstance() { if (this) delete this; } };
class ScriptList { public: virtual ~ScriptList(); void deleteInstance() { if (this) delete this; } };
class Dict { public: void clear(); };
class BfmeRecordCJ { public: void bfmeSwap(BfmeRecordCJ &other); };
class BFMERetailAsciiString : public AsciiString { public: ~BFMERetailAsciiString(); };

class Rva0019B640SideInfo {
public:
    __forceinline void clear() {
        if (m_pBuildList) delete m_pBuildList;
        m_pBuildList = 0;
        m_dict.clear();
        m_scripts->deleteInstance();
        m_scripts = 0;
        m_strings.clear();
    }
private:
    BuildListInfo *m_pBuildList;
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
