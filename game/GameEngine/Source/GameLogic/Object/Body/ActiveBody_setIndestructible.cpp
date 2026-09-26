// cl: /DNDEBUG /MD /EHsc
// Retail 0x00210690 is ActiveBody::setIndestructible.  The body stores the
// requested flag, follows the Object template override chain, tests the bridge
// kind bit, and propagates the flag to each of four bridge towers.

typedef bool Bool;
typedef int Int;
typedef int ObjectID;

class Object;

enum BridgeTowerType
{
	BRIDGE_TOWER_0
};

class BfmeActiveBodySetOverridable
{
public:
	unsigned char m_memoryPoolObject[4];
	BfmeActiveBodySetOverridable *m_nextOverride;
	const BfmeActiveBodySetOverridable *getFinalOverride() const;
};

class BridgeBehaviorInterface
{
public:
	virtual void setTower( BridgeTowerType type, Object *tower ) = 0;
	virtual ObjectID getTowerID( BridgeTowerType type ) = 0;
	virtual void createScaffolding() = 0;
	virtual void removeScaffolding() = 0;
	virtual Bool isScaffoldInMotion() = 0;
	virtual Bool isScaffoldPresent() = 0;
};

class BfmeActiveBodySetBridgeBehavior
{
public:
	static BridgeBehaviorInterface *getBridgeBehaviorInterfaceFromObject( Object *object );
};

class BodyModuleInterface
{
public:
	virtual void pad00() = 0; virtual void pad04() = 0; virtual void pad08() = 0;
	virtual void pad0C() = 0; virtual void pad10() = 0; virtual void pad14() = 0;
	virtual void pad18() = 0; virtual void pad1C() = 0; virtual void pad20() = 0;
	virtual void pad24() = 0; virtual void pad28() = 0; virtual void pad2C() = 0;
	virtual void pad30() = 0; virtual void pad34() = 0; virtual void pad38() = 0;
	virtual void pad3C() = 0; virtual void pad40() = 0; virtual void pad44() = 0;
	virtual void pad48() = 0; virtual void pad4C() = 0; virtual void pad50() = 0;
	virtual void pad54() = 0; virtual void pad58() = 0; virtual void pad5C() = 0;
	virtual void pad60() = 0; virtual void pad64() = 0; virtual void pad68() = 0;
	virtual void pad6C() = 0; virtual void pad70() = 0; virtual void pad74() = 0;
	virtual void pad78() = 0; virtual void pad7C() = 0; virtual void pad80() = 0;
	virtual void setIndestructible( Bool value ) = 0;
};

class Object
{
public:
	virtual void pad00() = 0;
	BfmeActiveBodySetOverridable *m_template;
	unsigned char m_padding[0x1F8];
	BodyModuleInterface *m_body;
};

class BfmeActiveBodySetGameLogic
{
public:
	Object *findObjectByID( int id );
};

extern BfmeActiveBodySetGameLogic *TheBfmeGameLogic;

class ActiveBody
{
public:
	virtual void setIndestructible( Bool indestructible );
};

// ?setIndestructible@ActiveBody@@UAEX_N@Z
void ActiveBody::setIndestructible( Bool indestructible )
{
	*(unsigned char *)((unsigned char *)this + 0x97) = (unsigned char)indestructible;

	Object *us = *(Object **)((unsigned char *)this - 8);
	BfmeActiveBodySetOverridable *thingTemplate = us->m_template;
	if( thingTemplate && thingTemplate->m_nextOverride )
	{
		thingTemplate = (BfmeActiveBodySetOverridable *)thingTemplate->m_nextOverride->getFinalOverride();
	}
	if( (*(unsigned int *)((unsigned char *)thingTemplate + 0xC8) & 0x400000) != 0 )
	{
		BridgeBehaviorInterface *bbi = BfmeActiveBodySetBridgeBehavior::getBridgeBehaviorInterfaceFromObject( us );
		if( bbi )
		{
			for( Int i = 0; i < 4; ++i )
			{
				Object *tower = TheBfmeGameLogic->findObjectByID( bbi->getTowerID( (BridgeTowerType)i ) );
				if( tower )
				{
					BodyModuleInterface *body = tower->m_body;
					if( body )
						body->setIndestructible( indestructible );
				}
			}
		}
	}
}
