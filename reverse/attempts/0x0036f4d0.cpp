// ?rva0036F4D0@CastleBehavior@@QAEXXZ
// partial score=0.7 date=2026-09-17
// ?rva0036F4D0@CastleBehavior@@QAEXXZ
// Retail 0x0036F4D0, 504 bytes.  The method is a non-virtual CastleBehavior
// helper called by the anonymous update body at 0x00376C70.  The address-derived
// spelling is intentional: the body owner is proven by the CastleBehavior
// destructor layout, but no semantic method name is proven by a caller or slot.
//
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

// The two reads at Player+0x24 are the witnessed player key used by the
// CastleBehavior key set and the map lookup below.
class Player
{
public:
	unsigned char m_pad00[0x24];
	Int m_playerKey;

	Relationship getRelationship(const Team *team) const;
};

class Team
{
public:
	Player *getControllingPlayer() const;
};

// ObjectModule stores its module-data pointer at +0x04.  Object's team and
// position offsets are from the retail GameLogic/Object.h witness.
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

	Object *findObjectByID(Int id);
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

class Eva
{
public:
	Bool setShouldPlay(EvaMessage message, const Coord3D *position);

	UnsignedInt m_at64;
	Int m_at68;
};

class Radar
{
public:
	void createEvent(const Coord3D *position, RadarEventType type,
		float secondsToLive);
};

class Rva0036E3E0KeySet
{
public:
	Bool containsDifferentKey(Int key, Int unused) const;
};

struct Rva002EE330PlayerList
{
	unsigned char m_pad00[0x0c];
	Player *m_localPlayer;
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
	UnsignedInt a[1];
};

typedef _STL::map<Int, Gen_t_000a3c70_p4pod> Rva0036F4D0Map;

// The CastleBehavior destructor proves the complete base/member layout:
// m_object is at +0x08 and its map<int, Gen_t_000a3c70_p4pod> is at +0x108.
// Only the fields read by this body are named here; the intervening members
// remain an explicit layout witness rather than guessed class semantics.
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

extern void j_00033e9c();
extern void j_00038203();


void CastleBehavior::rva0036F4D0()
{
	Team *team = m_object->m_team;
	if (team == 0)
		return;
	Player *controllingPlayer = team->getControllingPlayer();
	if (controllingPlayer == 0)
		return;

	Player *localPlayer;
	if (Rva002EE330ThePlayers == 0)
		localPlayer = 0;
	else
		localPlayer = Rva002EE330ThePlayers->m_localPlayer;
	if (localPlayer == 0)
		return;

	CastleMemberBehaviorModule *module = 0;
	Object *object = TheBfmeGameLogic->findObjectByID(m_ata0);
	if (object != 0)
	{
		static NameKeyType castleMemberBehaviorKey =
			TheNameKeyGenerator->nameToKey("CastleMemberBehavior");
		module = (CastleMemberBehaviorModule *)object->findModule(
			castleMemberBehaviorKey);
	}

	if (controllingPlayer == localPlayer)
	{
		typedef Bool (Rva0036E3E0KeySet::*ContainsDifferentKeyCall)(Int, Int) const;
		union { void *asVoid; ContainsDifferentKeyCall asMember; } containsCast;
		containsCast.asVoid = (void *)j_00038203;
		if (!(((Rva0036E3E0KeySet *)this)->*containsCast.asMember)(controllingPlayer->m_playerKey,
			TheEva->m_at68))
			return;

		EvaMessage event = (EvaMessage)11;
		if (module != 0)
			event = ((CastleMemberBehaviorModuleData *)module->m_moduleData)->m_localEvent;
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
		typedef Bool (Rva0036E3E0KeySet::*ContainsDifferentKeyCall)(Int, Int) const;
		union { void *asVoid; ContainsDifferentKeyCall asMember; } containsCast;
		containsCast.asVoid = (void *)j_00038203;
		if (!(((Rva0036E3E0KeySet *)this)->*containsCast.asMember)(controllingPlayer->m_playerKey,
			TheEva->m_at68))
			return;

		EvaMessage event = (EvaMessage)12;
		if (module != 0)
			event = ((CastleMemberBehaviorModuleData *)module->m_moduleData)->m_allyEvent;
		TheEva->setShouldPlay(event, 0);
		return;
	}
	if (relationship != RELATIONSHIP_ENEMIES)
		return;

	Int playerKey = localPlayer->m_playerKey;
	Rva0036F4D0Map::iterator it = m_map108.find(playerKey);
	if (it == m_map108.end())
		return;

	UnsignedInt expiry = TheEva->m_at64 +
		it->second.a[0];
	if (expiry < TheBfmeGameLogic->m_frame)
		return;

	EvaMessage event = (EvaMessage)10;
	if (module != 0)
		event = ((CastleMemberBehaviorModuleData *)module->m_moduleData)->m_enemyEvent;
	TheEva->setShouldPlay(event, 0);
}
