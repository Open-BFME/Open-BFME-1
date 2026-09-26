// ?rva0036F4D0@CastleBehavior@@QAEXXZ
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#include <map>

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

enum EvaMessage
{
	EVA_INVALID = -1
};

enum RadarEventType
{
	RADAR_EVENT_INVALID = -1
};

enum Relationship
{
	RELATIONSHIP_ENEMIES = 0,
	RELATIONSHIP_NEUTRAL = 1,
	RELATIONSHIP_ALLIES = 2
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Player;
class Team;
class Module;

class Player
{
public:
	unsigned char m_pad00[0x24];
	Int m_playerIndex;

	Int getPlayerIndex() const { return m_playerIndex; }

	Relationship getRelationship(const Team *team) const;
};

class Team
{
public:
	Player *getControllingPlayer() const;
};

// ObjectModule keeps its module-data pointer at +0x04.
class Module
{
public:
	void *m_vtable;
	void *m_moduleData;
};

class CastleMemberBehaviorModule : public Module
{
};

class Object
{
public:
	void *m_vtable;
	unsigned char m_pad04[0x34];
	Coord3D m_position;
	unsigned char m_pad44[0x23c - 0x44];
	Team *m_team;

	Module *findModule(NameKeyType key) const;
};

class GameLogic
{
public:
	Object *findObjectByID(Int id);
	unsigned char m_pad00[0x3c];
	UnsignedInt m_frame;
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

// Eva holds its MiscEvaData block at +0x60; +0x64 and +0x68 are its two frame timeouts.
class Eva
{
public:
	Bool setShouldPlay(EvaMessage message, const Coord3D *position);

	unsigned char m_pad00[0x64];
	UnsignedInt m_at64;
	Int m_at68;
};

class Radar
{
public:
	void createEvent(const Coord3D *position, RadarEventType type,
		float secondsToLive);
};

// Retail 0x0036E3E0 scans this CastleBehavior's +0x108 map through ECX.
class Rva0036E3E0KeySet
{
public:
	Bool containsDifferentKey(Int key, Int unused) const;
};

struct Rva002EE330PlayerList
{
	unsigned char m_pad00[0x0c];
	Player *m_localPlayer;

	Player *getLocalPlayer() { return m_localPlayer; }
};

struct CastleMemberBehaviorModuleData
{
	unsigned char m_pad00[0x18];
	EvaMessage m_localEvent;
	EvaMessage m_allyEvent;
	EvaMessage m_enemyEvent;
};

struct Gen_t_000a3c70_p4pod
{
	int a[1];
};

typedef _STL::map<Int, Gen_t_000a3c70_p4pod> Rva0036F4D0Map;

// The CastleBehavior destructor fixes m_object at +0x08 and the map at +0x108.
class FoundationAIUpdate
{
public:
	virtual ~FoundationAIUpdate() {}

protected:
	void *m_moduleData;
	Object *m_object;
};

class CastleBehavior : public FoundationAIUpdate
{
public:
	void rva0036F4D0();

private:
	unsigned char m_pad0c[0x9c - 0x0c];
	Int m_at9c;
	Int m_ata0;
	unsigned char m_ata4;
	unsigned char m_ata5;
	unsigned char m_pad_a6[2];
	Int m_ata8;
	unsigned char m_atac;
	unsigned char m_pad_ad[3];
	Int m_atb0;
	Int m_atb4;
	unsigned char m_pad_b8[0x108 - 0xb8];
	Rva0036F4D0Map m_map108;
};

extern GameLogic *TheBfmeGameLogic;
extern NameKeyGenerator *TheNameKeyGenerator;
extern Eva *TheEva;
extern Radar *TheRadar;
extern Rva002EE330PlayerList *Rva002EE330ThePlayers;

// Plays the local, allied or enemy Eva message configured on the +0xA0 object's
// CastleMemberBehavior module; the local message also raises a radar event.
void CastleBehavior::rva0036F4D0()
{
	Object *self = m_object;
	Team *team = self->m_team;
	if (team == 0)
		return;
	Player *controllingPlayer = team->getControllingPlayer();
	if (controllingPlayer == 0)
		return;

	Player *localPlayer = Rva002EE330ThePlayers ?
		Rva002EE330ThePlayers->getLocalPlayer() : 0;
	if (localPlayer == 0)
		return;

	Object *object = TheBfmeGameLogic->findObjectByID(m_ata0);
	CastleMemberBehaviorModule *module;
	if (object != 0)
	{
		static NameKeyType castleMemberBehaviorKey =
			TheNameKeyGenerator->nameToKey("CastleMemberBehavior");
		module = (CastleMemberBehaviorModule *)object->findModule(
			castleMemberBehaviorKey);
	}
	else
		module = 0;

	if (controllingPlayer == localPlayer)
	{
		if (!((const Rva0036E3E0KeySet *)this)->containsDifferentKey(
			controllingPlayer->getPlayerIndex(), TheEva->m_at68))
			return;

		EvaMessage event = module != 0 ?
			((CastleMemberBehaviorModuleData *)module->m_moduleData)->m_localEvent :
			(EvaMessage)11;
		if (TheEva->setShouldPlay(event, 0))
		{
			if (object == 0)
				return;
			TheRadar->createEvent(&object->m_position,
				(RadarEventType)10, 4.0f);
		}
		return;
	}

	Relationship relationship = localPlayer->getRelationship(team);
	if (relationship == RELATIONSHIP_ALLIES)
	{
		if (!((const Rva0036E3E0KeySet *)this)->containsDifferentKey(
			controllingPlayer->getPlayerIndex(), TheEva->m_at68))
			return;

		EvaMessage event = module != 0 ?
			((CastleMemberBehaviorModuleData *)module->m_moduleData)->m_allyEvent :
			(EvaMessage)12;
		TheEva->setShouldPlay(event, 0);
		return;
	}
	if (relationship != RELATIONSHIP_ENEMIES)
		return;

	Int playerKey = localPlayer->getPlayerIndex();
	Rva0036F4D0Map::iterator it = m_map108.find(playerKey);
	if (it == m_map108.end())
		return;

	UnsignedInt expiry = TheEva->m_at64 + it->second.a[0];
	if (expiry < TheBfmeGameLogic->m_frame)
		return;

	EvaMessage event = module != 0 ?
		((CastleMemberBehaviorModuleData *)module->m_moduleData)->m_enemyEvent :
		(EvaMessage)10;
	TheEva->setShouldPlay(event, 0);
}
