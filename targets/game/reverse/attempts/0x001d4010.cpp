// ?d_001d4010@@YAXXZ
// partial score=0.6036121673 date=2026-09-28
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Source/Common/Thing
// stlport
#define _STLP_USE_STATIC_LIB 1
// Scratch reconstruction of Object::~Object, RVA 0x001D4010, 1049 bytes.
// Identity: matched Object deleting destructor 0x001D5CF0 -> ILT 0x207C.
// Layout-only view: object.h does not model the non-primary bases or owning members.
// All Rva helper names below are address-derived ABI declarations; no pins claimed.
// Resume with probe symbol ??1Rva001D4010Object@@UAE@XZ. NOT a landed body.
// Shared object.h cannot emit this lifetime model: its secondary bases are raw words.
// Geometry vector layouts are independently witnessed by GeometryInfoCopyConstructor.cpp.
// Boundaries: RET at +0x418 followed by INT3. Retail FuncInfo at VA 0x011F8124 has 15 states.
// Flags 143/89/25/88 are positional evidence, not semantic KindOf names.
// Five words cover the highest referenced flag; the full ThingTemplate size is not claimed.
// Before landing reconcile these scratch callee/global/vtable spellings with existing
// ledger names. The target has ZERO unnamed direct targets; do not call this a missing-pin blocker.
enum Rva001D4010Kind { kind143=143, kind89=89, kind25=25, kind88=88 };
struct Rva001D4010Template;
#define THING_TU_MEMBERS const Rva001D4010Template *getTemplate() const; bool isKindOf(Rva001D4010Kind kind) const;
#include "thing.h"
#include "snapshot.h"
#include "ascii_string.h"
#include "unicode_string.h"
template<class T> inline StringBase<T>::~StringBase() { releaseBuffer(); }
inline UnicodeString::~UnicodeString() { ((StringBase<unsigned short> *)this)->releaseBuffer(); }
#include <vector>
#include <list>
#include <bitset>

struct Rva001D4010VirtualBase { virtual void vbase0(); virtual void vbase1(); virtual void vbase2(); virtual void vbase3(); virtual void vbase4(); };
struct Rva001D4010Base064 : virtual Rva001D4010VirtualBase { virtual void base064(); };
struct Rva001D4010Base06C { virtual void base06c(); };
struct Rva001D4010Base070 { virtual void base070(); };
struct Rva001D4010Owned { virtual ~Rva001D4010Owned(); };
struct GeometryShape { char bytes000[0x1c]; AsciiString name; char bytes020[4]; };
struct GeometryRecord { char bytes000[0xc]; AsciiString name; };
struct Rva001D4010Geometry : Snapshot {
    char bytes004[0x28]; std::vector<GeometryShape> shapes; std::vector<GeometryRecord> records; char bytes044[0x18];
    virtual const char *GetSnapshotName(); virtual void LoadPostProcess(); virtual void DoXfer(Xfer &);
};
struct Rva001D4010WeaponSet { char bytes[0x18]; ~Rva001D4010WeaponSet(); }; // 0x001EAD40
struct Rva001D4010ListValue { unsigned value; AsciiString text; };
struct Rva001D4010VectorValue { char bytes[0x5c]; };

struct Rva001D4010StringPair { char bytes[0x14]; UnicodeString wide; AsciiString narrow; };
struct Rva001DB3E0List { void *current; void *head; ~Rva001DB3E0List(); };
struct Rva00087A80Override {
    void *vfptr; Rva00087A80Override *next;
    Rva00087A80Override *getFinalOverride(); // 0x22BB -> 0x87A80
};

template<int N> struct Rva001D4010Flags { std::bitset<N> bits; bool test(int i) const { return bits.test(i); } };
struct Rva001D4010Template : Rva00087A80Override {
    char bytes008[0xc0]; Rva001D4010Flags<160> flags;
    bool isKindOf(Rva001D4010Kind kind) const { return flags.test(kind); }
};
struct Rva001D4010Object;
struct Rva0037CBC0Owner { bool removeObject(Rva001D4010Object *); };
extern Rva0037CBC0Owner *Rva012F0878;
struct Rva001D4010Logic {
    char bytes000[0x3c]; unsigned field03c; char bytes040[0x12c]; unsigned field16c;
    void sendDestroyed(Rva001D4010Object *); // 0x3B1B0 -> 0x383440; caller supplies ECX but body does not use it
};
extern Rva001D4010Logic *Rva012F0898;
struct Rva001D4010Script {
    virtual void slots0(); virtual void slots1(); virtual void slots2(); virtual void slots3();
    virtual void slots4(); virtual void slots5(); virtual void slots6(); virtual void slots7();
    virtual void slots8(); virtual void slots9(); virtual void slots10(); virtual void slots11();
    virtual void slots12(); virtual void slots13(); virtual void slots14(); virtual void slots15();
    virtual void slots16(); virtual void slots17(); virtual void slots18(); virtual void slots19();
    virtual void slots20(); virtual void slots21(); virtual void slots22(); virtual void slots23();
    virtual void slots24(); virtual void slots25(); virtual void slots26(); virtual void slots27();
    virtual void slots28(); virtual void slots29(); virtual void slots30(); virtual void slots31();
    virtual void destruction(Rva001D4010Object *);
    void changed(); // 0x3B15B
};
extern Rva001D4010Script *Rva012F076C;
struct Rva00595160Panel { void update(Rva001D4010Object *); };
struct Rva001D4010Palantir { char bytes000[0x2b8]; Rva00595160Panel panel; };
extern Rva001D4010Palantir *Rva012F4B98;
struct Rva00106C20Radar { void remove(Rva001D4010Object *); };
extern Rva00106C20Radar *Rva012EF0E4;
struct Rva008F73C0Manager { void remove(Rva001D4010Base064 *); };
extern Rva008F73C0Manager *Rva012ED5BC;
struct Rva00151800Group { bool remove(Rva001D4010Object *); }; // matched AIGroup::remove 0x151800

inline const Rva001D4010Template *Thing::getTemplate() const {
    Rva00087A80Override *p = (Rva00087A80Override *)m_template;
    return (const Rva001D4010Template *)(!p ? 0 : p->next ? p->next->getFinalOverride() : p);
}
inline bool Thing::isKindOf(Rva001D4010Kind kind) const { return getTemplate()->isKindOf(kind); }

struct Rva001D4010Object : Thing, Snapshot, Rva001D4010Base064, Rva001D4010Base06C, Rva001D4010Base070 {
    virtual ~Rva001D4010Object();
    virtual const char *GetSnapshotName(); virtual void LoadPostProcess(); virtual void DoXfer(Xfer &);
    virtual void reactToTransformChange(const Matrix3D *, const Coord3D *, Real);
    virtual void base064(); virtual void base06c(); virtual void base070();
    virtual void vbase0(); virtual void vbase1(); virtual void vbase2(); virtual void vbase3(); virtual void vbase4();
    unsigned m_id, m_producerID, m_builderID; void *m_drawable; AsciiString m_name;
    Rva001D4010Object *m_next, *m_prev; unsigned m_status[3]; char bytes09c[0x10];
    Rva001D4010Geometry m_geometryInfo;
    Rva001D4010Geometry *field108; char bytes10c[0x7c];
    Rva00151800Group *m_group; char bytes18c[0x48];
    void *field1d4, *field1d8, *field1dc, *field1e0, *m_defectionHelper, *field1e8, *m_firingTracker;
    Rva001D4010Owned **m_behaviors; char bytes1f4[8];
    void *m_contain, *m_body, *m_ai, *m_physics, *m_radarData;
    Rva001D4010Owned *m_experienceTracker; char bytes214[0x2c];
    AsciiString m_originalTeamName; unsigned m_indicatorColor; AsciiString field248; char bytes24c[0x18];
    Rva001D4010WeaponSet m_weaponSet; char bytes27c[0x3c];
    Rva001D4010Owned *field2b8, *field2bc; char bytes2c0[0x50];
    std::list<Rva001D4010ListValue> field310; char bytes314[0x14];
    AsciiString field328, field32c; char bytes330[0x1c];
    std::vector<Rva001D4010VectorValue> field34c; char bytes358[0xc];
    Rva001DB3E0List *field364; char bytes368; bool field369; char bytes36a[0xa];
    Rva001D4010StringPair field374; char bytes390[0x20];
    void *m_partitionData; char bytes3b4[8];
    void setTeam(void *); // direct call 0x2B74C
    void cleanup001BF300(); // direct call 0x25806
};
BFME_LAYOUT_CHECK(Rva001D4010Object,m_id,0x74);
BFME_LAYOUT_CHECK(Rva001D4010Object,m_geometryInfo,0xac);
BFME_LAYOUT_CHECK(Rva001D4010Object,m_group,0x188);
BFME_LAYOUT_CHECK(Rva001D4010Object,m_behaviors,0x1f0);
BFME_LAYOUT_CHECK(Rva001D4010Object,m_weaponSet,0x264);
BFME_LAYOUT_CHECK(Rva001D4010Object,field310,0x310);
BFME_LAYOUT_CHECK(Rva001D4010Object,field374,0x374);
BFME_LAYOUT_CHECK(Rva001D4010Object,m_partitionData,0x3b0);

Rva001D4010Object::~Rva001D4010Object() {
    field369 = true;
    if (isKindOf(kind143) || isKindOf(kind89))
        Rva012F0878->removeObject(this);
    if (!isKindOf(kind25) && !isKindOf(kind88)) {
        Rva012F0898->field16c = Rva012F0898->field03c;
        if (Rva012F076C) Rva012F076C->changed();
    }
    if (Rva012F4B98 && !(m_status[1] & 0x40000)) Rva012F4B98->panel.update(this);
    if (m_radarData) Rva012EF0E4->remove(this);
    Rva012F0898->sendDestroyed(this);
    setTeam(0);
    cleanup001BF300();
    if (m_partitionData) Rva012ED5BC->remove(this);
    if (m_group) m_group->remove(this);
    m_ai = 0; m_physics = 0; m_contain = 0; m_body = 0;
    for (Rva001D4010Owned **b = m_behaviors; *b; ++b) { delete *b; *b = 0; }
    delete [] m_behaviors; m_behaviors = 0;
    delete m_experienceTracker; m_experienceTracker = 0;
    m_firingTracker = 0; field1d4 = 0; field1d8 = 0; field1dc = 0; field1e0 = 0; m_defectionHelper = 0; field1e8 = 0;
    m_id = 0;
    if (Rva012F076C) Rva012F076C->destruction(this);
    if (field108 != &m_geometryInfo) delete field108;
    delete field364;
    delete field2b8; field2b8 = 0;
    delete field2bc; field2bc = 0;
}



