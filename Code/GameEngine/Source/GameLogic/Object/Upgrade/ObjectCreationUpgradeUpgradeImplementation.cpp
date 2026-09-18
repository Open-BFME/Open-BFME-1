// cl: /DNDEBUG /MD /EHsc

// ObjectCreationUpgrade::upgradeImplementation at retail 0x002D71D0, 224 bytes.
// The ObjectCreationUpgrade vtable at 0x010CD620 reaches this body in slot 7.

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

class Object
{
public:
    Module *findModule(NameKeyType key) const;
};

class BfmeDrop987
{
public:
    void bfmeClear987(int damageType, int deathType);
};

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

protected:
    virtual void upgradeImplementation();

public:
    virtual void setUpgradeExecuted(bool executed);
};

void ObjectCreationUpgrade::upgradeImplementation()
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

    BfmeDrop987 *slave =
        (BfmeDrop987 *)TheGameLogic->findObjectByID(slaveWatcher->m());
    if (slave == 0)
        return;

    slave->bfmeClear987(8, 0);

    if (data->m_firstInvokeArgument != -1)
    {
        ((BfmeItemRY *)slave)->bfmeDoRY(
            (void *)data->m_firstInvokeArgument,
            (void *)data->m_secondInvokeArgument);
    }
}
