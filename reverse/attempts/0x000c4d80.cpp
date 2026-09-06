// ?canActOnEnemy@Rva000C4D80Manager@@QAE_NPAVObject@@PBV2@H@Z
// partial score=0.9 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: an ActionManager-style predicate at 0x000C4D80 (195 B; thiscall
// with three stack arguments the this pointer unused): both objects present
// the target an enemy (relationship 2) the actor's status byte at +0x344 bit
// 0 and flag byte at +0x90 bit 2 clear the target without status 2 or 0x13
// then either (actor of kind 0xC above terrain or water with a target of kind
// 0x23) or (target of kind 0x1F); the actor's module at +0x200 must report
// equal values from its virtual slots 4 and 6 and the result is the negated
// shroud test.  The shroud helper at 0x000C3F80 takes its two objects in
// esi/edi (an LTCG register convention) so it is declared here with only its
// one stack argument.  Address-derived names.

typedef bool Bool;

enum Relationship
{
	ENEMIES = 2
};

enum KindOfType
{
	KINDOF_INVALID = -1
};

class Object;

class BFMEActionObject
{
public:
	Bool testStatus( int status ) const;
};

class Rva000C4D80Module
{
public:
	virtual void slot0( void );
	virtual void slot1( void );
	virtual void slot2( void );
	virtual void slot3( void );
	virtual float getCurrent( void );
	virtual void slot5( void );
	virtual float getMaximum( void );
};

class Object
{
public:
	Relationship getRelationship( const Object *other ) const;
	Bool isKindOf( KindOfType kind ) const;
	Bool isAboveTerrainOrWater( void ) const;

	char m_unreconstructed00[ 0x90 ];
	unsigned char m_flags90;
	char m_unreconstructed91[ 0x200 - 0x91 ];
	Rva000C4D80Module *m_module200;
	char m_unreconstructed204[ 0x344 - 0x204 ];
	unsigned char m_status344;
};

Bool __cdecl Rva000C3F80IsShroudedForAction( int commandSource );

class Rva000C4D80Manager
{
public:
	Bool canActOnEnemy( Object *obj, const Object *target, int commandSource );
};

// ?canActOnEnemy@Rva000C4D80Manager@@QAE_NPAVObject@@PBV2@H@Z
Bool Rva000C4D80Manager::canActOnEnemy( Object *obj, const Object *target, int commandSource )
{
	if( !obj || !target )
		return false;
	if( obj->getRelationship( target ) != ENEMIES )
		return false;
	if( obj->m_status344 & 1 )
		return false;
	if( obj->m_flags90 & 4 )
		return false;
	if( ((const BFMEActionObject *)target)->testStatus( 2 ) )
		return false;
	if( ((const BFMEActionObject *)target)->testStatus( 0x13 ) )
		return false;
	if( obj->isKindOf( (KindOfType)0xC ) )
	{
		if( !obj->isAboveTerrainOrWater() )
			return false;
		if( !target->isKindOf( (KindOfType)0x23 ) )
			return false;
	}
	else
	{
		if( !target->isKindOf( (KindOfType)0x1F ) )
			return false;
	}
	Rva000C4D80Module *module = obj->m_module200;
	float current = module->getCurrent();
	if( current != module->getMaximum() )
		return false;
	return !Rva000C3F80IsShroudedForAction( commandSource );
}
