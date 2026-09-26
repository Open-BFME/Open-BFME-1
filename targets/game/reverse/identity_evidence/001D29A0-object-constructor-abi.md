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
same compiler virtual-base/vtordisp pattern. The prior experiment used
/vd2, which VC7.1 ignores; /vd1 is the supported effective option.

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
// cl: /DNDEBUG /MD /EHsc /vd1
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


## Full native reconstruction, 2026-09-26

The bank now contains the complete 4,246-byte native constructor, including
member initialization, seven helper registrations, behavior module creation,
team attack-priority setup, experience tracker allocation, creation callbacks,
and final registration. It emits 227 relocations and is **not exact**: 889
masked byte positions differ (3,357 / 4,246 equal; score 0.7906264719736222).
Its normalized instruction comparison is 0.9951409135082604; that separate
shape figure is not byte coverage. There are nine structural differences,
mostly instruction scheduling. No source row or symbol pin was changed.

The first register difference is the -1 initialization at +0xFA (EBP versus
EDI, with the geometry pointer mirrored). Recovery-helper key loads/stores
around +0x768 use EDX in retail and EAX in the candidate; their two-byte width
difference displaces the following region. Other remaining differences include
the overridden-template parameter store, loop alignment, ScriptEngine global
load scheduling, ExperienceTracker result store, and the last receiver load.

Native layout refinements that improved the full body were the actual
DLINK_TeamMemberList object at +0x25C/+0x260 (independently present in
Team_loadPostProcess.cpp and the original MAKE_DLINK macro), inline helper
constructors with native STLport lists, the 20-byte ModuleInfo rows, native
BitFlags/bitset operations, and the by-value AsciiString lifetimes. Unknown
member and interface names retain address-derived labels.

The final allocator configuration is static native STLport with its default
node allocator, not _STLP_USE_NEWALLOC. Retail's two 0x0082E540 calls allocate
list sentinels; the existing native owner implements
_STL::__node_alloc<true,0>::_M_allocate, with mutex and free-list behavior.
Its historical __new_alloc alias in the ledger must not be interpreted as
permission to replace these calls with global operator new at 0x00881F30.

Independent direct-callee review established the following five declarations
that a future exact landing must resolve with evidenced pins or scoped typed
adapters. They are not unresolved semantic guesses:

* 0x003830A0: GameLogic::allocateObjectID returns the ObjectID enum. The native
  16-byte body postincrements this+0x108; no stack argument, EAX result.
* 0x0013E340: ThingTemplate::canPossiblyHaveAnyWeapon() const returns bool.
  The 55-byte body scans the +0x2F8..+0x2FC range at 0xEC stride.
* 0x0013B2F0: ModuleInfo::getNthName(int) const returns AsciiString by value.
  The 97-byte body has a hidden return buffer, integer index, RET 8, and
  20-byte vector rows. Existing spelling uses BFMERetailAsciiString.
* 0x00256710: ObjectGuardingHelper(Thing*, const ModuleData*) is a public
  constructor, returns this, RET 8. Its 147-byte body calls ObjectHelper,
  installs primary/secondary vtables at +0/+0xC/+0x10, initializes a list,
  and sleeps indefinitely. Primary vtable RVA 0x00CB3614 is independently
  named by its getModuleNameKey slot and native protected deleting destructor.
* 0x00594FD0: the address-derived Rva00594FD0::add(Object*) contract is thiscall,
  RET 4. Its 308-byte body reads the object's template and ID, and a receiver
  list at +4. The owning class's semantic identity is still unknown; the
  call uses the object at global 0x012F4B98 +0x2B8.

All 32 distinct direct retail targets were inventoried; Object::setTeam is
virtual, ModuleFactory::newModule takes ModuleType, and the allocation ABI
above was checked separately. Because instruction/relocation positions still
drift, this is not a zero-unresolved byte-gate receipt.

Bounded failed levers included EH/STL options, compiler architecture/optimization
flags, aggregate member initialization, loop-index lifetime, template local and
recursive getter forms, native field getters, ModuleData ctor visibility,
module-name lifetime, and behavior cursor declaration order. The bank preserves
the best complete body; no asm, byte emission, volatile forcing, or speculative
pin was added. Investigation t=55min, model=gpt-6.
