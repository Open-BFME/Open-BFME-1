// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4

#include "PreRTS.h"

class Team
{
public:
	Relationship getRelationship( const Team *that ) const;
};

class Player
{
public:
	Team *getDefaultTeam() const { return m_defaultTeam; }

private:
	char m_head[0x230];
	Team *m_defaultTeam;
};

class ContainModuleInterface
{
public:
	virtual void slot_000();
	virtual void slot_004();
	virtual void slot_008();
	virtual void slot_00c();
	virtual void slot_010();
	virtual void slot_014();
	virtual void slot_018();
	virtual void slot_01c();
	virtual void slot_020();
	virtual void slot_024();
	virtual void slot_028();
	virtual void slot_02c();
	virtual void slot_030();
	virtual void slot_034();
	virtual void slot_038();
	virtual Player *getApparentControllingPlayer( Player *localPlayer ) = 0;
};

class Object
{
public:
	Player *getControllingPlayer() const;
	Team *getTeam() const { return m_team; }
	ContainModuleInterface *getContain() const { return m_contain; }

private:
	char m_head[0x1fc];
	ContainModuleInterface *m_contain;
	char m_middle[0x23c - 0x200];
	Team *m_team;
};

static __declspec(noinline) Bool appearsToContainFriendlies( const Object *obj, const Object *otherObject )
{
	ContainModuleInterface *otherContain = otherObject->getContain();
	if( otherContain )
	{
		Player *otherPlayer = otherContain->getApparentControllingPlayer(obj->getControllingPlayer());
		if (otherPlayer &&
			obj->getTeam()->getRelationship(otherPlayer->getDefaultTeam()) != ENEMIES)
		{
			return TRUE;
		}
	}
	return FALSE;
}

static Bool callAppearsToContainFriendlies( const Object *obj, const Object *otherObject )
{
	return appearsToContainFriendlies( obj, otherObject );
}

static Bool (* volatile callAppearsToContainFriendliesAnchor)(
	const Object *, const Object * ) = callAppearsToContainFriendlies;
