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

struct Rva002E5FF0Field23C
{
	char m_unreconstructed00[ 4 ];
	void *m_field4;
};

class Object
{
public:
	bool getAttributeModifierBonus( int type, float *bonus ) const;

	char m_unreconstructed00[ 0x204 ];
	BfmeAI956 *m_ai;
	char m_unreconstructed208[ 0x23c - 0x208 ];
	Rva002E5FF0Field23C *m_field23c;
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

extern "C" void lua_pushstring( lua_State *state, const char *str );
extern "C" char g_bfmeEmptyAscii[];

struct Rva002E5FF0Str
{
	void *m_data;
};

extern Rva002E5FF0Str Rva01336E50Str;

// ?Rva002E5FF0ObjectFieldName@@YAHPAUlua_State@@@Z
int Rva002E5FF0ObjectFieldName( lua_State *state )
{
	unsigned id = Rva00990030Lookup( state, 1 );
	if( !id && lua_type( state, 1 ) != 1 )
	{
		lua_pushnil( state );
		return 1;
	}
	Object *object = TheGameLogic->bfmeFind1011( id );
	if( object )
	{
		void *field2 = object->m_field23c->m_field4;
		Rva002E5FF0Str *str = !field2 ? &Rva01336E50Str : (Rva002E5FF0Str *)( (char *)field2 + 0x14 );
		lua_pushstring( state, str->m_data ? (const char *)str->m_data + 8 : g_bfmeEmptyAscii );
		return 1;
	}
	lua_pushnil( state );
	return 1;
}

int bfmeLookup_001c62b0( void *name );

// ?Rva002E77F0ObjectBitTest@@YAHPAUlua_State@@@Z
int Rva002E77F0ObjectBitTest( lua_State *state )
{
	unsigned id = Rva00990030Lookup( state, 1 );
	if( !id && lua_type( state, 1 ) != 1 )
	{
		lua_pushnil( state );
		return 1;
	}
	Object *object = TheGameLogic->bfmeFind1011( id );
	if( object )
	{
		const char *name = lua_tostring( state, 2 );
		if( name )
		{
			int idx = bfmeLookup_001c62b0( (void *)name );
			if( idx != -1 )
			{
				unsigned *bits = (unsigned *)( (char *)object + 0x110 );
				bool bit = ( bits[ (unsigned)idx >> 5 ] & ( 1u << ( idx & 0x1f ) ) ) != 0;
				bfmeGo1039E( (BfmeQ1039 *)state, bit );
				return 1;
			}
		}
	}
	lua_pushnil( state );
	return 1;
}

struct BfmeAskResult;

class BfmeSubBIA
{
public:
	BfmeAskResult *lastNode00087A80( void );
};

// ?Rva002E60B0ObjectOverrideName@@YAHPAUlua_State@@@Z
int Rva002E60B0ObjectOverrideName( lua_State *state )
{
	unsigned id = Rva00990030Lookup( state, 1 );
	if( !id && lua_type( state, 1 ) != 1 )
	{
		lua_pushnil( state );
		return 1;
	}
	Object *object = TheGameLogic->bfmeFind1011( id );
	if( object )
	{
		void *p1 = *(void **)( (char *)object + 4 );
		void *r = p1;
		if( p1 )
		{
			void *p2 = *(void **)( (char *)p1 + 4 );
			if( p2 )
				r = ( (BfmeSubBIA *)p2 )->lastNode00087A80();
		}
		void *val = *(void **)( (char *)r + 0x20 );
		if( val )
		{
			lua_pushstring( state, (const char *)val + 8 );
			return 1;
		}
		lua_pushstring( state, g_bfmeEmptyAscii );
		return 1;
	}
	lua_pushnil( state );
	return 1;
}
