// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame
// stlport
#include <vector>
#include <list>
#include "Libraries/Source/WWVegas/WWLib/unicode_string.h"
#include "GameEngine/Source/Common/System/xfer.h"
#include "GameEngine/Source/Common/System/snapshot.h"
struct MissionObjectiveState { bool m_visible, m_completed; };
Xfer *Rva003C2830XferMissionObjectiveStateVector(Xfer *, std::vector<MissionObjectiveState> *);
class Xfer;
class BfmeHostBA { public: void bfmeSaveBA(Xfer *); };
inline UnicodeString::UnicodeString()
{
    m_text = 0;
}
inline UnicodeString::UnicodeString(const UnicodeString &that)
{
    ((StringBase<wchar_t> *)this)->StringBase<wchar_t>::StringBase(
        *(const StringBase<wchar_t> *)&that);
}
inline UnicodeString::~UnicodeString()
{
    ((StringBase<wchar_t> *)this)->releaseBuffer();
}
struct Rva003C12A0Element {
    UnicodeString m_text;
    int m_word4;
    int m_word8;
    Rva003C12A0Element() : m_text(), m_word4(0), m_word8(3) {}
    ~Rva003C12A0Element() {}
};
bool operator==(const Rva003C12A0Element &, const Rva003C12A0Element &);
bool operator<(const Rva003C12A0Element &, const Rva003C12A0Element &);
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
    char m_90[0x30]; _STL::list<Rva003C12A0Element> m_list;
};
// The matched load003C4160 caller and symbols.csv pin identify this method.
// Retail returns four bytes at +0x1B8 and begins int3 padding at +0x1BB.
void Transfer003C3D90::tail003C12A0(Xfer *xfer)
{
    int count = (int)m_list.size();
    *xfer == count;
    bool proceed = xfer->IsLoading();

    if (proceed)
    {
        m_list.clear();
        int i;
        i = 0;
        for (; i < count; ++i)
        {
            Rva003C12A0Element tmp;
            *xfer == tmp.m_text;
            *xfer == tmp.m_word4;
            xfer->XferRawBytes(&tmp.m_word8, 4);
            m_list.push_back(tmp);
        }
        return;
    }

    _STL::list<Rva003C12A0Element>::iterator it = m_list.begin();
    for (; it != m_list.end(); ++it)
    {
        Rva003C12A0Element tmp2(*it);
        *xfer == tmp2.m_text;
        *xfer == tmp2.m_word4;
        xfer->XferRawBytes(&tmp2.m_word8, 4);
    }
}
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
