// cl: /O2 /GR- /DNDEBUG /DWIN32 /MD /EHsc-
// Retail 0x001BC670 is the wings branch called by the Locomotor position
// maintainer at 0x001BC820. The BFME build passes only Object* here.

#include <math.h>

#pragma intrinsic(atan2)

typedef bool Bool;
typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Thing
{
public:
	Real getHeightAboveTerrain() const;

	char m_pad000[0x38];
	};

class Object : public Thing
{
public:
	Real m_x;
	Real m_y;
	Real m_z;
	Real m_orientation;
};

class Overridable
{
public:
	void *m_vtable;
	Overridable *m_nextOverride;
	Overridable *getFinalOverride();
};

class LocomotorTemplate : public Overridable
{
public:
	char m_pad008[0x60 - 0x08];
	Real m_circlingRadius;
};

class BfmeThingET
{
	char m_pad000[0x204];
};

class BfmeHostET
{
public:
	Real bfmeComputeET(BfmeThingET *thing, Real *out);
};

struct Rva001B59ScaleInfo
{
	char m_pad000[0x1d4];
	Real m_scale;
};

struct Rva001B59ScaleContext
{
	char m_pad000[0x204];
	Rva001B59ScaleInfo *m_info;
};

class Rva001B59FloatView
{
public:
	Real getScaledFirst(const Rva001B59ScaleContext *context) const;
};

struct Mat12
{
	char m_pad000[8];
	Real m_x;
	Real m_y;
	Real m_z;
	char m_pad014[0x34 - 0x14];
};

class BfmeSub1CC_EC3
{
public:
	void copyMatrixAndGo(Mat12 *matrix, int a, int b);
};

class BfmeSubC1054
{
public:
	char m_pad000[4];
};

class BfmeD1054
{
public:
	void bfmeAdd1054(BfmeSubC1054 *item);
};

class BfmeQ1282
{
};

class BfmeA1282
{
public:
	void bfmeFinish1282(BfmeQ1282 *object, int a, int b, int c);
};

class Locomotor
{
	protected:
	void maintainCurrentPositionWings(Object *object);

	private:
	void *m_vtable;
	LocomotorTemplate *m_template;
	Coord3D m_maintainPos;
	char m_pad014[0x40 - 0x14];
	unsigned m_flags;
};

extern const Real BfmeZeroRange;
extern Real g_millisecondsToSeconds;

extern Real Cos(Real radians);
extern Real Sin(Real radians);

#define g_rva001B59AnglePositive (*(const Real *)0x0109df8c)
#define g_rva001B59AngleNegative (*(const Real *)0x0109df88)

void Locomotor::maintainCurrentPositionWings(Object *object)
{
	if (!(object->getHeightAboveTerrain() > BfmeZeroRange))
		return;

	__asm { or dword ptr [esi+40h], 10h }

	LocomotorTemplate *locoTemplate = m_template;
	if (locoTemplate && locoTemplate->m_nextOverride)
		locoTemplate = (LocomotorTemplate *)locoTemplate->m_nextOverride->getFinalOverride();

	Real turnRadius = locoTemplate->m_circlingRadius;
	if (turnRadius == BfmeZeroRange)
		turnRadius = ((BfmeHostET *)this)->bfmeComputeET((BfmeThingET *)object, 0);

	Real dx = m_maintainPos.x - object->m_x;
	Real dy = m_maintainPos.y - object->m_y;
	Real angle;
	if (fabs(dx) < g_millisecondsToSeconds && fabs(dy) < g_millisecondsToSeconds)
		angle = object->m_orientation;
	else
		angle = (Real)atan2(dy, dx);

	Real aim = g_rva001B59AnglePositive;
	if (turnRadius < BfmeZeroRange)
	{
		turnRadius = -turnRadius;
		aim = g_rva001B59AngleNegative;
	}
	angle += aim;

	Coord3D desiredPos = m_maintainPos;
	desiredPos.x += Cos(angle) * turnRadius;
	desiredPos.y += Sin(angle) * turnRadius;
	Real desiredSpeed = ((Rva001B59FloatView *)this)->getScaledFirst(
		(const Rva001B59ScaleContext *)object);
	((BfmeSub1CC_EC3 *)this)->copyMatrixAndGo((Mat12 *)object,
		(int)&desiredPos, 0);
	((BfmeD1054 *)object)->bfmeAdd1054((BfmeSubC1054 *)((char *)this + 0x64));
	((BfmeA1282 *)this)->bfmeFinish1282((BfmeQ1282 *)object,
		(int)&desiredPos, 0, *(int *)&desiredSpeed);
}
