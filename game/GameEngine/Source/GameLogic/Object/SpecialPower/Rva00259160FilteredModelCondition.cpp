// cl: /DNDEBUG /MD /EHsc
// The caller at 0x00259670 adjusts its receiver by -0x10 before this no-arg
// call. The owner and original method spelling remain unresolved.
// Retail calls GameLogic::getFirstObject through 0x000358BE and traverses
// Object+0x88. It passes target->getControllingPlayer() and each object to the
// filter at context+0x1DC, then applies model condition 5 to passing objects.
typedef int Int;

class Player;
#define OBJECT_TU_MEMBERS \
	Player *getControllingPlayer() const; \
	void bfmeApplySpecialModelCondition(Int condition, const void *descriptor, Int frames);
#include "../object.h"
class GameLogic {
public:
    Object *getFirstObject();
};
extern GameLogic *TheBfmeGameLogic;
class Rva2225E0Filter {
public:
    bool accepts(Object *object, Player *player);
};
class Rva00259160Context {
public:
    unsigned char gap[0x1dc];
    Rva2225E0Filter filter;
};
class Rva00259160Owner {
public:
    void applyToFilteredObjects();
    unsigned char gap[4];
    Rva00259160Context *context;
    Object *target;
};

void Rva00259160Owner::applyToFilteredObjects()
{
    Object *targetObject = target;
    Object *object = TheBfmeGameLogic->getFirstObject();
    while (object != 0) {
        Rva00259160Context *currentContext = context;
        if (currentContext->filter.accepts(object, targetObject->getControllingPlayer()))
            object->bfmeApplySpecialModelCondition(5, targetObject, 1);
        object = object->m_next;
    }
}
