// ?updatePathPositions@Rva0022F960BfmeAODHordeContainOwner@@QAEXXZ
// partial score=0.99 date=2026-09-24
// cl: /DNDEBUG /MD /EHsc

#include <math.h>

extern float normalizeAngle(float angle);

struct Rva0022F960Coord3D
{
	float x;
	float y;
	float z;

	float length() const
	{
		return (float)sqrt(x * x + y * y + z * z);
	}
	void normalize()
	{
		float len = length();
		if (len != 0)
		{
			x /= len;
			y /= len;
			z /= len;
		}
	}
	void sub(const Rva0022F960Coord3D *a)
	{
		x -= a->x;
		y -= a->y;
		z -= a->z;
	}
	void scale(float s)
	{
		x *= s;
		y *= s;
		z *= s;
	}
	void add(const Rva0022F960Coord3D *a)
	{
		x += a->x;
		y += a->y;
		z += a->z;
	}
};

struct Rva0022F960PathPosition
{
	Rva0022F960Coord3D position;
	float frame;
};

struct Rva0022F960FlowPoint
{
	float distance;
	float angle;
	Rva0022F960Coord3D position;
	float unused;
};

class Rva0022F960BfmeAODHordeContainOwner
{
public:
	void updatePathPositions();

private:
	unsigned char m_prefix[0x250];
	Rva0022F960PathPosition m_pathPositions[0x3c];
	int m_pathPositionCount;
	Rva0022F960FlowPoint m_flowPoints[0x14];
	int m_flowPointCount;
};

// ?updatePathPositions@Rva0022F960BfmeAODHordeContainOwner@@QAEXXZ
void Rva0022F960BfmeAODHordeContainOwner::updatePathPositions()
{
	float firstFlowDistance = m_flowPoints[0].distance;
	float pathDistance = 0.0f;
	int pathIndex = 0;
	Rva0022F960Coord3D delta;
	delta.x = -1.0f;
	delta.y = 0.0f;

	for (int flowIndex = 0; flowIndex < m_flowPointCount; ++flowIndex)
	{
		float remaining = firstFlowDistance - m_flowPoints[flowIndex].distance - pathDistance;
		float length;
		for (;;)
		{
			if (pathIndex < m_pathPositionCount - 1)
			{
				delta = m_pathPositions[pathIndex + 1].position;
				delta.sub(&m_pathPositions[pathIndex].position);
				length = (float)sqrt(delta.x * delta.x + delta.y * delta.y);
			}
			else
				length = 99999.9f;
			if (length > remaining)
				break;
			++pathIndex;
			remaining -= length;
			pathDistance += length;
		}

		Rva0022F960Coord3D dir;
		dir.x = delta.x;
		dir.y = delta.y;
		dir.z = 0.0f;
		dir.normalize();
		dir.scale(remaining);
		dir.add(&m_pathPositions[pathIndex].position);
		m_flowPoints[flowIndex].position = dir;

		float curAngle = m_pathPositions[pathIndex].frame;
		float nextAngle = curAngle;
		if (pathIndex < m_pathPositionCount - 1)
			nextAngle = m_pathPositions[pathIndex + 1].frame;
		float desired = normalizeAngle(remaining / length * normalizeAngle(nextAngle - curAngle) + curAngle);
		float flowAngle = m_flowPoints[flowIndex].angle;
		float turn = normalizeAngle(desired - flowAngle);
		if (turn > 0.17453294f)
			m_flowPoints[flowIndex].angle = flowAngle + 0.17453294f;
		else if (turn < -0.17453294f)
			m_flowPoints[flowIndex].angle = flowAngle - 0.17453294f;
		else
			m_flowPoints[flowIndex].angle = desired;
		m_flowPoints[flowIndex].angle = normalizeAngle(m_flowPoints[flowIndex].angle);
	}
}
