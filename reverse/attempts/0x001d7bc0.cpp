// ?create@AttackNugget@@UBEPAVObject@@PBV2@PBUCoord3D@@1MI@Z
// partial score=0.9 date=2026-09-10
// cl: /DNDEBUG /MD /EHsc
// stlport
// Retail AttackNugget::create, 0x001D7BC0, 334 bytes.
//
// This TU keeps the BFME-only member offsets local.  The source class in
// ObjectCreationList.cpp uses the Zero Hour RadiusDecalTemplate layout, while
// retail places the following fields at +0x34, +0x38 and +0x3c.  The Object
// view likewise names the BFME AI pointer at +0x204 and the AI command
// subobject at +0x20.  All calls below use the existing named retail methods;
// no address-shaped fallback is used.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

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

class AIUpdatePrefix
{
public:
	unsigned char m_prefix[0x20];
};

class AIUpdateInterface : public AIUpdatePrefix,
	public AICommandInterface
{
};

typedef Int WeaponSlotType;

class OCLUpdate;

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
		const Coord3D *secondary, Real angle,
		UnsignedInt lifetimeFrames = 0) const;

private:
	RadiusDecalTemplate m_deliveryDecalTemplate;
	Real m_deliveryDecalRadius;
	Int m_numberOfShots;
	WeaponSlotType m_weaponSlot;
};

// ?create@AttackNugget@@UBEPAVObject@@PBV2@PBUCoord3D@@1MI@Z
Object *AttackNugget::create(const Object *primaryObj, const Coord3D *primary,
	const Coord3D *secondary, Real angle, UnsignedInt lifetimeFrames) const
{
	if (!primaryObj || !primary || !secondary)
		return 0;

	Object *primaryObject = const_cast<Object *>(primaryObj);
	AIUpdateInterface *ai = primaryObject->getAIUpdateInterface();
	if (ai)
	{
		primaryObject->setWeaponLock(m_weaponSlot, 1);
		ai->aiAttackPosition(secondary, m_numberOfShots, CMD_FROM_AI);
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
	return 0;
}
