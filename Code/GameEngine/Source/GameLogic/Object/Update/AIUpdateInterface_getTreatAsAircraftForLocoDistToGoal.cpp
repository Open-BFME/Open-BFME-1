// cl: /DNDEBUG /MD /EHsc
// readable body of ?getTreatAsAircraftForLocoDistToGoal@AIUpdateInterface@@: Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate.cpp
// readable body: Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate.cpp

typedef bool Bool;
typedef float Real;

enum LocomotorAppearance
{
	LOCO_HOVER = 2
};

class LocomotorOverridable
{
public:
	virtual ~LocomotorOverridable();
	LocomotorOverridable *friend_getFinalOverride();

	LocomotorOverridable *m_nextOverride;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Locomotor.h
class Locomotor : public LocomotorOverridable
{
public:
	LocomotorAppearance getAppearance() const
	{
		// Retail deliberately reads through the override pointer, so a missing
		// override remains an invalid Locomotor rather than silently using this.
		LocomotorOverridable *o = m_nextOverride;
		if( o && o->m_nextOverride )
			o = o->m_nextOverride->friend_getFinalOverride();
		return static_cast<const Locomotor *>(o)->m_appearance;
	}

private:
	unsigned char m_unmodelled_008[ 0x70 - 8 ];
	LocomotorAppearance m_appearance;
};

#define AI_SLOT(N) virtual void slot##N()

class AIUpdateVirtualPrefix
{
public:
	AI_SLOT(000); AI_SLOT(001); AI_SLOT(002); AI_SLOT(003);
	AI_SLOT(004); AI_SLOT(005); AI_SLOT(006); AI_SLOT(007);
	AI_SLOT(008); AI_SLOT(009); AI_SLOT(010); AI_SLOT(011);
	AI_SLOT(012); AI_SLOT(013); AI_SLOT(014); AI_SLOT(015);
	AI_SLOT(016); AI_SLOT(017); AI_SLOT(018); AI_SLOT(019);
	AI_SLOT(020); AI_SLOT(021); AI_SLOT(022); AI_SLOT(023);
	AI_SLOT(024); AI_SLOT(025); AI_SLOT(026); AI_SLOT(027);
	AI_SLOT(028); AI_SLOT(029); AI_SLOT(030); AI_SLOT(031);
	AI_SLOT(032); AI_SLOT(033); AI_SLOT(034); AI_SLOT(035);
	AI_SLOT(036); AI_SLOT(037); AI_SLOT(038); AI_SLOT(039);
	AI_SLOT(040); AI_SLOT(041); AI_SLOT(042); AI_SLOT(043);
	AI_SLOT(044); AI_SLOT(045); AI_SLOT(046); AI_SLOT(047);
	AI_SLOT(048); AI_SLOT(049); AI_SLOT(050); AI_SLOT(051);
	AI_SLOT(052); AI_SLOT(053); AI_SLOT(054); AI_SLOT(055);
	AI_SLOT(056); AI_SLOT(057); AI_SLOT(058); AI_SLOT(059);
	AI_SLOT(060); AI_SLOT(061); AI_SLOT(062); AI_SLOT(063);
	AI_SLOT(064); AI_SLOT(065); AI_SLOT(066); AI_SLOT(067);
	AI_SLOT(068); AI_SLOT(069); AI_SLOT(070); AI_SLOT(071);
	AI_SLOT(072); AI_SLOT(073); AI_SLOT(074); AI_SLOT(075);
	AI_SLOT(076); AI_SLOT(077); AI_SLOT(078); AI_SLOT(079);
	AI_SLOT(080); AI_SLOT(081); AI_SLOT(082); AI_SLOT(083);
	AI_SLOT(084); AI_SLOT(085); AI_SLOT(086); AI_SLOT(087);
	AI_SLOT(088); AI_SLOT(089); AI_SLOT(090); AI_SLOT(091);
	AI_SLOT(092); AI_SLOT(093); AI_SLOT(094); AI_SLOT(095);
	AI_SLOT(096); AI_SLOT(097); AI_SLOT(098); AI_SLOT(099);
	AI_SLOT(100); AI_SLOT(101); AI_SLOT(102); AI_SLOT(103);
	AI_SLOT(104); AI_SLOT(105); AI_SLOT(106); AI_SLOT(107);
	AI_SLOT(108); AI_SLOT(109); AI_SLOT(110); AI_SLOT(111);
	AI_SLOT(112); AI_SLOT(113); AI_SLOT(114); AI_SLOT(115);
	AI_SLOT(116); AI_SLOT(117); AI_SLOT(118); AI_SLOT(119);
	AI_SLOT(120); AI_SLOT(121); AI_SLOT(122);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface : public AIUpdateVirtualPrefix
{
public:
	virtual Bool isDoingGroundMovement() const;

protected:
	virtual Bool getTreatAsAircraftForLocoDistToGoal() const;

private:
	unsigned char m_unmodelled_004[ 0x168 - 4 ];
	Real m_pathExtraDistance;
	unsigned char m_unmodelled_16C[ 0x1CC - 0x16C ];
	Locomotor *m_curLocomotor;
};

#undef AI_SLOT

// ?getTreatAsAircraftForLocoDistToGoal@AIUpdateInterface@@MBE_NXZ
Bool AIUpdateInterface::getTreatAsAircraftForLocoDistToGoal() const
{
	Bool treatAsAircraft = !isDoingGroundMovement();
	if( m_pathExtraDistance > 1.0f )
		treatAsAircraft = true;
	if( m_curLocomotor && m_curLocomotor->getAppearance() == LOCO_HOVER )
		treatAsAircraft = true;
	return treatAsAircraft;
}
