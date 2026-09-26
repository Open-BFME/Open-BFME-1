// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// Complete destructor 0x0020B180 also emits scalar wrapper 0x0020C020.
// Constructor 0x0020AE30 installs vtable 0x010A6CCC with the wrapper at
// slot zero, independently establishing this shared class identity.
//
// SpawnBehavior's retail destructor uses the BFME-era UpdateModule layout and
// two interface-base slots.  Keep this recovered layout in the proper source
// family instead of changing the shared reference headers.

#include <list>

class Gen_dtor_00113d40
{
public:
	virtual ~Gen_dtor_00113d40();

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
class ObjectModule : public Gen_dtor_00113d40
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
public:
	virtual ~UpdateModule() {}

private:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	unsigned int m_updateState;
};

template <int Number>
class SpawnBehaviorSecondaryBase
{
public:
	virtual void slot();
};

class SpawnBehavior
	: public UpdateModule,
	  public SpawnBehaviorSecondaryBase<1>,
	  public SpawnBehaviorSecondaryBase<2>,
	  public SpawnBehaviorSecondaryBase<3>,
	  public SpawnBehaviorSecondaryBase<4>
{
public:
	virtual ~SpawnBehavior();

private:
	unsigned char m_unreconstructed_30[0x14];
	_STL::list<int> m_spawnList;
	_STL::list<int> m_list48;
};

// ??1SpawnBehavior@@UAE@XZ
SpawnBehavior::~SpawnBehavior()
{
	m_spawnList.clear();
}
