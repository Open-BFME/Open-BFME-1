// cl: /DNDEBUG /MD /EHsc

// RunOffMapBehavior method at 0x00205440 (354 B, ret then int3 padding).
// Identity: retail's ??_7RunOffMapBehavior@@6BRunOffMapBehaviorIface2@@@
// (VA 0x010A5E0C) holds its ILT 0x00038D25 in slot 0, so this is the
// RunOffMapBehavior override reached through the +0x10 interface (object at
// this-8, module data at this-0xC).  Its meaning is unproven, so the name
// keeps the address.  With an AI and module data present it sends the unit to
// the waypoint named by the module data (+0x14), or else 500 units along its
// facing on the ground; when no path exists it reports its last damage source
// and kills itself (damage 8), otherwise it issues one of two AI commands
// (module flag +0x18), sets status bit 0x31 and raises model-condition bit 241.

typedef bool Bool;
typedef float Real;

#include "../../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

// Zero Hour's Coord3D::scale; the canonical Coord3D carries no methods.
inline void scaleCoord3D(Coord3D &c, Real scale)
{
	c.x *= scale;
	c.y *= scale;
	c.z *= scale;
}

class Waypoint
{
public:
	const Coord3D *getLocation() const { return &m_location; }

private:
	char m_unmodelled_00[0x0C];
	Coord3D m_location;
};

class TerrainLogic
{
public:
	virtual void v00(); virtual void v01(); virtual void v02();
	virtual void v03(); virtual void v04(); virtual void v05();
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal);
	virtual void v07(); virtual void v08(); virtual void v09();
	virtual void v10(); virtual void v11(); virtual void v12();
	virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18();
	virtual void v19(); virtual void v20(); virtual void v21();
	virtual void v22(); virtual void v23(); virtual void v24();
	virtual void v25(); virtual void v26(); virtual void v27();
	virtual void v28(); virtual void v29(); virtual void v30();
	virtual Waypoint *getWaypointByName(AsciiString name);
};

extern TerrainLogic *TheTerrainLogic;

enum CommandSourceType { CMD_FROM_AI = 2 };
enum DamageType { DAMAGE_8 = 8 };
enum DeathType { DEATH_NORMAL = 0 };

class AICommandInterface
{
public:
	void aiBfmeCommand38(const Coord3D *pos, CommandSourceType cmdSource);
	void aiBfmeCommand41(const Coord3D *pos, CommandSourceType cmdSource);
};

class AIUpdateInterface
{
	char m_unmodelled_00[0x20];

public:
	AICommandInterface m_commands;
};

struct DamageInfo
{
	char m_unmodelled_00[8];
	int m_sourceID;
};

class BodyModuleInterface
{
public:
	virtual void v00(); virtual void v01(); virtual void v02();
	virtual void v03(); virtual void v04(); virtual void v05();
	virtual void v06(); virtual void v07(); virtual void v08();
	virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14();
	virtual const DamageInfo *getLastDamageInfo();
};

struct ModelConditionFlags
{
	// Returns the masked word, not a bool: retail keeps the mask in a register
	// for the test and the set that follows.
	unsigned int test(int i) const { return m_bits[i >> 5] & (1u << (i & 31)); }
	void set(int i) { m_bits[i >> 5] |= (1u << (i & 31)); }
	unsigned int m_bits[10];
};

class Thing
{
public:
	const Coord3D *getUnitDirectionVector2D() const;
};

class Object : public Thing
{
public:
	void setStatusBit(int bit, Bool set);
	void notifyModelConditionChanged();
	void kill(DamageType damageType, DeathType deathType);

	__forceinline void bfmeSetModelConditionState(int bit)
	{
		if (!m_modelConditionFlags.test(bit))
		{
			m_modelConditionFlags.set(bit);
			notifyModelConditionChanged();
		}
	}

	const Coord3D *getPosition() const { return &m_position; }
	BodyModuleInterface *getBodyModule() const { return m_body; }
	AIUpdateInterface *getAI() const { return m_ai; }

private:
	char m_unmodelled_00[0x38];
	Coord3D m_position;
	char m_unmodelled_44[0x110 - 0x44];
	ModelConditionFlags m_modelConditionFlags;
	char m_unmodelled_138[0x200 - 0x138];
	BodyModuleInterface *m_body;
	AIUpdateInterface *m_ai;
};

// The call at this body targets ILT0004A327, whose typed Zero Hour
// provider is not retail's body. Bind the existing address-owned thunk using
// the witnessed ECX receiver, four stack words, AL result and ret16 contract.
// All callers here pass zero in the fourth slot; its semantic type is unknown.
class Pathfinder {};
extern void j_0004a327();
typedef Bool (Pathfinder::*Rva0004A327Call)(
 Object *, const Coord3D *, const Coord3D *, unsigned int);
typedef char Rva0004A327PointerSize[
 sizeof(Rva0004A327Call) == sizeof(void (*)()) ? 1 : -1];

class AI
{
	char m_unmodelled_00[0x0C];

public:
	Pathfinder *pathfinder() { return m_pathfinder; }

private:
	Pathfinder *m_pathfinder;
};

extern AI *TheAI;

class GameLogic
{
public:
	Object *findObjectByID(int id);
};

extern GameLogic *TheGameLogic;

class BFMEReportDamageSource
{
public:
	void report(Object *victim, int setting);
};

// report is reached through ILT 0x0001B94B (body 0x001C9490, still a gen dump); the
// ledger defines that ILT as ?j_0001b94b@@YAXXZ, so the call names it through a
// member-pointer view.
extern void j_0001b94b(void);
static __forceinline void reportDamageSource(BFMEReportDamageSource *source, Object *victim, int setting)
{
	union { void (*raw)(void); void (BFMEReportDamageSource::*member)(Object *, int); } call;
	call.raw = j_0001b94b;
	(source->*call.member)(victim, setting);
}

struct RunOffMapBehaviorModuleData
{
	char m_unmodelled_00[0x14];
	AsciiString m_waypointName;
	unsigned char m_mode18;
};

class ObjectModule
{
public:
	virtual void objectModuleAnchor() = 0;

protected:
	const RunOffMapBehaviorModuleData *getModuleData() const { return m_moduleData; }
	Object *getObject() const { return m_object; }

private:
	const RunOffMapBehaviorModuleData *m_moduleData;
	Object *m_object;
};

class RunOffMapBehaviorIface1
{
public:
	virtual void runOffMapIface1Anchor() = 0;
};

class RunOffMapBehaviorIface2
{
public:
	virtual void rva00205440() = 0;
};

class RunOffMapBehavior : public ObjectModule,
	public RunOffMapBehaviorIface1,
	public RunOffMapBehaviorIface2
{
public:
	virtual void rva00205440();
};

// ?rva00205440@RunOffMapBehavior@@UAEXXZ
void RunOffMapBehavior::rva00205440()
{
	Object *obj = getObject();
	AIUpdateInterface *ai = obj->getAI();
	if (ai == 0)
		return;
	const RunOffMapBehaviorModuleData *data = getModuleData();
	if (data == 0)
		return;

	Coord3D destination;
	Waypoint *waypoint = TheTerrainLogic->getWaypointByName(data->m_waypointName);
	if (waypoint)
	{
		destination = *waypoint->getLocation();
	}
	else
	{
		const Coord3D *dir = obj->getUnitDirectionVector2D();
		Coord3D offset;
		offset.x = dir->x;
		offset.y = dir->y;
		offset.z = 0.0f;
		scaleCoord3D(offset, 500.0f);
		destination.x = obj->getPosition()->x + offset.x;
		destination.y = obj->getPosition()->y + offset.y;
		destination.z = TheTerrainLogic->getGroundHeight(destination.x, destination.y, 0);
	}

	union Rva0004A327Binding
 {
  void (*address)();
  Rva0004A327Call member;
 } pathCheck;
 pathCheck.address = &j_0004a327;
 if (!(TheAI->pathfinder()->*pathCheck.member)(obj, obj->getPosition(), &destination, 0))
	{
		int sourceID = obj->getBodyModule()->getLastDamageInfo() ? obj->getBodyModule()->getLastDamageInfo()->m_sourceID : 0;
		Object *source = TheGameLogic->findObjectByID(sourceID);
		if (source)
			reportDamageSource((BFMEReportDamageSource *)source, obj, 1);
		obj->kill(DAMAGE_8, DEATH_NORMAL);
		return;
	}

	if (data->m_mode18 == 1)
		ai->m_commands.aiBfmeCommand41(&destination, CMD_FROM_AI);
	else
		ai->m_commands.aiBfmeCommand38(&destination, CMD_FROM_AI);
	obj->setStatusBit(0x31, true);
	obj->bfmeSetModelConditionState(241);
}
