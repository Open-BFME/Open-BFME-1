// cl: /O2 /Ob2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// BFME secondary UpdateModuleInterface entry at retail RVA 0x00203660.

typedef unsigned int UnsignedInt;
typedef int ObjectID;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

enum KindOfType
{
	KINDOF_SCORE = 0x27,
	KINDOF_SCORE_CREATE = 0x28,
	KINDOF_SCORE_DESTROY = 0x29,
	KINDOF_MP_COUNT_FOR_VICTORY = 0x25
};

class Thing
{
public:
	bool isKindOf(KindOfType kind) const;
};

class Object : public Thing
{
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);

	unsigned char m_unmodelled00[0x3c];
	UnsignedInt m_frame;
};

class PropagandaTowerBehaviorModuleData
{
private:
	unsigned char m_unmodelled00[0x0c];

public:
	UnsignedInt m_scanDelayInFrames;
};

class PropagandaTowerBehaviorPrimary
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void removeAllInfluence() = 0;
	virtual void doScan() = 0;
	virtual void effectLogic(Object *object, bool giving,
		const PropagandaTowerBehaviorModuleData *moduleData) = 0;
};

class ObjectTracker
{
public:
	virtual void destroy(unsigned int flags) = 0;

	ObjectID objectID;
	ObjectTracker *next;
};

extern GameLogic *TheBfmeGameLogic;

class Rva00203660PropagandaTowerBehavior
{
public:
	virtual UpdateSleepTime update();
};

// ?update@PropagandaTowerBehavior@@UAE?AW4UpdateSleepTime@@XZ
UpdateSleepTime Rva00203660PropagandaTowerBehavior::update()
{
	unsigned char *secondaryThis = reinterpret_cast<unsigned char *>(this);
	Object *object = *reinterpret_cast<Object **>(secondaryThis - 0x08);
	PropagandaTowerBehaviorModuleData *moduleData =
		*reinterpret_cast<PropagandaTowerBehaviorModuleData **>(secondaryThis - 0x0c);

	UnsignedInt status = *reinterpret_cast<UnsignedInt *>(
		reinterpret_cast<unsigned char *>(object) + 0x90);
	if ((status & 4) != 0)
		return UPDATE_SLEEP_NONE;

	if ((status & 0x80000) != 0)
	{
		reinterpret_cast<PropagandaTowerBehaviorPrimary *>(secondaryThis - 0x10)->removeAllInfluence();
		return UPDATE_SLEEP_FOREVER;
	}

	if ((*reinterpret_cast<unsigned char *>(
			reinterpret_cast<unsigned char *>(object) + 0x344) & 1) != 0)
		return UPDATE_SLEEP_FOREVER;

	UnsignedInt disabled = *reinterpret_cast<UnsignedInt *>(
		reinterpret_cast<unsigned char *>(object) + 0x1a4);
	if (disabled != 0 && (disabled & 0x7f7) != 0)
	{
		reinterpret_cast<PropagandaTowerBehaviorPrimary *>(secondaryThis - 0x10)->removeAllInfluence();
		return UPDATE_SLEEP_NONE;
	}

	Object *containedBy = *reinterpret_cast<Object **>(
		reinterpret_cast<unsigned char *>(object) + 0x214);
	if (containedBy != 0 && *reinterpret_cast<Object **>(
			reinterpret_cast<unsigned char *>(containedBy) + 0x214) != 0)
	{
		reinterpret_cast<PropagandaTowerBehaviorPrimary *>(secondaryThis - 0x10)->removeAllInfluence();
		return UPDATE_SLEEP_NONE;
	}

	UnsignedInt now = TheBfmeGameLogic->m_frame;
	UnsignedInt lastScan = *reinterpret_cast<UnsignedInt *>(secondaryThis + 0x14);
	if (now - lastScan >= moduleData->m_scanDelayInFrames)
	{
		reinterpret_cast<PropagandaTowerBehaviorPrimary *>(secondaryThis - 0x10)->doScan();
		*reinterpret_cast<UnsignedInt *>(secondaryThis + 0x14) = now;
	}

	ObjectTracker *current = *reinterpret_cast<ObjectTracker **>(secondaryThis + 0x18);
	ObjectTracker *previous = 0;
	while (current != 0)
	{
		ObjectTracker *next = current->next;
		Object *affected = TheBfmeGameLogic->findObjectByID(current->objectID);
		if (affected != 0 &&
			(affected->isKindOf(KINDOF_SCORE) ||
			 affected->isKindOf(KINDOF_SCORE_CREATE) ||
			 affected->isKindOf(KINDOF_SCORE_DESTROY) ||
			 affected->isKindOf(KINDOF_MP_COUNT_FOR_VICTORY)))
		{
			reinterpret_cast<PropagandaTowerBehaviorPrimary *>(secondaryThis - 0x10)->effectLogic(
				affected, true,
			*reinterpret_cast<PropagandaTowerBehaviorModuleData **>(secondaryThis - 0x0c));
			previous = current;
		}
		else
		{
			if (previous != 0)
				previous->next = next;
			else
				*reinterpret_cast<ObjectTracker **>(secondaryThis + 0x18) = next;
			current->destroy(1);
		}
		current = next;
	}

	return UPDATE_SLEEP_NONE;
}
