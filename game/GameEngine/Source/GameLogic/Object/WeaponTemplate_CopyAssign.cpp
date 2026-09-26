// cl: /DNDEBUG /MD /Igame/Libraries/Source/WWVegas/WWLib
// Open-BFME5: WeaponTemplate::operator=, retail 0x001E80A0 size 1185.
// newOverride at 0x001E9AF0 calls this after the default ctor (ILT 0x0001AF3C).
// Layout is the BFME 0x53C record: AsciiString name at +8, nameKey at +0x0C,
// scatter vector at +0x34 (parseScatterTarget), 12-byte-element vector at
// +0x40, preferred target bone at +0x80, nine AudioEventRTS assigns from +0xB4,
// copied-override flag at +0x528. Focused TU; member types recover the
// 14 typed calls. Do not fold this into Weapon.cpp (ZH offsets differ).
// Property names follow retail FieldParse table 0x00C9FE18 (targets/game/reverse/field_names.csv).
// Reload/shot timing bounds follow the matched getters in sibling TUs.
// Scalar slots retain raw integer storage to preserve retail copy codegen;
// INI names identify properties, not recovered C++ types.

#include "string_base.h"

#include "ascii_string.h"

class WtVecCoord2D
{
public:
	WtVecCoord2D &operator=(const WtVecCoord2D &that);

private:
	void *m_start;
	void *m_finish;
	void *m_end;
};

class WtVecPod12
{
public:
	WtVecPod12 &operator=(const WtVecPod12 &that);

private:
	void *m_start;
	void *m_finish;
	void *m_end;
};

class AudioEventRTS
{
public:
	AudioEventRTS &assign(const AudioEventRTS &that);

private:
	unsigned char m_bytes[0x70];
};

class WtTail
{
public:
	WtTail &operator=(const WtTail &that);

private:
	void *m_data;
};

class MemoryPoolObject
{
public:
	virtual ~MemoryPoolObject() {}
};

class WeaponTemplate : public MemoryPoolObject
{
public:
	WeaponTemplate &operator=(const WeaponTemplate &that);

private:
	WeaponTemplate *m_nextTemplate;
	AsciiString m_name;
	int m_nameKey;
	int m_fxTrigger;
	int m_attackRange;
	int m_minimumAttackRange;
	int m_requestAssistRange;
	int m_aimDelta;
	int m_aimDirection;
	int m_scatterRadius;
	int m_scatterTargetScalar;
	unsigned char m_scatterIndependently;
	unsigned char m_disableScatterForTargetsOnWall;
	unsigned char m_pad032[2];
	WtVecCoord2D m_scatterTargets;
	WtVecPod12 m_linearTargets;
	int m_damageType;
	int m_deathType;
	int m_damageFXType;
	int m_weaponSpeed;
	int m_minWeaponSpeed;
	int m_maxWeaponSpeed;
	unsigned char m_isScaleWeaponSpeed;
	unsigned char m_canBeDodged;
	unsigned char m_pad066[2];
	int m_idleAfterFiringDelay;
	int m_holdAfterFiringDelay;
	unsigned char m_canFireWhileMoving;
	unsigned char m_canFireWhileCharging;
	unsigned char m_canSwoop;
	unsigned char m_pad073;
	int m_weaponRecoil;
	int m_minTargetPitch;
	int m_maxTargetPitch;
	AsciiString m_preferredTargetBone;
	int m_d084;
	int m_d088;
	int m_d08c;
	int m_d090;
	int m_d094;
	int m_d098;
	int m_d09c;
	int m_d0a0;
	int m_d0a4;
	int m_d0a8;
	int m_d0ac;
	int m_d0b0;
	AudioEventRTS m_fireSound;
	int m_fireSoundLoopTime;
	AudioEventRTS m_audio128[8];
	int m_d4a8;
	int m_clipSize;
	int m_minClipReloadTime;
	int m_maxClipReloadTime;
	int m_minDelayBetweenShots;
	int m_maxDelayBetweenShots;
	int m_continuousFireOneShotsNeeded;
	int m_continuousFireTwoShotsNeeded;
	int m_continuousFireCoastFrames;
	int m_autoReloadWhenIdleFrames;
	int m_shotsPerBarrel;
	int m_antiMask;
	int m_affectsMask;
	unsigned char m_b4dc;
	unsigned char m_pad4dd[3];
	int m_collideMask;
	unsigned char m_damageDealtAtSelfPosition;
	unsigned char m_pad4e5[3];
	int m_projectileFilterInContainer;
	unsigned char m_projectileSelf;
	unsigned char m_meleeWeapon;
	unsigned char m_chaseWeapon;
	unsigned char m_pad4ef;
	int m_reloadType;
	int m_prefireType;
	unsigned char m_leechRangeWeapon;
	unsigned char m_hitStoredTarget;
	unsigned char m_capableOfFollowingWaypoint;
	unsigned char m_isShowsAmmoPips;
	unsigned char m_allowAttackGarrisonedBldgs;
	unsigned char m_playFXWhenStealthed;
	unsigned char m_pad4fe[2];
	int m_preAttackDelay;
	int m_preAttackRandomAmount;
	unsigned char m_passengerProportionalAttack;
	// MaxAttackPassengers parses 32 bits here, but retail copies only this byte.
	unsigned char m_b509;
	unsigned char m_pad50a[2];
	int m_firingDuration;
	int m_continueAttackRange;
	int m_infantryInaccuracyDist;
	int m_suspendFXDelay;
	unsigned char m_ignoreLinearFirstTarget;
	unsigned char m_forceDisplayPercentReady;
	unsigned char m_isAimingWeapon;
	unsigned char m_b51f;
	int m_hitPercentage;
	int m_hitPassengerPercentage;
	unsigned char m_copiedOverride;
	unsigned char m_finishAttackOnceStarted;
	unsigned char m_pad52a[2];
	int m_restrictedHeightRange;
	unsigned char m_cannotTargetCastleVictims;
	unsigned char m_requireFollowThru;
	unsigned char m_shareTimers;
	unsigned char m_noVictimNeeded;
	unsigned char m_rotatingTurret;
	unsigned char m_shouldPlayUnderAttackEvaEvent;
	unsigned char m_pad536[2];
	WtTail m_tail;
};

// ??4WeaponTemplate@@QAEAAV0@ABV0@@Z
WeaponTemplate &WeaponTemplate::operator=(const WeaponTemplate &that)
{
	m_nextTemplate = that.m_nextTemplate;
	m_name = that.m_name;
	m_nameKey = that.m_nameKey;
	m_fxTrigger = that.m_fxTrigger;
	m_attackRange = that.m_attackRange;
	m_minimumAttackRange = that.m_minimumAttackRange;
	m_requestAssistRange = that.m_requestAssistRange;
	m_aimDelta = that.m_aimDelta;
	m_aimDirection = that.m_aimDirection;
	m_scatterRadius = that.m_scatterRadius;
	m_scatterTargetScalar = that.m_scatterTargetScalar;
	m_scatterIndependently = that.m_scatterIndependently;
	m_disableScatterForTargetsOnWall = that.m_disableScatterForTargetsOnWall;
	m_scatterTargets = that.m_scatterTargets;
	m_linearTargets = that.m_linearTargets;
	m_damageType = that.m_damageType;
	m_deathType = that.m_deathType;
	m_damageFXType = that.m_damageFXType;
	m_weaponSpeed = that.m_weaponSpeed;
	m_minWeaponSpeed = that.m_minWeaponSpeed;
	m_maxWeaponSpeed = that.m_maxWeaponSpeed;
	m_isScaleWeaponSpeed = that.m_isScaleWeaponSpeed;
	m_canBeDodged = that.m_canBeDodged;
	m_idleAfterFiringDelay = that.m_idleAfterFiringDelay;
	m_holdAfterFiringDelay = that.m_holdAfterFiringDelay;
	m_canFireWhileMoving = that.m_canFireWhileMoving;
	m_canFireWhileCharging = that.m_canFireWhileCharging;
	m_canSwoop = that.m_canSwoop;
	m_weaponRecoil = that.m_weaponRecoil;
	m_minTargetPitch = that.m_minTargetPitch;
	m_maxTargetPitch = that.m_maxTargetPitch;
	m_preferredTargetBone = that.m_preferredTargetBone;
	m_d084 = that.m_d084;
	m_d088 = that.m_d088;
	m_d08c = that.m_d08c;
	m_d090 = that.m_d090;
	m_d094 = that.m_d094;
	m_d098 = that.m_d098;
	m_d09c = that.m_d09c;
	m_d0a0 = that.m_d0a0;
	m_d0a4 = that.m_d0a4;
	m_d0a8 = that.m_d0a8;
	m_d0ac = that.m_d0ac;
	m_d0b0 = that.m_d0b0;
	m_fireSound.assign(that.m_fireSound);
	m_fireSoundLoopTime = that.m_fireSoundLoopTime;
	m_audio128[0].assign(that.m_audio128[0]);
	m_audio128[1].assign(that.m_audio128[1]);
	m_audio128[2].assign(that.m_audio128[2]);
	m_audio128[3].assign(that.m_audio128[3]);
	m_audio128[4].assign(that.m_audio128[4]);
	m_audio128[5].assign(that.m_audio128[5]);
	m_audio128[6].assign(that.m_audio128[6]);
	m_audio128[7].assign(that.m_audio128[7]);
	m_d4a8 = that.m_d4a8;
	m_clipSize = that.m_clipSize;
	m_minClipReloadTime = that.m_minClipReloadTime;
	m_maxClipReloadTime = that.m_maxClipReloadTime;
	m_minDelayBetweenShots = that.m_minDelayBetweenShots;
	m_maxDelayBetweenShots = that.m_maxDelayBetweenShots;
	m_continuousFireOneShotsNeeded = that.m_continuousFireOneShotsNeeded;
	m_continuousFireTwoShotsNeeded = that.m_continuousFireTwoShotsNeeded;
	m_continuousFireCoastFrames = that.m_continuousFireCoastFrames;
	m_autoReloadWhenIdleFrames = that.m_autoReloadWhenIdleFrames;
	m_shotsPerBarrel = that.m_shotsPerBarrel;
	m_antiMask = that.m_antiMask;
	m_affectsMask = that.m_affectsMask;
	m_b4dc = that.m_b4dc;
	m_collideMask = that.m_collideMask;
	m_damageDealtAtSelfPosition = that.m_damageDealtAtSelfPosition;
	m_projectileFilterInContainer = that.m_projectileFilterInContainer;
	m_projectileSelf = that.m_projectileSelf;
	m_meleeWeapon = that.m_meleeWeapon;
	m_chaseWeapon = that.m_chaseWeapon;
	m_reloadType = that.m_reloadType;
	m_prefireType = that.m_prefireType;
	m_leechRangeWeapon = that.m_leechRangeWeapon;
	m_hitStoredTarget = that.m_hitStoredTarget;
	m_capableOfFollowingWaypoint = that.m_capableOfFollowingWaypoint;
	m_isShowsAmmoPips = that.m_isShowsAmmoPips;
	m_allowAttackGarrisonedBldgs = that.m_allowAttackGarrisonedBldgs;
	m_playFXWhenStealthed = that.m_playFXWhenStealthed;
	m_preAttackDelay = that.m_preAttackDelay;
	m_preAttackRandomAmount = that.m_preAttackRandomAmount;
	m_passengerProportionalAttack = that.m_passengerProportionalAttack;
	m_b509 = that.m_b509;
	m_firingDuration = that.m_firingDuration;
	m_continueAttackRange = that.m_continueAttackRange;
	m_infantryInaccuracyDist = that.m_infantryInaccuracyDist;
	m_suspendFXDelay = that.m_suspendFXDelay;
	m_ignoreLinearFirstTarget = that.m_ignoreLinearFirstTarget;
	m_forceDisplayPercentReady = that.m_forceDisplayPercentReady;
	m_isAimingWeapon = that.m_isAimingWeapon;
	m_b51f = that.m_b51f;
	m_hitPercentage = that.m_hitPercentage;
	m_hitPassengerPercentage = that.m_hitPassengerPercentage;
	m_copiedOverride = that.m_copiedOverride;
	m_finishAttackOnceStarted = that.m_finishAttackOnceStarted;
	m_restrictedHeightRange = that.m_restrictedHeightRange;
	m_cannotTargetCastleVictims = that.m_cannotTargetCastleVictims;
	m_requireFollowThru = that.m_requireFollowThru;
	m_shareTimers = that.m_shareTimers;
	m_noVictimNeeded = that.m_noVictimNeeded;
	m_rotatingTurret = that.m_rotatingTurret;
	m_shouldPlayUnderAttackEvaEvent = that.m_shouldPlayUnderAttackEvaEvent;
	m_tail = that.m_tail;
	return *this;
}
