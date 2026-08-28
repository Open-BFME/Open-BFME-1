// ?isAircraftThatAdjustsDestination@AIUpdateInterface@@QBE_NXZ
// partial score=0.9 date=2026-08-28
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// readable body: Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate.cpp

typedef bool Bool;

enum LocomotorAppearance
{
	LOCO_HOVER = 2,
	LOCO_WINGS = 3
};

class LocomotorOverridable
{
public:
	virtual ~LocomotorOverridable();
	LocomotorOverridable *friend_getFinalOverride();

	LocomotorOverridable *m_nextOverride;
};

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
};

class AIUpdateInterface : public AIUpdateVirtualPrefix
{
public:
	virtual Bool isGiantBird() const;
	Bool isAircraftThatAdjustsDestination() const;

private:
	unsigned char m_unmodelled_004[ 0x1CC - 4 ];
	Locomotor *m_curLocomotor;
};

#undef AI_SLOT

// ?isAircraftThatAdjustsDestination@AIUpdateInterface@@QBE_NXZ
Bool AIUpdateInterface::isAircraftThatAdjustsDestination() const
{
	if( isGiantBird() )
		return true;

	Locomotor *curLocomotor = m_curLocomotor;
	if( curLocomotor == 0 )
		return false;

	if( curLocomotor->getAppearance() == LOCO_HOVER )
		return true;
	if( curLocomotor->getAppearance() == LOCO_WINGS )
		return true;

	return false;
}
