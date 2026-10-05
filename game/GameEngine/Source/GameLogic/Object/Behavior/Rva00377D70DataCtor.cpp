// cl: /O2 /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib /Igame/GameEngine/Source/Common/System
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <map>
#include <vector>
#include <bitset>
#include "ascii_string.h"
#define Rva00377D70Table ((const void * const *)0x010E9E78u)
#define Rva00125300Table ((const void * const *)0x01073744u)
struct Rva00377D70Base {
    const void * const *vptr;
    unsigned int field4,field8;
    Rva00377D70Base(const void * const *table) { field8=0; vptr=table; }
    ~Rva00377D70Base();
};
class DeliverPayloadNugget { public: struct Payload { AsciiString m_payloadName; int m_payloadCount; }; };
struct Gen_t_00375460_p12cd { std::vector<int> values; };
struct Gen_t_0036ecf0_p12cd { AsciiString first; int second,third; };
struct Gen_t_00374b60_p12cd { AsciiString first,second; float third; };
struct Rva0021FC80Mask {
    std::bitset<192> bits;
    Rva0021FC80Mask() {}
    explicit Rva0021FC80Mask(unsigned int bit) { bits.set(bit); }
};
class BfmeF1166 {
public:
    BfmeF1166(int,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int);
    unsigned int words[6];
    operator Rva0021FC80Mask const &() const { return *(Rva0021FC80Mask const*)this; }
};
template<int N> class BitFlags;
extern const BitFlags<192> KINDOFMASK_NONE;
#define Rva00377D70None (*(const Rva0021FC80Mask*)&KINDOFMASK_NONE)
struct Gen003A0410 {
    Gen003A0410(); ~Gen003A0410();

    unsigned int value;
};
struct Rva0039FF30Filter { void setMasks(Rva0021FC80Mask,Rva0021FC80Mask); };
struct RespawnPolicy { std::bitset<192> bits; };
class RespawnPolicyMember { public: void setPolicies(RespawnPolicy,RespawnPolicy); };
struct Rva00377D70Data : Rva00377D70Base {
    Rva00377D70Data();
    ~Rva00377D70Data();
    std::map<int,Gen_t_00375460_p12cd > field0c;
    bool field18,field19;
    AsciiString field1c,field20;
    float field24,field28,field2c,field30,field34,field38;
    Gen003A0410 field3c,field40;
    int field44,field48,field4c,field50;
    std::vector<DeliverPayloadNugget::Payload> field54;
    std::vector<Gen_t_00374b60_p12cd> field60;
    std::map<int,Gen_t_0036ecf0_p12cd> field6c;
    bool field78;
};
Rva00377D70Data::Rva00377D70Data() : Rva00377D70Base(Rva00377D70Table) {
    field0c.clear();
    field19=false; field18=false;
    field6c.clear();
    field1c.StringBase<char>::set("",0);
    field54.clear();
    field60.clear();
    field20.StringBase<char>::set("",0);
    field24=1.0f;field28=2.0f;field2c=2.0f;field30=5.0f;field34=100.0f;field38=0;
    field78=false;
    ((Rva0039FF30Filter*)&field3c)->setMasks(BfmeF1166(0,7,0x3b,0x67,0x98,0x72),Rva0021FC80Mask(135));
    ((RespawnPolicyMember*)&field40)->setPolicies(*(const RespawnPolicy*)&KINDOFMASK_NONE,*(const RespawnPolicy*)&KINDOFMASK_NONE);
    field50=0;field4c=0;field44=18;field48=10;
}

__declspec(noinline) Rva00377D70Base::~Rva00377D70Base() { vptr=Rva00125300Table; }
