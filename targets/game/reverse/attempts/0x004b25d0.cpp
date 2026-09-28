// ?d_004b25d0@@YAXXZ
// partial score=0.978021978 date=2026-09-27
// stlport
// cl: /EHsc /Igame/Libraries/Source/WWVegas/WWLib /I.
// Complete control-flow reconstruction of retail RVA 004B25D0, 1365 bytes.
// Identity deliberately retains the address. String literals establish tooltip
// behavior, not an owning class. Scratch only until caller AND helper ABIs match.
#include "ascii_string.h"
#include "unicode_string.h"
#include <new>
#include <bitset>

// Typed ABI view of the wide StringBase copy constructor. Avoid a placement-new
// expression's extra EH temporary when using the standalone UnicodeString header.
class WideCopy00888400 {
public: void construct(const UnicodeString&);
};
#pragma comment(linker, "/alternatename:?construct@WideCopy00888400@@QAEXABVUnicodeString@@@Z=??0?$StringBase@G@@AAE@ABV0@@Z")

template<class T> inline StringBase<T>::~StringBase() { releaseBuffer(); }
template<class T> inline void StringBase<T>::clear() { releaseBuffer(); }
template<class T> inline bool StringBase<T>::isEmpty() const { return !m_data || !m_data->length; }
template<class T> inline int StringBase<T>::getLength() const { return m_data ? m_data->length : 0; }
template<class T> inline const T *StringBase<T>::str() const {
    static const T TheNullChr = 0;
    return m_data ? m_data->data : &TheNullChr;
}
template<class T> inline void StringBase<T>::swap(StringBase<T>& other) {
    Header *tmp=m_data; m_data=other.m_data; other.m_data=tmp;
}
inline UnicodeString::UnicodeString() { ((StringBase<unsigned short>*)this)->m_data=0; }
__forceinline UnicodeString::UnicodeString(const UnicodeString& other) {
    ((WideCopy00888400*)this)->construct(other);
}
inline UnicodeString::~UnicodeString() { ((StringBase<unsigned short>*)this)->releaseBuffer(); }
inline UnicodeString& UnicodeString::operator=(const UnicodeString& other) {
    ((StringBase<unsigned short>*)this)->set(*(const StringBase<unsigned short>*)&other); return *this;
}
template<class T> inline T& field004B25D0(void *p, unsigned n) { return *(T*)((char*)p+n); }
inline void clear004B25D0(UnicodeString& s) { ((StringBase<unsigned short>*)&s)->clear(); }
inline void swap004B25D0(UnicodeString& a, UnicodeString& b) {
    ((StringBase<unsigned short>*)&a)->swap(*(StringBase<unsigned short>*)&b);
}
inline void set004B25D0(UnicodeString& a, const UnicodeString& b) {
    ((StringBase<unsigned short>*)&a)->set(*(const StringBase<unsigned short>*)&b);
}

class Object;
class GameLogic { public: Object *findObjectByID(int); };
extern GameLogic *TheBfmeGameLogic;
class BfmeHostERH { public: int bfmeGoERH(); };
class Overridable { public: const Overridable *getFinalOverride() const; };
class Rva0036CA00Str;
class Rva00415A60 { public: bool take(Rva0036CA00Str&); };
class Rva00415AE0 { public: bool take(Rva0036CA00Str&); };
enum KindOfType;
#define THING_TU_MEMBERS bool isKindOf(KindOfType) const;
#define OBJECT_TU_MEMBERS bool getAttributeModifierBonus(int,float*) const;
#include "game/GameEngine/Source/GameLogic/Object/object.h"
class HealthView004B25D0 {
public:
    virtual void slot00(); virtual void slot04(); virtual void slot08();
    virtual void slot0c(); virtual void slot10(); virtual void slot14();
    virtual float slot18();
};
class GameTextInterface {
public:
    virtual ~GameTextInterface();
    virtual void slot04(); virtual void slot08(); virtual void slot0c();
    virtual void slot10(); virtual void slot14(); virtual void slot18();
    virtual void slot1c(); virtual void slot20();
    virtual UnicodeString fetch(const char*,bool*);
    virtual UnicodeString fetch(AsciiString,bool*);
};
extern GameTextInterface *TheGameText;
enum NameKeyType;
class Rva0010A950UpgradeTemplate;
class Rva0010A950UpgradeCenter {
public: const Rva0010A950UpgradeTemplate *findByKey(NameKeyType) const;
};
extern Rva0010A950UpgradeCenter *UpgradeCenter004B25D0;

// The following four static helpers must remain visible to MSVC: retail uses
// private EAX/EDI/ESI/EBX inputs. These definitions are evidence, not new claims.
struct Iterator004B25D0 {
    void *a; void *b;
    Iterator004B25D0() {}
    Iterator004B25D0(const Iterator004B25D0& p):a(p.a),b(p.b) {}
};
class ExperienceView004B25D0 {
public:
    void at0037F190(Iterator004B25D0*,Object*);
    bool at0037E810(Iterator004B25D0);
    Iterator004B25D0 at0037F220(Iterator004B25D0);
    int at0037D810(Iterator004B25D0);
};
extern ExperienceView004B25D0 *Experience004B25D0;
class RankLimit004B25D0 { public: bool at001B2030(int*); };
inline void *template004B25D0(Object *object) {
    void *p=object->m_template;
    return !p ? 0 : field004B25D0<void*>(p,4) ?
        (void*)((Overridable*)field004B25D0<void*>(p,4))->getFinalOverride() : p;
}
struct UpgradeBits004B25D0 {
    char pad[0x224];
    _STL::bitset<192> bits;
    __forceinline bool any() const { return bits.any(); }
    bool test(unsigned bit) const { return bits._Unchecked_test(bit); }
};
extern "C" __declspec(dllimport) double __cdecl floor(double);
static __declspec(noinline) void damage004B2260(Object *object,void *templ,int& melee,int& ranged) {
    float bonus;
    if (!object->getAttributeModifierBonus(2,&bonus)) bonus=0;
    int value=(int)floor(bonus+0.5f);
    melee=field004B25D0<int>(templ,0x470);
    if (melee>=0) melee+=value;
    ranged=field004B25D0<int>(templ,0x474);
    if (ranged>=0) ranged+=value;
}
static __declspec(noinline) int rank004B24F0(Object *object) {
    Iterator004B25D0 it;
    Experience004B25D0->at0037F190(&it,object);
    if (!Experience004B25D0->at0037E810(it)) return 0;
    return Experience004B25D0->at0037D810(it);
}
static __declspec(noinline) int maxRank004B2330(Object *object) {
    Iterator004B25D0 it;
    Experience004B25D0->at0037F190(&it,object);
    if (!Experience004B25D0->at0037E810(it)) return 0;
    Iterator004B25D0 next=Experience004B25D0->at0037F220(it);
    while (Experience004B25D0->at0037E810(next)) {
        it=next;
        next=Experience004B25D0->at0037F220(it);
    }
    int rank=Experience004B25D0->at0037D810(it);
    int cap;
    if (field004B25D0<RankLimit004B25D0*>(object,0x210)->at001B2030(&cap) && cap<rank) rank=cap;
    return rank;
}
static __declspec(noinline) void append004B2560(UnicodeString& out,const UnicodeString& line) {
    StringBase<unsigned short>& dest=*(StringBase<unsigned short>*)&out;
    if (!out.isEmpty()) { unsigned short newline=10; dest.concat(&newline,1); }
    dest.concat((const unsigned short*)line.str(),line.getLength());
}

class TooltipText004B25D0 {
public: void build(UnicodeString&,UnicodeString&,UnicodeString&,UnicodeString&);
    void *at00; int at04;
};
void TooltipText004B25D0::build(UnicodeString& name,UnicodeString& unused2,
                             UnicodeString& unused3,UnicodeString& description) {
    clear004B25D0(name); clear004B25D0(unused2);
    clear004B25D0(unused3); clear004B25D0(description);
    bool disguised=false;
    if (!at04) return;
    Object *object=TheBfmeGameLogic->findObjectByID(at04);
    if (!object) return;
    void *templ=(void*)((BfmeHostERH*)object)->bfmeGoERH();
    if (templ) disguised=true;
    else templ=template004B25D0(object);
    if (!templ) return;
    AsciiString label;
    void *drawable=object->getDrawable();
    if (drawable && ((Rva00415A60*)drawable)->take((Rva0036CA00Str&)label)) {
        set004B25D0(name,TheGameText->fetch(label,0));
    } else {
        set004B25D0(name,field004B25D0<UnicodeString>(object,0x388));
        if (name.isEmpty()) set004B25D0(name,field004B25D0<UnicodeString>(templ,0xc));
        Object *horde=field004B25D0<Object*>(object,0x214);
        if (horde && ((Thing*)horde)->isKindOf((KindOfType)0x6c) &&
            !field004B25D0<UnicodeString>(horde,0x388).isEmpty()) {
            UnicodeString text;
            text.format(TheGameText->fetch("TOOLTIP:VerteranHordeMemberName",0),name.str(),
                        field004B25D0<UnicodeString>(horde,0x388).str());
            swap004B25D0(name,text);
        }
    }
    int rank=disguised ? 1 : rank004B24F0(object);
    if (rank>0) {
        int maximum=maxRank004B2330(object);
        if (maximum>1) {
            UnicodeString text;
            text.format(TheGameText->fetch("TOOLTIP:Rank",0),rank,maximum);
            append004B2560(description,text);
        }
    }
    if (!((Thing*)object)->isKindOf((KindOfType)0x6c) &&
        !((Thing*)object)->isKindOf((KindOfType)0x3c) &&
        !((Thing*)object)->isKindOf((KindOfType)0x35) &&
        !((Thing*)object)->isKindOf((KindOfType)0x87) &&
        !((Thing*)object)->isKindOf((KindOfType)0x67) && !disguised) {
        UnicodeString text;
        HealthView004B25D0 *health=field004B25D0<HealthView004B25D0*>(object,0x200);
        if (health) {
            int maximum=(int)health->slot18();
            if (maximum>0) {
                text.format(TheGameText->fetch("TOOLTIP:MaxHealth",0),maximum);
                append004B2560(description,text);
            }
        }
        int melee,ranged;
        damage004B2260(object,templ,melee,ranged);
        if (melee>=0) {
            text.format(TheGameText->fetch("TOOLTIP:MeleeDamage",0),melee);
            append004B2560(description,text);
        }
        if (ranged>=0) {
            text.format(TheGameText->fetch("TOOLTIP:RangedDamage",0),ranged);
            append004B2560(description,text);
        }
    }
    { const unsigned *bits=(const unsigned*)((char*)object+0x224); unsigned i; for(i=0;i<6;++i) if(bits[i]) goto hasUpgrades; goto noUpgrades; }
hasUpgrades:
    for (int bit=0;bit<192;++bit) {
        if (((UpgradeBits004B25D0*)object)->test(bit)) {
            const Rva0010A950UpgradeTemplate *upgrade=UpgradeCenter004B25D0->findByKey((NameKeyType)bit);
            if (upgrade && !field004B25D0<AsciiString>((void*)upgrade,0x14).isEmpty())
                append004B2560(description,TheGameText->fetch(field004B25D0<AsciiString>((void*)upgrade,0x14),0));
        }
    }
noUpgrades:
    int battles=field004B25D0<int>(object,0x374);
    if (battles>0) {
        UnicodeString text;
        text.format(TheGameText->fetch("TOOLTIP:BattlesFought",0),battles);
        append004B2560(description,text);
    }
    AsciiString descriptionLabel;
    UnicodeString extra(field004B25D0<UnicodeString>(templ,0x10));
    drawable=object->getDrawable();
    if (drawable && ((Rva00415AE0*)drawable)->take((Rva0036CA00Str&)descriptionLabel))
        set004B25D0(extra,TheGameText->fetch(descriptionLabel,0));
    if (!extra.isEmpty()) append004B2560(description,extra);
}
