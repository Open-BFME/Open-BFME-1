// ?finish@BfmeSub1CC_EC3@@QAEXPAUMat12@@HHH@Z
// partial score=0.6 date=2026-09-28
// cl: /DNDEBUG /MD /Igame/GameEngine/Source/GameLogic/Object /Igame/Libraries/Source/WWVegas/WWMath /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
// partial: retail 0x001B8400, 1878 B, thiscall ret 0x10. Banked 2026-09-28 (opus-5.5).
// Caller: Locomotor rotate-toward at 0x001B9C50 (?copyMatrixAndGo@BfmeSub1CC_EC3)
// through ILT 0x00033861; prep there is the matched Locomotor::getMaxTurnRate,
// so this is the BFME form of ZH Locomotor::rotateObjAroundLocoPivot (void, the
// turn goes to Locomotor+0xA4). Model-condition bits 125/126/129/130 are
// TURN_LEFT/TURN_RIGHT/TURN_LEFT_HIGH_SPEED/TURN_RIGHT_HIGH_SPEED (name table
// VA 0x012A6918). bfmeClearYG (0x001B6EB0) is clearAndSet(empty, set), i.e. a set.
// 0x01075350/0x01075C70/0x0107533C/0x0109DF58 are the float literals 0, 0.1, 0.5, 0.0625.
// Compiled 1885 B, 1260 differing non-reloc bytes, shape 0.932. Remaining:
//  * retail saves ebx AND ebp: ebp = 1 for the two m_turn0A4 = 1 stores and
//    later 0x40000000 (TURN_RIGHT mask); ours only saves ebx.
//  * offset/threshold stack slots swapped (retail 0x1C/0x18, ours 0x18/0x1C
//    in retail terms); position x/y load order.
//  * B-path In_Place_Pre_Rotate_Z row-1 multiply order (retail c*tmp2 first).
//  * mtx.mul row-1 submul order (retail Z,Y,X; ours X,Z,Y).
//  * tail merge of the two setModelConditionFlags calls (retail keeps the -1 copy).
// SHAPING HACKS (not original source): `volatile` on showTurn keeps it on the
// stack so the AI flag gets bl as in retail; `Real &amount = angle` reuses the
// angle slot for amount as retail does (plain `angle = ...` gives 1267/0.929).
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <bitset>
#include <math.h>
#define _OPERATOR_NEW_DEFINED_
#include "matrix3d.h"

typedef bool Bool;
typedef int Int;

struct Coord3D
{
	float x;
	float y;
	float z;
};

enum BogusInitType { kInit = 0 };

template <int NUMBITS>
class BitFlags
{
public:
	BitFlags(BogusInitType k, Int idx1, Int idx2);
	// The masked word, not a bool: retail keeps each mask in a register for
	// the test and the update that follows.
	unsigned int test(Int i) const { return m_bits[i >> 5] & (1u << (i & 31)); }
	void set(Int i) { m_bits[i >> 5] |= (1u << (i & 31)); }
	void reset(Int i) { m_bits[i >> 5] &= ~(1u << (i & 31)); }

private:
	unsigned int m_bits[(NUMBITS + 31) / 32];
};

typedef BitFlags<320> ModelConditionFlags;

#define BFME_HAVE_COORD3D
#define BFME_HAVE_MODELCONDITIONFLAGS
#define THING_TU_MEMBERS \
	const Coord3D *getUnitDirectionVector2D() const; \
	const Coord3D *getPosition() const { return &m_cachedPos; } \
	Real getOrientation() const { return m_cachedAngle; }
#define OBJECT_TU_MEMBERS \
	void notifyModelConditionChanged(); \
	void bfmeClearYG(const BitFlags<320> &set); \
	Real getBoundingCircleRadius() const { return *(const Real *)&m_geometryInfo[4]; }
#include "object.h"

class AIUpdateInterface
{
public:
	virtual void slot000() = 0; virtual void slot001() = 0; virtual void slot002() = 0; virtual void slot003() = 0;
	virtual void slot004() = 0; virtual void slot005() = 0; virtual void slot006() = 0; virtual void slot007() = 0;
	virtual void slot008() = 0; virtual void slot009() = 0; virtual void slot010() = 0; virtual void slot011() = 0;
	virtual void slot012() = 0; virtual void slot013() = 0; virtual void slot014() = 0; virtual void slot015() = 0;
	virtual void slot016() = 0; virtual void slot017() = 0; virtual void slot018() = 0; virtual void slot019() = 0;
	virtual void slot020() = 0; virtual void slot021() = 0; virtual void slot022() = 0; virtual void slot023() = 0;
	virtual void slot024() = 0; virtual void slot025() = 0; virtual void slot026() = 0; virtual void slot027() = 0;
	virtual void slot028() = 0; virtual void slot029() = 0; virtual void slot030() = 0; virtual void slot031() = 0;
	virtual void slot032() = 0; virtual void slot033() = 0; virtual void slot034() = 0; virtual void slot035() = 0;
	virtual void slot036() = 0; virtual void slot037() = 0; virtual void slot038() = 0; virtual void slot039() = 0;
	virtual void slot040() = 0; virtual void slot041() = 0; virtual void slot042() = 0; virtual void slot043() = 0;
	virtual void slot044() = 0; virtual void slot045() = 0; virtual void slot046() = 0; virtual void slot047() = 0;
	virtual void slot048() = 0; virtual void slot049() = 0; virtual void slot050() = 0; virtual void slot051() = 0;
	virtual void slot052() = 0; virtual void slot053() = 0; virtual void slot054() = 0; virtual void slot055() = 0;
	virtual void slot056() = 0; virtual void slot057() = 0; virtual void slot058() = 0; virtual void slot059() = 0;
	virtual void slot060() = 0; virtual void slot061() = 0; virtual void slot062() = 0; virtual void slot063() = 0;
	virtual void slot064() = 0; virtual void slot065() = 0; virtual void slot066() = 0; virtual void slot067() = 0;
	virtual void slot068() = 0; virtual void slot069() = 0; virtual void slot070() = 0; virtual void slot071() = 0;
	virtual void slot072() = 0; virtual void slot073() = 0; virtual void slot074() = 0; virtual void slot075() = 0;
	virtual void slot076() = 0; virtual void slot077() = 0; virtual void slot078() = 0; virtual void slot079() = 0;
	virtual void slot080() = 0; virtual void slot081() = 0; virtual void slot082() = 0; virtual void slot083() = 0;
	virtual void slot084() = 0; virtual void slot085() = 0; virtual void slot086() = 0; virtual void slot087() = 0;
	virtual void slot088() = 0; virtual void slot089() = 0; virtual void slot090() = 0; virtual void slot091() = 0;
	virtual void slot092() = 0; virtual void slot093() = 0; virtual void slot094() = 0; virtual void slot095() = 0;
	virtual void slot096() = 0; virtual void slot097() = 0; virtual void slot098() = 0; virtual void slot099() = 0;
	virtual void slot100() = 0; virtual void slot101() = 0; virtual void slot102() = 0; virtual void slot103() = 0;
	virtual void slot104() = 0; virtual void slot105() = 0; virtual void slot106() = 0; virtual void slot107() = 0;
	virtual void slot108() = 0; virtual void slot109() = 0; virtual void slot110() = 0; virtual void slot111() = 0;
	virtual void slot112() = 0; virtual void slot113() = 0; virtual void slot114() = 0; virtual void slot115() = 0;
	virtual void slot116() = 0; virtual void slot117() = 0; virtual void slot118() = 0; virtual void slot119() = 0;
	virtual void slot120() = 0; virtual void slot121() = 0; virtual void slot122() = 0; virtual void slot123() = 0;
	virtual Bool slot124_1F0() const = 0;
};

class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	unsigned char m_unmodelled000[4];
	const Overridable *m_nextOverride;
};

class LocomotorTemplate : public Overridable
{
public:
	unsigned char m_unmodelled008[0x30];
	Real m_turnThreshold038;
	unsigned char m_unmodelled03C[0x34];
	Int m_appearance;
	unsigned char m_unmodelled074[0x44];
	Real m_turnPivotOffset;
	unsigned char m_unmodelled0BC[0x41];
	Bool m_flag0FD;
};

class Gen_001B51C0;
class BfmeBlockQB;

extern Real normalizeAngle(Real angle);

#pragma comment(linker, "/alternatename:??0?$BitFlags@$0BEA@@@QAE@W4BogusInitType@@HH@Z=?j_00004048@@YAXXZ")
#pragma comment(linker, "/alternatename:?bfmeClearYG@Object@@QAEXABV?$BitFlags@$0BEA@@@@Z=?j_0001a9dd@@YAXXZ")
#pragma comment(linker, "/alternatename:?setTransform001B51C0@BfmeSub1CC_EC3@@QAEXPBVMatrix3D@@@Z=?j_00033bae@@YAXXZ")

struct Mat12;

#define ROT2EXPR (float)(c*tmp2 + s*tmp1)


enum
{
	MODELCONDITION_TURN_LEFT = 125,
	MODELCONDITION_TURN_RIGHT = 126,
	MODELCONDITION_TURN_LEFT_HIGH_SPEED = 129,
	MODELCONDITION_TURN_RIGHT_HIGH_SPEED = 130
};

static __forceinline void clearModelCondition(Object *object, Int bit)
{
	if (object->m_modelConditionFlags.test(bit))
	{
		object->m_modelConditionFlags.reset(bit);
		object->notifyModelConditionChanged();
	}
}

static __forceinline void setModelCondition(Object *object, Int bit)
{
	if (!object->m_modelConditionFlags.test(bit))
	{
		object->m_modelConditionFlags.set(bit);
		object->notifyModelConditionChanged();
	}
}

class BfmeSub1CC_EC3
{
public:
	void finish(Mat12 *object, int goalBits, int maxTurnRateBits, int relAngleBits);
	Real effectiveMaxSpeed(void *object);
	void setTransform001B51C0(const Matrix3D *mtx);

	const LocomotorTemplate *getTemplate() const
	{
		if (m_template != 0 && m_template->m_nextOverride != 0)
			return (const LocomotorTemplate *)m_template->m_nextOverride->getFinalOverride();
		return m_template;
	}

	unsigned char m_unmodelled000[4];
	const LocomotorTemplate *m_template;
	unsigned char m_unmodelled008[0x34];
	Real m_preferredHeight;
	unsigned char m_unmodelled040[0x24];
	Matrix3D m_transform064;
	unsigned char m_flag094;
	unsigned char m_flag095;
	unsigned char m_unmodelled096[0xE];
	Int m_turn0A4;
};

void BfmeSub1CC_EC3::finish(Mat12 *objectBits, int goalBits, int maxTurnRateBits, int relAngleBits)
{
	Object *obj = (Object *)objectBits;
	const Coord3D &goalPos = *(const Coord3D *)goalBits;
	Real maxTurnRate = *(Real *)&maxTurnRateBits;
	Real *relAngle = (Real *)relAngleBits;

	Real angle = obj->getOrientation();
	Real offset = getTemplate()->m_turnPivotOffset;
	Real threshold = getTemplate()->m_turnThreshold038;
	if (m_flag095)
		threshold *= 0.0625f;

	Bool aiFlag = (obj->m_ai != 0 && obj->m_ai->slot124_1F0()) ? true : false;

	m_turn0A4 = 0;

	Int appearance = getTemplate()->m_appearance;
	offset *= obj->getBoundingCircleRadius();
	Coord3D turnPos;
	turnPos.x = obj->getPosition()->x;
	turnPos.y = obj->getPosition()->y;

	if (appearance == 5)
	{
		const Coord3D *dir = obj->getUnitDirectionVector2D();
		turnPos.x += offset * dir->x;
		turnPos.y += offset * dir->y;
		Real dx = goalPos.x - turnPos.x;
		Real dy = goalPos.y - turnPos.y;
		if (fabs(dx) < 0.1f && fabs(dy) < 0.1f)
			return;
		Real desiredAngle = atan2(dy, dx);
		Real &amount = angle; amount = normalizeAngle(desiredAngle - angle);
		if (relAngle)
			*relAngle = amount;
		if (amount > 0.0f)
		{
			if (amount > getTemplate()->m_turnThreshold038)
				m_turn0A4 = 1;
			if (amount > maxTurnRate)
				amount = maxTurnRate;
		}
		else
		{
			if (amount < -getTemplate()->m_turnThreshold038)
				m_turn0A4 = -1;
			if (amount < -maxTurnRate)
				amount = -maxTurnRate;
		}

		Matrix3D mtx;
		Matrix3D tmp(1);
		tmp.Translate(turnPos.x, turnPos.y, 0);
		tmp.In_Place_Pre_Rotate_Z(amount);
		tmp.Translate(-turnPos.x, -turnPos.y, 0);
		mtx.mul(tmp, obj->m_transform);
		setTransform001B51C0(&mtx);
	}
	else
	{
		const Coord3D *dir = obj->getUnitDirectionVector2D();
		turnPos.x += offset * dir->x;
		turnPos.y += offset * dir->y;
		Real dx = goalPos.x - turnPos.x;
		Real dy = goalPos.y - turnPos.y;
		if (fabs(dx) < 0.1f && fabs(dy) < 0.1f)
			return;
		Real desiredAngle = atan2(dy, dx);
		Real amount = normalizeAngle(desiredAngle - angle);
		if (relAngle)
			*relAngle = amount;
		if (amount > 0.0f)
		{
			if (amount > threshold)
				m_turn0A4 = 1;
			if (amount > maxTurnRate)
				amount = maxTurnRate;
		}
		else
		{
			if (amount < -threshold)
				m_turn0A4 = -1;
			if (amount < -maxTurnRate)
				amount = -maxTurnRate;
		}
		if (aiFlag)
			amount *= 0.5f;
		{
			float tmp1, tmp2, c, s;
			c = cosf(amount);
			s = sinf(amount);
			tmp1 = m_transform064[0][0]; tmp2 = m_transform064[1][0];
			m_transform064[0][0] = (float)(c*tmp1 - s*tmp2);
			m_transform064[1][0] = ROT2EXPR;
			tmp1 = m_transform064[0][1]; tmp2 = m_transform064[1][1];
			m_transform064[0][1] = (float)(c*tmp1 - s*tmp2);
			m_transform064[1][1] = ROT2EXPR;
			tmp1 = m_transform064[0][2]; tmp2 = m_transform064[1][2];
			m_transform064[0][2] = (float)(c*tmp1 - s*tmp2);
			m_transform064[1][2] = ROT2EXPR;
		}
	}

	Real speed = m_preferredHeight;
	Real halfMaxSpeed = effectiveMaxSpeed(obj) * 0.5f;
	volatile Bool showTurn = true;
	if (speed > halfMaxSpeed && !getTemplate()->m_flag0FD)
		showTurn = false;
	if (aiFlag)
		showTurn = false;

	if (!m_flag095)
	{
		clearModelCondition(obj, MODELCONDITION_TURN_LEFT);
		clearModelCondition(obj, MODELCONDITION_TURN_RIGHT);
		clearModelCondition(obj, MODELCONDITION_TURN_LEFT_HIGH_SPEED);
		clearModelCondition(obj, MODELCONDITION_TURN_RIGHT_HIGH_SPEED);
	}

	if (showTurn)
	{
		if (m_turn0A4 == -1)
		{
			if (speed > halfMaxSpeed)
			{
				obj->bfmeClearYG(ModelConditionFlags(kInit, MODELCONDITION_TURN_RIGHT_HIGH_SPEED, MODELCONDITION_TURN_RIGHT));
				return;
			}
			setModelCondition(obj, MODELCONDITION_TURN_RIGHT);
		}
		else if (m_turn0A4 == 1)
		{
			if (speed > halfMaxSpeed)
			{
				obj->bfmeClearYG(ModelConditionFlags(kInit, MODELCONDITION_TURN_LEFT_HIGH_SPEED, MODELCONDITION_TURN_LEFT));
				return;
			}
			setModelCondition(obj, MODELCONDITION_TURN_LEFT);
		}
	}
}
