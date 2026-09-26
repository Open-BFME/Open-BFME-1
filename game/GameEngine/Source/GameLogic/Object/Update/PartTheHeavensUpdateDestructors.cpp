// cl: /DNDEBUG /MD /EHsc

// Complete destructor 0x00299820 and emitted scalar wrapper 0x00299A50.
// The matched constructor at 0x002999D0, typed factories, and module-name
// getter establish identity; wrapper ILT 0x0000806C reaches this teardown.
// The retail object is an UpdateModule-shaped multiple-inheritance object.  The
// declarations are deliberately TU-local: only the ABI-relevant base layout and
// the one explicitly destroyed pointee are needed here.

class Gen_dtor_00113f20
{
public:
	virtual ~Gen_dtor_00113f20();

private:
	const void *m_moduleData;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModuleInterface
{
public:
	virtual void getBehaviorModuleInterface() = 0;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModuleInterface
{
public:
	virtual void updateModuleInterface() = 0;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ObjectModule : public Gen_dtor_00113f20
{
private:
	void *m_object;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
public:
	virtual ~BehaviorModule() {}
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
private:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	unsigned int m_updateState;
	unsigned int m_nextUpdateFrame;

public:
	virtual ~UpdateModule() {}
};

class PartTheHeavensUpdatePointee
{
public:
	virtual void pointeeSlot0();
	virtual void pointeeSlot1();
	virtual void releasePointee();
};

class PartTheHeavensUpdate : public UpdateModule
{
public:
	virtual ~PartTheHeavensUpdate();

private:
	PartTheHeavensUpdatePointee *m_pointee;
};

// ??1PartTheHeavensUpdate@@UAE@XZ
PartTheHeavensUpdate::~PartTheHeavensUpdate()
{
	if (m_pointee)
		m_pointee->releasePointee();
}
