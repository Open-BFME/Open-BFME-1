// ?onExit@AIAttackApproachTargetState@@UAEXW4StateExitType@@@Z
// partial score=0.96 date=2026-08-29
// The AI vtable is the one BFMEAIUpdateCommandSource already pins: retail's
// getLastCommandSource is slot 128 (+0x200), which makes isDoingGroundMovement
// slot 123 (+0x1EC).  Retail also calls slot 122 (+0x1E8) unconditionally at the
// end of the ai block -- an 11-byte virtual whose whole body is
// `AIUpdateInterface+0x1D8 = 0`.  The reference has ai->destroyPath() commented
// out at exactly that point, but destroyPath is not virtual in this image, so the
// slot is spelled by its offset rather than given a name the bytes do not prove.
class BFMEApproachTargetAI : public BFMEVirtualSlots<122>
{
public:
	virtual void clearFieldAt1D8() = 0;			///< vtable +0x1E8
	virtual Bool isDoingGroundMovement() const = 0;		///< vtable +0x1EC
};

// setUsePreciseZPos(false) is inlined to a single `and [Locomotor+0x40], ~8`,
// so the flag is bit 3 of the same word BFMEEnterStateLocomotor clears bit 1 of.
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

	unsigned char m_unreconstructed_000[ 0x40 ];
	UnsignedInt m_flags;					///< retail this+0x40
};

class BFMEApproachTargetLocomotorSet
{
public:
	BFMEApproachTargetLocomotor *getCurLocomotor() const
	{
		return *(BFMEApproachTargetLocomotor **)((char *)this + 0x1cc);
	}
};

// Retail inlines Thing::getTemplate() and the first level of
// Overridable::getFinalOverride(); the shared Thing.h declares getTemplate out of
// line and the shared Overridable.h defines getFinalOverride inline, so the two
// come out exactly the wrong way round.  BfmeOverridable is the view spelling
// already pinned at ILT 0x000022BB, so no new pin.  The `this` retail hands the
// template read is Object+4, which is where its Thing sub-object starts.
class BfmeOverridable
{
public:
	BfmeOverridable *friend_getFinalOverride();

	unsigned char m_unreconstructed_000[ 4 ];
	BfmeOverridable *m_nextOverride;			///< retail this+0x04
};

struct BFMEApproachTargetThing
{
	// The whole of retail's inlined Thing::getTemplate(): read the template, and
	// if it carries an override chain hand the chain walker its first link.
	BfmeOverridable *getTemplateOverridable() const
	{
		BfmeOverridable *t = m_template;
		if (t && t->m_nextOverride)
			t = t->m_nextOverride->friend_getFinalOverride();
		return t;
	}


	BfmeOverridable *m_template;				///< retail Thing+0x00 == Object+0x04
};

struct BFMEApproachTargetObjectHead
{
	unsigned char m_unreconstructed_000[ 4 ];
};

struct BFMEApproachTargetObject
{
	unsigned char m_unreconstructed_000[ 4 ];
	BFMEApproachTargetThing m_thing;			///< retail Object+0x04
};

// Retail tests bit 25 of the dword at ThingTemplate+0xC8.  The shared KindOf.h
// numbers KINDOF_PROJECTILE 22 -- the out-of-line isKindOf call this replaces
// pushed 0x16 -- so BFME has three more kinds ahead of it.  The bit is what the
// bytes prove; the name is not, so the mask is spelled as a value.
struct BFMEApproachTargetTemplate
{
	unsigned char m_unreconstructed_000[ 0xc8 ];
	UnsignedInt m_kindOfBits;				///< retail this+0xC8
};

enum { BFME_KINDOF_PROJECTILE_BIT = 0x02000000 };

struct BFMEApproachTargetFields
{
	unsigned char m_unreconstructed_000[ 0x1c ];
	BfmeMoveStateMachineFields *m_machine;			///< retail this+0x1c
	unsigned char m_unreconstructed_020[ 4 ];
	Coord3D m_goalPosition;					///< retail this+0x24
	unsigned char m_unreconstructed_030[ 0x73 - 0x30 ];
	Bool m_isInitialApproach;				///< retail this+0x73
};

void AIAttackApproachTargetState::onExit( StateExitType status )
{
	BFMEApproachTargetFields *self = (BFMEApproachTargetFields *)this;

	// contained by AIAttackState, so no separate timer
	AIInternalMoveToState::onExit( status );

	AIUpdateInterface *ai = ((BFMEObjectAI *)self->m_machine->m_owner)->getAI();
	Object *obj = self->m_machine->m_owner;
	if (ai) {
		ai->ignoreObstacle(NULL);
		
		// Per JohnA, this state should not be calling ai->destroyPath, because we can have spastic users
		// that click the target repeadedly. This will prevent the unit from stuttering for said spastic 
		// users.
		// ai->destroyPath();
		// urg. hacky. if we are a projectile, reset precise z-pos.
		BFMEApproachTargetThing &thing =
			((BFMEApproachTargetObject *)self->m_machine->m_owner)->m_thing;
		BfmeOverridable *tmpl = thing.getTemplateOverridable();
		if (((BFMEApproachTargetTemplate *)tmpl)->m_kindOfBits & BFME_KINDOF_PROJECTILE_BIT)
		{
			if (ai && ((BFMEApproachTargetLocomotorSet *)ai)->getCurLocomotor())
				((BFMEApproachTargetLocomotorSet *)ai)->getCurLocomotor()->setUsePreciseZPos(false);
		}
		if (((BFMEApproachTargetAI *)ai)->isDoingGroundMovement()) {
			Real dx = self->m_goalPosition.x-obj->getPosition()->x;
			Real dy = self->m_goalPosition.y-obj->getPosition()->y;
			if (dx*dx+dy*dy<PATHFIND_CELL_SIZE_F*PATHFIND_CELL_SIZE_F*0.125f) 
			{
				// We are doing accurate ground movement, so make sure we end exactly at the goal.
				obj->setPosition(&self->m_goalPosition);
			}
		}
		((BFMEApproachTargetAI *)ai)->clearFieldAt1D8();
	}

	self->m_isInitialApproach = false;	// We only want to allow turreted things to fire at enemies during their
																// first approach
}
