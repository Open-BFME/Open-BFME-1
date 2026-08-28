// cl: /DNDEBUG /MD /EHsc

class Thing;
class ModuleData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ObjectModule
{
public:
	virtual void objectModuleAnchor();
	ObjectModule(Thing *, const ModuleData *);

protected:
	const ModuleData *m_moduleData;
	void *m_object;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModuleInterface
{
public:
	virtual void updateModuleInterfaceAnchor();
};

class FadeAndDieOrnamentData
{
public:
	FadeAndDieOrnamentData()
		: m_00(0x3f800000), m_04(0x3f800000), m_08(0x3f800000), m_0c(0),
		  m_10(1), m_14(1), m_18(1), m_1c(-1), m_20(-1), m_24(0)
	{
	}

	unsigned int m_00;
	unsigned int m_04;
	unsigned int m_08;
	unsigned int m_0c;
	unsigned int m_10;
	unsigned int m_14;
	unsigned int m_18;
	int m_1c;
	int m_20;
	int m_24;
};

class FadeAndDieOrnamentUpdate : public ObjectModule,
	public BehaviorModuleInterface,
	public UpdateModuleInterface
{
public:
	FadeAndDieOrnamentUpdate(Thing *, const ModuleData *);

private:
	unsigned int m_14;
	int m_18;
	int m_1c;
	unsigned int m_20;
	unsigned int m_24;
	FadeAndDieOrnamentData m_data;
};

// ??0FadeAndDieOrnamentUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
FadeAndDieOrnamentUpdate::FadeAndDieOrnamentUpdate(
	Thing *thing, const ModuleData *moduleData)
	: ObjectModule(thing, moduleData),
	  m_14(0), m_18(-1), m_1c(-1)
{
	m_20 = 0;
	m_24 = 0;
	m_data = *(const FadeAndDieOrnamentData *)((const unsigned char *)m_moduleData + 0x0c);
}
