// Retail [0x0025E450, 0x0025E497): 71 bytes, RET at +0x46.
// The old 81-byte dump included ten trailing INT3 padding bytes.
// Original method identity remains unknown. The three called methods have
// existing typed pins; the final jump uses the primary SpecialAbilityUpdate
// receiver, and the AI command interface is at owner->AIUpdate + 0x20.
// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
#include "Common/GameType.h"
#include "Common/GameCommon.h"

class AICommandInterface {
public:
    void aiIdle(CommandSourceType);
};
struct Rva0025E450ObjectView {
    unsigned char prefix[0x204];
    void *aiUpdate;
};
class Object;
class GameLogic {
public:
    Object *findObjectByID(ObjectID);
};
extern GameLogic *TheGameLogic;
// BFME-only method: the upstream SpecialAbilityUpdate header has no declaration.
class SpecialAbilityUpdate {
public:
    void bfmeAbortAbility();
};
class Rva0025E450Cleanup {
public:
    void cleanup();
private:
    unsigned char prefix[8];
    Rva0025E450ObjectView *owner;
    unsigned char gap00c[0xa0];
    ObjectID objectId;
    unsigned char gap0b0[0x39];
    unsigned char pending;
};
void Rva0025E450Cleanup::cleanup()
{
    Object *object = TheGameLogic->findObjectByID(objectId);
    if (object != 0 && pending) {
        reinterpret_cast<AICommandInterface *>(
            static_cast<char *>(owner->aiUpdate) + 0x20)->aiIdle(CMD_FROM_AI);
        pending = 0;
        reinterpret_cast<SpecialAbilityUpdate *>(this)->bfmeAbortAbility();
    }
}
