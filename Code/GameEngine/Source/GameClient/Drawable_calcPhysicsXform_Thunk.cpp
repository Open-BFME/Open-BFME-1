// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// readable body of ?calcPhysicsXform@Drawable@@IAE_NAAUPhysicsXformInfo@1@@Z: Code/GameEngine/Source/GameClient/Drawable.cpp
// Lift the Drawable::calcPhysicsXform naked dump to clean C++.
//
// Zero Hour's Drawable.cpp body without the trailing denormal-clamping hotfix,
// which retail does not have at all.
//
// The jump table regroups the cases. Reading it gives, for appearance values 1
// through 8: wheels and motorcycle reach one helper through two separate case
// bodies, treads and hover share a single body, wings and thrust have one each,
// and climber and other fall through to the default. ZH pairs hover with wings
// instead, so the ZH helper names below are attached to the case ZH itself
// routes to them; the pairing is BFME's.
//
// Two cases reaching the same helper through separate bodies rather than a
// fall-through is what tells them apart: a fall-through emits one body and two
// table entries pointing at it, which is what treads and hover do.
//
// getAppearance walks the overridable chain with one level unrolled, the same
// shape as SpecialPowerTemplate::getRequiredScience, and reads the appearance
// at locomotor+0x70. The current locomotor at ai+0x1CC agrees with the
// TransportContain conversion.

typedef int Int;
typedef bool Bool;

class Object;

enum LocomotorAppearance
{
	LOCO_LEGS_TWO,
	LOCO_WHEELS_FOUR,
	LOCO_TREADS,
	LOCO_HOVER,
	LOCO_THRUST,
	LOCO_WINGS,
	LOCO_CLIMBER,
	LOCO_OTHER,
	LOCO_MOTORCYCLE
};

// A different overridable base from SpecialPowerTemplate's: that walker is at
// 0x00097880 and this one at 0x00087A80, two distinct bodies rather than ICF
// aliases, so they need distinct names.
class LocomotorOverridable
{
public:
	virtual ~LocomotorOverridable();								///< the vtable pointer occupies +0x00

	LocomotorOverridable *friend_getFinalOverride(void);	///< ILT thunk at 0x000022BB

	LocomotorOverridable *m_nextOverride;						///< retail this+0x04
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Locomotor.h
class Locomotor : public LocomotorOverridable
{
public:
	LocomotorAppearance getAppearance(void) const
	{
		// no fallback to this: retail reads straight through the override pointer,
		// so a locomotor with no override dereferences null here
		LocomotorOverridable *o = m_nextOverride;
		if (o && o->m_nextOverride)
			o = o->m_nextOverride->friend_getFinalOverride();
		return ((const Locomotor *)o)->m_appearance;
	}

private:
	unsigned char m_unreconstructed_08[0x70 - 8];
	LocomotorAppearance m_appearance;					///< retail this+0x70
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface
{
public:
	const Locomotor *getCurLocomotor(void) const { return m_curLocomotor; }

private:
	unsigned char m_unreconstructed_00[0x1CC];
	Locomotor *m_curLocomotor;							///< retail this+0x1CC
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	const AIUpdateInterface *getAIUpdateInterface(void) const { return m_ai; }

private:
	unsigned char m_unreconstructed_00[0x204];
	AIUpdateInterface *m_ai;							///< retail this+0x204
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Drawable.h
class Drawable
{
public:
	// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Drawable.h
	struct PhysicsXformInfo
	{
		float m_totalPitch;
		float m_totalRoll;
		float m_totalYaw;
		float m_totalZ;
	};

protected:
	Bool calcPhysicsXform(PhysicsXformInfo &info);

	void calcPhysicsXformWheels(const Locomotor *loco, PhysicsXformInfo &info);		///< ILT thunk at 0x000090BB
	void calcPhysicsXformTreads(const Locomotor *loco, PhysicsXformInfo &info);		///< ILT thunk at 0x00034ABD
	void calcPhysicsXformHoverOrWings(const Locomotor *loco, PhysicsXformInfo &info);///< ILT thunk at 0x00020865
	void calcPhysicsXformThrust(const Locomotor *loco, PhysicsXformInfo &info);		///< ILT thunk at 0x00027651

	Object *getObject(void) const { return m_object; }

private:
	unsigned char m_unreconstructed_00[0xFC];
	Object *m_object;									///< retail this+0xFC
};

// ?calcPhysicsXform@Drawable@@IAE_NAAUPhysicsXformInfo@1@@Z
Bool Drawable::calcPhysicsXform(PhysicsXformInfo& info)
{
	const Object* obj = getObject();
	const AIUpdateInterface *ai = obj ? obj->getAIUpdateInterface() : 0;
	Bool hasPhysicsXform = false;
	if (ai)
	{
		const Locomotor *locomotor = ai->getCurLocomotor();
		if (locomotor)
		{
			switch (locomotor->getAppearance())
			{
				case LOCO_WHEELS_FOUR:
					calcPhysicsXformWheels(locomotor, info);
					hasPhysicsXform = true;
					break;
				case LOCO_TREADS:
				case LOCO_HOVER:
					calcPhysicsXformTreads(locomotor, info);
					hasPhysicsXform = true;
					break;
				case LOCO_WINGS:
					calcPhysicsXformHoverOrWings(locomotor, info);
					hasPhysicsXform = true;
					break;
				case LOCO_THRUST:
					calcPhysicsXformThrust(locomotor, info);
					hasPhysicsXform = true;
					break;
				case LOCO_MOTORCYCLE:
					calcPhysicsXformWheels( locomotor, info );
					hasPhysicsXform = true;
					break;
			}
		}
	}

	return hasPhysicsXform;
}
