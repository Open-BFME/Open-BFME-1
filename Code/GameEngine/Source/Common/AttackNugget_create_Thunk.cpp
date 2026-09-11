// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: clean reconstruction of the BFME AttackNugget::create body.
//
// Identity is established by the RadiusDecalUpdate call, the AttackNugget
// vtable thunk at 0x0000BD25, and the queue caller recorded for this body at
// 0x003992F7.  BFME's RadiusDecalTemplate is 0x30 bytes, so the member offsets
// in this TU intentionally remain local rather than changing the shared ZH
// ObjectCreationList layout.
//
// The decorated ledger spelling retained for the retail body includes the
// legacy lifetimeFrames type, but the retail epilogue is ret 0x10 and the
// entry consumes four stack arguments.  The clean C++ method below therefore
// uses the actual BFME four-argument override ABI; functions.csv records its
// object-symbol explicitly when it verifies this canonical retail row.

typedef int Int;
typedef float Real;
typedef bool Bool;

#pragma warning(disable : 4716)

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

#define NAMEKEY(name) (TheNameKeyGenerator->nameToKey(name))

class Object;
class Team;
class Waypoint;
class PolygonTrigger;
class CommandButton;
class Path;
class OCLUpdate;

enum AICommandType
{
	AICMD_ATTACK_POSITION = 0x0e
};

enum CommandSourceType
{
	CMD_FROM_AI = 2
};

class PathVector
{
public:
	~PathVector();

	unsigned char m_data[12];
};

struct AICommandParms
{
	AICommandType m_cmd;
	CommandSourceType m_cmdSource;
	Coord3D m_pos;
	Object *m_obj;
	Object *m_otherObj;
	const Team *m_team;
	PathVector m_coords;
	const Waypoint *m_waypoint;
	const PolygonTrigger *m_polygon;
	Int m_intValue;
	unsigned char m_damage[0x5c];
	const CommandButton *m_commandButton;
	Path *m_path;

	AICommandParms(AICommandType cmd, CommandSourceType cmdSource);
};

class AICommandInterface
{
public:
	virtual void aiDoCommand(const AICommandParms *parms);

	__forceinline void aiAttackPosition(const Coord3D *pos, Int maxShotsToFire,
		CommandSourceType cmdSource)
	{
		AICommandParms parms(AICMD_ATTACK_POSITION, cmdSource);
		parms.m_pos = *pos;
		parms.m_intValue = maxShotsToFire;
		aiDoCommand(&parms);
	}
};

// The BFME AI command vtable is the secondary object at AI +0x20.
class AIUpdateInterface
{
	unsigned char m_prefix[0x20];
public:
	AICommandInterface m_command;
};

class Object
{
public:
	void setWeaponLock(Int weaponSlot, Int lockType);
	OCLUpdate *findUpdateModule(NameKeyType key);
	AIUpdateInterface *getAIUpdateInterface() const
	{
		return m_ai;
	}

	unsigned char m_prefix[0x204];
	AIUpdateInterface *m_ai;
};

class RadiusDecalTemplate
{
public:
	unsigned char m_storage[0x30];
};

class RadiusDecalUpdate
{
public:
	void createRadiusDecal(const RadiusDecalTemplate &tmpl, Real radius,
		const Coord3D &pos);

	unsigned char m_prefix[0x30];
	Bool m_killWhenNoLongerAttacking;
};

class AttackNugget
{
public:
	virtual Object *create(const Object *primaryObj, const Coord3D *primary,
		const Coord3D *secondary, Real angle) const;

private:
	RadiusDecalTemplate m_deliveryDecalTemplate;
	Real m_deliveryDecalRadius;
	Int m_numberOfShots;
	Int m_weaponSlot;
};

// ?create@AttackNugget@@UBEPAVObject@@PBV2@PBUCoord3D@@1M@Z
Object *AttackNugget::create(const Object *primaryObj, const Coord3D *primary,
	const Coord3D *secondary, Real angle) const
{
	if (primaryObj && primary && secondary)
	{
		Object *primaryObject = const_cast<Object *>(primaryObj);
		AIUpdateInterface *ai = primaryObject->getAIUpdateInterface();
		if (ai)
		{
			primaryObject->setWeaponLock(m_weaponSlot, 1);
			ai->m_command.aiAttackPosition(secondary, m_numberOfShots, CMD_FROM_AI);
		}

		static NameKeyType key_RadiusDecalUpdate = NAMEKEY("RadiusDecalUpdate");
		RadiusDecalUpdate *rd = (RadiusDecalUpdate *)primaryObject->findUpdateModule(
			key_RadiusDecalUpdate);
		if (rd)
		{
			rd->createRadiusDecal(m_deliveryDecalTemplate, m_deliveryDecalRadius,
				*secondary);
			rd->m_killWhenNoLongerAttacking = true;
		}
	}
}
