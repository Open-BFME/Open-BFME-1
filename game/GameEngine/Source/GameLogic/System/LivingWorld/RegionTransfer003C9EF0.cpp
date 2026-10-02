// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#include <vector>
#include "ascii_string.h"
#include "GameEngine/Source/Common/System/xfer.h"
class Gen_003BEA30;
class BfmeSinkAM { public: void registerItem(int,Gen_003BEA30 *,int); };
// The global at 0x012F706C is EA's `LivingWorldManager *TheLivingWorldManager`
// (data_rows.csv row ?TheLivingWorldManager@@3PAVLivingWorldManager@@A), defined
// once in LivingWorldManager.cpp; here it is only reached through the BfmeSinkAM
// view the registerItem call needs.
class LivingWorldManager;
extern LivingWorldManager *TheLivingWorldManager;
class LivingWorldRegion {
public:
    char m_00[4]; AsciiString m_04;
    char m_08[0xa4]; int m_AC;
    char m_B0[0x30]; char m_E0[4];
};
class LivingWorldRegionManager {
public:
    LivingWorldRegion *rva003C8A50(const AsciiString &);
    void transfer003C9EF0(Xfer *);
    char m_00[0x14]; std::vector<LivingWorldRegion *> m_14;
};
void LivingWorldRegionManager::transfer003C9EF0(Xfer *xfer) {
    {
    union { Xfer::Version version; unsigned storage; }; version.data[0]=1; version.data[1]=1;
    *xfer==version;
    }
    if(xfer->IsLoading()) {
        int count; *xfer==count;
        for(int i=0;i<count;++i) {
            AsciiString name;
            *xfer==name;
            LivingWorldRegion *region=rva003C8A50(name);
            if(region) {
                reinterpret_cast<BfmeSinkAM *>(TheLivingWorldManager)->registerItem(region->m_AC,(Gen_003BEA30*)region->m_E0,0);
                m_14.push_back(region);
            }
        }
    } else {
        int count=m_14.size(); *xfer==count;
        for(int i=0;i<count;++i) {
            AsciiString name=m_14[i]->m_04;
            *xfer==name;
        }
    }
}
