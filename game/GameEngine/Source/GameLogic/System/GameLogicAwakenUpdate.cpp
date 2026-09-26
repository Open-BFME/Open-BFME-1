// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// BFME scheduler wake path, RVA0x0038D870 (329B). The existing UpdateModule
// caller reaches this body through ILT0x9944. Unlike the older Zero Hour
// reference, BFME maintains four update-phase vectors plus a sleeping vector.
// Moving a sleeper removes it by swapping in the last entry and repairing
// that entry's index, then appends the awakened module to its phase.
// The same-frame guard preserves an update already due on the current frame.
// TU-local layout: GameLogic object list+A8, phase vectors+C4, sleeping+F4,
// current update+100; UpdateModule next frame+14, index+18, phase+1C.
// Unused virtual slots below specify only layout, not recovered signatures.

#include <vector>

typedef unsigned int UnsignedInt;
typedef int Int;

enum UpdateSleepTime
{
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};

class ModuleData;
class Object;

class Module
{
public:
	virtual ~Module();
	virtual Int getModuleNameKey() const;
	virtual void onObjectCreated();
	virtual void onDrawableBoundToObject();
	virtual void preloadAssets(Int);
	virtual void onDelete();
	virtual void crc(void *);
	virtual void xfer(void *);
	virtual void loadPostProcess();

private:
	const ModuleData *m_moduleData;
};

class ObjectModule : public Module
{
public:
	virtual void onCapture(Object *, Object *);

private:
	Object *m_object;
};

class BodyModuleInterface;
class CollideModuleInterface;
class ContainModuleInterface;
class CreateModuleInterface;
class DamageModuleInterface;
class DestroyModuleInterface;
class DieModuleInterface;
class SpecialPowerModuleInterface;
class UpdateModuleInterface;

class BehaviorModuleInterface
{
public:
	virtual BodyModuleInterface *getBody() = 0;
	virtual CollideModuleInterface *getCollide() = 0;
	virtual ContainModuleInterface *getContain() = 0;
	virtual CreateModuleInterface *getCreate() = 0;
	virtual DamageModuleInterface *getDamage() = 0;
	virtual DestroyModuleInterface *getDestroy() = 0;
	virtual DieModuleInterface *getDie() = 0;
	virtual SpecialPowerModuleInterface *getSpecialPower() = 0;
	virtual UpdateModuleInterface *getUpdate() = 0;
};

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update();
	virtual Int getUpdatePhase() const;

	UnsignedInt m_nextCallFrame;
	Int m_indexInLogic;
	Int m_phaseInLogic;

	UnsignedInt friend_getNextCallFrame() const
	{
		return m_nextCallFrame;
	}

	void friend_setNextCallFrame(UnsignedInt frame)
	{
		if (frame > UPDATE_SLEEP_FOREVER)
			frame = UPDATE_SLEEP_FOREVER;
		m_nextCallFrame = frame;
	}

	void friend_setIndexInLogic(Int index)
	{
		m_phaseInLogic = -1;
		m_indexInLogic = index;
	}

	void friend_setIndexInLogic(Int index, Int phase)
	{
		m_phaseInLogic = phase;
		m_indexInLogic = index;
	}

};

typedef UpdateModule *UpdateModulePtr;

class Object { public: bool isInList(Object **) const; };
class BfmeAwakenLog {
public:
 virtual void slot00();
 virtual void slot04();
 virtual void slot08();
 virtual void slot0C();
 virtual void slot10();
 virtual void slot14();
 virtual void slot18();
 virtual void slot1C();
 virtual void slot20();
 virtual void slot24();
 virtual void slot28();
 virtual void slot2C();
 virtual void slot30();
 virtual void slot34();
 virtual BfmeAwakenLog *slot38(const char *);
 virtual void slot3C();
 virtual void slot40();
 virtual void slot44();
 virtual void slot48();
 virtual void slot4C(int);
};
class BfmeAwakenDebug { public:
 virtual void slot00();
 virtual void slot04();
 virtual void slot08();
 virtual void slot0C();
 virtual void slot10();
 virtual void slot14();
 virtual void slot18();
 virtual void slot1C();
 virtual void slot20();
 virtual void slot24();
 virtual void slot28();
 virtual void slot2C();
 virtual void slot30();
 virtual void slot34();
 virtual void slot38();
 virtual void slot3C();
 virtual void slot40();
 virtual void slot44();
 virtual void slot48();
 virtual void slot4C();
 virtual void slot50();
 virtual void slot54();
 virtual void slot58();
 virtual void slot5C();
 virtual void slot60();
 virtual void slot64();
 virtual void slot68();
 virtual BfmeAwakenLog *slot6C(int,int);
};
extern BfmeAwakenDebug *TheBfmeAwakenDebug;
void _bfme_debugRecordCallsite(int);
class GameLogic
{
public:
    void setDefaults(bool);
    void friend_awakenUpdateModule(Object *, UpdateModule *, unsigned);

    char pad00[0x34];
    float width;
    float height;
    unsigned frame;
    char pad40[0x68];
    Object *objList;
    char padAC[0x18];
    _STL::vector<UpdateModule *> phaseUpdates[4];
    _STL::vector<UpdateModule *> sleeping;
    UpdateModule *current;
    char pad104[4];
    unsigned nextObjectID;
};

extern GameLogic *TheBfmeGameLogic;

void GameLogic::setDefaults(bool loadingSaveGame)
{
    frame = 0;
    width = 64.0f;
    height = 64.0f;
    objList = 0;
    for (int i = 0; i != 4; ++i)
    {
        for (_STL::vector<UpdateModule *>::iterator it = phaseUpdates[i].begin();
             it != phaseUpdates[i].end(); ++it)
        {
            (*it)->friend_setIndexInLogic(-1);
        }
        phaseUpdates[i].clear();
    }
    for (_STL::vector<UpdateModule *>::iterator it = sleeping.begin();
         it != sleeping.end(); ++it)
    {
        (*it)->friend_setIndexInLogic(-1);
    }
    sleeping.clear();
    current = 0;
    if (!loadingSaveGame)
        nextObjectID = 1;
}

void GameLogic::friend_awakenUpdateModule(Object *obj, UpdateModule *u, unsigned when)
{
    unsigned now = TheBfmeGameLogic->frame;
    if (u == current)
        return;
    if (when == u->friend_getNextCallFrame())
        return;
    if (now > 0 && u->friend_getNextCallFrame() == now && when == now + 1)
        return;

    int idx = u->m_indexInLogic;
    int phase = u->m_phaseInLogic;
    if (obj->isInList(&objList))
    {
        if (phase < 0 && when < UPDATE_SLEEP_FOREVER)
        {
            // A negative phase marks the inactive sleeping vector.
            int newPhase = u->getUpdatePhase();
            if (idx < (int)sleeping.size() - 1)
            {
                sleeping[idx] = sleeping.back();
                sleeping[idx]->friend_setIndexInLogic(idx);
            }
            sleeping.pop_back();
            int newIndex = phaseUpdates[newPhase].size();
            phaseUpdates[newPhase].push_back(u);
            u->friend_setIndexInLogic(newIndex, newPhase);
        }
        u->friend_setNextCallFrame(when);
    }
    else
    {
        if (idx != -1)
        {
            _bfme_debugRecordCallsite(1);
            TheBfmeAwakenDebug->slot60();
            TheBfmeAwakenDebug->slot6C(0, 0)->slot38(
                "fatal error! sleepy update module index mismatch.\n")->slot4C(1);
            return;
        }
        // Object initialization may wake a module before list insertion.
        u->friend_setNextCallFrame(when);
    }
}
