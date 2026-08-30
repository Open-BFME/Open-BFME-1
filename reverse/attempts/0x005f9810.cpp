// ?d_005f9810@@YAXXZ
// partial score=0.9 date=2026-08-30
#include "System/game_client_random_variable.h"

struct BfmeVec1287
{
	BfmeVec1287() {}
	BfmeVec1287(float x_, float y_, float z_)
	{
		x = x_;
		y = y_;
		z = z_;
	}

	float x;
	float y;
	float z;
};

inline BfmeVec1287 operator*(const BfmeVec1287 &value, float scale)
{
	return BfmeVec1287(value.x * scale, value.y * scale, value.z * scale);
}

extern "C" void bfmeRandomUnitVector1287(BfmeVec1287 *out);

class BfmeA1287
{
public:
	BfmeVec1287 bfmeScaledRandom1287(int, int);
	char m_bfmePad00[0x1c];
	GameClientRandomVariable m_scale;
};

BfmeVec1287 BfmeA1287::bfmeScaledRandom1287(int, int)
{
	float scale = m_scale.getValue();
	BfmeVec1287 result;
	bfmeRandomUnitVector1287(&result);
	return result * scale;
}
