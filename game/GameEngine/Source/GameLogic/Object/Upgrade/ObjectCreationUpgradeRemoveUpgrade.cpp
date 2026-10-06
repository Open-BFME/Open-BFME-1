// cl: /DNDEBUG /MD /EHsc

// ObjectCreationUpgrade::removeUpgrade (UpgradeMux slot 7) at retail 0x002D71D0, 224 bytes.
// The ObjectCreationUpgrade vtable at 0x010CD620 reaches this body in slot 7.
// Slot 7 is EA's removeUpgrade (BFME2/RotWK WorldBuilder labels, matching slot),
// a virtual that UpgradeMux::attemptUpgrade (0x002D9AD0)
// never calls; slot 9 is upgradeImplementation (0x002D6E60), which this
// body undoes.
// Evidence: targets/game/reverse/identity_evidence/upgrademux-slot7-removeupgrade.md
// Evidence: targets/game/reverse/identity_evidence/upgrademux-slot9-upgradeimplementation.md

enum NameKeyType
{
    NAME_KEY_NONE = 0
};

class NameKeyGenerator
{
public:
    NameKeyType nameToKey(const char *name);
};

class Module;

enum DamageType
{
    BFME_DAMAGE_TYPE_8 = 8
};

enum DeathType
{
    BFME_DEATH_TYPE_0 = 0
};

#define OBJECT_TU_MEMBERS \
	Module *findModule(NameKeyType key) const; \
	void kill(DamageType damageType, DeathType deathType);
#include "../object.h"
#undef OBJECT_TU_MEMBERS

class BfmeItemRY
{
public:
    void bfmeDoRY(void *first, void *second);
};

class GameLogic
{
public:
    Object *findObjectByID(int objectID);
};

class Gen_002072a0
{
public:
    int m();
};

struct ObjectCreationUpgradeModuleData
{
    unsigned char m_padding[0x90];
    unsigned char m_destroyWhenSold;
    int m_firstInvokeArgument;
    int m_secondInvokeArgument;
};

extern NameKeyGenerator *TheNameKeyGenerator;
extern GameLogic *TheGameLogic;

class ObjectCreationUpgrade
{
public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0c();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();

public:
    virtual void removeUpgrade();

public:
    virtual void setUpgradeExecuted(bool executed);
};

void ObjectCreationUpgrade::removeUpgrade()
{
    setUpgradeExecuted(false);

    ObjectCreationUpgradeModuleData *data =
        *(ObjectCreationUpgradeModuleData **)((char *)this + 0x0c);
    *(unsigned int *)((char *)this + 0x28) = 0x3fffffff;
    *(unsigned char *)((char *)this + 0x2c) = 0;

    if (data == 0 || data->m_destroyWhenSold == 0)
        return;

    static NameKeyType slaveWatcherBehaviorKey =
        TheNameKeyGenerator->nameToKey("SlaveWatcherBehavior");
    Object *object = *(Object **)((char *)this + 0x10);
    Gen_002072a0 *slaveWatcher =
        (Gen_002072a0 *)object->findModule(slaveWatcherBehaviorKey);
    if (slaveWatcher == 0)
        return;

    Object *slave = TheGameLogic->findObjectByID(slaveWatcher->m());
    if (slave == 0)
        return;

    slave->kill((DamageType)8, (DeathType)0);

    if (data->m_firstInvokeArgument != -1)
    {
        ((BfmeItemRY *)slave)->bfmeDoRY(
            (void *)data->m_firstInvokeArgument,
            (void *)data->m_secondInvokeArgument);
    }
}
