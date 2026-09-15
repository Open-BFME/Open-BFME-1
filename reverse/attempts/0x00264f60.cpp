// ?clearAffected@Rva00264F60Owner@@QAEXXZ
// partial score=0.86 date=2026-09-15
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include
// stlport
#include <list>
#include <bitset>
#include "Common/GameType.h"
class Rva00264F60Conditions {
public:
    bool test(int bit) const { return bits.test(bit); }
    void reset(int bit) { bits.reset(bit); }
private:
    _STL::bitset<320> bits;
};
class Object {
public:
    void notifyModelConditionChanged();
    char prefix[0x110];
    Rva00264F60Conditions conditions;
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
class Rva00264F60Owner {
public:
    char prefix[0xe8];
    _STL::list<ObjectID> ids;
    void clearAffected();
};
void Rva00264F60Owner::clearAffected()
{
    if (!ids.empty()) {
        for (_STL::list<ObjectID>::iterator i=ids.begin(); i!=ids.end(); ++i) {
            Object *object=TheGameLogic->findObjectByID(*i);
            if (object) {
                clearCondition(object, 191);
                object->word360=0;
            }
        }
        ids.clear();
    }
}
