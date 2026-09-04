// ?attackOptimizedTarget@AIStateTargetDispatch@@QAEXPAVThing@@@Z
// partial score=0.96 date=2026-09-04
// cl: /DNDEBUG /MD /EHs-c-
// AIStateTargetDispatch::attackOptimizedTarget — retail 0x0027E070 / 194B.
// 186B / 194B: prologue, regs (ebx=target, edi=m_ai@+0x204, ebp=this,
// esi=this+8), all six calls, terrain vslot +0xBC, and integer x/y spill
// match. Tail is the only miss: ours `fld y; fmul [eax+4]; fld x; fmul [eax];
// faddp; fcomp; test; jne` vs retail `fld [eax]; fld [eax+4]; fld y;
// fmul st(1); fxch st(2); fmul x; faddp st(2); fxch; fcomp; fstp; test; jnp`.
// Tried Coord3D/Coord2D copies, tx/ty temps, <= invert, /O1 /G6 /Op /Oi —
// all keep the two-operand memory-fmul form. Next lever is whatever forces
// both pointer floats onto the x87 stack before the first multiply.
// Dump sibling of BoneFXUpdate::initTimes in Code/gen_asm/d_0027db50.asm.
// Caller: AIUpdateTargetDispatch::attackTarget (AIUpdateTargetDispatch_Thunk.cpp)
// when the owning Thing is KINDOF_BFME_6C.  this+8 is the owning Object*;
// target+0x204 is the other unit's AI (same BfmeHordeMember refresh predicate
// used by HordeContain / PathfindMoveAllies).  Continues into
// attackOrdinaryTarget when both units face the same way (2D dir dot > 0).
// upstream: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL = 1,
	ALLIES = 2
};

enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_GROUND = 1
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

class BfmeHordeMember
{
public:
	bool bfmeBlocksFormationRefresh();
};

class Thing;
class Object;

class AIStateTargetDispatch : public BfmeHordeMember
{
public:
	void attackOptimizedTarget(Thing *target);
	void attackOrdinaryTarget(Thing *target);

	unsigned char m_beforeObject[8];
	Object *m_object;
};

class Thing
{
public:
	const Coord3D *getUnitDirectionVector2D() const;

	unsigned char m_beforePos[0x38];
	Coord3D m_pos;
	unsigned char m_beforeAI[0x204 - 0x44];
	BfmeHordeMember *m_ai;
};

class Object : public Thing
{
public:
	Relationship getRelationship(const Object *that) const;
	int getLayer() const;
};

class TerrainLogic
{
public:
	virtual void pad00();
	virtual void pad01();
	virtual void pad02();
	virtual void pad03();
	virtual void pad04();
	virtual void pad05();
	virtual void pad06();
	virtual void pad07();
	virtual void pad08();
	virtual void pad09();
	virtual void pad10();
	virtual void pad11();
	virtual void pad12();
	virtual void pad13();
	virtual void pad14();
	virtual void pad15();
	virtual void pad16();
	virtual void pad17();
	virtual void pad18();
	virtual void pad19();
	virtual void pad20();
	virtual void pad21();
	virtual void pad22();
	virtual void pad23();
	virtual void pad24();
	virtual void pad25();
	virtual void pad26();
	virtual void pad27();
	virtual void pad28();
	virtual void pad29();
	virtual void pad30();
	virtual void pad31();
	virtual void pad32();
	virtual void pad33();
	virtual void pad34();
	virtual void pad35();
	virtual void pad36();
	virtual void pad37();
	virtual void pad38();
	virtual void pad39();
	virtual void pad40();
	virtual void pad41();
	virtual void pad42();
	virtual void pad43();
	virtual void pad44();
	virtual void pad45();
	virtual void pad46();
	virtual bool probePosition(const Coord3D *pos);
};

TerrainLogic *TheTerrainLogic;

void AIStateTargetDispatch::attackOptimizedTarget(Thing *target)
{
	BfmeHordeMember *otherAI = target->m_ai;
	if (!otherAI)
		return;

	Object *self = m_object;
	bool selfBlocks = bfmeBlocksFormationRefresh();
	bool otherBlocks = otherAI->bfmeBlocksFormationRefresh();
	if (self->getRelationship(static_cast<Object *>(target)) != ALLIES)
		return;
	if (self->getLayer() != LAYER_GROUND)
		return;
	if (TheTerrainLogic->probePosition(&self->m_pos))
		return;
	if (!selfBlocks)
		return;
	if (!otherBlocks)
		return;

	const Coord3D *selfDir = self->getUnitDirectionVector2D();
	Coord3D dir;
	dir.x = selfDir->x;
	dir.y = selfDir->y;
	dir.z = selfDir->z;
	const Coord3D *targetDir = target->getUnitDirectionVector2D();
	if (targetDir->x * dir.x + targetDir->y * dir.y > 0.0f)
		attackOrdinaryTarget(target);
}
