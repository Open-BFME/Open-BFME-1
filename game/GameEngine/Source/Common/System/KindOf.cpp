// cl: /DNDEBUG /MD /EHsc
// stlport
//
// Data-only TU: it owns KINDOFMASK_NONE, the one empty KindOf mask the linked
// build references and nothing in game/ defines.
//
// Upstream: Zero Hour GameEngine/Source/Common/System/KindOf.cpp:164
//     KindOfMaskType KINDOFMASK_NONE;	// inits to all zeroes
// BFME widened KindOfMaskType past Zero Hour's 126-bit KINDOF_COUNT (the
// reference shim inputs/reference/shims/bfmekindof/Common/KindOf.h still
// enumerates 126), so the mask is six dwords, not one.
// Size is proven from retail bytes, not from the width pin:
// game/GameEngine/Source/Common/KindOfMaskCountThunk.cpp pins the width only,
// and game/GameEngine/Source/GameLogic/System/CrateSystem.cpp proves it falls
// in (160,192]. The extent is fixed by the TransportContain module-data
// constructor at RVA 0x0021FC80 (matched row ??0TransportContainModuleData@@QAE@XZ),
// which loads six dwords, 0x012ED8B8 through 0x012ED8CC inclusive, and passes
// them by value to the filter setter at 0x0039FF30 -- 24 bytes, so
// BitFlags<192>, not a guess.
// The type here is spelled `const BitFlags<192>` because that is what the
// referencing objects ask for. Of the 69 game/ TUs that name KINDOFMASK_NONE,
// 50 carry an extern declaration; the spellings that mangle to
// ?KINDOFMASK_NONE@@3V?$BitFlags@$0MA@@@B, the one
// targets/game/reverse/dir32_addresses.csv records at 0x012ED8B8, are:
//     extern const KindOfMaskType KINDOFMASK_NONE;  24 TUs whose TU-local
//         typedef BitFlags<192> KindOfMaskType; resolves to BitFlags<192>
//     extern const BitFlags<192> KINDOFMASK_NONE;     9 TUs
//     extern const KindOfMask KINDOFMASK_NONE;        4 TUs whose TU-local
//         typedef BitFlags<192> KindOfMask; likewise resolves to BitFlags<192>
// ($0MA is MSVC's encoding of the non-type argument 192: hex digits shifted
// into A..P, so $0HE is 116, $0HO is 126 and $0N is 13.)
// The TU-local BitFlags below is the upstream Common/BitFlags.h layout
// (std::bitset<NUMBITS> rounds to whole 32-bit words). It is declared locally
// because ObjectStatusBits.h's BitFlags has a user-provided constructor, which
// would give this global a dynamic initializer retail does not have.
// Still to be respelled, deliberately out of scope for this data-only TU:
//   - 5 TUs that declare `extern const KindOfMaskType` but typedef it
//     BitFlags<116>, which mangles to ?$BitFlags@$0HE@@ and will not link:
//     OpenContainGetPassengerBoneName.cpp, ThingTemplateInitForLTA.cpp,
//     ScoreKeeperCounters.cpp (and 2 more spelling BitFlags<116> directly).
//   - 7 TUs declaring a TU-local non-template class (KindOfMask126,
//     KindOfBlock, VptrZeroBlock24, ...), which mangles to a different name.
//   - 4 TUs that take the symbol from the shared shim
//     inputs/reference/shims/bfmekindof/Common/KindOf.h, which declares it
//     non-const BitFlags<126>; a shim header edit is out of scope here.

template<int NUMBITS>
class BitFlags
{
public:
	unsigned int m_bits[(NUMBITS + 31) / 32];
private:
	static const char *s_bitNameList[];
};

typedef BitFlags<192> KindOfMaskType;

// upstream Common/KindOf.h declares it before the definition; MSVC 7.1 only
// mangles the global when it sees that declaration first.
extern const KindOfMaskType KINDOFMASK_NONE;

// ?KINDOFMASK_NONE@@3V?$BitFlags@$0MA@@@B -- retail VA 0x012ED8B8, 24 zero bytes
const KindOfMaskType KINDOFMASK_NONE;
// KindOf name lookup table at retail VA 0x012AA068.
const char *BitFlags<181>::s_bitNameList[] =
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
