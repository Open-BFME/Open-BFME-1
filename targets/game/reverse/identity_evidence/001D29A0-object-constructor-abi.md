# Object constructor ABI, 0x001D29A0 / 4246 bytes

The existing lift has a stale three-argument BitFlags<45> decoration. Native
GameLogic::friend_createObject at 0x003830C0 allocates 0x3C4 bytes and passes
ThingTemplate*, const BitFlags<86>&, Team*, unsigned ID, and a trailing 1.
The trailing value is the MSVC virtual-base construction flag, not a fifth
source-level argument: the callee tests it before installing the vbptr at
+0x68 and the virtual base at +0x3C0. It returns with `ret 20`.
The four-argument native decoration is
`??0Object@@QAE@PBVThingTemplate@@ABV?$BitFlags@$0FG@@@PAVTeam@@I@Z`.

Independent native Object_bfmeRefreshPartitionCells.cpp reads vbptr +0x68,
vbtable[1] = 0x358, and the five-slot geometry/position/partition virtual
interface at +0x3C0. GhostObjectCtorDtor.cpp independently demonstrates the
same compiler virtual-base/vtordisp pattern with /vd2.

The small native experiment below reproduces the complete vtable and
vtordisp instruction sequence between the Thing constructor return and
member initialization (retail +0x51..+0xBB), modulo address relocations.
It puts Thing at +0, the snapshot base at +0x60, the virtual-inheritance
interface at +0x64/+0x68, and two additional interfaces at +0x6C/+0x70.
The vtordisp is +0x3BC, virtual base +0x3C0, total size 0x3C4.
Interface names remain address-derived because this establishes layout,
not their semantic identities. No ledger signature or pin was changed.

This is a prefix experiment, not a recovered full constructor and not a
byte-match/progress claim. The full body still needs approximately 100 member
initializers, seven static helper-data registrations, and module setup.
A full native implementation and direct-callee ABI review remain necessary.

```cpp
// cl: /DNDEBUG /MD /EHsc /vd2
class ThingTemplate;class Team;
template<int N> class BitFlags {public:unsigned int m_bits[(N+31)/32];};
class Thing {public:Thing(const ThingTemplate*);virtual ~Thing();char m_04[0x5c];};
class Rva001D29A0Snapshot {public:virtual void snapshot(){};};
class Rva001D29A0Virtual {public:virtual void v0(){};virtual void v1(){};virtual void v2(){};virtual void v3(){};virtual void v4(){};};
class Rva001D29A0IfaceA {public:virtual void a0(){};};
class Rva001D29A0IfaceB {public:virtual void b0(){};};
class Rva001D29A0IfaceC {public:virtual void c0(){};};
class Rva001D29A0IfaceV:public Rva001D29A0IfaceA,public virtual Rva001D29A0Virtual {};
class Object:public Thing,public Rva001D29A0Snapshot,public Rva001D29A0IfaceV,public Rva001D29A0IfaceB,public Rva001D29A0IfaceC {
public:Object(const ThingTemplate*,const BitFlags<86>&,Team*,unsigned);
virtual ~Object();virtual void snapshot(){};virtual void a0(){};virtual void b0(){};virtual void c0(){};virtual void v0(){};
char m_74[0x3bc-0x74];
};
Object::Object(const ThingTemplate*t,const BitFlags<86>&status,Team*team,unsigned id):Thing(t){}
```
