// Full230B RVA0025EF90..0025F076. Original owner/method name unresolved.
// Retail literal RohanCharge at VA010B566C; list<ObjectID> sentinel at+E8.
// The two preliminary member calls preserve this and take no stack arguments;
// the old 002A9850 destructor label is not used as identity evidence.
// Native bitset accessors retain retail mask materialization; bit191 is word124.
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include
// stlport
#include <list>
#include <bitset>
#include "ascii_string.h"
#include "Common/GameType.h"

inline AsciiString::~AsciiString() { ((StringBase<char> *)this)->releaseBuffer(); }
struct Rva0025EF90SubjectResult {
    char prefix[0x114];
    unsigned int word114;
};
class Rva0025EF90ConditionBits {
public:
    bool test(int bit) const { return bits.test(bit); }
    void set(int bit) { bits.set(bit); }
private:
    _STL::bitset<320> bits;
};
class Object {
public:
    virtual void slot00(); virtual void slot01(); virtual void slot02();
    virtual void slot03(); virtual void slot04(); virtual void slot05();
    virtual void slot06(); virtual void slot07(); virtual void slot08();
    virtual void slot09(); virtual Rva0025EF90SubjectResult *slot28();
    bool applyAttributeModifier(const AsciiString &, int);
    void notifyModelConditionChanged();
    char prefix004[0x70];
    ObjectID m_id;
    char prefix078[0x98];
    Rva0025EF90ConditionBits conditionBits;
    char gap138[0x228];
    unsigned int word360;
};
static __forceinline void setCondition(Object *object, int bit) {
    if (!object->conditionBits.test(bit)) {
        object->conditionBits.set(bit);
        object->notifyModelConditionChanged();
    }
}
class GameLogic {
public:
    Object *findObjectByID(ObjectID);
};
extern GameLogic *TheGameLogic;
class Rva0025EF90Owner {
public:
    void callAt002A9850();
    void callAt0025ED50();
    void applyCharge();
    char prefix[8];
    Object *owner;
    char gap00c[0xdc];
    _STL::list<ObjectID> ids;
};
typedef char ListSizeCheck[(sizeof(_STL::list<ObjectID>) == 4) ? 1 : -1];
void Rva0025EF90Owner::applyCharge()
{
    callAt002A9850();
    callAt0025ED50();
    if (!ids.empty()) {
        for (_STL::list<ObjectID>::iterator i=ids.begin(); i!=ids.end(); ++i) {
            Object *object=TheGameLogic->findObjectByID(*i);
            if (object) {
                object->applyAttributeModifier(AsciiString("RohanCharge"), -1);
                setCondition(object, 191);
                object->word360=owner->m_id;
            }
            // Retail performs this call even when the lookup returned null.
            Rva0025EF90SubjectResult *result=object->slot28();
            if (result) result->word114 |= 8;
        }
    }
}
