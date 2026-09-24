// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
// Lua script binding ObjectPlaySound (cdecl int f(lua_State*)), retail
// 0x002E6850 (335 B).  Identity: the Lua registration routine at 0x002EC990
// pushes ILT 0x0003C3AD (jmp 0x002E6850) at +0x308 and passes the string
// "ObjectPlaySound" (VA 0x010CFCE8) to lua_setglobal at +0x31C.
// With at least two arguments and the audio manager present, argument 1
// resolves to an object (the table lookup at 0x00990030 or a boolean tag)
// and argument 2 names an audio event played on that object (m_id at +0x74,
// layout_witness); a handle of 5 or more is pushed back as a number,
// otherwise nil.  The (float) conversion is retail's: its unsigned fixup
// reads the dword 2^32 constant, not the qword a direct double conversion
// emits.

struct lua_State;
extern "C" int lua_gettop( lua_State *state );
extern "C" int lua_type( lua_State *state, int index );
extern "C" const char *lua_tostring( lua_State *state, int index );
extern "C" void lua_pushnil( lua_State *state );
extern "C" void lua_pushnumber( lua_State *state, double value );

unsigned Rva00990030Lookup( lua_State *range, int index );

#include "ascii_string.h"

enum ObjectID
{
	INVALID_ID = 0,
	FORCE_OBJECTID_TO_LONG_SIZE = 0x7ffffff
};

class Object
{
public:
	ObjectID getID() const { return m_id; }

	char m_unreconstructed00[ 0x74 ];
	ObjectID m_id;
};

class GameLogic
{
public:
	Object *findObjectByID( int id );
};

class AudioEventRTS
{
public:
	AudioEventRTS( const AsciiString &eventName, ObjectID ownerID );
	~AudioEventRTS();

private:
	unsigned char m_eventData[ 0x70 ];
};

class AudioManager
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16();
	virtual unsigned int addAudioEvent( const AudioEventRTS *event );
};

extern GameLogic *TheGameLogic;
extern AudioManager *TheAudio;

// ?ObjectPlaySound@@YAHPAUlua_State@@@Z
int ObjectPlaySound( lua_State *state )
{
	if( lua_gettop( state ) < 2 || !TheAudio )
		return 0;
	unsigned id = Rva00990030Lookup( state, 1 );
	if( !id && lua_type( state, 1 ) != 1 )
		return 0;
	Object *object = TheGameLogic->findObjectByID( id );
	if( !object )
		return 0;
	AudioEventRTS event( lua_tostring( state, 2 ), object->getID() );
	unsigned int handle = TheAudio->addAudioEvent( &event );
	if( handle >= 5 )
		lua_pushnumber( state, (float)handle );
	else
		lua_pushnil( state );
	return 1;
}
