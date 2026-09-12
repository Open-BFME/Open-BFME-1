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

class Rva002E9F70CommandIface
{
public:
	void j_000186e7( int arg );
};

class BfmeAI956
{
public:
	int bfmeKind956( void );
	bool j_0004a057( void );
	void j_000486fd( void );

	char m_unreconstructed00[ 0x20 ];
	Rva002E9F70CommandIface m_cmdAt20;
};

struct Rva002E5FF0Field23C
{
	char m_unreconstructed00[ 4 ];
	void *m_field4;
};

class ThingTemplate;

class Object
{
public:
	bool getAttributeModifierBonus( int type, float *bonus ) const;

	void *m_vftable;
	ThingTemplate *m_thingTemplate;
	char m_unreconstructed08[ 0x1F8 ];
	void *m_at200;
	BfmeAI956 *m_ai;
	void *m_at208;
	char m_unreconstructed20c[ 0x23c - 0x20c ];
	Rva002E5FF0Field23C *m_team;
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
extern "C" const char g_bfmeEmptyAscii[];

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
		void *field2 = object->m_team->m_field4;
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

class Rva002E9F70Vtbl94
{
public:
	virtual void v0( void ) {}
	virtual void v1( void ) {}
	virtual void v2( void ) {}
	virtual void v3( void ) {}
	virtual void v4( void ) {}
	virtual void v5( void ) {}
	virtual void v6( void ) {}
	virtual void v7( void ) {}
	virtual void v8( void ) {}
	virtual void v9( void ) {}
	virtual void v10( void ) {}
	virtual void v11( void ) {}
	virtual void v12( void ) {}
	virtual void v13( void ) {}
	virtual void v14( void ) {}
	virtual void v15( void ) {}
	virtual void v16( void ) {}
	virtual void v17( void ) {}
	virtual void v18( void ) {}
	virtual void v19( void ) {}
	virtual void v20( void ) {}
	virtual void v21( void ) {}
	virtual void v22( void ) {}
	virtual void v23( void ) {}
	virtual void v24( void ) {}
	virtual void v25( void ) {}
	virtual void v26( void ) {}
	virtual void v27( void ) {}
	virtual void v28( void ) {}
	virtual void v29( void ) {}
	virtual void v30( void ) {}
	virtual void v31( void ) {}
	virtual void v32( void ) {}
	virtual void v33( void ) {}
	virtual void v34( void ) {}
	virtual void v35( void ) {}
	virtual void v36( void ) {}
	virtual void v37call( bool arg ) {}
};

// ?Rva002E9F70ObjectDock@@YAHPAUlua_State@@@Z
int Rva002E9F70ObjectDock( lua_State *state )
{
	unsigned id = Rva00990030Lookup( state, 1 );
	if( !id && lua_type( state, 1 ) != 1 )
		return 0;
	Object *object = TheGameLogic->bfmeFind1011( id );
	if( !object )
		return 0;
	void *p1 = object->m_at208;
	if( p1 && *( (unsigned char *)p1 + 0x5c ) )
		return 0;
	void *p2 = object->m_at200;
	if( !p2 )
		return 0;
	( (Rva002E9F70Vtbl94 *)p2 )->v37call( 1 );
	BfmeAI956 *child = object->m_ai;
	if( !child )
		return 0;
	if( child->j_0004a057() )
		child->j_000486fd();
	child->m_cmdAt20.j_000186e7( 1 );
	return 0;
}

class AsciiString
{
public:
	AsciiString() { m_data = 0; }
	AsciiString( const char *text );
	~AsciiString();
	AsciiString &operator=( const AsciiString &text );
	const char *str() const
	{
		return m_data ? (const char *)m_data + 8 : g_bfmeEmptyAscii;
	}

	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	void *m_vftable;
	Overridable *m_nextOverride;
	Overridable *getFinalOverride();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate : public Overridable
{
public:
	char m_pad08[ 0x18 ];
	AsciiString m_name;
};

// ?Rva002E60B0ObjectOverrideName@@YAHPAUlua_State@@@Z
// The neutral name records the proven Lua callback boundary; no public EA
// spelling is claimed.  Object::m_thingTemplate is the Thing +4 pointer, and
// ThingTemplate::m_name is the source-backed AsciiString at +20.
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
		ThingTemplate *thingTemplate = object->m_thingTemplate;
		if( thingTemplate && thingTemplate->m_nextOverride )
			thingTemplate = (ThingTemplate *)thingTemplate->m_nextOverride->getFinalOverride();
		lua_pushstring( state, thingTemplate->m_name.str() );
		return 1;
	}
	lua_pushnil( state );
	return 1;
}

AsciiString DescribeObject( const Object *object );

// ?Rva002E5F40ObjectDescribe@@YAHPAUlua_State@@@Z
int Rva002E5F40ObjectDescribe( lua_State *state )
{
	unsigned id = Rva00990030Lookup( state, 1 );
	if( !id && lua_type( state, 1 ) != 1 )
	{
		lua_pushnil( state );
		return 1;
	}
	Object *object = TheGameLogic->bfmeFind1011( id );
	AsciiString result = DescribeObject( object );
	lua_pushstring( state, result.m_data ? (const char *)result.m_data + 8 : g_bfmeEmptyAscii );
	return 1;
}

unsigned Rva00990210Lookup( lua_State *range, int index );

class Rva002E6B70Object : public Object
{
public:
	// The retail call is through ILT RVA 0x0001E33F to body RVA 0x001C1EA0.
	// Its public Object method name is not recovered; the body references the
	// EnragedBehavior module literal, so retain an address-derived ABI view.
	void Rva001E33FSetBool( bool flag );
};

// ?ObjectSetEnragedState@@YAHPAUlua_State@@@Z
int ObjectSetEnragedState( lua_State *state )
{
	if( lua_gettop( state ) < 2 )
		return 0;
	unsigned id = Rva00990030Lookup( state, 1 );
	if( !id && lua_type( state, 1 ) != 1 )
		return 0;
	Rva002E6B70Object *object = (Rva002E6B70Object *)TheGameLogic->bfmeFind1011( id );
	if( !object )
		return 0;
	bool flag = Rva00990210Lookup( state, 2 ) != 0;
	object->Rva001E33FSetBool( flag );
	return 1;
}

class Rva002E6A00Object : public Object
{
public:
	// The retail call is through ILT RVA 0x0001ED6C to body RVA 0x001CF8F0.
	// The public Object method name is not recovered; retain an address-derived
	// ABI view for the ObjectSetChanting binding.
	void Rva001ED6CSetBool( bool flag );
};

// ?ObjectSetChanting@@YAHPAUlua_State@@@Z
int ObjectSetChanting( lua_State *state )
{
	if( lua_gettop( state ) < 2 )
		return 0;
	unsigned id = Rva00990030Lookup( state, 1 );
	if( !id && lua_type( state, 1 ) != 1 )
		return 0;
	Rva002E6A00Object *object = (Rva002E6A00Object *)TheGameLogic->bfmeFind1011( id );
	if( !object )
		return 0;
	bool flag = Rva00990210Lookup( state, 2 ) != 0;
	object->Rva001ED6CSetBool( flag );
	return 1;
}

// ?ObjectSetDelayedDeath@@YAHPAUlua_State@@@Z
int ObjectSetDelayedDeath( lua_State *state )
{
	if( lua_gettop( state ) < 2 )
		return 0;
	unsigned id = Rva00990030Lookup( state, 1 );
	if( !id && lua_type( state, 1 ) != 1 )
		return 0;
	Object *object = TheGameLogic->bfmeFind1011( id );
	if( !object )
		return 0;
	bool delayed = Rva00990210Lookup( state, 2 ) != 0;
	Rva002E9F70Vtbl94 *contain = (Rva002E9F70Vtbl94 *)object->m_at200;
	if( !contain )
		return 0;
	contain->v37call( delayed );
	return 0;
}

typedef unsigned NameKeyType;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
class NameKeyGenerator
{
public:
	NameKeyType nameToKey( const char *name );
};

extern NameKeyGenerator *TheNameKeyGenerator;

struct BfmeDelayedLuaEvent
{
	unsigned char m_data[0x18];
};

struct BfmeDelayedLuaEventList
{
	BfmeDelayedLuaEventList();
	~BfmeDelayedLuaEventList();

	void *m_vtable;
	BfmeDelayedLuaEvent m_events[3];
};

struct BfmeDispatchDelayedLuaEvent
{
	void *m_vtable;
	float m_number;
	unsigned char m_boolean;
	unsigned char m_padding[3];
	unsigned m_objectID;
	AsciiString m_string;
	unsigned m_type;
};

struct LuaDrawableState
{
	unsigned char m_data[0x78];
};

extern LuaDrawableState *g_obj12F060C;

struct BfmeCallJ63
{
	void *invoke( void *event );
};

struct BfmeObjectEventDispatch
{
	// The second argument is an Object pointer here.  Retail's dispatcher
	// consumes its +0x204 module field; the horde sibling supplies the same
	// slot from its member-pointer list.
	void invoke( void *event, void *object, BfmeDelayedLuaEventList *eventList );
};

// The registration at 0x002EC990 pairs ObjectDispatchEvent with the thunk at
// RVA 0x0001A578, which jumps directly to this 320-byte body.  The body uses
// the delayed-event list's established three-record layout: record zero is an
// object-ID value (type 3), and record one is a copied string (type 4).
// ?ObjectDispatchEvent@@YAHPAUlua_State@@@Z
int ObjectDispatchEvent( lua_State *state )
{
	unsigned objectID = Rva00990030Lookup( state, 1 );
	if( !objectID && lua_type( state, 1 ) != 1 )
		return 0;
	Object *object = TheGameLogic->bfmeFind1011( objectID );
	if( !object )
		return 0;

	BfmeDelayedLuaEventList eventList;
	unsigned eventID = Rva00990030Lookup( state, 2 );
	if( !eventID && lua_type( state, 1 ) != 1 )
		return 0;
	const char *eventName = lua_tostring( state, 3 );
	if( !eventName )
		return 0;

	NameKeyType eventKey = TheNameKeyGenerator->nameToKey( eventName );
	void *eventData = reinterpret_cast<BfmeCallJ63 *>(g_obj12F060C)->invoke(
		(void *)eventKey);
	if( eventData )
	{
		const char *text = lua_tostring( state, 4 );
		BfmeDispatchDelayedLuaEvent *events =
			reinterpret_cast<BfmeDispatchDelayedLuaEvent *>( &eventList.m_events[0] );
		events[0].m_objectID = eventID;
		events[0].m_type = 3;
		{
			AsciiString value( text );
			events[1].m_string = value;
			events[1].m_type = 4;
		}
		reinterpret_cast<BfmeObjectEventDispatch *>(g_obj12F060C)->invoke(
			eventData, object, &eventList);
	}

	return 0;
}

extern "C" void lua_pushnumber( lua_State *state, double value );

#pragma intrinsic( _ReadWriteBarrier )
extern "C" void _ReadWriteBarrier( void );

class LuaScriptEngine;
extern LuaScriptEngine *TheLuaScriptEngine;
extern double g_bfmeSubB3;

// ?Rva002E7690LuaValueLookup@@YAHPAUlua_State@@@Z
int Rva002E7690LuaValueLookup( lua_State *state )
{
	void *field78 = *(void **)( (char *)TheLuaScriptEngine + 0x78 );
	if( field78 )
	{
		unsigned *esiBase = *(unsigned **)( (char *)field78 + 0xc );
		if( esiBase )
		{
			if( lua_gettop( state ) > 0 )
			{
				const char *name = lua_tostring( state, 1 );
				int idx = bfmeLookup_001c62b0( (void *)name );
				if( idx != -1 )
				{
					unsigned char bit = ( esiBase[ ( (unsigned)idx >> 5 ) + ( 0x250 / 4 ) ] & ( 1u << ( idx & 0x1f ) ) ) != 0;
					_ReadWriteBarrier();
					if( bit != 0 )
					{
						lua_pushnumber( state, g_bfmeSubB3 );
						return 1;
					}
				}
			}
		}
	}
	lua_pushnil( state );
	return 1;
}
