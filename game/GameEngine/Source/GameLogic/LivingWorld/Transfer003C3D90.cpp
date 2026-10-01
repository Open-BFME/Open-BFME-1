// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame
// stlport
#include <vector>
#include "GameEngine/Source/Common/System/xfer.h"
#include "GameEngine/Source/Common/System/snapshot.h"
struct MissionObjectiveState { bool m_visible, m_completed; };
Xfer *Rva003C2830XferMissionObjectiveStateVector(Xfer *, std::vector<MissionObjectiveState> *);
class Xfer;
class BfmeHostBA { public: void bfmeSaveBA(Xfer *); };
struct Record003C3D90 {
    char m_00[8]; int m_08; char m_0C[4],m_10[4]; bool m_14;
};
class Transfer003C3D90 {
public:
    void transfer(Xfer *);
    void vector003C3480(Xfer *, void *);
    void records003C3BA0(Xfer *);
    void tail003C12A0(Xfer *);
    char m_00[0xc]; std::vector<Snapshot *> m_0C;
    char m_18[0x20]; std::vector<Record003C3D90 *> m_38;
    char m_44[0xc]; char m_50[0xc]; char m_5C[0xc];
    char m_68[0x1c]; std::vector<MissionObjectiveState> m_84;
};
void Transfer003C3D90::transfer(Xfer *xfer) {
    union { Xfer::Version version; unsigned padding; };
    version.data[0]=1; version.data[1]=3;
    *xfer==version;
    ((BfmeHostBA*)this)->bfmeSaveBA((Xfer*)xfer);
    int count=m_0C.size();
    *xfer==count;
    for(int i=0;i<count;++i) m_0C[i]->DoXfer(*xfer);
    int second=m_38.size();
    *xfer==second;
    for(int j=0;j<second;++j) {
        Record003C3D90 *r=m_38[j];
        *xfer==*(Coord2D*)r;
        *xfer==r->m_08;
        *xfer==*(AsciiString*)r->m_0C;
        *xfer==*(AsciiString*)r->m_10;
        *xfer==r->m_14;
    }
    vector003C3480(xfer,m_50);
    vector003C3480(xfer,m_5C);
    records003C3BA0(xfer);
    if(xfer->IsLoading()) m_84.clear();
    Rva003C2830XferMissionObjectiveStateVector(xfer,&m_84);
    if(version.data[1]>=2) tail003C12A0(xfer);
}
