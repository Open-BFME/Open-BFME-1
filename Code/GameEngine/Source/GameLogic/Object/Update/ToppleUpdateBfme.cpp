// ?update@ToppleUpdate@@UAE?AW4UpdateSleepTime@@XZ
// BFME ToppleUpdate::update [0x002B1610,0x002B1A95), including the
// authentic static deathByToppling helper at 0x002B1440 (58 bytes).
// cl: /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

#define ToppleUpdate DonorToppleUpdate
#define DamageInfo DonorDamageInfo
#include "PreRTS.h"

#include "Common/ThingTemplate.h"
#include "Common/ThingFactory.h"
#include "Common/PlayerList.h"
#include "Common/Player.h"
#include "Common/RandomValue.h"
#include "Common/Xfer.h"
#include "GameClient/FXList.h"
#include "GameLogic/AI.h"
#include "GameLogic/AIPathfind.h"
#include "GameLogic/Module/ToppleUpdate.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/Object.h"
#include "GameClient/Drawable.h"
#include "GameClient/Module/SwayClientUpdate.h"
#include "GameLogic/Module/PhysicsUpdate.h"
#include "GameLogic/ScriptEngine.h"
#include "GameLogic/Damage.h"
#undef DamageInfo
#undef ToppleUpdate

// Retail DamageInfo is 0x5c bytes; these offsets agree with the matched
// constructor and Object::kill family. The donor has a different layout.
class DamageInfo {
public:
 DamageInfo();
 unsigned char pad00[8];
 ObjectID sourceID;
 unsigned char pad0c[4];
 int damageType;
 unsigned char pad14[4];
 int deathType;
 float amount;
 unsigned char rest20[0x3c];
};

static const Real ANGULAR_LIMIT = PI/2 - PI/64;

enum Rva002B1610ToppleState
{
	TOPPLE_UPRIGHT = 0,
	TOPPLE_FALLING,
	TOPPLE_DOWN
};

class Rva002B1610ModuleData
{
public:
	unsigned char m_pad00[0x0c];
	const FXList *m_bounceFX;
	unsigned char m_pad10[0x0c];
	Real m_bounceVelocityPercent;
	unsigned char m_pad20[4];
	Bool m_killWhenToppled;
	Bool m_killWhenStartToppled;
	Bool m_killStumpWhenToppled;
	Bool m_toppleLeftOrRightOnly;
	Bool m_reorientToppledRubble;
};

class Rva002B1610Base
{
public:
	void *m_vptr;
	const Rva002B1610ModuleData *m_moduleData;
	Object *m_object;
};

class Rva002B1610ObjectView
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual Drawable *getDrawable();
	virtual void slot2c();
	virtual void slot30();
	virtual void attemptDamage(DamageInfo *);
};

class ToppleUpdate
{
public:
	virtual UpdateSleepTime update();

private:
	unsigned char m_pad04[0x10];
	Real m_angularVelocity;
	Real m_angularAcceleration;
	Coord3D m_toppleDirection;
	int m_toppleState;
	Real m_angularAccumulation;
	Real m_angleDeltaX;
	int m_numAngleDeltaX;
	Bool m_doBounceFX;
	UnsignedInt m_options;
	ObjectID m_stumpID;
	Real m_bfmeState;
};

// This BFME transform-copy body is independently owned at RVA 0x00132200.
// Keep its actual ILT: the donor setTransformMatrix name also names another body.
extern void j_000361ce();
class BfmeThingTransformTarget { public: void copyTransform(const Matrix3D *); };
static inline void bfmeCopyThingTransform(Object *object,const Matrix3D *matrix)
{
 union { void (*function)(); void (BfmeThingTransformTarget::*method)(const Matrix3D *); } target;
 target.function=j_000361ce;
 (reinterpret_cast<BfmeThingTransformTarget *>(object)->*target.method)(matrix);
}

// BFME ordinals; Zero Hour assigns UNRESISTABLE a different value.
static const int BFME_DAMAGE_UNRESISTABLE = 8;

// The static helper deliberately retains its authentic C++ body: MSVC 7.1
// infers the private ESI argument convention from these two local callers.
static __declspec(noinline) void deathByToppling(Object *obj)
{
 DamageInfo damageInfo;
 damageInfo.damageType=BFME_DAMAGE_UNRESISTABLE;
 damageInfo.deathType=DEATH_TOPPLED;
 damageInfo.sourceID=INVALID_ID;
 damageInfo.amount=999999.0f;
 reinterpret_cast<Rva002B1610ObjectView *>(obj)->attemptDamage(&damageInfo);
}

#define RVA002B1610_BOUNCE_STEP (*(const Real *)0x010C51AC)
#define RVA002B1610_BOUNCE_FLOOR (*(const Real *)0x010BA670)

#define RVA002B1610_BASE ((Rva002B1610Base *)((char *)this - 0x10))

// ?update@ToppleUpdate@@UAE?AW4UpdateSleepTime@@XZ
UpdateSleepTime ToppleUpdate::update()
{
	DEBUG_ASSERTCRASH(m_toppleState != TOPPLE_UPRIGHT, ("hmm, we should be sleeping here"));
	if ((m_toppleState == TOPPLE_UPRIGHT) || (m_toppleState == TOPPLE_DOWN))
		return UPDATE_SLEEP_FOREVER;

	const Rva002B1610ModuleData *d = RVA002B1610_BASE->m_moduleData;
	const Real VELOCITY_BOUNCE_LIMIT = 0.01f;
	const Real VELOCITY_BOUNCE_SOUND_LIMIT = 0.03f;

	Object *obj = RVA002B1610_BASE->m_object;
	if (m_numAngleDeltaX)
	{
		Matrix3D xfrm = *obj->getTransformMatrix();
		xfrm.In_Place_Pre_Rotate_Z(m_angleDeltaX);
		bfmeCopyThingTransform(obj,&xfrm);
		--m_numAngleDeltaX;
	}

	Real curVelToUse = m_angularVelocity;
	if (m_angularAccumulation + curVelToUse > ANGULAR_LIMIT)
		curVelToUse = ANGULAR_LIMIT - m_angularAccumulation;

	Real minimumBounceVelocity;
	Matrix3D xfrm = *obj->getTransformMatrix();
	xfrm.In_Place_Pre_Rotate_X(-curVelToUse * m_toppleDirection.y);
	xfrm.In_Place_Pre_Rotate_Y(curVelToUse * m_toppleDirection.x);
	bfmeCopyThingTransform(obj,&xfrm);

	m_angularAccumulation += curVelToUse;
	if ((m_angularAccumulation >= ANGULAR_LIMIT) && (m_angularVelocity > 0))
	{
		Real bounceVelocity = d->m_bounceVelocityPercent - m_bfmeState;
		minimumBounceVelocity = 0.05f;
		const Real *bounceVelocityToUse =
			(RVA002B1610_BOUNCE_FLOOR > bounceVelocity) ?
			&minimumBounceVelocity : &bounceVelocity;

		m_angularVelocity *= -(*bounceVelocityToUse);
		m_bfmeState += RVA002B1610_BOUNCE_STEP;

		if (BitTest(m_options, TOPPLE_OPTIONS_NO_BOUNCE) == TRUE ||
			fabs(m_angularVelocity) < VELOCITY_BOUNCE_LIMIT)
		{
			m_angularVelocity = 0;
			m_toppleState = TOPPLE_DOWN;

			if (d->m_killWhenToppled)
			{
				deathByToppling(obj);
				if (d->m_reorientToppledRubble)
				{
					Vector3 pos;
					pos.X = 0;
					pos.Y = 0;
					pos.Z = ((GeometryInfo *)((char *)obj + 0xac))->getMaxHeightAbovePosition();
					Matrix3D::Transform_Vector(*obj->getTransformMatrix(), pos, &pos);

					Coord3D tmp;
					tmp.x = pos.X;
					tmp.y = pos.Y;
					tmp.z = pos.Z;
					obj->setPosition(&tmp);
					obj->setOrientation(obj->getOrientation());
				}
			}

			if (d->m_killStumpWhenToppled)
			{
				Object *stump = TheGameLogic->findObjectByID(m_stumpID);
				if (stump)
				{
					deathByToppling(stump);
				}
			}
		}
		else if (fabs(m_angularVelocity) >= VELOCITY_BOUNCE_SOUND_LIMIT)
		{
			if (BitTest(m_options, TOPPLE_OPTIONS_NO_FX) == FALSE)
				FXList::doFXObj(d->m_bounceFX, obj);
		}
	}
	else
	{
		m_angularVelocity += m_angularAcceleration;
	}

	Drawable *draw = ((Rva002B1610ObjectView *)obj)->getDrawable();
	if (draw)
		draw->setShadowsEnabled(false);

	return UPDATE_SLEEP_NONE;
}
