
#pragma once

// Existing BFME1 enum contract from inputs/reference/shims/sweep/GameLogic/Damage.h.
// Original provider contexts remain intact; this narrow header is for proven consumers.
enum DamageType
{
	DAMAGE_EXPLOSION							= 0,
	DAMAGE_CRUSH									= 1,
	DAMAGE_ARMOR_PIERCING					= 2,
	DAMAGE_SMALL_ARMS							= 3,
	DAMAGE_GATTLING								= 4,
	DAMAGE_RADIATION							= 5,
	DAMAGE_FLAME									= 6,
	DAMAGE_LASER									= 7,
	DAMAGE_SNIPER									= 8,
	DAMAGE_POISON									= 9,
	DAMAGE_HEALING								= 10,
	DAMAGE_UNRESISTABLE						= 11,		// this is for scripting to cause 'armorproof' damage
	DAMAGE_WATER									= 12,
	DAMAGE_DEPLOY									= 13,					// for transports to deploy units and order them to all attack.
	DAMAGE_SURRENDER							= 14,				// if something "dies" to surrender damage, they surrender.... duh!
	DAMAGE_HACK										= 15,
	DAMAGE_KILLPILOT							= 16,				// special snipe attack that kills the pilot and renders a vehicle unmanned.
	DAMAGE_PENALTY								= 17,					// from game penalty (you won't receive radar warnings BTW)
	DAMAGE_FALLING								= 18,
	DAMAGE_MELEE									= 19,						// Blades, clubs...
	DAMAGE_DISARM									= 20,	// "special" damage type used for disarming mines, bombs, etc (NOT for "disarming" an opponent!)
	DAMAGE_HAZARD_CLEANUP					= 21,	// special damage type for cleaning up hazards like radiation or bio-poison.
	DAMAGE_PARTICLE_BEAM					= 22,	// Incinerates virtually everything (insanely powerful orbital beam)
	DAMAGE_TOPPLING								= 23,	// damage from getting toppled.
	DAMAGE_INFANTRY_MISSILE				= 24,
	DAMAGE_AURORA_BOMB						= 25,
	DAMAGE_LAND_MINE							= 26,
	DAMAGE_JET_MISSILES						= 27,
	DAMAGE_STEALTHJET_MISSILES		= 28,
	DAMAGE_MOLOTOV_COCKTAIL				= 29,
	DAMAGE_COMANCHE_VULCAN				= 30,
	DAMAGE_SUBDUAL_MISSILE				= 31,	///< Damage that does not kill you, but produces some special effect based on your Body Module. Seperate HP from normal damage.
	DAMAGE_SUBDUAL_VEHICLE				= 32,
	DAMAGE_SUBDUAL_BUILDING				= 33,
	DAMAGE_SUBDUAL_UNRESISTABLE		= 34,
	DAMAGE_MICROWAVE							= 35, ///< Radiation that only affects infantry
	DAMAGE_KILL_GARRISONED				= 36, ///< Kills Passengers up to the number specified in Damage
	DAMAGE_STATUS									= 37, ///< Damage that gives a status condition, not that does hitpoint damage

	// Please note: There is a string array DamageTypeFlags::s_bitNameList[]

	DAMAGE_NUM_TYPES			// keep this last
};
