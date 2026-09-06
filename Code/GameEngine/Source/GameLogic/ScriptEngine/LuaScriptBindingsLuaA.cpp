// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Open-BFME7: Lua script bindings lane "luaA" (cdecl int f(lua_State*)).
// Address-derived names where the real ZH identity is unknown.

struct lua_State;
extern "C" int lua_gettop( lua_State *state );
extern "C" int lua_type( lua_State *state, int index );
extern "C" const char *lua_tostring( lua_State *state, int index );
extern "C" void lua_pushnil( lua_State *state );

unsigned Rva00990030Lookup( lua_State *range, int index );

extern "C" char _bfmeString10CF498[];

struct Coord3D
{
	float x, y, z;
};

class BfmeAI956
{
public:
	int bfmeKind956( void );
};

class Object
{
public:
	bool getAttributeModifierBonus( int type, float *bonus ) const;

	char m_unreconstructed00[ 0x204 ];
	BfmeAI956 *m_ai;
};

class GameLogic
{
public:
	Object *bfmeFind1011( int id );
};

extern GameLogic *TheGameLogic;

int GetGameLogicRandomValue( int lo, int hi, const char *file, int line );

struct BfmeQ1039;
void bfmeGo1039E( BfmeQ1039 *q, int v );

// ?Rva002E6170ObjectRandomChance@@YAHPAUlua_State@@@Z
int Rva002E6170ObjectRandomChance( lua_State *state )
{
	unsigned id = Rva00990030Lookup( state, 1 );
	if( !id && lua_type( state, 1 ) != 1 )
	{
		lua_pushnil( state );
		return 0;
	}
	Object *object = TheGameLogic->bfmeFind1011( id );
	if( object )
	{
		bool flag = true;
		float bonus = 0.0f;
		if( object->getAttributeModifierBonus( 4, &bonus ) )
			flag = (float)GetGameLogicRandomValue( 0, 1, _bfmeString10CF498, 0x794 ) > bonus;
		if( object->m_ai && object->m_ai->bfmeKind956() == 0x2d )
			flag = false;
		bfmeGo1039E( (BfmeQ1039 *)state, flag );
		return 1;
	}
	lua_pushnil( state );
	return 1;
}
