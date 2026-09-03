// cl: /DNDEBUG /MD /EHsc

typedef bool Bool;

enum KindOfType
{
	KINDOF_FOUNDATION = 0x95
};

enum ModelConditionFlagType
{
	MODELCONDITION_FOUNDATION = 3
};

class Drawable
{
public:
	void setSelectable(Bool selectable);
};

class Thing
{
public:
	Bool isKindOf(KindOfType kind) const;
};

class Object
{
public:
	virtual void objectSlot00() = 0;
	virtual void objectSlot04() = 0;
	virtual void objectSlot08() = 0;
	virtual void objectSlot0c() = 0;
	virtual void objectSlot10() = 0;
	virtual void objectSlot14() = 0;
	virtual void objectSlot18() = 0;
	virtual void objectSlot1c() = 0;
	virtual void objectSlot20() = 0;
	virtual void objectSlot24() = 0;
	virtual Drawable *getDrawable() const = 0;

	void clearModelConditionState(ModelConditionFlagType flag);
};

class BfmeA1057
{
public:
	void bfmeGo1057A(int value);
};

class BehaviorModule
{
public:
	virtual void behaviorModuleAnchor() = 0;

protected:
	unsigned int m_moduleData;
	Object *m_object;
};

class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor() = 0;
};

class UpdateModuleInterface
{
public:
	virtual void updateModuleInterfaceAnchor() = 0;
};

class UpdateModule : public BehaviorModule, public BehaviorModuleInterface,
	public UpdateModuleInterface
{
protected:
	unsigned int m_nextCallFrame;
	int m_indexInLogic;
	int m_updateState;
};

class FoundationAIUpdateIface3
{
public:
	virtual void iface3Slot00() = 0;
	virtual void iface3Slot04() = 0;
	virtual void iface3Slot08() = 0;
	virtual void iface3Slot0c() = 0;
	virtual void iface3Slot10() = 0;
	virtual void iface3Slot14() = 0;
	virtual void handle() = 0;
	virtual void iface3Slot1c() = 0;
};

class FoundationAIUpdateMember
{
public:
	virtual void memberAnchor();

	private:
	char m_padding[0x6c];
};

class FoundationAIUpdate : public UpdateModule, public FoundationAIUpdateIface3
{
private:
	FoundationAIUpdateMember m_member;
	void *m_pendingFoundation;
	Bool m_pendingFlag;

public:
	virtual void handle();
};

// ?handle@FoundationAIUpdate@@QAEXXZ
void FoundationAIUpdate::handle()
{
	if (m_pendingFoundation != 0)
	{
		Object *owner = m_object;
		m_pendingFoundation = 0;
		if (((Thing *)owner)->isKindOf(KINDOF_FOUNDATION))
			return;

		owner->clearModelConditionState(MODELCONDITION_FOUNDATION);
		Drawable *drawable = m_object->getDrawable();
		if (drawable == 0)
			return;

		if (((Thing *)m_object)->isKindOf(KINDOF_FOUNDATION))
			return;

		drawable->setSelectable(true);
		((BfmeA1057 *)drawable)->bfmeGo1057A(0x1e);
	}
}
