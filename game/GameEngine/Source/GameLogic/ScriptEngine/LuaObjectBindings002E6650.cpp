// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Open-BFME7: two Lua script bindings (cdecl int f(lua_State*)).
// 0x002E6650 (151 B): with at least two arguments and the client subsystem
// global present, argument 1 resolves to an object (the table lookup at
// 0x00990030 or a boolean tag) and argument 2 names a weapon template found
// through the store at VA 0x012EF738 (by-value AsciiString) which is fired as
// a temporary weapon at the object's position (+0x38); returns 1 on success.
// 0x002E9EA0 (160 B): arguments 1 and 2 resolve to objects (the second type
// check re-reads index 1 as retail does) argument 3 is a boolean and when the
// first object owns an AI update (+0x204) its command interface (+0x20)
// receives command 2F for the second object with source 1 and the flag byte
// at +0x332; returns 0.  Address-derived names where identity is unknown.

struct lua_State;
extern "C" int lua_gettop( lua_State *state );
extern "C" int lua_type( lua_State *state, int index );
extern "C" const char *lua_tostring( lua_State *state, int index );

unsigned Rva00990030Lookup( lua_State *range, int index );
unsigned Rva00990210Lookup( lua_State *range, int index );

#include "ascii_string.h"

struct Coord3D
{
	float x, y, z;
};

enum CommandSourceType { CMD_FROM_SCRIPT_2E6650 = 1 };

class AICommandInterface
{
public:
	// Retail ILT 0x0003D73F lands on 0x002E9030, matched as
	// AICommandInterface::aiBfmeCommand2F(Object *, CommandSourceType).
	void aiBfmeCommand2F( class Object *target, CommandSourceType commandSource );
};

class Rva002E9EA0AIUpdate
{
public:
	char m_unreconstructed00[ 0x20 ];
	AICommandInterface m_commands;
	char m_unreconstructed21[ 0x332 - 0x21 ];
	unsigned char m_flag332;
};

class Object
{
public:
	char m_unreconstructed00[ 0x38 ];
	Coord3D m_position;
	char m_unreconstructed44[ 0x204 - 0x44 ];
	Rva002E9EA0AIUpdate *m_ai;
};

class GameLogic
{
public:
	Object *findObjectByID( int id );
};

class WeaponTemplate;

class WeaponStore
{
public:
	// Retail ILT 0x0000D3FA lands on 0x001E4F50, matched as
	// WeaponStore::findWeaponTemplate(AsciiString) const.
	const WeaponTemplate *findWeaponTemplate( AsciiString name ) const;
	void createAndFireTempWeapon( const WeaponTemplate *weaponTemplate, const Object *source, const Coord3D *position );
};

// Retail's global at 0x012ED668 is EA's `AudioManager *TheAudio`, defined once in
// Common/Audio/GameAudio.cpp.  This TU only null-tests it, so an opaque forward
// declaration is the whole view; the canonical type keeps the linked build on one
// mangled name.
class AudioManager;

extern GameLogic *TheGameLogic;
extern WeaponStore *TheWeaponStore;
extern AudioManager *TheAudio;

// ?Rva002E6650FireTempWeaponAtObject@@YAHPAUlua_State@@@Z
int Rva002E6650FireTempWeaponAtObject( lua_State *state )
{
	if( lua_gettop( state ) < 2 )
		return 0;
	if( !TheAudio )
		return 0;
	unsigned id = Rva00990030Lookup( state, 1 );
	if( !id && lua_type( state, 1 ) != 1 )
		return 0;
	Object *object = TheGameLogic->findObjectByID( id );
	if( !object )
		return 0;
	const WeaponTemplate *weapon = TheWeaponStore->findWeaponTemplate( lua_tostring( state, 2 ) );
	if( weapon )
	{
		TheWeaponStore->createAndFireTempWeapon( weapon, object, &object->m_position );
		return 1;
	}
	return 0;
}

// ?Rva002E9EA0CommandObjectAtObject@@YAHPAUlua_State@@@Z
int Rva002E9EA0CommandObjectAtObject( lua_State *state )
{
	unsigned id = Rva00990030Lookup( state, 1 );
	if( !id && lua_type( state, 1 ) != 1 )
		return 0;
	Object *object = TheGameLogic->findObjectByID( id );
	if( !object )
		return 0;
	unsigned targetId = Rva00990030Lookup( state, 2 );
	if( !targetId && lua_type( state, 1 ) != 1 )
		return 0;
	Object *target = TheGameLogic->findObjectByID( targetId );
	if( !target )
		return 0;
	bool flag = Rva00990210Lookup( state, 3 ) != 0;
	Rva002E9EA0AIUpdate *ai = object->m_ai;
	if( ai )
	{
		ai->m_commands.aiBfmeCommand2F( target, CMD_FROM_SCRIPT_2E6650 );
		ai->m_flag332 = flag;
	}
	return 0;
}
