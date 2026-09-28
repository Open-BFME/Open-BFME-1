// ??0WeaponTemplate@@QAE@XZ
// partial score=0.9935691318 date=2026-09-28
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib

// Partial recovery: retail RVA 0x001E74B0, 933 bytes.
// Identity is WeaponTemplate::WeaponTemplate, NOT the ledger lift's Weapon().
// Matched newWeaponTemplate and newOverride call ILT 0x0004456C -> this body;
// vtable VA0x010A1418 is also installed by WeaponTemplate::~WeaponTemplate.
// Layout reused from the matched WeaponTemplateDestructor.cpp (size 0x53C).
// ZH Weapon.cpp supplies the constructor skeleton; BFME adds the other fields.
// All 15 unwind states independently checked with tools/eh_info.py.
// Shaping barriers preserve retail store order and the four-element loop.
// Remaining six masked-byte differences: at +0x390 retail returns this in EAX
// before loading the previous exception chain and popping EDI; ours does it after.
// No relocation-aware acceptance has passed; the AudioEventRTS int-constructor
// pin currently disagrees with the body row and must be checked during landing.
// The existing destructor's m_maxWeaponSpeed at +0x60 is retained; name_oracle
// reports the ZH-derived m_shockWaveRadius there, requiring review before landing.

// stlport
#include <vector>
#include <bitset>
#include "ascii_string.h"

extern "C" void _WriteBarrier();
#pragma intrinsic(_WriteBarrier)
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)

struct WtCoord2D
{
	int m_x;
	int m_y;
};

struct WtPod12
{
	int m_x;
	int m_y;
	int m_z;
};

class AttributeHandleStandIn
{
public:
	AttributeHandleStandIn();
	~AttributeHandleStandIn();

private:
	unsigned int m_handle;
};

extern const AsciiString Rva01336E50EmptyString;
class AudioEventRTS
{
public:
	AudioEventRTS(const AsciiString &name = Rva01336E50EmptyString, int id = 0);
	~AudioEventRTS();

private:
	unsigned char m_bytes[0x70];
};

#pragma comment(linker, "/alternatename:??1AudioEventRTS@@QAE@XZ=?j_00026f35@@YAXXZ")

class Rva001E3F90NuggetBase
{
public:
	virtual ~Rva001E3F90NuggetBase();
};

class Rva001E3F90Nugget : public Rva001E3F90NuggetBase
{
public:
	unsigned char m_pad04[0x50];
	volatile bool m_field54;
};

struct Rva001E3F90Node
{
	Rva001E3F90Node *m_next;
	Rva001E3F90Node *m_previous;
	Rva001E3F90Nugget *volatile m_value;
};

class WtNuggetList
{
public:
	Rva001E3F90Node *m_node;
	WtNuggetList() : m_node(0) {
		Rva001E3F90Node *node = (Rva001E3F90Node*)_STL::__new_alloc::allocate(12);
		node->m_next = node; node->m_previous = node; m_node = node;
	}

	__forceinline void clear()
	{
		Rva001E3F90Node *node = m_node->m_next;
		while (node != m_node)
		{
			Rva001E3F90Node *current = node;
			node = node->m_next;
			_STL::__node_alloc<true, 0>::deallocate(current, 0xc);
		}
		m_node->m_next = m_node;
		m_node->m_previous = m_node;
	}

	__forceinline ~WtNuggetList()
	{
		clear();
		if (m_node)
			_STL::__node_alloc<true, 0>::deallocate(m_node, 0xc);
	}
};

class KindOfMask { public: KindOfMask() {} private: std::bitset<181> m_bits; };
extern const KindOfMask KINDOFMASK_NONE;
class EmotionTrackerUpdateName { public: void setPolicies(KindOfMask, KindOfMask); };

class WeaponTemplate
{
public:
	WeaponTemplate();
	void deleteInstance() { delete this; }

protected:
	virtual ~WeaponTemplate();

private:
	WeaponTemplate *m_nextTemplate;
	AsciiString m_name;
	int m_nameKey;
	int m_fxTrigger;
	float m_attackRange;
	float m_minimumAttackRange;
	float m_requestAssistRange;
	float m_aimDelta;
	float m_aimDirection;
	float m_scatterRadius;
	float m_scatterTargetScalar;
	bool m_scatterIndependently;
	bool m_disableScatterForTargetsOnWall;
	unsigned char m_pad032[2];
	std::vector<WtCoord2D> m_scatterTargets;
	std::vector<WtPod12> m_linearTargets;
	int m_damageType;
	int m_deathType;
	int m_damageFXType;
	float m_weaponSpeed;
	float m_minWeaponSpeed;
	float m_maxWeaponSpeed;
	bool m_isScaleWeaponSpeed;
	bool m_canBeDodged;
	unsigned char m_pad066[2];
	int m_idleAfterFiringDelay;
	int m_holdAfterFiringDelay;
	bool m_canFireWhileMoving;
	bool m_canFireWhileCharging;
	bool m_canSwoop;
	bool m_pad073;
	float m_weaponRecoil;
	float m_minTargetPitch;
	float m_maxTargetPitch;
	AsciiString m_preferredTargetBone;
	void *m_projectileExhausts[4];
	void *m_fireFXs[4];
	void *m_projectileDetonateFXs[4];
	AudioEventRTS m_fireSound;
	int m_fireSoundLoopTime;
	AudioEventRTS m_audio1280;
	AudioEventRTS m_audio1281;
	AudioEventRTS m_audio1282;
	AudioEventRTS m_audio1283;
	AudioEventRTS m_audio1284;
	AudioEventRTS m_audio1285;
	AudioEventRTS m_audio1286;
	AudioEventRTS m_audio1287;
	void *m_extraBonus;
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
	bool m_b4dc;
	unsigned char m_pad4dd[3];
	int m_collideMask;
	bool m_damageDealtAtSelfPosition;
	unsigned char m_pad4e5[3];
	AttributeHandleStandIn m_attributeHandle;
	bool m_projectileSelf;
	bool m_meleeWeapon;
	bool m_chaseWeapon;
	bool m_pad4ef;
	int m_reloadType;
	int m_prefireType;
	bool m_leechRangeWeapon;
	bool m_hitStoredTarget;
	bool m_capableOfFollowingWaypoint;
	bool m_isShowsAmmoPips;
	bool m_allowAttackGarrisonedBldgs;
	bool m_playFXWhenStealthed;
	unsigned char m_pad4fe[2];
	int m_preAttackDelay;
	int m_preAttackRandomAmount;
	bool m_passengerProportionalAttack;
	bool m_b509;
	unsigned char m_pad50a[2];
	int m_firingDuration;
	int m_continueAttackRange;
	int m_infantryInaccuracyDist;
	int m_suspendFXDelay;
	bool m_ignoreLinearFirstTarget;
	bool m_forceDisplayPercentReady;
	bool m_isAimingWeapon;
	bool m_b51f;
	float m_hitPercentage;
	int m_hitPassengerPercentage;
	bool m_copiedOverride;
	bool m_finishAttackOnceStarted;
	unsigned char m_pad52a[2];
	int m_restrictedHeightRange;
	bool m_cannotTargetCastleVictims;
	bool m_requireFollowThru;
	bool m_shareTimers;
	bool m_noVictimNeeded;
	bool m_rotatingTurret;
	bool m_shouldPlayUnderAttackEvaEvent;
	unsigned char m_pad536[2];
	WtNuggetList m_nuggets;
};


WeaponTemplate::WeaponTemplate() : m_nextTemplate(0)
{
	m_name.StringBase<char>::set("NoNameWeapon", 12);
	m_weaponSpeed = 999999.0f;
	m_minWeaponSpeed = 999999.0f;
	m_maxWeaponSpeed = 999999.0f;
	_ReadWriteBarrier();
	m_nameKey = 0;
	m_attackRange = 0;
	m_minimumAttackRange = 0;
	m_requestAssistRange = 0;
	m_aimDelta = 0;
	m_aimDirection = 0;
	m_scatterRadius = 0;
	m_scatterTargetScalar = 0;
	m_scatterIndependently = 0;
	m_disableScatterForTargetsOnWall = 0;
	m_fxTrigger = 0;
	m_damageType = 22;
	m_deathType = 0;
	m_damageFXType = 15;
	m_isScaleWeaponSpeed = 0;
	m_canBeDodged = 0;
	m_idleAfterFiringDelay = -1;
	m_holdAfterFiringDelay = 0;
	m_weaponRecoil = 0;
	m_minTargetPitch = -3.14159265358979323846f;
	m_maxTargetPitch = 3.14159265358979323846f;
	m_canFireWhileMoving = 0;
	m_canFireWhileCharging = 0;
	m_canSwoop = 0;
	for (int i = 0; i < 4; ++i) {
		m_projectileExhausts[i] = 0;
		m_fireFXs[i] = 0;
		m_projectileDetonateFXs[i] = 0;
		_ReadWriteBarrier();
	}
	m_damageDealtAtSelfPosition = 0;
	((EmotionTrackerUpdateName*)&m_attributeHandle)->setPolicies(KINDOFMASK_NONE, KINDOFMASK_NONE);
	m_continuousFireOneShotsNeeded = 0x7fffffff;
	m_continuousFireTwoShotsNeeded = 0x7fffffff;
	m_shotsPerBarrel = 1;
	m_finishAttackOnceStarted = 1;
	m_shouldPlayUnderAttackEvaEvent = 1;
	m_projectileSelf = 0;
	m_meleeWeapon = 0;
	m_chaseWeapon = 0;
	m_affectsMask = 14;
	_ReadWriteBarrier();
	m_b4dc = 0;
	m_collideMask = 8;
	_ReadWriteBarrier();
	m_reloadType = 0;
	m_prefireType = 0;
	m_clipSize = 0;
	m_continuousFireCoastFrames = 0;
	m_autoReloadWhenIdleFrames = 0;
	m_minClipReloadTime = 0;
	m_maxClipReloadTime = 0;
	m_minDelayBetweenShots = 0;
	m_maxDelayBetweenShots = 0;
	m_fireSoundLoopTime = 0;
	m_extraBonus = 0;
	m_antiMask = 2;
	_ReadWriteBarrier();
	m_leechRangeWeapon = 0;
	m_hitStoredTarget = 0;
	m_capableOfFollowingWaypoint = 0;
	m_isShowsAmmoPips = 0;
	m_allowAttackGarrisonedBldgs = 0;
	m_playFXWhenStealthed = 0;
	m_passengerProportionalAttack = 0;
	m_b509 = 0;
	m_preAttackDelay = 0;
	m_preAttackRandomAmount = 0;
	m_firingDuration = 0;
	m_continueAttackRange = 0;
	m_infantryInaccuracyDist = 0;
	m_suspendFXDelay = 0;
	m_ignoreLinearFirstTarget = 0;
	m_forceDisplayPercentReady = 0;
	m_isAimingWeapon = 0;
	m_b51f = 0;
	m_hitPercentage = 1.0f;
	_ReadWriteBarrier();
	m_hitPassengerPercentage = 0;
	m_copiedOverride = 0;
	m_restrictedHeightRange = 0;
	m_cannotTargetCastleVictims = 0;
	m_requireFollowThru = 0;
	m_shareTimers = 0;
	m_noVictimNeeded = 0;
	m_rotatingTurret = 0;
    _ReadWriteBarrier();
}


