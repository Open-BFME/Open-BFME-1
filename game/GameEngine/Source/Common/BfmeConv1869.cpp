// BFME terrain cell probes on the height-map render object (vtable slot +0x248 is
// BaseHeightMapRenderObjClass::getHeightMapHeight); the owner keeps its placeholder name.
#include <math.h>

typedef float Real;

#include "../../../Libraries/Include/Lib/Coord3D.h"

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

#define BfmeCoordinateScale 10.0f
#define BfmeAngleScale 57.295776f
#define BfmeAngleQuarterTurn 90.0f

int BfmeOwnerZA::bfmeTryZA(void *a, void *b, float value)
{
	char ok = 0;
	float out;

	bfmeDoZA(a, b, 0x100, 0, (int)value, 0, &out, &ok);

	return ok == 0 ? 1 : 0;
}

// Sets *out (as a byte) when all four cell corners lie inside [zero, mode] height and
// *ok when every corner's normal angles lie inside [flags, amount] degrees.
void BfmeOwnerZA::bfmeDoZA(void *a, void *b, int mode, int zero,
	int amount, int flags, float *out, char *ok)
{
	char *heightOK = reinterpret_cast<char *>(out);
	Coord3D normal;
	int height;
	Real xAngle;
	Real yAngle;

	Real yPos = (Real)(int)b * BfmeCoordinateScale;
	*heightOK = 1;
	Real xPos = (Real)(int)a * BfmeCoordinateScale;
	*ok = 1;

	height = (int)getHeightMapHeight(xPos, yPos, &normal);
	if (height < zero || height > mode)
		*heightOK = 0;
	xAngle = (Real)fabs(BfmeAngleQuarterTurn - (Real)atan2(normal.z, normal.x) * BfmeAngleScale);
	yAngle = (Real)fabs(BfmeAngleQuarterTurn - (Real)atan2(normal.z, normal.y) * BfmeAngleScale);
	if (xAngle < flags || xAngle > amount || yAngle < flags || yAngle > amount)
		*ok = 0;

	Real xPos1 = (Real)((int)a + 1) * BfmeCoordinateScale;

	height = (int)getHeightMapHeight(xPos1, yPos, &normal);
	if (height < zero || height > mode)
		*heightOK = 0;
	xAngle = (Real)fabs(BfmeAngleQuarterTurn - (Real)atan2(normal.z, normal.x) * BfmeAngleScale);
	yAngle = (Real)fabs(BfmeAngleQuarterTurn - (Real)atan2(normal.z, normal.y) * BfmeAngleScale);
	if (xAngle < flags || xAngle > amount || yAngle < flags || yAngle > amount)
		*ok = 0;

	Real yPos1 = (Real)((int)b + 1) * BfmeCoordinateScale;

	height = (int)getHeightMapHeight(xPos1, yPos1, &normal);
	if (height < zero || height > mode)
		*heightOK = 0;
	xAngle = (Real)fabs(BfmeAngleQuarterTurn - (Real)atan2(normal.z, normal.x) * BfmeAngleScale);
	yAngle = (Real)fabs(BfmeAngleQuarterTurn - (Real)atan2(normal.z, normal.y) * BfmeAngleScale);
	if (xAngle < flags || xAngle > amount || yAngle < flags || yAngle > amount)
		*ok = 0;

	height = (int)getHeightMapHeight(xPos, yPos1, &normal);
	if (height < zero || height > mode)
		*heightOK = 0;
	xAngle = (Real)fabs(BfmeAngleQuarterTurn - (Real)atan2(normal.z, normal.x) * BfmeAngleScale);
	yAngle = (Real)fabs(BfmeAngleQuarterTurn - (Real)atan2(normal.z, normal.y) * BfmeAngleScale);
	if (xAngle < flags || xAngle > amount || yAngle < flags || yAngle > amount)
		*ok = 0;
}

#undef BfmeAngleQuarterTurn
#undef BfmeAngleScale
#undef BfmeCoordinateScale
#undef BFME_UNUSED_VIRTUALS_16
