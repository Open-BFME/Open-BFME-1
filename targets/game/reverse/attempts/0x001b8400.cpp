// cl: /O2 /GR- /DNDEBUG /DWIN32 /MD /EHsc- /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWDebug
// partial score=0.35 date=2026-09-17
//
// BFME retail 0x001B8400, reached through the proven
// ?finish@BfmeSub1CC_EC3@@QAEXPAUMat12@@HHH@Z ILT at 0x00033861.  The
// caller at 0x001B9C50 supplies an Object/Mat12 view, a goal Coord3D pointer,
// the max-turn-rate bits returned by the preceding ILT, and an optional angle
// output pointer.

#include <math.h>
#include "../../../../Libraries/Source/WWVegas/WWMath/vector4.h"

#pragma intrinsic(atan2)

typedef bool Bool;
typedef float Real;

extern const Real BfmeZeroRange;

// The retail body was built against the BFME Matrix3D inline definition.  Its
// identity rows use the canonical zero object, which is observable in the
// expanded x87 sequence (the retail code loads 0x01075350 repeatedly instead
// of folding those terms away).  Keep that source-level detail local to this
// reconstruction rather than changing the shared WWMath header.
__forceinline Real rva001B8400Submul(const Vector4 &row,
	Real x, Real y, Real z)
{
	return row.X * x + row.Y * y + row.Z * z;
}

class Matrix3D
{
public:
	Vector4 Row[3];

	__forceinline Matrix3D() {}
	__forceinline explicit Matrix3D(bool init)
	{
		if (init)
			Make_Identity();
	}

	__forceinline Vector4 &operator[](int index)
	{
		return Row[index];
	}

	__forceinline const Vector4 &operator[](int index) const
	{
		return Row[index];
	}

	__forceinline void Make_Identity()
	{
		Row[0].Set(1.0f, BfmeZeroRange, BfmeZeroRange, BfmeZeroRange);
		Row[1].Set(BfmeZeroRange, 1.0f, BfmeZeroRange, BfmeZeroRange);
		Row[2].Set(BfmeZeroRange, BfmeZeroRange, 1.0f, BfmeZeroRange);
	}

	__forceinline void Translate(Real x, Real y, Real z)
	{
		Row[0][3] += (Real)(Row[0][0] * x + Row[0][1] * y + Row[0][2] * z);
		Row[1][3] += (Real)(Row[1][0] * x + Row[1][1] * y + Row[1][2] * z);
		Row[2][3] += (Real)(Row[2][0] * x + Row[2][1] * y + Row[2][2] * z);
	}

	__forceinline void In_Place_Pre_Rotate_Z(Real theta)
	{
		Real tmp1;
		Real tmp2;
		Real c = (Real)cosf(theta);
		Real s = (Real)sinf(theta);

		tmp1 = Row[0][0];
		tmp2 = Row[1][0];
		Row[0][0] = (Real)(c * tmp1 - s * tmp2);
		Row[1][0] = (Real)(s * tmp1 + c * tmp2);

		tmp1 = Row[0][1];
		tmp2 = Row[1][1];
		Row[0][1] = (Real)(c * tmp1 - s * tmp2);
		Row[1][1] = (Real)(s * tmp1 + c * tmp2);

		tmp1 = Row[0][2];
		tmp2 = Row[1][2];
		Row[0][2] = (Real)(c * tmp1 - s * tmp2);
		Row[1][2] = (Real)(s * tmp1 + c * tmp2);
	}

	__forceinline void mul(const Matrix3D &a, const Matrix3D &b)
	{
		Real tmp1;
		Real tmp2;
		Real tmp3;

		tmp1 = b.Row[0].X;
		tmp2 = b.Row[1].X;
		tmp3 = b.Row[2].X;
		Row[0].X = rva001B8400Submul(a.Row[0], tmp1, tmp2, tmp3);
		Row[1].X = rva001B8400Submul(a.Row[1], tmp1, tmp2, tmp3);
		Row[2].X = rva001B8400Submul(a.Row[2], tmp1, tmp2, tmp3);

		tmp1 = b.Row[0].Y;
		tmp2 = b.Row[1].Y;
		tmp3 = b.Row[2].Y;
		Row[0].Y = rva001B8400Submul(a.Row[0], tmp1, tmp2, tmp3);
		Row[1].Y = rva001B8400Submul(a.Row[1], tmp1, tmp2, tmp3);
		Row[2].Y = rva001B8400Submul(a.Row[2], tmp1, tmp2, tmp3);

		tmp1 = b.Row[0].Z;
		tmp2 = b.Row[1].Z;
		tmp3 = b.Row[2].Z;
		Row[0].Z = rva001B8400Submul(a.Row[0], tmp1, tmp2, tmp3);
		Row[1].Z = rva001B8400Submul(a.Row[1], tmp1, tmp2, tmp3);
		Row[2].Z = rva001B8400Submul(a.Row[2], tmp1, tmp2, tmp3);

		tmp1 = b.Row[0].W;
		tmp2 = b.Row[1].W;
		tmp3 = b.Row[2].W;
		Row[0].W = rva001B8400Submul(a.Row[0], tmp1, tmp2, tmp3) + a.Row[0].W;
		Row[1].W = rva001B8400Submul(a.Row[1], tmp1, tmp2, tmp3) + a.Row[1].W;
		Row[2].W = rva001B8400Submul(a.Row[2], tmp1, tmp2, tmp3) + a.Row[2].W;
	}
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

// The retail call is the printed ILT, not the already-landed body spelling.
class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	char m_pad000[4];
	const Overridable *m_nextOverride;
};

class LocomotorTemplate : public Overridable
{
public:
	char m_pad008[0x30];
	Real m_turnThreshold;
	char m_pad03c[0x34];
	unsigned int m_appearance;
	char m_pad074[0x44];
	Real m_turnPivotOffset;
	char m_pad0bc[0x41];
	unsigned char m_field0fd;
};

class Thing
{
public:
	const Coord3D *getUnitDirectionVector2D() const;
};

class BfmeQueryCall
{
public:
	Real query(void *value);
};

class BfmeSetBlockCall
{
public:
	void setBlock(const Matrix3D *block);
};

class BfmeNotifyCall
{
public:
	void notifyModelConditionChanged();
};

class BfmeI1166Call
{
public:
	BfmeI1166Call(int tag, unsigned int first, unsigned int second);

	unsigned int m_words[10];
};

class BfmeClearCall
{
public:
	void clear(const BfmeI1166Call *flags);
};

#pragma comment(linker, "/alternatename:?getFinalOverride@Overridable@@QBEPBV1@XZ=?j_000022bb@@YAXXZ")
#pragma comment(linker, "/alternatename:?getUnitDirectionVector2D@Thing@@QBEPBUCoord3D@@XZ=?j_00040246@@YAXXZ")
#pragma comment(linker, "/alternatename:?query@BfmeQueryCall@@QAEMPAX@Z=?j_000230ab@@YAXXZ")
#pragma comment(linker, "/alternatename:?setBlock@BfmeSetBlockCall@@QAEXPBVMatrix3D@@@Z=?j_00033bae@@YAXXZ")
#pragma comment(linker, "/alternatename:?notifyModelConditionChanged@BfmeNotifyCall@@QAEXXZ=?j_0002191d@@YAXXZ")
#pragma comment(linker, "/alternatename:??0BfmeI1166Call@@QAE@HII@Z=?j_00004048@@YAXXZ")
#pragma comment(linker, "/alternatename:?clear@BfmeClearCall@@QAEXPBVBfmeI1166Call@@@Z=?j_0001a9dd@@YAXXZ")
#pragma comment(linker, "/alternatename:?Rva001B8400Normalize@@YAMM@Z=?j_0000991c@@YAXXZ")

extern Real Rva001B8400Normalize(Real angle);

extern const Real g_bfmeScaleBK;
extern const Real BfmeZeroRange;
extern const Real g_bfmeK1253;

struct Mat12
{
	char m_pad000[8];
	Matrix3D m_transform;
	Coord3D m_position;
	Real m_orientation;
	char m_pad048[0x74];
	Real m_radius;
	char m_pad0c0[0x5c];
	unsigned int m_modelFlags11c;
	unsigned int m_modelFlags120;
	char m_pad124[0xe0];
	void *m_ai;
};

class BfmeAIInterface
{
public:
	virtual void slot000() = 0;
	virtual void slot001() = 0;
	virtual void slot002() = 0;
	virtual void slot003() = 0;
	virtual void slot004() = 0;
	virtual void slot005() = 0;
	virtual void slot006() = 0;
	virtual void slot007() = 0;
	virtual void slot008() = 0;
	virtual void slot009() = 0;
	virtual void slot010() = 0;
	virtual void slot011() = 0;
	virtual void slot012() = 0;
	virtual void slot013() = 0;
	virtual void slot014() = 0;
	virtual void slot015() = 0;
	virtual void slot016() = 0;
	virtual void slot017() = 0;
	virtual void slot018() = 0;
	virtual void slot019() = 0;
	virtual void slot020() = 0;
	virtual void slot021() = 0;
	virtual void slot022() = 0;
	virtual void slot023() = 0;
	virtual void slot024() = 0;
	virtual void slot025() = 0;
	virtual void slot026() = 0;
	virtual void slot027() = 0;
	virtual void slot028() = 0;
	virtual void slot029() = 0;
	virtual void slot030() = 0;
	virtual void slot031() = 0;
	virtual void slot032() = 0;
	virtual void slot033() = 0;
	virtual void slot034() = 0;
	virtual void slot035() = 0;
	virtual void slot036() = 0;
	virtual void slot037() = 0;
	virtual void slot038() = 0;
	virtual void slot039() = 0;
	virtual void slot040() = 0;
	virtual void slot041() = 0;
	virtual void slot042() = 0;
	virtual void slot043() = 0;
	virtual void slot044() = 0;
	virtual void slot045() = 0;
	virtual void slot046() = 0;
	virtual void slot047() = 0;
	virtual void slot048() = 0;
	virtual void slot049() = 0;
	virtual void slot050() = 0;
	virtual void slot051() = 0;
	virtual void slot052() = 0;
	virtual void slot053() = 0;
	virtual void slot054() = 0;
	virtual void slot055() = 0;
	virtual void slot056() = 0;
	virtual void slot057() = 0;
	virtual void slot058() = 0;
	virtual void slot059() = 0;
	virtual void slot060() = 0;
	virtual void slot061() = 0;
	virtual void slot062() = 0;
	virtual void slot063() = 0;
	virtual void slot064() = 0;
	virtual void slot065() = 0;
	virtual void slot066() = 0;
	virtual void slot067() = 0;
	virtual void slot068() = 0;
	virtual void slot069() = 0;
	virtual void slot070() = 0;
	virtual void slot071() = 0;
	virtual void slot072() = 0;
	virtual void slot073() = 0;
	virtual void slot074() = 0;
	virtual void slot075() = 0;
	virtual void slot076() = 0;
	virtual void slot077() = 0;
	virtual void slot078() = 0;
	virtual void slot079() = 0;
	virtual void slot080() = 0;
	virtual void slot081() = 0;
	virtual void slot082() = 0;
	virtual void slot083() = 0;
	virtual void slot084() = 0;
	virtual void slot085() = 0;
	virtual void slot086() = 0;
	virtual void slot087() = 0;
	virtual void slot088() = 0;
	virtual void slot089() = 0;
	virtual void slot090() = 0;
	virtual void slot091() = 0;
	virtual void slot092() = 0;
	virtual void slot093() = 0;
	virtual void slot094() = 0;
	virtual void slot095() = 0;
	virtual void slot096() = 0;
	virtual void slot097() = 0;
	virtual void slot098() = 0;
	virtual void slot099() = 0;
	virtual void slot100() = 0;
	virtual void slot101() = 0;
	virtual void slot102() = 0;
	virtual void slot103() = 0;
	virtual void slot104() = 0;
	virtual void slot105() = 0;
	virtual void slot106() = 0;
	virtual void slot107() = 0;
	virtual void slot108() = 0;
	virtual void slot109() = 0;
	virtual void slot110() = 0;
	virtual void slot111() = 0;
	virtual void slot112() = 0;
	virtual void slot113() = 0;
	virtual void slot114() = 0;
	virtual void slot115() = 0;
	virtual void slot116() = 0;
	virtual void slot117() = 0;
	virtual void slot118() = 0;
	virtual void slot119() = 0;
	virtual void slot120() = 0;
	virtual void slot121() = 0;
	virtual void slot122() = 0;
	virtual void slot123() = 0;
	virtual Bool condition() = 0;
};

class BfmeSub1CC_EC3
{
public:
	void finish(Mat12 *object, int goalBits, int maxTurnRateBits, int outputBits);

private:
	char m_pad000[4];
	LocomotorTemplate *m_template;
	char m_pad008[0x34];
	Real m_value;
	char m_pad040[0x24];
	Matrix3D m_savedTransform;
	unsigned char m_field094;
	unsigned char m_field095;
	unsigned short m_field096;
	unsigned int m_field098;
	unsigned int m_field09c;
	unsigned int m_field0a0;
	int m_turnState;
};

void BfmeSub1CC_EC3::finish(Mat12 *object, int goalBits,
	int maxTurnRateBits, int outputBits)
{
	const Coord3D *goal = (const Coord3D *)(unsigned int)goalBits;
	Real maxTurnRate = *(Real *)&maxTurnRateBits;
	Real angle = object->m_orientation;

	LocomotorTemplate *locoTemplate = (LocomotorTemplate *)m_template;
	if (locoTemplate != 0 && locoTemplate->m_nextOverride != 0)
	{
		locoTemplate = (LocomotorTemplate *)locoTemplate->m_nextOverride->getFinalOverride();
	}
	Real turnPointOffset = locoTemplate->m_turnPivotOffset;

	locoTemplate = (LocomotorTemplate *)m_template;
	if (locoTemplate != 0 && locoTemplate->m_nextOverride != 0)
	{
		locoTemplate = (LocomotorTemplate *)locoTemplate->m_nextOverride->getFinalOverride();
	}
	Real threshold = locoTemplate->m_turnThreshold;
	if (m_field095 != 0)
		threshold *= *(const Real *)0x0109df58;

	Bool aiCondition = false;
	void *ai = object->m_ai;
	if (ai != 0)
		aiCondition = ((BfmeAIInterface *)ai)->condition();

	m_turnState = 0;

	locoTemplate = (LocomotorTemplate *)m_template;
	if (locoTemplate != 0 && locoTemplate->m_nextOverride != 0)
	{
		locoTemplate = (LocomotorTemplate *)locoTemplate->m_nextOverride->getFinalOverride();
	}
	turnPointOffset = locoTemplate->m_turnPivotOffset * object->m_radius;
	Real pivotX = object->m_position.x;
	Real pivotY = object->m_position.y;

	if (locoTemplate->m_appearance == 5)
	{
		const Coord3D *direction = ((Thing *)object)->getUnitDirectionVector2D();
		pivotX = turnPointOffset * direction->x + pivotX;
		pivotY = turnPointOffset * direction->y + pivotY;

		Real dx = goal->x - pivotX;
		Real dy = goal->y - pivotY;
		if (fabs(dx) < g_bfmeScaleBK && fabs(dy) < g_bfmeScaleBK)
			return;

		Real amount = Rva001B8400Normalize((Real)atan2(dy, dx) - angle);
		Real *relAngle = (Real *)(unsigned int)outputBits;
		if (relAngle != 0)
			*relAngle = amount;

		if (amount > BfmeZeroRange)
		{
			LocomotorTemplate *turnTemplate = (LocomotorTemplate *)m_template;
			if (turnTemplate != 0 && turnTemplate->m_nextOverride != 0)
			{
				turnTemplate = (LocomotorTemplate *)turnTemplate->m_nextOverride->getFinalOverride();
			}
			if (amount > turnTemplate->m_turnThreshold)
				m_turnState = 1;
			if (amount > maxTurnRate)
				amount = maxTurnRate;
		}
		else
		{
			LocomotorTemplate *turnTemplate = (LocomotorTemplate *)m_template;
			if (turnTemplate != 0 && turnTemplate->m_nextOverride != 0)
			{
				turnTemplate = (LocomotorTemplate *)turnTemplate->m_nextOverride->getFinalOverride();
			}
			if (amount < -turnTemplate->m_turnThreshold)
				m_turnState = -1;
			if (amount < -maxTurnRate)
				amount = -maxTurnRate;
		}

		Matrix3D matrix;
		Matrix3D temporary(1);
		temporary.Translate(pivotX, pivotY, BfmeZeroRange);
		temporary.In_Place_Pre_Rotate_Z(amount);
		temporary.Translate(-pivotX, -pivotY, BfmeZeroRange);
		matrix.mul(temporary, object->m_transform);
		((BfmeSetBlockCall *)this)->setBlock(&matrix);
	}
	else
	{
		const Coord3D *direction = ((Thing *)object)->getUnitDirectionVector2D();
		pivotX = turnPointOffset * direction->x + pivotX;
		pivotY = turnPointOffset * direction->y + pivotY;

		Real dx = goal->x - pivotX;
		Real dy = goal->y - pivotY;
		if (fabs(dx) < g_bfmeScaleBK && fabs(dy) < g_bfmeScaleBK)
			return;

		Real amount = Rva001B8400Normalize((Real)atan2(dy, dx) - angle);
		Real *relAngle = (Real *)(unsigned int)outputBits;
		if (relAngle != 0)
			*relAngle = amount;

		if (amount > BfmeZeroRange)
		{
			if (amount > threshold)
				m_turnState = 1;
			if (amount > maxTurnRate)
				amount = maxTurnRate;
		}
		else
		{
			if (amount < -threshold)
				m_turnState = -1;
			if (amount < -maxTurnRate)
				amount = -maxTurnRate;
		}

		if (aiCondition != false)
		{
			Real halfAmount = amount * g_bfmeK1253;
			Real cosine = (Real)cosf(halfAmount);
			Real sine = (Real)sinf(halfAmount);
			Real old64 = m_savedTransform[0][0];
			Real old74 = m_savedTransform[1][0];
			m_savedTransform[0][0] = old64 * cosine - old74 * sine;
			m_savedTransform[1][0] = old64 * sine + old74 * cosine;
			Real old68 = m_savedTransform[0][1];
			Real old78 = m_savedTransform[1][1];
			m_savedTransform[0][1] = old68 * cosine - old78 * sine;
			m_savedTransform[1][1] = old68 * sine + old78 * cosine;
			Real old6c = m_savedTransform[0][2];
			Real old7c = m_savedTransform[1][2];
			m_savedTransform[0][2] = old6c * cosine - old7c * sine;
			m_savedTransform[1][2] = old6c * sine + old7c * cosine;
		}
	}

	Real limit = m_value;
	Real queryHalf = ((BfmeQueryCall *)this)->query(object) * g_bfmeK1253;
	Bool keepMoving = true;
	if (limit > queryHalf)
	{
		LocomotorTemplate *limitTemplate = (LocomotorTemplate *)m_template;
		if (limitTemplate != 0 && limitTemplate->m_nextOverride != 0)
		{
			limitTemplate = (LocomotorTemplate *)limitTemplate->m_nextOverride->getFinalOverride();
		}
		if (limitTemplate->m_field0fd == 0)
			keepMoving = false;
		if (aiCondition != false)
			keepMoving = false;
	}

	if (m_field095 == 0)
	{
		if ((object->m_modelFlags11c & 0x20000000) != 0)
		{
			object->m_modelFlags11c &= 0xdfffffff;
			((BfmeNotifyCall *)object)->notifyModelConditionChanged();
		}
		if ((object->m_modelFlags11c & 0x40000000) != 0)
		{
			object->m_modelFlags11c &= 0xbfffffff;
			((BfmeNotifyCall *)object)->notifyModelConditionChanged();
		}
		if ((object->m_modelFlags120 & 2) != 0)
		{
			object->m_modelFlags120 &= 0xfffffffd;
			((BfmeNotifyCall *)object)->notifyModelConditionChanged();
		}
		if ((object->m_modelFlags120 & 4) != 0)
		{
			object->m_modelFlags120 &= 0xfffffffb;
			((BfmeNotifyCall *)object)->notifyModelConditionChanged();
		}
	}

	if (keepMoving != false)
	{
		if (m_turnState == -1)
		{
			if (limit > queryHalf)
			{
				BfmeI1166Call flags(0, 0x82, 0x7e);
				((BfmeClearCall *)object)->clear(&flags);
				return;
			}
			if ((object->m_modelFlags11c & 0x40000000) == 0)
			{
				object->m_modelFlags11c |= 0x40000000;
				((BfmeNotifyCall *)object)->notifyModelConditionChanged();
			}
		}
		else if (m_turnState == 1)
		{
			if (limit > queryHalf)
			{
				BfmeI1166Call flags(0, 0x81, 0x7d);
				((BfmeClearCall *)object)->clear(&flags);
				return;
			}
			if ((object->m_modelFlags11c & 0x20000000) == 0)
			{
				object->m_modelFlags11c |= 0x20000000;
				((BfmeNotifyCall *)object)->notifyModelConditionChanged();
			}
		}
	}
}

