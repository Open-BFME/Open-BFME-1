
#pragma once

// Existing BFME1 enum contract from inputs/reference/shims/sweep/GameLogic/Damage.h.
// Original provider contexts remain intact; this narrow header is for proven consumers.
enum DeathType
{
	// note that these DELIBERATELY have (slightly) different names from the damage names,
	// since there isn't necessarily a one-to-one correspondence. e.g., DEATH_BURNED
	// can come from DAMAGE_FLAME but also from DAMAGE_PARTICLE_BEAM.
	DEATH_NORMAL		= 0,
	DEATH_NONE			= 1,					///< this is a "special case" that can't normally cause death
  DEATH_CRUSHED		= 2,
  DEATH_BURNED		= 3,
  DEATH_EXPLODED	= 4,
	DEATH_POISONED	= 5,
	DEATH_TOPPLED		= 6,
	DEATH_FLOODED		= 7,
	DEATH_SUICIDED	= 8,
	DEATH_LASERED		= 9,
	DEATH_DETONATED	= 10,		/**< this is the "death" that occurs when a missile/warhead/etc detonates normally,
														as opposed to being shot down, etc */
	DEATH_SPLATTED	= 11,		/**< the death that results from DAMAGE_FALLING */
	DEATH_POISONED_BETA	= 12,

	// these are the "extra" types for yet-to-be-defined stuff. Don't bother renaming or adding
	// or removing these; they are reserved for modders :-)
	DEATH_EXTRA_2		= 13,
	DEATH_EXTRA_3		= 14,
	DEATH_EXTRA_4		= 15,
	DEATH_EXTRA_5		= 16,
	DEATH_EXTRA_6		= 17,
	DEATH_EXTRA_7		= 18,
	DEATH_EXTRA_8		= 19,
	DEATH_POISONED_GAMMA = 20,

	DEATH_NUM_TYPES			// keep this last
};
