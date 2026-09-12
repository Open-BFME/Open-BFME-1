// cl: /DNDEBUG /MD /EHsc

typedef bool Bool;
typedef float Real;

class Thing;
class ModuleData;

template<typename T>
inline const T& max(const T& a, const T& b)
{
	if (a > b)
		return a;
	return b;
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModule
{
public:
	virtual void behaviorModuleAnchor();

private:
	unsigned char m_data[8];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BodyModule.h
class BodyModuleInterface
{
public:
	virtual void bodyModuleInterfaceAnchor();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ActiveBody.h
class ActiveBody : public BehaviorModule,
	public BehaviorModuleInterface,
	public BodyModuleInterface
{
public:
	ActiveBody( Thing *thing, const ModuleData *moduleData );
	virtual ~ActiveBody();

	virtual void slot0();
	virtual void slot1();
	virtual Real getHealth() const;
	virtual void slot3();
	virtual void slot4();
	virtual void internalChangeHealth( Real delta, Bool something );
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ImmortalBody.h
class ImmortalBody : public ActiveBody
{
public:
	ImmortalBody( Thing *thing, const ModuleData *moduleData );
	virtual ~ImmortalBody();

	virtual void internalChangeHealth( Real delta, Bool something );
};

ImmortalBody::ImmortalBody( Thing *thing, const ModuleData *moduleData )
	: ActiveBody( thing, moduleData )
{
}

ImmortalBody::~ImmortalBody()
{
}

void ImmortalBody::internalChangeHealth( Real delta, Bool something )
{
	delta = max( delta, -getHealth() + 1.0f );
	ActiveBody::internalChangeHealth( delta, something );
}
