// cl: /DNDEBUG /MD
// BFME camera-path angle helper at retail 0x00740440.

#include <math.h>

typedef float Real;
typedef bool Bool;

class Rva00740AE0Base
{
public:
	virtual void dummy();

	int m_04;
	int m_08;
	char m_0c[4];
	char m_sub[8];
	int m_18;
	int m_1c;
	int m_20;
	char m_24;
	int m_28;
};

class AsciiString
{
public:
	AsciiString(const AsciiString &other);
	~AsciiString();

private:
	void *m_data;
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

struct Rva00740AE0Elem
{
	Coord3D position;
	AsciiString name;
	int m_10;
};

class WWMath
{
	public:
	static __forceinline Real Acos(Real value)
	{
		return (Real)acos(value);
	}
	static __forceinline Real Sqrt(Real value)
	{
		Real result;
		__asm {
			fld [value]
			fsqrt
			fstp [result]
		}
		return result;
	}
	static __forceinline void SqrtTo(Real value, Real *result)
	{
		__asm {
			fld [value]
			fsqrt
			mov eax, [result]
			fstp dword ptr [eax]
		}
	}
};

extern Real g_bfmePiOverTwo;
extern void __fastcall normAngle(Real &angle);

class Vector2
{
public:
	Real X;
	Real Y;
	__forceinline Real Length(void) const
	{
		return WWMath::Sqrt(Length2());
	}
	__forceinline Real Length2(void) const
	{
		return X * X + Y * Y;
	}
};

class Rva00740440 : public Rva00740AE0Base
{
public:
	void setCameraPathAngles(Bool orient, Real angle, int firstWaypoint);

private:
	Rva00740AE0Elem m_waypoints[255];
	Rva00740AE0Elem m_extraWaypoints[4];
	Real m_cameraAngles[256];
	Real m_waySegmentLengths[256];
	Real m_totalDistance;
	Real m_currentSegmentDistance;
	char m_padding1c70[0x2070 - 0x1c70];
	int m_numWaypoints;
};

void Rva00740440::setCameraPathAngles(Bool orient, Real angle, int firstWaypoint)
{
	Real *cameraAngle = m_cameraAngles;
	int i;
	if (orient)
	{
		++cameraAngle;
		for (i = 2; i < m_numWaypoints + 2; ++i)
		{
			Vector2 direction;
			Real *current = &m_waypoints[i].position.x;
			Real *next = &m_waypoints[i + firstWaypoint].position.x;
			direction.X = *current - *next;
			direction.Y = current[1] - next[1];
			Real pathAngle = direction.Length2();
			pathAngle = WWMath::Sqrt(pathAngle);
			pathAngle = direction.X / pathAngle;
			if (pathAngle < -1.0f)
				pathAngle = -1.0f;
			if (pathAngle > 1.0f)
				pathAngle = 1.0f;
			if (direction.Y < 0.0f)
				pathAngle = -WWMath::Acos(pathAngle);
			else
				pathAngle = WWMath::Acos(pathAngle);
			pathAngle -= g_bfmePiOverTwo;
			normAngle(pathAngle);
			*cameraAngle++ = pathAngle;
		}
		m_cameraAngles[1] = angle;
		m_cameraAngles[0] = angle;
	}
	else
	{
		Real *end = cameraAngle + m_numWaypoints;
		for (Real *p = cameraAngle; p != end; ++p)
			*p = angle;
	}
}
