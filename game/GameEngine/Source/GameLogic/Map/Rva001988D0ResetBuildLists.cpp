// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/asciistring_copyctor_outofline /Iinputs/reference/shims/buildlistinfo /Iinputs/reference/shims/moduledata /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#include "PreRTS.h"
#include <vector>
#include "Common/NameKeyGenerator.h"

// Retail RVA 0x001988D0, 252 bytes through RET at 0x001989CB.
// The 241-byte analysis extent omits the loop back-edge and epilogue.
// Its caller at 0x0019B030 resets these records before loading Camps.map
// and Others.map. The original owner/method names are not established.
// Retail starts 32 records at this+0x66C: a name key and two 12-byte
// vectors. Both clear operations retain capacity and destroy live values
// through virtual slot zero with a zero deleting-destructor flag.
// The canonical buildlistinfo shim has a protected pool destructor, which
// prevents this BFME by-value vector use. The matched assignment operator
// and retail vector strides establish this TU-local 140-byte lifetime view.
class BuildListInfo {
public:
    virtual ~BuildListInfo();
    BuildListInfo &operator=(const BuildListInfo &);
private:
    unsigned char m_unmodelled[136];
};

typedef char CheckBuildListStride[(sizeof(BuildListInfo)==140)?1:-1];
struct Rva001988D0Entry {
    NameKeyType key;
    std::vector<BuildListInfo> camps;
    std::vector<BuildListInfo> others;
};
typedef char CheckEntryStride[(sizeof(Rva001988D0Entry)==28)?1:-1];
class Rva001988D0SidesLists {
public:
    void resetBuildLists();
private:
    unsigned char m_prefix[0x66c];
    Rva001988D0Entry m_entries[32];
};
void Rva001988D0SidesLists::resetBuildLists()
{
    for(int i=0;i<32;++i) {
        m_entries[i].key=TheNameKeyGenerator->nameToKey("UNASSIGNED");
        m_entries[i].camps.clear();
        m_entries[i].others.clear();
    }
}
