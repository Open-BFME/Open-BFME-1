// cl: /DNDEBUG /MD /EHsc
// readable body of ?privateCombatDrop@AIUpdateInterface@@: Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate.cpp
// readable body: Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate.cpp

typedef bool Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x;
	float y;
	float z;
};

enum CommandSourceType {};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ContainModule.h
class ContainModuleInterface
{
public:
	// BFME's contain interface places removeAllContained at vtable slot 37.
	virtual void containAnchor00();
	virtual void containAnchor04();
	virtual void containAnchor08();
	virtual void containAnchor0C();
	virtual void containAnchor10();
	virtual void containAnchor14();
	virtual void containAnchor18();
	virtual void containAnchor1C();
	virtual void containAnchor20();
	virtual void containAnchor24();
	virtual void containAnchor28();
	virtual void containAnchor2C();
	virtual void containAnchor30();
	virtual void containAnchor34();
	virtual void containAnchor38();
	virtual void containAnchor3C();
	virtual void containAnchor40();
	virtual void containAnchor44();
	virtual void containAnchor48();
	virtual void containAnchor4C();
	virtual void containAnchor50();
	virtual void containAnchor54();
	virtual void containAnchor58();
	virtual void containAnchor5C();
	virtual void containAnchor60();
	virtual void containAnchor64();
	virtual void containAnchor68();
	virtual void containAnchor6C();
	virtual void containAnchor70();
	virtual void containAnchor74();
	virtual void containAnchor78();
	virtual void containAnchor7C();
	virtual void containAnchor80();
	virtual void containAnchor84();
	virtual void containAnchor88();
	virtual void containAnchor8C();
	virtual void containAnchor90();
	virtual void removeAllContained( Bool exposeStealthUnits = false );
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	ContainModuleInterface *getContain() const
	{
		return m_contain;
	}

private:
	unsigned char m_unmodelled_00[ 0x1FC ];
	ContainModuleInterface *m_contain;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface
{
protected:
	virtual void privateCombatDrop( Object *target, const Coord3D &pos, CommandSourceType cmdSource );

	Object *getObject() const
	{
		return m_object;
	}

private:
	unsigned char m_unmodelled_04[ 4 ];
	Object *m_object;
};

// ?privateCombatDrop@AIUpdateInterface@@MAEXPAVObject@@ABUCoord3D@@W4CommandSourceType@@@Z
void AIUpdateInterface::privateCombatDrop( Object *target, const Coord3D &pos, CommandSourceType cmdSource )
{
	if( getObject()->getContain() )
		getObject()->getContain()->removeAllContained( false );
}
