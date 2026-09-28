// ?d_0024da80@@YAXXZ
// partial score=0.88 date=2026-09-28
// cl: /DNDEBUG /MD /EHsc
// Retail 0x0024DA80, 1742 bytes, thiscall ret 12: (Object *member,
// const Coord3D *goal, Real orientation).  Reached through ILT 0x0000E200 from
// the matched MemberTurnAndGoal0024E310::apply.  The two updateGoal calls pass
// the HorseHordeContain.cpp source path with lines 499 and 503, which places
// the body in that module; the method name is not known, so the class and the
// method keep the address.
//
// BANKED DRAFT (not matching). State 2026-09-28 (second opus-5.5 pass):
// 1737/1742 bytes, frame table now IDENTICAL to retail (/FAsc listing):
// minDist+locomotor -100, owner -96, speed -92, fastSpeed+maxSpeed+
// ownerLocomotor -88, goal -84, dest -72, myPos -60, target+delta -48,
// point -36, ownerAI/dist/preferredHeight in the dead parameter slots.
// 451 of 503 retail instructions align exactly (was 408).  Levers that
// fixed the frame (docs/shape_levers.md "one more object"):
//  - maxSpeed*0.66 is a NEW local (fastSpeed), not an in-place *=; that
//    extra object re-pairs the scalar slots.
//  - the tail copy is its own object (target), not delta reused; VC7.1
//    orders slots by reference count and delta+target outweighed myPos.
//  - target packs onto delta (not myPos) only when delta lives in an
//    ENDED block and target's block opens before myPos's last use
//    (dest.z = myPos.z); a block-scoped target at the tail packs onto
//    myPos instead.
//  - surfaces via an inline LocomotorSet accessor and the owner via an
//    inline object08() accessor fix the validMovementPosition registers.
// Remaining (52 instructions): entry schedule (retail keeps this in ECX
// over the goal copy and loads goal.x before push ebx; we move this to EBP
// first and copy the position pointer to ECX), the owner store placement,
// the surfaces load placement, record->m_state compared in memory (retail
// cmp [eax],1), the tail call setup hoisted above the m_byte204 branch in
// ours (retail keeps one copy per arm), and an eax/ecx/edx rotation in
// the pathfinder calls.
// Earlier levers kept: force-inlined model-condition helpers (60/127/128);
// copy member+0xA4 before the cell compare; one shared aiIdle block reached
// from the m_1fc path (goto into the then-branch); member+0x44 read
// directly for the angle; no Path* local.

#include <math.h>
#pragma intrinsic(fabs)

typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef unsigned char UnsignedByte;

#define TRUE true
#define FALSE false

struct Coord3D
{
	Real x;
	Real y;
	Real z;

	Real length() const;
};

struct ICoord2D
{
	Int x;
	Int y;
};

class Object;

extern const Real BfmeZeroRange;

Real normalizeAngle(Real angle);

struct Obj001B49C0;
UnsignedByte __stdcall rva001b49c0(Obj001B49C0 *obj);

// Nine-dword output of Path::computePointOnPath; the body reads the first.
struct Rva001B7200PathPoint
{
	Real m_distance;
	Real m_unmodelled_04[8];
};

class Rva001B7200Locomotor;

class Path
{
public:
	void computePointOnPath(Object *obj, Rva001B7200Locomotor *locomotor, Rva001B7200PathPoint *out, Bool advance);
};

class BfmeSub1CC_EC3
{
public:
	Real queryDivMin40(void *obj);
	Real effectiveMaxSpeed(void *obj);
};

class Rva00233D20
{
public:
	Int value() const;
};

class Locomotor
{
public:
	Real getPreferredHeight() const;
	Real rva001B8010(Object *obj) { return ((BfmeSub1CC_EC3 *)this)->queryDivMin40(obj); }
	Real rva001B7E90(Object *obj) { return ((BfmeSub1CC_EC3 *)this)->effectiveMaxSpeed(obj); }
	Int rva00233D20() const { return ((const Rva00233D20 *)this)->value(); }
};

class LocomotorSet
{
public:
	UnsignedInt surfaceMask10() const { return m_surfaceMask10; }
	UnsignedByte m_unmodelled_00[0x10];
	UnsignedInt m_surfaceMask10;
};

enum CommandSourceType
{
	CMD_FROM_AI = 2
};

class AICommandInterface
{
public:
	void aiIdle(CommandSourceType cmdSource);
};

class BfmeInnerCPB
{
public:
	void bfmeOneCPB(Int a, Int b);
};

struct Rva0024DA80State
{
	UnsignedByte m_unmodelled_00[4];
	Int m_id;
};

struct Rva0024DA80StateHolder
{
	UnsignedByte m_unmodelled_00[0x1c];
	Rva0024DA80State *m_state;
};

#define SLOT(n) virtual void slot##n();

class AIUpdateInterface
{
public:
	SLOT(000) SLOT(004) SLOT(008) SLOT(00c) SLOT(010) SLOT(014) SLOT(018) SLOT(01c)
	SLOT(020) SLOT(024) SLOT(028) SLOT(02c) SLOT(030) SLOT(034) SLOT(038) SLOT(03c)
	SLOT(040) SLOT(044) SLOT(048) SLOT(04c) SLOT(050) SLOT(054) SLOT(058) SLOT(05c)
	SLOT(060) SLOT(064) SLOT(068) SLOT(06c) SLOT(070) SLOT(074) SLOT(078) SLOT(07c)
	SLOT(080) SLOT(084) SLOT(088) SLOT(08c) SLOT(090) SLOT(094) SLOT(098) SLOT(09c)
	SLOT(0a0) SLOT(0a4) SLOT(0a8) SLOT(0ac) SLOT(0b0) SLOT(0b4) SLOT(0b8) SLOT(0bc)
	SLOT(0c0) SLOT(0c4) SLOT(0c8) SLOT(0cc) SLOT(0d0) SLOT(0d4) SLOT(0d8) SLOT(0dc)
	SLOT(0e0) SLOT(0e4) SLOT(0e8) SLOT(0ec) SLOT(0f0) SLOT(0f4) SLOT(0f8) SLOT(0fc)
	SLOT(100) SLOT(104) SLOT(108) SLOT(10c) SLOT(110) SLOT(114) SLOT(118) SLOT(11c)
	SLOT(120) SLOT(124) SLOT(128) SLOT(12c) SLOT(130) SLOT(134) SLOT(138) SLOT(13c)
	SLOT(140) SLOT(144) SLOT(148) SLOT(14c) SLOT(150) SLOT(154) SLOT(158) SLOT(15c)
	SLOT(160) SLOT(164) SLOT(168) SLOT(16c) SLOT(170) SLOT(174) SLOT(178) SLOT(17c)
	virtual Bool slot180();
	virtual Bool slot184();
	SLOT(188)
	virtual Bool slot18c();
	SLOT(190) SLOT(194) SLOT(198) SLOT(19c)
	SLOT(1a0) SLOT(1a4) SLOT(1a8) SLOT(1ac) SLOT(1b0) SLOT(1b4) SLOT(1b8) SLOT(1bc)
	SLOT(1c0) SLOT(1c4) SLOT(1c8) SLOT(1cc) SLOT(1d0) SLOT(1d4)
	virtual void slot1d8(const Coord3D *pos);
	virtual void slot1dc(const Coord3D *pos);
	SLOT(1e0)
	virtual void slot1e4(Real angle);
	virtual void slot1e8();
	SLOT(1ec) SLOT(1f0)
	virtual void slot1f4(const Coord3D *pos);

	Bool bfmeBlocksFormationRefresh();
	void setDesiredSpeed(Real speed);

	Locomotor *getCurLocomotor() const { return m_curLocomotor1cc; }
	Path *getPath() const { return m_path140; }
	AICommandInterface *getCommand() { return &m_command20; }

	UnsignedByte m_unmodelled_004[0x20 - 4];
	AICommandInterface m_command20;
	UnsignedByte m_unmodelled_021[0x30 - 0x21];
	Rva0024DA80StateHolder *m_stateHolder30;
	UnsignedByte m_unmodelled_034[0x140 - 0x34];
	Path *m_path140;
	UnsignedByte m_unmodelled_144[0x1a8 - 0x144];
	LocomotorSet m_locomotorSet1a8;
	UnsignedByte m_unmodelled_1bc[0x1cc - 0x1bc];
	Locomotor *m_curLocomotor1cc;
};

class Rva0026FE90DwordSlot
{
public:
	void set(Int value);
};

class Gen_0024D1E0
{
public:
	void bfmePush(UnsignedByte value);
};

class BFMESelectionStatusBits
{
public:
	Bool test(UnsignedInt bit) const;
};

class WordBitTest000D2F40
{
public:
	Bool test(UnsignedInt bit) const;
};

struct Rva001B3F60Payload;

class Rva001B3F60Target
{
public:
	void copy(Rva001B3F60Payload *payload);
};

// Object+0x110 is the 320-bit model-condition array.  test returns the masked
// word (docs/shape_levers.md, model-condition bit masks).
struct Rva0024DA80ConditionFlags
{
	UnsignedInt test(Int i) const { return m_bits[i >> 5] & (1u << (i & 31)); }
	void set(Int i) { m_bits[i >> 5] |= (1u << (i & 31)); }
	void reset(Int i) { m_bits[i >> 5] &= ~(1u << (i & 31)); }
	UnsignedInt m_bits[10];
};

class Object
{
public:
	void notifyModelConditionChanged();
	Int getLayer() const;
	void setPosition(const Coord3D *pos);

	const Coord3D *getPosition() const { return &m_position38; }
	Real getOrientation() const { return m_orientation44; }
	AIUpdateInterface *getAI() const { return m_ai204; }

	__forceinline void setCondition(Int bit)
	{
		if (!m_conditions110.test(bit))
		{
			m_conditions110.set(bit);
			notifyModelConditionChanged();
		}
	}
	__forceinline void clearCondition(Int bit)
	{
		if (m_conditions110.test(bit))
		{
			m_conditions110.reset(bit);
			notifyModelConditionChanged();
		}
	}

	UnsignedByte m_unmodelled_000[0x38];
	Coord3D m_position38;
	Real m_orientation44;
	UnsignedByte m_unmodelled_048[0x74 - 0x48];
	Int m_int74;
	UnsignedByte m_unmodelled_078[0x9c - 0x78];
	ICoord2D m_cell9c;
	ICoord2D m_cellA4;
	UnsignedByte m_unmodelled_0ac[0x110 - 0xac];
	Rva0024DA80ConditionFlags m_conditions110;
	UnsignedByte m_unmodelled_138[0x204 - 0x138];
	AIUpdateInterface *m_ai204;
};

class Pathfinder
{
public:
	Bool validMovementPosition(const Coord3D *pos, Int layer, UnsignedInt surfaces, Object *obj);
	Bool adjustDestination(Object *obj, const LocomotorSet &locomotorSet, Coord3D *dest, const Coord3D *groupDest);
	void updateGoal(Object *obj, const Coord3D *goal, Int layer, const char *file, Int line);
	void removeGoal(Object *obj);
};

class AI
{
public:
	Pathfinder *pathfinder() { return m_pathfinder0c; }

	UnsignedByte m_unmodelled_00[0xc];
	Pathfinder *m_pathfinder0c;
};
extern AI *TheAI;

class TerrainLogic
{
public:
	SLOT(000) SLOT(004) SLOT(008) SLOT(00c) SLOT(010) SLOT(014) SLOT(018)
	virtual Real getLayerHeight(Real x, Real y, Int layer, Coord3D *normal = 0, Bool clip = true);
};
extern TerrainLogic *TheTerrainLogic;

class BfmeAODHordeContainOwner
{
public:
	Int bfmeGetMemberIndex(Int id);
};

class Rva0023BE60Receiver
{
public:
	Bool rva0023BE60(Object *obj);
};

struct Rva0024DA80MemberRecord
{
	Int m_state;
	UnsignedByte m_unmodelled_04[0x18];
};

class HorseHordeContain0024DA80
{
public:
	void rva0024DA80(Object *member, const Coord3D *pos, Real orientation);
	Object *object08() const { return m_object08; }

	UnsignedByte m_unmodelled_000[8];
	Object *m_object08;
	UnsignedByte m_unmodelled_00c[0xe8 - 0xc];
	Bool m_byteE8;
	Bool m_byteE9;
	UnsignedByte m_unmodelled_0ea[0x1d8 - 0xea];
	Rva0024DA80MemberRecord *m_records1d8;
	UnsignedByte m_unmodelled_1dc[0x1fc - 0x1dc];
	Bool m_byte1fc;
	UnsignedByte m_unmodelled_1fd[0x204 - 0x1fd];
	Bool m_byte204;
};

// ?rva0024DA80@HorseHordeContain0024DA80@@QAEXPAVObject@@PBUCoord3D@@M@Z
void HorseHordeContain0024DA80::rva0024DA80(Object *member, const Coord3D *pos, Real orientation)
{
	Coord3D goal = *pos;
	Coord3D myPos = *member->getPosition();
	Object *owner = m_object08;
	{
	AIUpdateInterface *ownerAI = owner->getAI();
	AIUpdateInterface *ai = member->getAI();
	if (!ownerAI || !ai)
		return;

	Rva0024DA80State *state = ownerAI->m_stateHolder30->m_state;
	if (state && state->m_id == 7)
	{
		((Gen_0024D1E0 *)member)->bfmePush(0);
		((Gen_0024D1E0 *)member)->bfmePush(0);
		m_byteE9 = TRUE;
	}

	Locomotor *locomotor = ai->getCurLocomotor();
	Locomotor *ownerLocomotor = ownerAI->getCurLocomotor();
	if (!locomotor || !ownerLocomotor)
		return;

	if (rva001b49c0((Obj001B49C0 *)member))
	{
		member->clearCondition(60);
		return;
	}

	if (!ownerAI->bfmeBlocksFormationRefresh())
	{
		ICoord2D cell = member->m_cellA4;
		if (member->m_cell9c.x >= 0 && member->m_cell9c.x == cell.x && member->m_cell9c.y == cell.y)
			goal = *member->getPosition();
	}

	Coord3D dest;
	Real dist;
	{
		Coord3D delta;
		delta.x = goal.x - myPos.x;
		delta.y = goal.y - myPos.y;
		delta.z = 0.0f;
		dist = delta.length();
	}
	{
	Coord3D target;
	Real speed = dist;

	if (ownerAI->getPath())
	{
		Rva001B7200PathPoint point;
		ownerAI->getPath()->computePointOnPath(owner, (Rva001B7200Locomotor *)ownerAI->getCurLocomotor(), &point, FALSE);
		speed = point.m_distance - ownerLocomotor->getPreferredHeight() + dist;
	}

	if (m_byte1fc)
		goto doIdle;
	if (ai->slot184() && ownerAI->slot184())
	{
	}
	else if (ownerAI->bfmeBlocksFormationRefresh() || ai->slot180())
	{
		if (ownerAI->slot184())
		{
doIdle:
			if (!ai->slot180() && !ai->slot184())
				ai->getCommand()->aiIdle(CMD_FROM_AI);
		}
		else if (!ai->slot18c())
			((BfmeInnerCPB *)ai->getCommand())->bfmeOneCPB(0, CMD_FROM_AI);
	}

	Real minDist = locomotor->rva001B8010(member);
	Real maxSpeed = locomotor->rva001B7E90(member);
	if (minDist > maxSpeed * 0.2f)
		minDist = maxSpeed * 0.2f;

	if (dist < minDist)
	{
		dest = goal;
		if (locomotor->rva00233D20() != 8)
		{
			dest.z = myPos.z;
			if (TheAI->pathfinder()->validMovementPosition(&dest, member->getLayer(), ai->m_locomotorSet1a8.surfaceMask10(), object08()))
				dest.z = TheTerrainLogic->getLayerHeight(dest.x, dest.y, member->getLayer(), 0, true);
		}
		member->setPosition(&dest);
		((Rva001B3F60Target *)member)->copy((Rva001B3F60Payload *)&dest);

		Real turn = orientation - member->m_orientation44;
		Real angle = normalizeAngle(turn);
		if (!m_byte1fc && fabs(angle) > 0.17453294f)
		{
			ai->slot1e4(orientation);
			m_byteE8 = TRUE;
			return;
		}

		member->clearCondition(60);
		ai->slot1e8();
		if (m_byte1fc)
		{
			Rva0024DA80MemberRecord *record = &m_records1d8[((BfmeAODHordeContainOwner *)this)->bfmeGetMemberIndex(member->m_int74)];
			if (record->m_state == 1)
				record->m_state = 3;
		}

		if (ownerAI->bfmeBlocksFormationRefresh())
		{
			m_byteE8 = TRUE;
			return;
		}

		if (!((Rva0023BE60Receiver *)this)->rva0023BE60(member))
		{
			if (!TheAI->pathfinder()->adjustDestination(member, ai->m_locomotorSet1a8, &dest, 0))
				return;
			ai->slot1f4(&dest);
			TheAI->pathfinder()->updateGoal(member, &dest, member->getLayer(),
				"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Contain\\HordeContain\\HorseHordeContain.cpp", 499);
			m_byteE8 = TRUE;
			return;
		}

		TheAI->pathfinder()->updateGoal(member, member->getPosition(), member->getLayer(),
			"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Contain\\HordeContain\\HorseHordeContain.cpp", 503);
		return;
	}

	Real preferredHeight = locomotor->getPreferredHeight();
	Real stopDist = locomotor->rva001B8010(member);
	if (preferredHeight == BfmeZeroRange && dist < stopDist)
		return;

	m_byteE8 = TRUE;
	if (!m_byte1fc)
		TheAI->pathfinder()->removeGoal(member);

	target = goal;
	if (m_byte204)
		ai->slot1d8(&target);
	else
		ai->slot1dc(&target);
	((Rva0026FE90DwordSlot *)ai)->set(*(Int *)&speed);
	ai->setDesiredSpeed(dist);

	member->setCondition(60);
	member->clearCondition(127);

	Bool raise = FALSE;
	if (((BFMESelectionStatusBits *)member)->test(0x80))
	{
		if (((WordBitTest000D2F40 *)&owner->m_conditions110)->test(0x80) || !ownerAI->bfmeBlocksFormationRefresh())
			raise = TRUE;
	}

	Real fastSpeed = maxSpeed * 0.66f;
	if (dist > preferredHeight && preferredHeight < fastSpeed)
	{
		member->clearCondition(128);
	}
	else if (dist < preferredHeight && preferredHeight < fastSpeed)
	{
		member->clearCondition(127);
		if (((WordBitTest000D2F40 *)&owner->m_conditions110)->test(0x80) || !ownerAI->bfmeBlocksFormationRefresh())
			member->setCondition(128);
		else
			member->clearCondition(128);
	}
	else
	{
		member->clearCondition(127);
		member->clearCondition(128);
	}

	if (raise && preferredHeight > BfmeZeroRange)
		member->setCondition(128);
	}
}
}
