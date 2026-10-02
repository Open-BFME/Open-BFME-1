// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/shims/stringinline
// stlport
#include <vector>
#include "StringInline.h"
#include <new>
#include "GameEngine/Source/Common/System/xfer.h"
#include "GameEngine/Source/Common/System/snapshot.h"
struct MissionObjectiveState { bool m_visible, m_completed; };
Xfer *Rva003C2830XferMissionObjectiveStateVector(Xfer *, std::vector<MissionObjectiveState> *);
class Xfer;
class BfmeHostBA { public: void bfmeSaveBA(Xfer *); };
struct Record003C3D90 {
    char m_00[8]; int m_08; AsciiString m_0C,m_10; bool m_14;
};
class Rva003C1A50 { public: void run(); };
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
// Existing dump symbols; the call sites and callee ret 4/8 instructions
// establish the member-call signatures used below.
void d_003a44a0();
void d_003c3480();
void d_003c12a0();
class Gen_003BEA30;
// The singleton at 0x012F706C is retail's ?g_bfmeGameCW@@3PAVBfmeGameCW@@A
// (dir32_addresses.csv); only the member registerItem is named under the
// local view, so the global carries its real type and the view is applied at
// the call.
class BfmeGameCW;
class BfmeSinkAM { public: void registerItem(int,Gen_003BEA30*,int); };
extern BfmeGameCW *g_bfmeGameCW;
class UnicodeString;
class Rva003A5450 {
public:
 Rva003A5450();
 virtual void slot0(); virtual void slot1(); virtual void slot2(); virtual void transfer(Xfer*);
 void setUnicode(const UnicodeString &); void setFlag(char);
 char m_04[4]; char m_08[0x16]; unsigned char m_1E; char m_1F[0x35];
};
class Rva000F9CF0 { public: void xfer(Xfer *); };
class Rva000F9FF0 { public: Rva000F9FF0(const Rva000F9FF0 &); };
struct RecordTail003C3BA0 {
    char m_00[0x14];
    UnicodeString wide;
    AsciiString narrow;
};
class Rva000FA610 {
public:
    Rva000FA610();
    AsciiString narrow;
    char m_04[0x40];
    RecordTail003C3BA0 tail;
};
struct BfmeVecElem_000FAFF0 { char body[96]; };
struct Rva000FB210Element {
    char body[96];
    Rva000FB210Element(const Rva000FB210Element &);
    ~Rva000FB210Element();
};
namespace _STL {
template<> BfmeVecElem_000FAFF0 *vector<BfmeVecElem_000FAFF0>::erase(
    BfmeVecElem_000FAFF0 *, BfmeVecElem_000FAFF0 *);
template<> inline void _Construct(Rva000FB210Element *p,
                                  const Rva000FB210Element &value) {
    new (p) Rva000F9FF0(*(const Rva000F9FF0 *)&value);
}
}
struct RecordVector003C3BA0 : _STL::vector<Rva000FB210Element> {
    int size() const { return (int)_STL::vector<Rva000FB210Element>::size(); }
    Rva000FA610 *first() const { return (Rva000FA610 *)begin(); }
    Rva000FA610 *last() const { return (Rva000FA610 *)end(); }
    void clear() {
        ((_STL::vector<BfmeVecElem_000FAFF0> *)this)->erase(
            (BfmeVecElem_000FAFF0 *)begin(), (BfmeVecElem_000FAFF0 *)end());
    }
    void append(const Rva000FA610 &value) {
        push_back(*(const Rva000FB210Element *)&value);
    }
};
class Transfer003C3D90 {
public:
    void transfer(Xfer *);
    int load003C4160(Xfer *);
    virtual void slot0(); virtual void reset();
    void records003C3BA0(Xfer *);
    char m_04[8]; std::vector<Rva003A5450 *> m_0C;
    char m_18[0x20]; std::vector<Record003C3D90 *> m_38;
    char m_44[0xc]; char m_50[0xc]; char m_5C[0xc];
    RecordVector003C3BA0 m_68; char m_74[0x10];
    std::vector<MissionObjectiveState> m_84;
};
int Transfer003C3D90::load003C4160(Xfer *xfer) {
    Xfer::Version version; version.data[0]=1; version.data[1]=3;
    *xfer==version;
    reset();
    reinterpret_cast<Rva003C1A50 *>(TheLivingWorldLogic)->run();
    ((BfmeHostBA*)this)->bfmeSaveBA((Xfer*)xfer);
    int count; *xfer==count;
    for(int i=0;i<count;++i) {
        Rva003A5450 *item=new Rva003A5450;
        item->transfer(xfer);
        item->setUnicode(*(UnicodeString*)item->m_08);
        union { void (*address)(); void (Rva003A5450::*method)(int); } state;
        state.address = d_003a44a0;
        (item->*state.method)(1);
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
        reinterpret_cast<BfmeSinkAM *>(g_bfmeGameCW)->registerItem(record->m_08,(Gen_003BEA30*)record,1);
    }
    union { void (*address)(); void (Transfer003C3D90::*method)(Xfer *, void *); } vector;
    vector.address = d_003c3480;
    (this->*vector.method)(xfer,m_50);
    (this->*vector.method)(xfer,m_5C);
    records003C3BA0(xfer);
    if(xfer->IsLoading()) m_84.clear();
    Rva003C2830XferMissionObjectiveStateVector(xfer,&m_84);
    if(version.data[1]>=2) {
        union { void (*address)(); void (Transfer003C3D90::*method)(Xfer *); } tail;
        tail.address = d_003c12a0;
        (this->*tail.method)(xfer);
    }
    return version.data[1];
}

void Transfer003C3D90::records003C3BA0(Xfer *xfer) {
    int count = m_68.size();
    *xfer == count;
    if (xfer->IsLoading()) {
        m_68.clear();
        for (int i = 0; i < count; ++i) {
            Rva000FA610 record;
            ((Rva000F9CF0 *)&record)->xfer(xfer);
            m_68.append(record);
        }
    } else {
        for (int i = 0; i < count; ++i)
            ((Rva000F9CF0 *)(m_68.first() + i))->xfer(xfer);
    }
}
