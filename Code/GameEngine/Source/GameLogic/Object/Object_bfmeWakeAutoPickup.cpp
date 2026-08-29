// cl: /DNDEBUG /MD /EHsc

// Retail command dispatch index 47 is MSG_WAKE_AUTO_PICKUP. Callers pass
// button numbers 1, 2, or 3, and the selected AutoPickUpUpdate interface wakes
// only when its RunFromButtonNumber agrees. The bfme prefix records that the
// exact retail spelling of this Object helper is not present in the image.

class AutoPickUpUpdateInterface
{
public:
	virtual int getRunFromButtonNumber() const = 0;
	virtual void autoPickUpSlot1() = 0;
	virtual void wakeUp() = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModuleInterface
{
public:
	virtual void behaviorSlot00() = 0;
	virtual void behaviorSlot01() = 0;
	virtual void behaviorSlot02() = 0;
	virtual void behaviorSlot03() = 0;
	virtual void behaviorSlot04() = 0;
	virtual void behaviorSlot05() = 0;
	virtual void behaviorSlot06() = 0;
	virtual void behaviorSlot07() = 0;
	virtual void behaviorSlot08() = 0;
	virtual void behaviorSlot09() = 0;
	virtual void behaviorSlot10() = 0;
	virtual void behaviorSlot11() = 0;
	virtual void behaviorSlot12() = 0;
	virtual void behaviorSlot13() = 0;
	virtual void behaviorSlot14() = 0;
	virtual void behaviorSlot15() = 0;
	virtual void behaviorSlot16() = 0;
	virtual void behaviorSlot17() = 0;
	virtual void behaviorSlot18() = 0;
	virtual void behaviorSlot19() = 0;
	virtual void behaviorSlot20() = 0;
	virtual void behaviorSlot21() = 0;
	virtual void behaviorSlot22() = 0;
	virtual void behaviorSlot23() = 0;
	virtual void behaviorSlot24() = 0;
	virtual void behaviorSlot25() = 0;
	virtual AutoPickUpUpdateInterface *getAutoPickUpUpdateInterface() = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ObjectModule
{
public:
	virtual void objectModuleAnchor() = 0;

private:
	unsigned int m_data[2];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	void bfmeWakeAutoPickup(int runFromButtonNumber);

private:
	unsigned char m_pad[0x1f0];
	BehaviorModule **m_behaviors;
};

void Object::bfmeWakeAutoPickup(int runFromButtonNumber)
{
	for (BehaviorModule **module = m_behaviors; *module; ++module)
	{
		AutoPickUpUpdateInterface *autoPickUp = (*module)->getAutoPickUpUpdateInterface();
		if (autoPickUp && autoPickUp->getRunFromButtonNumber() == runFromButtonNumber)
			autoPickUp->wakeUp();
	}
}
