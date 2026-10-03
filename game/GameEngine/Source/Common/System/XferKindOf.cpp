// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringinline

#include "StringInline.h"

typedef bool Bool;
typedef int Int;

enum KindOfType
{
	KINDOF_INVALID = -1
};

// Retail's table of the 181 KindOf bit names at 0x012AA068, in KindOfType
// order, closed by a null entry (scanIndexList walks to it; 0x2D8 bytes, zeros
// follow). The name is address-derived: no EA spelling is proven for it.
const char *g_bfmeRva012AA068[0xB5 + 1] =
{
	"OBSTACLE",
	"SELECTABLE",
	"IMMOBILE",
	"CAN_ATTACK",
	"STICK_TO_TERRAIN_SLOPE",
	"CAN_CAST_REFLECTIONS",
	"SHRUBBERY",
	"STRUCTURE",
	"INFANTRY",
	"CAVALRY",
	"MONSTER",
	"MACHINE",
	"AIRCRAFT",
	"HUGE_VEHICLE",
	"DOZER",
	"SWARM_DOZER",
	"HARVESTER",
	"COMMANDCENTER",
	"CASTLE_CENTER",
	"SALVAGER",
	"WEAPON_SALVAGER",
	"TRANSPORT",
	"BRIDGE",
	"LANDMARK_BRIDGE",
	"BRIDGE_TOWER",
	"PROJECTILE",
	"PRELOAD",
	"NO_GARRISON",
	"CASTLE_KEEP",
	"WAVE_EFFECT",
	"NO_COLLIDE",
	"REPAIR_PAD",
	"HEAL_PAD",
	"STEALTH_GARRISON",
	"SUPPLY_GATHERING_CENTER",
	"AIRFIELD",
	"DRAWABLE_ONLY",
	"MP_COUNT_FOR_VICTORY",
	"REBUILD_HOLE",
	"SCORE",
	"SCORE_CREATE",
	"SCORE_DESTROY",
	"NO_HEAL_ICON",
	"CAN_RAPPEL",
	"PARACHUTABLE",
	"CAN_BE_REPULSED",
	"MOB_NEXUS",
	"IGNORED_IN_GUI",
	"CRATE",
	"CAPTURABLE",
	"CLEARED_BY_BUILD",
	"SMALL_MISSILE",
	"ALWAYS_VISIBLE",
	"UNATTACKABLE",
	"MINE",
	"CLEANUP_HAZARD",
	"PORTABLE_STRUCTURE",
	"ALWAYS_SELECTABLE",
	"ATTACK_NEEDS_LINE_OF_SIGHT",
	"WALK_ON_TOP_OF_WALL",
	"DEFENSIVE_WALL",
	"FS_POWER",
	"FS_FACTORY",
	"FS_BASE_DEFENSE",
	"FS_TECHNOLOGY",
	"AIRCRAFT_PATH_AROUND",
	"LOW_OVERLAPPABLE",
	"FORCEATTACKABLE",
	"AUTO_RALLYPOINT",
	"OATHBREAKER",
	"POWERED",
	"PRODUCED_AT_HELIPAD",
	"DRONE",
	"CAN_SEE_THROUGH_STRUCTURE",
	"BALLISTIC_MISSILE",
	"CLICK_THROUGH",
	"SUPPLY_SOURCE_ON_PREVIEW",
	"PARACHUTE",
	"GARRISONABLE_UNTIL_DESTROYED",
	"BOAT",
	"IMMUNE_TO_CAPTURE",
	"HULK",
	"SHOW_PORTRAIT_WHEN_CONTROLLED",
	"SPAWNS_ARE_THE_WEAPONS",
	"CANNOT_BUILD_NEAR_SUPPLIES",
	"SUPPLY_SOURCE",
	"REVEAL_TO_ALL",
	"DISGUISER",
	"INERT",
	"HERO",
	"IGNORES_SELECT_ALL",
	"DONT_AUTO_CRUSH_INFANTRY",
	"SIEGE_TOWER",
	"TREE",
	"SHRUB",
	"CLUB",
	"ROCK",
	"THROWN_OBJECT",
	"GRAB_AND_KILL",
	"OPTIMIZED_PROP",
	"ENVIRONMENT",
	"DEFLECT_BY_SPECIAL_POWER",
	"WORKING_PASSENGER",
	"BASE_FOUNDATION",
	"NEED_BASE_FOUNDATION",
	"REACT_WHEN_SELECTED",
	"GIMLI",
	"ORC",
	"HORDE",
	"COMBO_HORDE",
	"NONOCCLUDING",
	"NO_FREEWILL_ENTER",
	"CAN_USE_SIEGE_TOWER",
	"CAN_RIDE_SIEGE_LADDER",
	"TACTICAL_MARKER",
	"PATH_THROUGH_EACH_OTHER",
	"NOTIFY_OF_PREATTACK",
	"GARRISON",
	"MELEE_HORDE",
	"BASE_SITE",
	"INERT_SHROUD_REVEALER",
	"OCL_BIT",
	"SPELL_BOOK",
	"DEPRECATED",
	"PATH_THROUGH_INFANTRY",
	"NO_FORMATION_MOVEMENT",
	"NO_BASE_CAPTURE",
	"ARMY_SUMMARY",
	"HOBBIT",
	"NOT_AUTOACQUIRABLE",
	"URUK",
	"CHUNK_VENDOR",
	"ARCHER",
	"MOVE_ONLY",
	"FS_CASH_PRODUCER",
	"ROCK_VENDOR",
	"BLOCKING_GATE",
	"CAN_RIDE_BATTERING_RAM",
	"SIEGE_LADDER",
	"MINE_TRIGGER",
	"BUFF",
	"GRAB_AND_DROP",
	"PORTER",
	"SCARY",
	"CRITTER_EMITTER",
	"SALT_LICK",
	"CAN_ATTACK_WALLS",
	"IGNORE_FOR_VICTORY",
	"DO_NOT_CLASSIFY",
	"WALL_UPGRADE",
	"ARMY_OF_DEAD",
	"TAINT",
	"BASE_DEFENSE_FOUNDATION",
	"NOT_SELLABLE",
	"WEBBED",
	"____OBSOLETE____",
	"BUILD_FOR_FREE",
	"IGNORE_FOR_EVA_SPEECH_POSITION",
	"MADE_OF_WOOD",
	"MADE_OF_METAL",
	"MADE_OF_STONE",
	"MADE_OF_DIRT",
	"FACE_AWAY_FROM_CASTLE_KEEP",
	"BANNER",
	"I_WANT_TO_EAT_YOU",
	"INDUSTRY_AFFECTED",
	"GANDALF",
	"ARAGORN",
	"HAS_HEALTH_BAR",
	"BIG_MONSTER",
	"DEPLOYED_MINE",
	"CANNOT_RETALIATE",
	"CREEP",
	"TAINTEFFECT",
	"TROLL",
	"VITAL_FOR_BASE_SURVIVAL",
	"DO_NOT_PICK_ME_WHEN_BUILDING",
	"SUMMONED",
	"HIDE_IF_FOGGED",
	"ALWAYS_SHOW_HOUSE_COLOR",
	"MOVE_FOR_NOONE",
	0
};

class KindOfMaskType
{
public:
	static const char *getNameFromSingleBit(Int bit)
	{
		if (bit < 0 || bit >= sizeof(g_bfmeRva012AA068)/sizeof(g_bfmeRva012AA068[0]) - 1)
			return 0;
		return g_bfmeRva012AA068[bit];
	}
};

extern int bfmeLookup_000d1020(void *name); // ILT 0x0004AFFC

class Xfer;

class Rva0010C980XferView
{
public:
	virtual ~Rva0010C980XferView(void);
	virtual Bool slot01(void);                         // +04
	virtual Bool isSaving(void) const;                 // +08
	virtual Bool slot03(void);                         // +0C
	virtual Bool isLightCRC(void) const;               // +10
	virtual void slot05(void);                         // +14
	virtual void slot06(void);                         // +18
	virtual void slot07(void);                         // +1C
	virtual void slot08(void);                         // +20
	virtual void slot09(void);                         // +24
	virtual void slot10(void);                         // +28
	virtual void slot11(void);                         // +2C
	virtual void slot12(void);                         // +30
	virtual void slot13(void);                         // +34
	virtual void slot14(void);                         // +38
	virtual void slot15(void);                         // +3C
	virtual void slot16(void);                         // +40
	virtual void slot17(void);                         // +44
	virtual void slot18(void);                         // +48
	virtual void slot19(void);                         // +4C
	virtual void slot20(void);                         // +50
	virtual void slot21(void);                         // +54
	virtual void slot22(void);                         // +58
	virtual void slot23(void);                         // +5C
	virtual void slot24(void);                         // +60
	virtual void slot25(void);                         // +64
	virtual Rva0010C980XferView &xferAsciiString(AsciiString &value); // +68
	virtual void slot27(void);                         // +6C
	virtual void slot28(void);                         // +70
	virtual void slot29(void);                         // +74
	virtual void slot30(void);                         // +78
	virtual void slot31(void);                         // +7C
	virtual void slot32(void);                         // +80
	virtual void slot33(void);                         // +84
	virtual void slot34(void);                         // +88
	virtual void slot35(void);                         // +8C
	virtual Rva0010C980XferView &xferEnum(const char *name, void *data, unsigned int size); // +90
};

// Retail 0x0010C980 transfers a KindOfType as an enum during LightCRC and as
// an AsciiString during save and load.
Xfer *__cdecl Rva0010C980XferKindOf(Xfer *xfer, KindOfType *kindOfData)
{
	Rva0010C980XferView *receiver = reinterpret_cast<Rva0010C980XferView *>(xfer);
	if (receiver->isLightCRC())
	{
		receiver->xferEnum("KindOfType", kindOfData, 4);
		return xfer;
	}
	if (receiver->isSaving())
	{
		AsciiString kindOfName = KindOfMaskType::getNameFromSingleBit(*kindOfData);
		receiver->xferAsciiString(kindOfName);
	}
	else
	{
		AsciiString kindOfName;
		receiver->xferAsciiString(kindOfName);
		Int bit = bfmeLookup_000d1020((void *)kindOfName.str());
		if (bit != -1)
			*kindOfData = (KindOfType)bit;
	}
	return xfer;
}
