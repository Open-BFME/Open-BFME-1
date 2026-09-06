// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

typedef int Int;
typedef bool Bool;

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	NAMEKEY_MAX = 1 << 23,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

enum EvaMessage
{
	EVA_INVALID = -1,
	EVA_VALUE_7 = 7
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Player;
class Module;

// The 0x00370730 body is slot 2 of CastleMemberBehavior's secondary
// interface at +0x10.  This view is deliberately non-virtual: it is only a
// declaration of the slot body and must not emit a partial interface table.
class Rva00370730CastleMemberInterface
{
public:
	void run( Int unused1, Int unused2, Int mode );
};

class Object
{
public:
	Player *getControllingPlayer() const;
	Module *findModule( NameKeyType key ) const;
};

class GameLogic
{
public:
	Object *findObjectByID( Int id );
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey( const char *name );
};

class Eva
{
public:
	Bool setShouldPlay( EvaMessage message, const Coord3D *position );
};

// Retail 0x00108520 is the bounded radar-event helper called through ILT
// 0x0001b6d0.  Its first explicit argument is the event type and its second
// is the position; the body proves the event bound and the Coord3D use.
class Radar
{
public:
	Bool rva00108520( Int eventType, Coord3D *position );
};

typedef Int (__cdecl *Rva0036ff70Callback)( void *, void * );

// Retail 0x0036ff70 iterates module-owned records and invokes the callback;
// its two explicit arguments are callback then callback context and it
// returns the callback-chain result.  This declaration emits no table.
class Rva0036ff70Module
{
public:
	Int query( Rva0036ff70Callback callback, void *context );
};

struct Rva005655C0PlayerList
{
	unsigned char m_padding00[ 0x0c ];
	Player *m_localPlayer0c;
};

struct Rva00370730ModuleData
{
	unsigned char m_padding00[ 0x29 ];
	unsigned char m_isCastleBehavior;
};

extern Rva005655C0PlayerList *g_rva005655C0PlayerList;
extern GameLogic *TheBfmeGameLogic;
extern NameKeyGenerator *TheNameKeyGenerator;
extern Eva *TheEva;
extern Radar *TheRadar;

// Retail callback36CFD0 returns a full EAX integer and accepts two cdecl
// arguments (object and context); the query tests EAX, not AL.
extern "C" Int __cdecl bfmeRva0036CFD0Callback(void *, void *);

// ?run@Rva00370730CastleMemberInterface@@QAEXHHH@Z
void Rva00370730CastleMemberInterface::run( Int, Int, Int mode )
{
	if( mode == 3 )
	{
		unsigned char *self = (unsigned char *)this;
		Rva00370730ModuleData *moduleData =
			*(Rva00370730ModuleData **)( self - 0x0c );
		if( moduleData->m_isCastleBehavior )
		{
			Player *localPlayer =
				g_rva005655C0PlayerList->m_localPlayer0c;
			if( localPlayer ==
				(*(Object * volatile *)( self - 0x08 ))->getControllingPlayer() )
			{
				Object *pendingObject = TheBfmeGameLogic->findObjectByID(
					*(Int *)( self + 0x08 ) );
				if( pendingObject != 0 )
				{
					static volatile NameKeyType castleBehaviorKey =
						TheNameKeyGenerator->nameToKey(
							"CastleBehavior" );
					Module *module = pendingObject->findModule( castleBehaviorKey );
					if( module != 0 )
					{
						Rva0036ff70Callback callback =
							bfmeRva0036CFD0Callback;
						if( ( (Rva0036ff70Module *)module )->query(
							callback, 0 ) == 1 )
						{
							if( TheEva->setShouldPlay( EVA_VALUE_7,
								(Coord3D *)( (unsigned char *)*(Object **)
									( self - 0x08 ) + 0x38 ) ) )
							{
								register Coord3D *radarPosition =
									(Coord3D *)( (unsigned char *)*(Object **)
										( self - 0x08 ) + 0x38 );
								(*(Radar * volatile *)&TheRadar)->rva00108520( 10,
									radarPosition );
							}
						}
					}
				}
			}
		}
		*(unsigned char *)( self + 0x15 ) = 1;
	}
	else if( mode < 2 )
		*(unsigned char *)( (unsigned char *)this + 0x15 ) = 0;
}
