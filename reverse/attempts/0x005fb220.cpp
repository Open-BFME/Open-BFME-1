// ?getVelocity@LightningEmissionModule@FXParticleSystem@@UAE?AUCoord3D@2@PBU32@MM@Z
// partial score=0.65 date=2026-09-11
#include <math.h>

extern const float BfmeZeroRange;
extern float g_bfmeDefaultBU;

namespace FXParticleSystem
{

struct Coord3D
{
	Coord3D(float xValue, float yValue, float zValue)
		: x(xValue), y(yValue), z(zValue) {}

	float x;
	float y;
	float z;
};

class LightningEmissionModule
{
public:
	virtual Coord3D getVelocity(const Coord3D *position, float speed, float radialSpeed);

	unsigned char m_pad[0x08];
	Coord3D m_start;
	Coord3D m_end;
};

Coord3D LightningEmissionModule::getVelocity(const Coord3D *, float speed, float radialSpeed)
{
	float x = m_end.x - m_start.x;
	float y = m_end.y - m_start.y;
	float z = m_end.z - m_start.z;

	float length = (float)sqrt(x * x + y * y + z * z);
	if (length != BfmeZeroRange)
	{
		float scale = g_bfmeDefaultBU / length;
		x *= scale;
		y *= scale;
		z *= scale;
	}

	volatile float sideX = BfmeZeroRange * z - y;
	volatile float sideY = x - BfmeZeroRange * z;
	volatile float sideZ = y - BfmeZeroRange * x;

	return Coord3D(x * speed + sideX * radialSpeed,
		y * speed + sideY * radialSpeed,
		z * speed + sideZ * radialSpeed);
}

}
