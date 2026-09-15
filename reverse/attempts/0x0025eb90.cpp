// ?clearAffected@Rva0025EB90Owner@@QAEXXZ
// partial score=0.87 date=2026-09-15
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include
// stlport
#include <list>
#include <bitset>
#include "Common/GameType.h"
class BfmeThingYY {
public:
    void bfmeClearYY(unsigned int);
};
class Rva0025EB90Conditions {
public:
    bool test(int bit) const { return bits.test(bit); }
    void reset(int bit) { bits.reset(bit); }
private:
    _STL::bitset<320> bits;
};
class Object {
public:
    virtual void slot00(); virtual void slot01(); virtual void slot02();
    virtual void slot03(); virtual void slot04(); virtual void slot05();
    virtual void slot06(); virtual void slot07(); virtual void slot08();
    virtual void slot09(); virtual BfmeThingYY *slot28();
    void notifyModelConditionChanged();
    char prefix004[0x10c];
    Rva0025EB90Conditions conditions;
    char gap138[0x228];
    unsigned int word360;
};
static __forceinline void clearCondition(Object *object, int bit) {
    if (object->conditions.test(bit)) {
        object->conditions.reset(bit);
        object->notifyModelConditionChanged();
    }
}
class GameLogic {
public:
    Object *findObjectByID(ObjectID);
};
extern GameLogic *TheGameLogic;
class Rva0025EB90Owner {
public:
    char prefix[0xe8];
    _STL::list<ObjectID> ids;
    void clearAffected();
};
void Rva0025EB90Owner::clearAffected()
{
    if (!ids.empty()) {
        for (_STL::list<ObjectID>::iterator i=ids.begin(); i!=ids.end(); ++i) {
            Object *object=TheGameLogic->findObjectByID(*i);
            if (object) {
                clearCondition(object, 191);
                object->word360=0;
                BfmeThingYY *result=object->slot28();
                if (result) result->bfmeClearYY(8);
            }
        }
        ids.clear();
    }
}
