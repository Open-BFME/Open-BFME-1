// ?updatePathPositions@BfmeAODHordeContainOwner@@QAEXXZ
// partial score=0.52 date=2026-09-11
// cl: /DNDEBUG /MD /EHsc

#include <math.h>

struct Rva0022F960Coord3D
{
	float x;
	float y;
	float z;
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

extern const float BfmeZeroRange;
extern float g_bfmeDefaultBU;
extern const float g_bfmeAngleUpper;
extern const float g_bfmeAngleLower;
extern float normalizeAngle(float angle);

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

// ?updatePathPositions@BfmeAODHordeContainOwner@@QAEXXZ
void Rva0022F960BfmeAODHordeContainOwner::updatePathPositions()
{
	Rva0022F960BfmeAODHordeContainOwner *owner = this;
	float firstFlowDistance = owner->m_flowPoints[0].distance;
	int pathIndex = 0;
	if (owner->m_flowPointCount <= pathIndex)
		return;

	float pathDistance = 0.0f;
	float currentFrame = -1.0f;
	int flowIndex = 0;
	float *flow = reinterpret_cast<float *>(
		reinterpret_cast<unsigned char *>(owner) + 0x618);
	Rva0022F960Coord3D delta;
	Rva0022F960Coord3D scaledDelta;

	while (flowIndex < owner->m_flowPointCount)
	{
		float remaining = firstFlowDistance - flow[-1] - pathDistance;
		Rva0022F960PathPosition *next = reinterpret_cast<Rva0022F960PathPosition *>(
			reinterpret_cast<unsigned char *>(owner) + (pathIndex + 0x26) * 0x10);
		float length;
		if (pathIndex < owner->m_pathPositionCount - 1)
		{
			delta.x = next->position.x - (next - 1)->position.x;
			delta.y = next->position.y - (next - 1)->position.y;
			delta.z = next->position.z;
			length = (float)sqrt(delta.x * delta.x + delta.y * delta.y);
		}
		else
			length = 99999.9f;

		if (length <= remaining)
		{
			++pathIndex;
			remaining -= length;
			pathDistance += length;
			continue;
		}

		float horizontalLength = (float)sqrt(delta.x * delta.x + delta.y * delta.y);
		scaledDelta.x = delta.x;
		scaledDelta.y = delta.y;
		scaledDelta.z = BfmeZeroRange;
		if (horizontalLength > BfmeZeroRange)
		{
			float scale = g_bfmeDefaultBU / horizontalLength;
			scaledDelta.x = delta.x * scale;
			scaledDelta.y = delta.y * scale;
			scaledDelta.z = scale * BfmeZeroRange;
		}

		Rva0022F960PathPosition *current = reinterpret_cast<Rva0022F960PathPosition *>(
			reinterpret_cast<unsigned char *>(owner) + (pathIndex + 0x25) * 0x10);
		flow[1] = current->position.x + scaledDelta.x * remaining;
		flow[2] = current->position.y + scaledDelta.y * remaining;
		flow[3] = current->position.z + scaledDelta.z * remaining;

		currentFrame = current->frame;
		float frameDelta = currentFrame;
		if (pathIndex < owner->m_pathPositionCount - 1)
			frameDelta = next->frame;
		frameDelta -= currentFrame;
		frameDelta = normalizeAngle(frameDelta);
		float desiredAngle = normalizeAngle(remaining / horizontalLength * frameDelta + currentFrame);
		float angleDelta = normalizeAngle(desiredAngle - flow[0]);
		float adjustedAngle = flow[0];
		if (angleDelta > g_bfmeAngleUpper)
			adjustedAngle = currentFrame + g_bfmeAngleUpper;
		else if (angleDelta < g_bfmeAngleLower)
			adjustedAngle = currentFrame - g_bfmeAngleUpper;
		flow[0] = normalizeAngle(adjustedAngle);

		++flowIndex;
		flow += 6;
	}
}
