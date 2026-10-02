// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <bitset>
#include "../../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"
// WeaponChangeSpecialPowerModule::doSpecialPower, retail 0x0026CF90: slot 11 of
// the SpecialPowerModuleInterface table 0x010B8A50, which the registered
// constructor 0x0026CC80 stores at +0x10; reached only through ILT 0x00045C8C
// (VA appears once in the image). Object::doSpecialPower (0x001C3790) calls
// slot 11 as doSpecialPower. `this` is the interface sub-object.
// Evidence: targets/game/reverse/identity_evidence/specialpower-slot11-12-dospecialpower.md
template<int N> class BitFlags {
    _STL::bitset<N> bits;
public:
    BitFlags() {}
    void clear() { bits.reset(); }
    void set(int i) { if(i>=0) bits._Unchecked_set(i); }
};
typedef BitFlags<320> ConditionMask0026CF90;
int bfmeLookup_001c62b0(void*);
inline int lookupCondition0026CF90(const char* s) { return bfmeLookup_001c62b0((void*)s); }
// Existing pinned ABI spellings below are retained solely to resolve retail calls.
// They are not new semantic identities or new layout claims.
class BfmeOwnFDH { public: char bfmeAskFDH(int); };
class BfmeRvaBA00Object { public: void action(int); };
class BfmeObjE10 { public: void actionA(int); };
class BfmeItemRY { public: void bfmeDoRY(void*,void*); };
class SpecialPowerModule { public: virtual void doSpecialPower(unsigned); };
enum DisabledType {};
class Object { public:
    void clearAndSetModelConditionFlags(const BitFlags<320>&,const BitFlags<320>&);
    bool applyAttributeModifier(const AsciiString&,int);
    void setDisabledUntil(DisabledType,unsigned);
};
struct Object0026CF90 {
    bool has(int i) const { return reinterpret_cast<BfmeOwnFDH*>(const_cast<Object0026CF90*>(this))->bfmeAskFDH(i)!=0; }
    void remove(int i) { reinterpret_cast<BfmeRvaBA00Object*>(this)->action(i); }
    void add(int i) { reinterpret_cast<BfmeObjE10*>(this)->actionA(i); }
    void conditions(const ConditionMask0026CF90& a,const ConditionMask0026CF90& b) { reinterpret_cast<Object*>(this)->clearAndSetModelConditionFlags(a,b); }
    bool modifier(const AsciiString& s,int i) { return reinterpret_cast<Object*>(this)->applyAttributeModifier(s,i); }
    void disable(int i,unsigned n) { reinterpret_cast<Object*>(this)->setDisabledUntil((DisabledType)i,n); }
    void notify(int i,int n) { reinterpret_cast<BfmeItemRY*>(this)->bfmeDoRY((void*)i,(void*)n); }
};
struct Data0026CF90 {
    char pad00[0x210]; unsigned field210;
    int field214,field218;
    AsciiString field21C,field220;
};
class GameLogic { public: char pad00[0x3c]; unsigned field3C; };
extern GameLogic* TheGameLogic;
struct WeaponChangeSpecialPowerModule {
    // The base SpecialPowerModule::doSpecialPower (0x0026A550), called directly.
    void basePower(unsigned n) { reinterpret_cast<SpecialPowerModule*>(this)->SpecialPowerModule::doSpecialPower(n); }
    virtual void doSpecialPower(unsigned);
};
struct StringHeader0026CF90 { int refs; unsigned short length,capacity; };
static inline bool stringNotEmpty(const AsciiString& value) {
    const StringHeader0026CF90* p=*reinterpret_cast<const StringHeader0026CF90* const*>(&value);
    return p && p->length;
}
void WeaponChangeSpecialPowerModule::doSpecialPower(unsigned options) {
    Object0026CF90* object=reinterpret_cast<Object0026CF90**>(this)[-2];
    if(object) {
        Data0026CF90* data=reinterpret_cast<Data0026CF90**>(this)[-3];
        static ConditionMask0026CF90 mask;
        mask.clear();
        mask.set(lookupCondition0026CF90("MOVING"));
        mask.set(lookupCondition0026CF90("ATTACKING"));
        mask.set(lookupCondition0026CF90("FIRING_OR_PREATTACK_A"));
        mask.set(lookupCondition0026CF90("FIRING_OR_PREATTACK_B"));
        if(!data) return;
        unsigned bits=data->field210;
        bool enabled=false;
        for(int i=0;i<29;++i) {
            if(bits & (1u << (i&31))) {
                if(object->has(i)) object->remove(i);
                else {
                    object->add(i);
                    object->conditions(mask,ConditionMask0026CF90());
                    enabled=true;
                    object->conditions(mask,ConditionMask0026CF90());
                }
            }
        }
        if(enabled) {
            if(stringNotEmpty(data->field21C) && data->field214)
                object->modifier(data->field21C,data->field214);
            object->disable(4,TheGameLogic->field3C+data->field214);
            object->notify(0x128,data->field214);
        } else {
            if(stringNotEmpty(data->field220) && data->field218)
                object->modifier(data->field220,data->field218);
            object->disable(4,TheGameLogic->field3C+data->field218);
        }
    }
    basePower(options);
}
