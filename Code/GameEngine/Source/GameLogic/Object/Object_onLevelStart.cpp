// cl: /DNDEBUG /MD /EHsc

class Dict;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Drawable.h
class Drawable
{
public:
	void onLevelStart();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModuleInterface
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
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual void slot31() = 0;
	virtual void slot32() = 0;
	virtual void slot33() = 0;
	virtual void slot34() = 0;
	virtual void slot35() = 0;
	virtual void slot36() = 0;
	virtual void slot37() = 0;
	virtual void slot38() = 0;
	virtual void onLevelStart(Dict *properties) = 0;
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
	virtual void objectSlot00() = 0;
	virtual void objectSlot01() = 0;
	virtual void objectSlot02() = 0;
	virtual void objectSlot03() = 0;
	virtual void objectSlot04() = 0;
	virtual void objectSlot05() = 0;
	virtual void objectSlot06() = 0;
	virtual void objectSlot07() = 0;
	virtual void objectSlot08() = 0;
	virtual void objectSlot09() = 0;
	virtual Drawable *getDrawable() const = 0;

	void onLevelStart(Dict *properties);

private:
	unsigned char m_unmodelled004[0x1f0 - 4];
	BehaviorModule **m_behaviors;
};

void Object::onLevelStart(Dict *properties)
{
	for (BehaviorModule **module = m_behaviors; *module; ++module)
		(*module)->onLevelStart(properties);

	Drawable *drawable = getDrawable();
	if (drawable)
		drawable->onLevelStart();
}
