// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// Open-BFME5: clean C++ reconstruction of the WeaponTemplate default
// constructor at retail RVA 0x001E74B0 (933 bytes, 15 EH unwind states).
//
// The ledger lift this replaces was named ??0Weapon@@QAE@XZ; the body proves
// it is WeaponTemplate::WeaponTemplate. Evidence:
//   targets/game/reverse/identity_evidence/001e74b0-weapontemplate-ctor.md
//   - vtable 0x010A1418 installed here and removed by the matched
//     ??1WeaponTemplate@@MAE@XZ at 0x001E7940 (WeaponTemplateDestructor.cpp)
//   - the two call sites, both matched, are WeaponStore::newWeaponTemplate and
//     WeaponStore::newOverride, typed to return WeaponTemplate *
//   - nine AudioEventRTS members and a 0x53C extent match WeaponTemplate
// Layout is the one established by the matched WeaponTemplateDestructor.cpp
// (0x53C bytes); the member order follows the retail store order.
//
// All scalar members are declared volatile. This is what makes the body
// byte-exact: with plain members the compiler hoists the trailing bool stores
// past the epilogue and emits the implicit `mov eax,esi` return after
// `pop edi` instead of before the exception-chain restore. Volatile stores
// pin the order, and the resulting shape is the same one the matched
// SpecialAbilityUpdateModuleData constructor (0x002A5AA0) uses. No
// _ReadWriteBarrier() is needed or wanted: a trailing barrier restores the
// wrong epilogue order even with volatile tail stores.
//
// CALLEE IDENTITY: tools/callees.py 0x001E74B0 933 reports 5 distinct call
// targets and 0 unnamed, and the gate resolves every REL32 site with no new
// pin. The nugget-list allocation must call the out-of-line free-list
// allocator _STL::__node_alloc<true,0>::allocate (retail 0x0082E540), not
// stlport's inline __new_alloc::allocate, which would fold to operator new at
// 0x00881F30.
//
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h
// upstream source:  inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Weapon.cpp (WeaponTemplate::WeaponTemplate)

// stlport
#include <vector>
#include <bitset>
#include "ascii_string.h"

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
		Rva001E3F90Node *node = (Rva001E3F90Node*)_STL::__node_alloc<true, 0>::allocate(12);
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
	// Every scalar member is volatile so the compiler keeps the retail store
	// order; see the header comment.
	WeaponTemplate * volatile m_nextTemplate;
	AsciiString m_name;
	volatile int m_nameKey;
	volatile int m_fxTrigger;
	volatile float m_attackRange;
	volatile float m_minimumAttackRange;
	volatile float m_requestAssistRange;
	volatile float m_aimDelta;
	volatile float m_aimDirection;
	volatile float m_scatterRadius;
	volatile float m_scatterTargetScalar;
	volatile bool m_scatterIndependently;
	volatile bool m_disableScatterForTargetsOnWall;
	unsigned char m_pad032[2];
	std::vector<WtCoord2D> m_scatterTargets;
	std::vector<WtPod12> m_linearTargets;
	volatile int m_damageType;
	volatile int m_deathType;
	volatile int m_damageFXType;
	volatile float m_weaponSpeed;
	volatile float m_minWeaponSpeed;
	volatile float m_maxWeaponSpeed;
	volatile bool m_isScaleWeaponSpeed;
	volatile bool m_canBeDodged;
	unsigned char m_pad066[2];
	volatile int m_idleAfterFiringDelay;
	volatile int m_holdAfterFiringDelay;
	volatile bool m_canFireWhileMoving;
	volatile bool m_canFireWhileCharging;
	volatile bool m_canSwoop;
	bool m_pad073;
	volatile float m_weaponRecoil;
	volatile float m_minTargetPitch;
	volatile float m_maxTargetPitch;
	AsciiString m_preferredTargetBone;
	void * volatile m_projectileExhausts[4];
	void * volatile m_fireFXs[4];
	void * volatile m_projectileDetonateFXs[4];
	AudioEventRTS m_fireSound;
	volatile int m_fireSoundLoopTime;
	AudioEventRTS m_audio1280;
	AudioEventRTS m_audio1281;
	AudioEventRTS m_audio1282;
	AudioEventRTS m_audio1283;
	AudioEventRTS m_audio1284;
	AudioEventRTS m_audio1285;
	AudioEventRTS m_audio1286;
	AudioEventRTS m_audio1287;
	void * volatile m_extraBonus;
	volatile int m_clipSize;
	volatile int m_minClipReloadTime;
	volatile int m_maxClipReloadTime;
	volatile int m_minDelayBetweenShots;
	volatile int m_maxDelayBetweenShots;
	volatile int m_continuousFireOneShotsNeeded;
	volatile int m_continuousFireTwoShotsNeeded;
	volatile int m_continuousFireCoastFrames;
	volatile int m_autoReloadWhenIdleFrames;
	volatile int m_shotsPerBarrel;
	volatile int m_antiMask;
	volatile int m_affectsMask;
	volatile bool m_b4dc;
	unsigned char m_pad4dd[3];
	volatile int m_collideMask;
	volatile bool m_damageDealtAtSelfPosition;
	unsigned char m_pad4e5[3];
	AttributeHandleStandIn m_attributeHandle;
	volatile bool m_projectileSelf;
	volatile bool m_meleeWeapon;
	volatile bool m_chaseWeapon;
	volatile bool m_pad4ef;
	volatile int m_reloadType;
	volatile int m_prefireType;
	volatile bool m_leechRangeWeapon;
	volatile bool m_hitStoredTarget;
	volatile bool m_capableOfFollowingWaypoint;
	volatile bool m_isShowsAmmoPips;
	volatile bool m_allowAttackGarrisonedBldgs;
	volatile bool m_playFXWhenStealthed;
	unsigned char m_pad4fe[2];
	volatile int m_preAttackDelay;
	volatile int m_preAttackRandomAmount;
	volatile bool m_passengerProportionalAttack;
	volatile bool m_b509;
	unsigned char m_pad50a[2];
	volatile int m_firingDuration;
	volatile int m_continueAttackRange;
	volatile int m_infantryInaccuracyDist;
	volatile int m_suspendFXDelay;
	volatile bool m_ignoreLinearFirstTarget;
	volatile bool m_forceDisplayPercentReady;
	volatile bool m_isAimingWeapon;
	volatile bool m_b51f;
	volatile float m_hitPercentage;
	volatile int m_hitPassengerPercentage;
	volatile bool m_copiedOverride;
	volatile bool m_finishAttackOnceStarted;
	unsigned char m_pad52a[2];
	volatile int m_restrictedHeightRange;
	volatile bool m_cannotTargetCastleVictims;
	volatile bool m_requireFollowThru;
	volatile bool m_shareTimers;
	volatile bool m_noVictimNeeded;
	volatile bool m_rotatingTurret;
	volatile bool m_shouldPlayUnderAttackEvaEvent;
	unsigned char m_pad536[2];
	WtNuggetList m_nuggets;
};

WeaponTemplate::WeaponTemplate() : m_nextTemplate(0)
{
	m_name.StringBase<char>::set("NoNameWeapon", 12);
	m_weaponSpeed = 999999.0f;
	m_minWeaponSpeed = 999999.0f;
	m_maxWeaponSpeed = 999999.0f;
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
	m_b4dc = 0;
	m_collideMask = 8;
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
	m_hitPassengerPercentage = 0;
	m_copiedOverride = 0;
	m_restrictedHeightRange = 0;
	m_cannotTargetCastleVictims = 0;
	m_requireFollowThru = 0;
	m_shareTimers = 0;
	m_noVictimNeeded = 0;
	m_rotatingTurret = 0;
}
