// ?update@Rva00363050Owner@@QAEXABVBfmeSharedString@@HABUCoord2D@@_N@Z
// partial score=0.6938 date=2026-10-09
// cl: /DNDEBUG /MD /O2 /EHsc /I.
#include <string.h>

// stlport
#include <vector>
#include "game/Libraries/Source/WWVegas/WWLib/ascii_string.h"
template <>
inline int StringBase<char>::compare(const StringBase<char> &other) const {
    int nb=other.m_data?other.m_data->length:0;
    const char *b=other.m_data?other.m_data->data:"";
    return compare(b,nb);
}
template <>
inline int StringBase<char>::compare(const char *b,int nb) const {
    int na=m_data?m_data->length:0;
    const char *a=m_data?m_data->data:"";
    int cmp=memcmp(a,b,na<nb?na:nb);
    return cmp?cmp:na-nb;
}
class BfmeSharedString : private AsciiString {
public:
    BfmeSharedString(const BfmeSharedString& other) : AsciiString(other) {}
    ~BfmeSharedString() {}
    int compare(const BfmeSharedString &other) const { return StringBase<char>::compare(other); }
};
class Rva00361960 {
public: BfmeSharedString copyString();
private: char preceding[0x10]; BfmeSharedString m_string;
};
#include "game/Libraries/Include/Lib/Coord2D.h"
typedef Coord2D Rva00363050Pair;
struct Rva00363050Entry : Rva00361960 {
    char pad14[0xC]; int field20,field24; char pad28[0x14]; Rva00363050Pair field3C; char pad44[8];bool field4C;char pad4D[0xB];
    void setDuration(int duration) { field20=0; field24=(int)(duration*5.0f); }
    void setPair(Rva00363050Pair pair) { field3C=pair; }
    void setFlag(bool flag) { field4C=flag; }
};
class Rva00363050Owner {
public:void update(const BfmeSharedString &name,int duration,const Rva00363050Pair &pair,bool flag);
private:char pad00[0x18];std::vector<Rva00363050Entry> m_entries;
};
void Rva00363050Owner::update(const BfmeSharedString &name,int duration,const Rva00363050Pair &pair,bool flag) {
    for(unsigned i=0;i<m_entries.size();++i) {
        if(m_entries[i].copyString().compare(name)==0) { m_entries[i].setDuration(duration);m_entries[i].setPair(pair);m_entries[i].setFlag(flag); }
    }
}
