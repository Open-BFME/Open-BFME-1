// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: convert AIAttackApproachTargetState::onExit to clean C++.
//
// The BFME state, Object, template, locomotor, and AI vtable layouts differ
// from the vendored Zero Hour declarations.  These narrow views preserve the
// recovered retail offsets without changing the shared headers.

typedef int Int;
typedef bool Bool;
typedef float Real;
typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

enum StateExitType { STATE_EXIT_UNKNOWN = 0 };

class Object;
class AIUpdateInterface;

class AIUpdateInterface
{
public:
	void ignoreObstacle(Object *obj);                 // ILT thunk at 0x0000315C
};

class Object
{
public:
	void setPosition(const Coord3D *position);        // ILT thunk at 0x0003A1A7
};

template <Int N>
class BFMEVirtualSlots : public BFMEVirtualSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};

template <>
class BFMEVirtualSlots<0>
{
};

// BFME calls the argument-less virtual at +0x1E8 immediately before leaving
// this block, then tests isDoingGroundMovement at +0x1EC.
class BFMEApproachTargetAI : public BFMEVirtualSlots<122>
{
public:
	virtual void clearFieldAt1D8() = 0;                 // vtable +0x1E8
	virtual Bool isDoingGroundMovement() const = 0;    // vtable +0x1EC
};

class BFMEObjectAI
{
public:
	AIUpdateInterface *getAI() const
	{
		return *(AIUpdateInterface **)((char *)this + 0x204);
	}
};

// BFME's Locomotor::setUsePreciseZPos(false) is an inline flag clear.
class BFMEApproachTargetLocomotor
{
public:
	void setUsePreciseZPos(Bool set)
	{
		if (!set)
			m_flags &= ~PRECISE_Z_POS;
	}

private:
	enum { PRECISE_Z_POS = 0x00000008 };
	UnsignedByte m_unreconstructed_000[0x40];
	UnsignedInt m_flags;                               // retail this+0x40
};

class BFMEApproachTargetLocomotorSet
{
public:
	BFMEApproachTargetLocomotor *getCurLocomotor() const
	{
		return *(BFMEApproachTargetLocomotor **)((char *)this + 0x1CC);
	}
};

// The ILT at 0x000022BB is already identified as the override-chain walker.
// This view intentionally starts with the Object+4 Thing sub-object's
// leading dword, so the next override remains at the BFME +0x04 offset.
class BfmeOverridable
{
public:
	BfmeOverridable *friend_getFinalOverride();

	UnsignedByte m_unreconstructed_000[4];
	BfmeOverridable *m_nextOverride;                   // retail this+0x04
};

struct BFMEApproachTargetThing
{
	BfmeOverridable *getTemplateOverridable() const
	{
		BfmeOverridable *tmpl = m_template;
		if (tmpl && tmpl->m_nextOverride)
			tmpl = tmpl->m_nextOverride->friend_getFinalOverride();
		return tmpl;
	}

	BfmeOverridable *m_template;                       // retail Object+0x04
};

struct BFMEApproachTargetObjectHead
{
	UnsignedByte m_unreconstructed_000[4];
};

struct BFMEApproachTargetObject : public BFMEApproachTargetObjectHead,
	public BFMEApproachTargetThing
{
	UnsignedByte m_unreconstructed_008[0x38 - 0x08];
	Coord3D m_position;                                // retail Object+0x38
};

// Retail tests bit 25 of the dword at ThingTemplate+0xC8.  The shared
// KindOf.h numbering is not the BFME numbering, so the recovered mask is
// spelled directly.
struct BFMEApproachTargetTemplate
{
	UnsignedByte m_unreconstructed_000[0xC8];
	UnsignedInt m_kindOfBits;                          // retail this+0xC8
};

enum { BFME_KINDOF_PROJECTILE_BIT = 0x02000000 };

struct BfmeMoveStateMachineFields
{
	UnsignedByte m_unreconstructed_000[0x10];
	Object *m_owner;                                   // retail this+0x10
};

struct BFMEApproachTargetFields
{
	UnsignedByte m_unreconstructed_000[0x1C];
	BfmeMoveStateMachineFields *m_machine;             // retail this+0x1C
	UnsignedByte m_unreconstructed_020[4];
	Coord3D m_goalPosition;                            // retail this+0x24
	UnsignedByte m_unreconstructed_030[0x73 - 0x30];
	Bool m_isInitialApproach;                          // retail this+0x73
};

class AIInternalMoveToState
{
public:
	virtual void onExit(StateExitType status);
};

class BfmeAIAttackApproachTargetState : public AIInternalMoveToState
{
public:
	virtual void onExit(StateExitType status);
};

// ?onExit@AIAttackApproachTargetState@@UAEXW4StateExitType@@@Z
#pragma comment(linker, "/alternatename:?onExit@AIAttackApproachTargetState@@UAEXW4StateExitType@@@Z=?onExit@BfmeAIAttackApproachTargetState@@UAEXW4StateExitType@@@Z")
void BfmeAIAttackApproachTargetState::onExit(StateExitType status)
{
	BFMEApproachTargetFields *self = (BFMEApproachTargetFields *)this;

	// contained by AIAttackState, so no separate timer
	AIInternalMoveToState::onExit(status);

	AIUpdateInterface *ai = ((BFMEObjectAI *)self->m_machine->m_owner)->getAI();
	Object *obj = self->m_machine->m_owner;
	if (ai)
	{
		ai->ignoreObstacle(0);

		// BFME inlines Thing::getTemplate and starts from the OVERRIDE wrapper
		// at Object+4.  Keep the wrapper materialization as two operations: this
		// is the ABI-visible address used by the retail body.
		volatile UnsignedByte *thing =
			(volatile UnsignedByte *)self->m_machine->m_owner;
		thing += 4;
		BfmeOverridable *tmpl = *(BfmeOverridable * volatile *)thing;
		if (tmpl && tmpl->m_nextOverride)
			tmpl = tmpl->m_nextOverride->friend_getFinalOverride();
		if (((BFMEApproachTargetTemplate *)tmpl)->m_kindOfBits &
			BFME_KINDOF_PROJECTILE_BIT)
		{
			if (ai && ((BFMEApproachTargetLocomotorSet *)ai)->getCurLocomotor())
				((BFMEApproachTargetLocomotorSet *)ai)->getCurLocomotor()->setUsePreciseZPos(false);
		}

		if (((BFMEApproachTargetAI *)ai)->isDoingGroundMovement())
		{
			Real dx = self->m_goalPosition.x -
				((BFMEApproachTargetObject *)obj)->m_position.x;
			Real dy = self->m_goalPosition.y -
				((BFMEApproachTargetObject *)obj)->m_position.y;
			if (dx * dx + dy * dy < 10.0f * 10.0f * 0.125f)
				obj->setPosition(&self->m_goalPosition);
		}

		((BFMEApproachTargetAI *)ai)->clearFieldAt1D8();
	}

	self->m_isInitialApproach = false;
}
