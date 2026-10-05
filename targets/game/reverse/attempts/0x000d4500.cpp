// ?Rva000D4500CastleSearchCallback@@YAHPAVObject@@PAX@Z
// partial score=0.9817 date=2026-10-05
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/GameEngine/Source
// Retail 0x000D4500, 273 bytes: the Player::iterateObjects callback that
// Player::rva000D4660 (0x000D4660) pushes with its four-word search record
// { Player *, Bool, Object *best, CastleBehavior *bestCastle }; the caller
// returns the best castle's owner (or the best object) when the walk ends.
//
// Each candidate must be a STRUCTURE (the template's own bit test, inlined as
// in BuildAssistant_sellObject.cpp) or a BASE_FOUNDATION (out-of-line
// Thing::isKindOf, 0x000A2CF0); its CastleBehavior is found through the
// function-static "CastleBehavior" key. Candidates the matched comparator
// Rva000CDA90Compare does not rank above the current best are skipped, and
// with the record's flag set so is one whose castle owner (or itself, when the
// castle names no live owner) has private status bit 0x08 set. The EA name of
// the callback is not proven, so it keeps its address.
// Kind indices come from retail's KindOf name table at VA 0x012AA068.

#define NULL 0

typedef bool Bool;

enum KindOfType
{
	KINDOF_STRUCTURE = 7,			///< retail KindOf name table entry 7
	KINDOF_BASE_FOUNDATION = 103	///< retail KindOf name table entry 103
};

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey( const char *name );		///< 0x0008FFC0
};
extern NameKeyGenerator *TheNameKeyGenerator;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	virtual ~Overridable();

	const Overridable *getFinalOverride( void ) const;	///< ILT thunk at 0x000022BB

	Overridable *m_nextOverride;						///< retail this+0x04
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate : public Overridable
{
public:
	Bool isKindOf( KindOfType t ) const
	{
		return (m_kindof[(unsigned int)t >> 5] & (1 << ((unsigned int)t & 31))) != 0;
	}

private:
	unsigned char m_unreconstructed_08[0xC8 - 0x08];
	unsigned int m_kindof[3];							///< retail this+0xC8
};

class Module;

#define THING_TU_MEMBERS \
	const ThingTemplate *getTemplate( void ) const; \
	Bool isKindOf( KindOfType t ) const;

#define OBJECT_TU_MEMBERS \
	Module *findModule( NameKeyType key ) const;

#include "GameLogic/Object/object.h"

inline const ThingTemplate *Thing::getTemplate( void ) const
{
	const ThingTemplate *tmpl = m_template;
	if( tmpl == 0 )
		return 0;
	if( tmpl->m_nextOverride )
		tmpl = (const ThingTemplate *)tmpl->m_nextOverride->getFinalOverride();
	return tmpl;
}

// Only the owner's object ID at +0xA0 is read here.
class CastleBehavior
{
public:
	Int getOwnerID( void ) const { return m_ownerID; }

private:
	unsigned char m_unmodelled_000[0xA0];
	Int m_ownerID;										///< retail this+0xA0
};

class GameLogic
{
public:
	Object *findObjectByID( Int id );					///< 0x0009A510
};
extern GameLogic *TheGameLogic;

int Rva000CDA90Compare( Object *first, CastleBehavior *firstCastle,
	Object *second, CastleBehavior *secondCastle );

class Player;

// The search record Player::rva000D4660 builds on its stack.
struct Rva000D4500CastleSearch
{
	Player *m_player;
	Bool m_skipFlaggedOwner;
	Object *m_bestObject;
	CastleBehavior *m_bestCastle;
};

int Rva000D4500CastleSearchCallback( Object *obj, void *userData )
{
	if( obj == NULL )
		return 1;

	if( !obj->getTemplate()->isKindOf( KINDOF_STRUCTURE ) && !obj->isKindOf( KINDOF_BASE_FOUNDATION ) )
		return 1;

	static NameKeyType key = TheNameKeyGenerator->nameToKey( "CastleBehavior" );
	CastleBehavior *castle = (CastleBehavior *)obj->findModule( key );

	Rva000D4500CastleSearch *search = (Rva000D4500CastleSearch *)userData;
	if( search->m_bestObject &&
			Rva000CDA90Compare( search->m_bestObject, search->m_bestCastle, obj, castle ) >= 0 )
		return 1;

	if( search->m_skipFlaggedOwner )
	{
		if( castle )
		{
			Object *castleOwner = TheGameLogic->findObjectByID( castle->getOwnerID() );
			if( castleOwner )
			{
				if( castleOwner->m_privateStatus & 0x08 )
					return 1;
			}
			else if( obj->m_privateStatus & 0x08 )
				return 1;
		}
		else if( obj->m_privateStatus & 0x08 )
			return 1;
	}

	search->m_bestObject = obj;
	search->m_bestCastle = castle;
	return 1;
}
