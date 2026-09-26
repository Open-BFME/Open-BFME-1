// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib

#include "ascii_string.h"

namespace _STL
{
template <bool threads, int instance>
class __node_alloc
{
public:
	static void _M_deallocate(void *node, unsigned int bytes);
};
}

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

class WtVecCoord2D
{
public:
	~WtVecCoord2D()
	{
		if (m_start)
		{
			unsigned int bytes = (unsigned int)((m_end - m_start) * sizeof(WtCoord2D));
			if (bytes > 0x80)
				operator delete(m_start);
			else
				_STL::__node_alloc<true, 0>::_M_deallocate(m_start, bytes);
		}
	}

private:
	WtCoord2D *m_start;
	WtCoord2D *m_finish;
	WtCoord2D *m_end;
};

class WtVecPod12
{
public:
	~WtVecPod12()
	{
		if (m_start)
		{
			unsigned int bytes = (unsigned int)((m_end - m_start) * sizeof(WtPod12));
			if (bytes > 0x80)
				operator delete(m_start);
			else
				_STL::__node_alloc<true, 0>::_M_deallocate(m_start, bytes);
		}
	}

private:
	WtPod12 *m_start;
	WtPod12 *m_finish;
	WtPod12 *m_end;
};

class AttributeHandleStandIn
{
public:
	~AttributeHandleStandIn();

private:
	unsigned int m_handle;
};

class AudioEventRTS
{
public:
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
	volatile unsigned char m_field54;
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

	__forceinline void clear()
	{
		Rva001E3F90Node *node = m_node->m_next;
		while (node != m_node)
		{
			Rva001E3F90Node *current = node;
			node = node->m_next;
			_STL::__node_alloc<true, 0>::_M_deallocate(current, 0xc);
		}
		m_node->m_next = m_node;
		m_node->m_previous = m_node;
	}

	__forceinline ~WtNuggetList()
	{
		clear();
		if (m_node)
			_STL::__node_alloc<true, 0>::_M_deallocate(m_node, 0xc);
	}
};

class WeaponTemplate
{
public:
	void deleteInstance() { delete this; }

protected:
	virtual ~WeaponTemplate();

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
	unsigned char m_b4dc;
	unsigned char m_pad4dd[3];
	int m_collideMask;
	unsigned char m_damageDealtAtSelfPosition;
	unsigned char m_pad4e5[3];
	AttributeHandleStandIn m_attributeHandle;
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
	WtNuggetList m_nuggets;
};

// ??1WeaponTemplate@@MAE@XZ
WeaponTemplate::~WeaponTemplate()
{
	if (m_nextTemplate)
		m_nextTemplate->deleteInstance();

	if (m_extraBonus)
		operator delete(m_extraBonus);

	Rva001E3F90Node *node = m_nuggets.m_node->m_next;
	while (node != m_nuggets.m_node)
	{
		if (!m_copiedOverride || node->m_value->m_field54)
		{
			Rva001E3F90Nugget *held = node->m_value;
			if (held)
				delete held;
		}
		node = node->m_next;
	}

	m_nuggets.clear();

}
