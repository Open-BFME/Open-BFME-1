// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#include <vector>
#include "ascii_string.h"
#include "GameEngine/Source/Common/System/xfer.h"
#include "GameEngine/Source/Common/System/snapshot.h"
struct MissionObjectiveState { bool m_visible, m_completed; };
Xfer *Rva003C2830XferMissionObjectiveStateVector(Xfer *, std::vector<MissionObjectiveState> *);
class BfmeAgentBA;
class BfmeHostBA { public: void bfmeSaveBA(BfmeAgentBA *); };
struct Record003C3D90 {
    char m_00[8]; int m_08; AsciiString m_0C,m_10; bool m_14;
};
class Rva003C1A50 { public: void run(); };
extern Rva003C1A50 *TheLivingWorldLogic;
class Gen_003BEA30;
class BfmeSinkAM { public: void registerItem(int,Gen_003BEA30*,int); };
extern BfmeSinkAM *g_bfmeSinkAM;
class UnicodeString;
class Rva003A5450 {
public:
 Rva003A5450();
 virtual void slot0(); virtual void slot1(); virtual void slot2(); virtual void transfer(Xfer*);
 void setUnicode(const UnicodeString &); void state003A44A0(int); void setFlag(char);
 char m_04[4]; char m_08[0x16]; unsigned char m_1E; char m_1F[0x35];
};
class Transfer003C3D90 {
public:
    void transfer(Xfer *);
    int load003C4160(Xfer *);
    virtual void slot0(); virtual void reset();
    void vector003C3480(Xfer *, void *);
    void records003C3BA0(Xfer *);
    void tail003C12A0(Xfer *);
    char m_04[8]; std::vector<Rva003A5450 *> m_0C;
    char m_18[0x20]; std::vector<Record003C3D90 *> m_38;
    char m_44[0xc]; char m_50[0xc]; char m_5C[0xc];
    char m_68[0x1c]; std::vector<MissionObjectiveState> m_84;
};
int Transfer003C3D90::load003C4160(Xfer *xfer) {
    Xfer::Version version; version.data[0]=1; version.data[1]=3;
    *xfer==version;
    reset();
    TheLivingWorldLogic->run();
    ((BfmeHostBA*)this)->bfmeSaveBA((BfmeAgentBA*)xfer);
    int count; *xfer==count;
    for(int i=0;i<count;++i) {
        Rva003A5450 *item=new Rva003A5450;
        item->transfer(xfer);
        item->setUnicode(*(UnicodeString*)item->m_08);
        item->state003A44A0(1);
        m_0C.push_back(item);
        item->setFlag(item->m_1E);
    }
    int second; *xfer==second;
    for(int j=0;j<second;++j) {
        Record003C3D90 *record=new Record003C3D90;
        *xfer==*(Coord2D*)record;
        *xfer==record->m_08;
        *xfer==record->m_0C;
        *xfer==record->m_10;
        *xfer==record->m_14;
        m_38.push_back(record);
        g_bfmeSinkAM->registerItem(record->m_08,(Gen_003BEA30*)record,1);
    }
    vector003C3480(xfer,m_50);
    vector003C3480(xfer,m_5C);
    records003C3BA0(xfer);
    if(xfer->IsLoading()) m_84.clear();
    Rva003C2830XferMissionObjectiveStateVector(xfer,&m_84);
    if(version.data[1]>=2) tail003C12A0(xfer);
    return version.data[1];
}
