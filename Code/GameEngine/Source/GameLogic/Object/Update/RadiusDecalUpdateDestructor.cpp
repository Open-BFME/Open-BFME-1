// cl: /DNDEBUG /MD /EHsc

// The retail object is an UpdateModule-shaped multiple-inheritance object with
// one RadiusDecal member.  These declarations keep the BFME destructor layout
// local to the proper source area instead of changing shared engine headers.

class Gen_dtor_00113f20
{
public:
	virtual ~Gen_dtor_00113f20();

private:
	const void *m_moduleData;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModuleInterface
{
public:
	virtual void getBehaviorModuleInterface() = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModuleInterface
{
public:
	virtual void updateModuleInterface() = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ObjectModule : public Gen_dtor_00113f20
{
private:
	void *m_object;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
public:
	virtual ~BehaviorModule() {}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
private:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	unsigned int m_updateState;

public:
	virtual ~UpdateModule() {}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/RadiusDecal.h
class RadiusDecal
{
public:
	void clear();
	~RadiusDecal();

private:
	const void *m_template;
	void *m_decal;
	unsigned char m_empty;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/RadiusDecalUpdate.h
class RadiusDecalUpdate : public UpdateModule
{
public:
	virtual ~RadiusDecalUpdate();

private:
	RadiusDecal m_deliveryDecal;
};

// ??1RadiusDecalUpdate@@UAE@XZ
RadiusDecalUpdate::~RadiusDecalUpdate()
{
	m_deliveryDecal.clear();
}
