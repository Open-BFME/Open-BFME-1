// cl: /DNDEBUG /MD /EHsc
//
// A module destructor landed as a relocation-blind twin of
// Code/GameEngine/Source/Common/AutoAbilityBehaviorDestructorThunk.cpp
// (0x001ED6E0).  Every differing slot is a per-class symbol -- its own EH
// table and its own three vtables -- so giving the class a distinct name is
// the whole conversion.  The class is named after its address: nothing in
// these bytes says which module it is.

class Gen_dtor_00113f20
{
public:
	virtual ~Gen_dtor_00113f20();

private:
	const void *m_moduleData;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ObjectModule : public Gen_dtor_00113f20
{
private:
	void *m_object;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor() = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModuleInterface
{
public:
	virtual void updateModuleInterfaceAnchor() = 0;
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
public:
	virtual ~UpdateModule() {}

private:
	unsigned int m_14;
	int m_18;
	int m_1c;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	~AsciiString();

private:
	char *m_data;
};


class Open2Module28AC90 : public UpdateModule
{
public:
	virtual ~Open2Module28AC90();

private:
	AsciiString m_20;
};

// @??1Open2Module28AC90@@UAE@XZ 0x0028AC90
Open2Module28AC90::~Open2Module28AC90()
{
}
