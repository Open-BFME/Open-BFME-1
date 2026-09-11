// ?updatePosition@Gen0060CBB0@@AAEXXZ
// partial score=0.9 date=2026-09-11
// cl: -I Code/GameEngine/Include/Precompiled -I Code/Libraries/Source/WWVegas/WWLib -I Code/Libraries/Source/WWVegas/WWMath -I Code/Libraries/Source/WWVegas/WWDebug -I Code/Libraries/Include

#include <math.h>
#include "coord.h"
#include "matrix3.h"

#pragma intrinsic(sin, cos, sqrt, atan2)

#define BfmeZeroRange (*(volatile const float *)0x01075350)
#define g_bfmeDefaultEG (*(volatile const float *)0x01097114)

#define Rva0060C620Global28 (*(const float *)0x012D6A28)
#define Rva0060C620Global2C (*(const float *)0x012D6A2C)
#define Rva0060C620Global30 (*(const float *)0x012D6A30)
#define Rva0060C620Global34 (*(const float *)0x012D6A34)
#define Rva0060C620Global38 (*(const float *)0x012D6A38)
#define Rva0060C620Global3C (*(const float *)0x012D6A3C)
#define Rva0060C620Global40 (*(const float *)0x012D6A40)
#define Rva0060C620Global44 (*(const float *)0x012D6A44)
#define Rva0060C620Global48 (*(const float *)0x012D6A48)

struct Rva0060C620Coord3D
{
	float x;
	float y;
	float z;

	void set(float ax, float ay, float az)
	{
		x = ax;
		y = ay;
		z = az;
	}
};

class U4Target0060C2C0
{
public:
	void hand( void *payload );
};

class Gen0060CBB0
{
private:
	void updatePosition();

	char m_head[0x18];
	void *m_firstTarget;
	unsigned int m_unused1C;
	void *m_secondTarget;
	volatile float m_frameX;
	volatile float m_frameY;
	volatile float m_frameZ;
	volatile float m_targetX;
	volatile float m_targetY;
	volatile float m_targetZ;
};

// ?updatePosition@Gen0060CBB0@@AAEXXZ
void Gen0060CBB0::updatePosition()
{
	Rva0060C620Coord3D frame;
	frame.set(m_frameY, m_frameZ, m_frameX);
	Matrix3 first;
	Matrix3 second;
	Matrix3 result;
	float dx = frame.x - m_targetX;
	float dy = frame.y - m_targetY;
	float dz = frame.z - m_targetZ;
	float horizontal = (float)sqrt(dx * dx + dy * dy);
	float angle = (float)atan2(-dz, horizontal);
	float sine = (float)sin(angle);
	float cosine = (float)cos(angle);

	second = Matrix3(
		cosine - sine * BfmeZeroRange, BfmeZeroRange,
		sine + cosine * BfmeZeroRange,
		cosine * BfmeZeroRange - sine * BfmeZeroRange, 1.0f,
		sine * BfmeZeroRange + cosine * BfmeZeroRange,
		cosine * BfmeZeroRange - sine, BfmeZeroRange,
		sine * BfmeZeroRange + cosine);
	first = Create_Z_Rotation_Matrix3(
		(float)sin(angle - g_bfmeDefaultEG),
		(float)cos(angle - g_bfmeDefaultEG));
	Matrix3::Multiply(first, second, &result);

	if (m_firstTarget != 0)
	{
		((U4Target0060C2C0 *)m_firstTarget)->hand(&result);
	}

	float secondAngle = (float)atan2(-(frame.y - m_targetY),
		frame.x - m_targetX);
	float s = (float)sin(secondAngle);
	float c = (float)cos(secondAngle);
	second = Matrix3(
		Rva0060C620Global28 * c - Rva0060C620Global30 * s,
		Rva0060C620Global2C,
		Rva0060C620Global30 * s + Rva0060C620Global28 * c,
		Rva0060C620Global34 * c - Rva0060C620Global3C * s,
		Rva0060C620Global38,
		Rva0060C620Global34 * s + Rva0060C620Global3C * c,
		Rva0060C620Global40 * c - Rva0060C620Global48 * s,
		Rva0060C620Global44,
		Rva0060C620Global40 * s + Rva0060C620Global48 * c);
	first = Create_Z_Rotation_Matrix3(
		(float)sin(angle - 3.14159265358979323846f),
		(float)cos(angle - 3.14159265358979323846f));
	Matrix3::Multiply(
		first, second, &result);

	if (m_secondTarget != 0)
	{
		((U4Target0060C2C0 *)m_secondTarget)->hand(&result);
	}
}
