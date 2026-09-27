// Retail 0x000FB610 / 477 B: versioned vector of 96-byte records.
// Owning class remains unidentified. All typed calls reuse matched contracts.
// Player+0x24 is m_playerIndex per name_oracle.
// Native STLport push_back and nontrivial version construction reproduce the
// retail saved registers and stack lifetimes. The erase specialization reuses
// the separately matched 96-byte-record erase contract; _Construct delegates
// to the matched copy constructor at 0x000F9FF0.
// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/stringinline /Igame/GameEngine/Source/Common/System
#include "StringInline.h"
#include "xfer.h"
#include <new>
// stlport
#include <vector>
class Rva000F9CF0 { public: void xfer(Xfer *); };
class Rva000F9FF0 { public: Rva000F9FF0(const Rva000F9FF0 &); };
struct RecordTail000FB610 {
    char field00[0x14];
    UnicodeString field14;
    AsciiString field18;
};
class Rva000FA610 { public:
    Rva000FA610();
    AsciiString field00;
    char field04[0x40];
    RecordTail000FB610 field44;
};
struct BfmeVecElem_000FAFF0 { char body[96]; };
struct Rva000FB210Element {
    char body[96];
    Rva000FB210Element(const Rva000FB210Element&);
    ~Rva000FB210Element();
};
namespace _STL {
template<> BfmeVecElem_000FAFF0 *vector<BfmeVecElem_000FAFF0>::erase(BfmeVecElem_000FAFF0 *, BfmeVecElem_000FAFF0 *);
template<> inline void _Construct(Rva000FB210Element *p, const Rva000FB210Element &v) {
    new (p) Rva000F9FF0(*(const Rva000F9FF0*)&v);
}
}
struct RecordVector000FB610 : _STL::vector<Rva000FB210Element> {
    unsigned int size() const { return _STL::vector<Rva000FB210Element>::size(); }
    Rva000FA610 *first() const { return (Rva000FA610*)begin(); }
    Rva000FA610 *last() const { return (Rva000FA610*)end(); }
    void clear() {
        ((_STL::vector<BfmeVecElem_000FAFF0>*)this)->erase((BfmeVecElem_000FAFF0*)begin(),(BfmeVecElem_000FAFF0*)end());
    }
    void append(const Rva000FA610 &v) { push_back(*(const Rva000FB210Element*)&v); }
};
struct Version000FB610 : Xfer::Version { Version000FB610(unsigned char a,unsigned char b) { data[0]=a; data[1]=b; } };
class Player;
class PlayerList { public: Player *getNthPlayer(int); };
extern PlayerList *ThePlayerList;
class RecordVectorXfer000FB610 { public:
    void xfer(Xfer *xfer);
    int field00;
    RecordVector000FB610 field04;
    Player *field10;
};
void RecordVectorXfer000FB610::xfer(Xfer *xfer) {
    Version000FB610 version(1,1);
    *xfer == version;
    unsigned int count = field04.size();
    *xfer == count;
    if(xfer->IsStoring()) {
        for(Rva000FA610 *it = field04.first(); it != field04.last(); ++it)
            ((Rva000F9CF0*)it)->xfer(xfer);
        int index = field10 ? *(int*)((char*)field10 + 0x24) : -1;
        *xfer == index;
    } else {
        field04.clear();
        for(unsigned int i=0;i<count;++i) {
            Rva000FA610 record;
            ((Rva000F9CF0*)&record)->xfer(xfer);
            field04.append(record);
        }
        int index;
        *xfer == index;
        if(index != -1) field10 = ThePlayerList->getNthPlayer(index);
        else field10 = 0;
    }
}
