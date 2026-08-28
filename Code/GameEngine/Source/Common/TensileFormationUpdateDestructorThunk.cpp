// cl: /DNDEBUG /MD /EHsc

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

// Deliberately not called UpdateModule. Every other Update-module destructor
// tears its base down as [+0x10]=0x109CBAC, [+0]=0x109CB5C, [+0xC]=0x109CA98;
// this one writes 0x10B1DC4 at +0x10 and the other two unchanged, so the class
// it derives from is not the same one they derive from - there is an
// intermediate here that nothing has named yet. Modelling it as UpdateModule
// made this TU resolve ??_7UpdateModule@@6B@ to a second address and fail the
// DIR32 consistency check.
class TensileFormationUpdateBase : public BehaviorModule, public UpdateModuleInterface
{
private:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	unsigned int m_updateState;

public:
	virtual ~TensileFormationUpdateBase() {}
};

class TensileFormationUpdateMember
{
public:
	~TensileFormationUpdateMember();

private:
	void *m_begin;
	void *m_end;
	void *m_capacity;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/TensileFormationUpdate.h
class TensileFormationUpdate : public TensileFormationUpdateBase
{
public:
	virtual ~TensileFormationUpdate();

private:
	unsigned char m_pad[0xb4];
	TensileFormationUpdateMember m_member;
};

// ??1TensileFormationUpdate@@UAE@XZ
TensileFormationUpdate::~TensileFormationUpdate()
{
}
