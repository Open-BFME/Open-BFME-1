// ?bfmeDoZA@BfmeOwnerZA@@QAEXPAX0HHHHPAMPAD@Z
// partial score=0.3 date=2026-09-27
#include <math.h>

typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

#define BFME_UNUSED_VIRTUALS_16(prefix) \
	virtual void prefix##0() = 0; virtual void prefix##1() = 0; \
	virtual void prefix##2() = 0; virtual void prefix##3() = 0; \
	virtual void prefix##4() = 0; virtual void prefix##5() = 0; \
	virtual void prefix##6() = 0; virtual void prefix##7() = 0; \
	virtual void prefix##8() = 0; virtual void prefix##9() = 0; \
	virtual void prefix##a() = 0; virtual void prefix##b() = 0; \
	virtual void prefix##c() = 0; virtual void prefix##d() = 0; \
	virtual void prefix##e() = 0; virtual void prefix##f() = 0

class BfmeOwnerZA
{
public:
	BFME_UNUSED_VIRTUALS_16(unused000_);
	BFME_UNUSED_VIRTUALS_16(unused040_);
	BFME_UNUSED_VIRTUALS_16(unused080_);
	BFME_UNUSED_VIRTUALS_16(unused0c0_);
	BFME_UNUSED_VIRTUALS_16(unused100_);
	BFME_UNUSED_VIRTUALS_16(unused140_);
	BFME_UNUSED_VIRTUALS_16(unused180_);
	BFME_UNUSED_VIRTUALS_16(unused1c0_);
	BFME_UNUSED_VIRTUALS_16(unused200_);
	virtual void unused240_0() = 0;
	virtual void unused240_1() = 0;
	virtual Real getHeightMapHeight(Real x, Real y, Coord3D *normal) const;

	int bfmeTryZA(void *a, void *b, float value);
	void bfmeDoZA(void *a, void *b, int mode, int zero, int amount, int flags,
	              float *out, char *ok);
};

#pragma intrinsic(atan2, fabs)

#define BfmeCoordinateScale (*(const Real *)0x01075C74)
#define BfmeAngleScale (*(const Real *)0x0109ECC0)
#define BfmeAngleQuarterTurn (*(const Real *)0x0111D874)

int BfmeOwnerZA::bfmeTryZA(void *a, void *b, float value)
{
	char ok = 0;
	float out;

	bfmeDoZA(a, b, 0x100, 0, (int)value, 0, &out, &ok);

	return ok == 0 ? 1 : 0;
}

void BfmeOwnerZA::bfmeDoZA(void *a, void *b, int mode, int zero,
	int amount, int flags, float *out, char *ok)
{
	char *heightOK = reinterpret_cast<char *>(out);
	Coord3D normal;
	Real xPos;
	Real yPos;
	BfmeOwnerZA *owner;

	yPos = (Real)(int)(unsigned int)(size_t)b * BfmeCoordinateScale;
	*heightOK = 1;
	xPos = (Real)(int)(unsigned int)(size_t)a * BfmeCoordinateScale;
	*ok = 1;
	owner = this;
	{
		int height = (int)owner->getHeightMapHeight(xPos, yPos, &normal);
		if (height < zero || height > mode)
			*heightOK = 0;
	}
	{
		Real xAngle;
		Real yAngle;
		xAngle = (Real)fabs(BfmeAngleQuarterTurn -
			(Real)atan2(normal.z, normal.x) * BfmeAngleScale);
		yAngle = (Real)fabs(BfmeAngleQuarterTurn -
			(Real)atan2(normal.z, normal.y) * BfmeAngleScale);
		if (xAngle < flags || xAngle > amount || yAngle < flags || yAngle > amount)
			*ok = 0;
	}

	a = (void *)((unsigned int)(size_t)a + 1);
	xPos = (Real)(int)(unsigned int)(size_t)a * BfmeCoordinateScale;
	{
		int height = (int)owner->getHeightMapHeight(xPos, yPos, &normal);
		if (height < zero || height > mode)
			*heightOK = 0;
	}
	{
		Real xAngle;
		Real yAngle;
		xAngle = (Real)fabs(BfmeAngleQuarterTurn -
			(Real)atan2(normal.z, normal.x) * BfmeAngleScale);
		yAngle = (Real)fabs(BfmeAngleQuarterTurn -
			(Real)atan2(normal.z, normal.y) * BfmeAngleScale);
		if (xAngle < flags || xAngle > amount || yAngle < flags || yAngle > amount)
			*ok = 0;
	}

	b = (void *)((unsigned int)(size_t)b + 1);
	yPos = (Real)(int)(unsigned int)(size_t)b * BfmeCoordinateScale;
	{
		int height = (int)owner->getHeightMapHeight(xPos, yPos, &normal);
		if (height < zero || height > mode)
			*heightOK = 0;
	}
	{
		Real xAngle;
		Real yAngle;
		xAngle = (Real)fabs(BfmeAngleQuarterTurn -
			(Real)atan2(normal.z, normal.x) * BfmeAngleScale);
		yAngle = (Real)fabs(BfmeAngleQuarterTurn -
			(Real)atan2(normal.z, normal.y) * BfmeAngleScale);
		if (xAngle < flags || xAngle > amount || yAngle < flags || yAngle > amount)
			*ok = 0;
	}

	a = (void *)((unsigned int)(size_t)a - 1);
	xPos = (Real)(int)(unsigned int)(size_t)a * BfmeCoordinateScale;
	{
		int height = (int)owner->getHeightMapHeight(xPos, yPos, &normal);
		if (height < zero || height > mode)
			*heightOK = 0;
	}
	{
		Real xAngle;
		Real yAngle;
		xAngle = (Real)fabs(BfmeAngleQuarterTurn -
			(Real)atan2(normal.z, normal.x) * BfmeAngleScale);
		yAngle = (Real)fabs(BfmeAngleQuarterTurn -
			(Real)atan2(normal.z, normal.y) * BfmeAngleScale);
		if (xAngle < flags || xAngle > amount || yAngle < flags || yAngle > amount)
			*ok = 0;
	}
}

#undef BfmeAngleQuarterTurn
#undef BfmeAngleScale
#undef BfmeCoordinateScale
#undef BFME_UNUSED_VIRTUALS_16
