// BFME Drawable visibility gate at retail 0x0041B8B0.

typedef bool Bool;
typedef unsigned int UnsignedInt;

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL = 1,
	ALLIES = 2
};

class Team;
class Object;

class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	void *m_vtable;
	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	unsigned char m_bfmePadding[ 0xC8 - 8 ];
	UnsignedInt m_kindOf[ 5 ];
};

class Player
{
public:
	Relationship getRelationship( const Team *team ) const;
};

class PlayerList
{
private:
	unsigned char m_bfmePadding[ 0x0C ];

public:
	Player *m_localPlayer;
};

class BfmeTargetGate
{
public:
	virtual Bool bfmeAllowsAttack() const;
};

class BfmeTargetGateModule
{
private:
	unsigned char m_bfmePadding[ 0x24 ];

public:
	BfmeTargetGate m_gate;
	volatile UnsignedInt m_objectID;
};

extern BfmeTargetGateModule *bfmeFindTargetGate( const Object *object );
extern PlayerList *ThePlayerList;

class GameLogic
{
public:
	Object *findObjectByID( int objectID );
};

extern GameLogic *TheGameLogic;

class Object
{
public:
	virtual void bfmeObjectSlot00();
	virtual void bfmeObjectSlot01();
	virtual void bfmeObjectSlot02();
	virtual void bfmeObjectSlot03();
	virtual void bfmeObjectSlot04();
	virtual void bfmeObjectSlot05();
	virtual void bfmeObjectSlot06();
	virtual void bfmeObjectSlot07();
	virtual void bfmeObjectSlot08();
	virtual void bfmeObjectSlot09();
	virtual int bfmeVisibilityResult() const;

	ThingTemplate *m_template;
	unsigned char m_bfmePadding[ 0x23C - 8 ];
	Team *m_team;

	ThingTemplate *getFinalTemplate() const
	{
		ThingTemplate *thingTemplate = m_template;
		if (thingTemplate && thingTemplate->m_nextOverride)
			thingTemplate = (ThingTemplate *)thingTemplate->m_nextOverride->getFinalOverride();
		return thingTemplate;
	}
};

class Drawable
{
private:
	unsigned char m_bfmePadding[ 0xFC ];
	Object *m_object;

public:
	int bfmeVisibilityGate();
};

int Drawable::bfmeVisibilityGate()
{
	Object *object = m_object;
	Object *gateObject;
	BfmeTargetGateModule *module;
	Team *team;
	if (object == 0)
		goto failure;

	ThingTemplate *thingTemplate = object->getFinalTemplate();
	if ((thingTemplate->m_kindOf[ 4 ] & 0x00200000) == 0)
		goto failure;

	module = bfmeFindTargetGate( object );
	if (module == 0 || module->m_gate.bfmeAllowsAttack())
		goto failure;

	team = object->m_team;
	if (ThePlayerList->m_localPlayer->getRelationship( team ) != ENEMIES)
		goto failure;

	gateObject = TheGameLogic->findObjectByID( module->m_objectID );
	if (gateObject == 0)
		goto failure;

	return gateObject->bfmeVisibilityResult();

failure:
	return 0;
}
