// ??0Rva00377D70Data@@QAE@XZ
// partial score=1.0 date=2026-10-03
// cl: /O2 /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib /Igame/GameEngine/Source/Common/System
// Bank only: 614-byte constructor is exact modulo 28 relocations; strict
// selected-row instruction/call, string, constant, and DIR32 checks passed.
// Retail span 00377D70..00377FD5 ends RET before CC. model=gpt-6-astra.
// Existing SpyVisionUpdateModuleData identity is contradicted by the registry:
// CastleBehavior init0012C3B2/name00C83C50 installs data factory001144C0;
// that factory allocates 0x7c and calls ILT00035E22 -> this constructor.
// Parser00378170 registers tables010EA060 and010EA0B0, with fields below.
// Keep the opaque owner until the factory/destructor family's old identities
// and call-site pins are reconciled. This bank does not claim those identities.
// The explicit vptr references existing retail tables; NO local virtual table
// is emitted. Rva00377D70Table binds VA010E9E78 (17 slots), base table01073744.
// Snapshot.h's four-slot facade is not the retail ModuleData slot ordering.
// Before landing, independently bind both table symbols and cleanup call targets;
// an instruction/DIR32 masked match alone is not a table or EH-data proof.
// EH handler00C1ADF0 -> FuncInfo00E0B1EC: nine sequential unwind states (-1..7)
// clean this+0,0c,1c,20,3c,40,54,60,6c. Native bank reproduces that map and
// each action's receiver displacement. The 7-byte base dtor stores01073744.
// Container evidence: 00370DA0 pair cleanup destroys vector<int> at pair+4;
// native NamedIndexListParser00377AF0 independently uses that first map.
// 00374CF0 parser and0036CCB0 pair cleanup prove the final map's string+2ints.
// 00374B00 erase stride8 /0036CC00 cleanup and00374B60 stride12 /0036CC30
// cleanup establish the two vector payload layouts. Existing callee type names
// below are inherited ledger spellings, not new semantic identity claims.
// Shape levers: native node allocator (not _STLP_USE_NEWALLOC); StringBase::set
// with explicit zero length; vector.clear() rather than erase(begin(),end()).
// Probes progressed602B ->614B/7diff ->614B exact. No shared header changes.
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <map>
#include <vector>
#include <bitset>
#include "ascii_string.h"
extern const void * const Rva00377D70Table[17];
extern const void * const Rva00125300Table[17];
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
