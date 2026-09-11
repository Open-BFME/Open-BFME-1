// ?updatePathPositions@BfmeAODHordeContainOwner@@QAEXXZ
// partial score=0.48 date=2026-09-10
// cl: /DNDEBUG /MD /EHsc

#include <math.h>

struct Coord3D
{
	float x;
	float y;
	float z;
};

struct BfmeAODPathPosition
{
	Coord3D m_position;
	float m_frame;
};

struct BfmeAODFlowPointView
{
	float m_angle;
	Coord3D m_position;
	float m_field14;
};

extern const float BfmeZeroRange;
extern float g_bfmeDefaultBU;
extern const float g_bfmeAngleUpper;
extern const float g_bfmeAngleLower;
extern float normalizeAngle(float angle);

// This TU-local mirror is the BFME-owned tail witnessed by the AOD constructor
// and updateFormationMembers: path positions begin at +0x250, the flow records
// begin at +0x614, and their count is at +0x7f4.
class BfmeAODHordeContainOwner
{
public:
	void updatePathPositions();

private:
	unsigned char m_prefix[0x250];
	BfmeAODPathPosition m_pathPositions[0x3c];
	int m_pathPositionCount;
	float m_firstFlowDistance;
	unsigned char m_flowTail[0x1dc];
	int m_flowPointCount;
};

// ?updatePathPositions@BfmeAODHordeContainOwner@@QAEXXZ
void BfmeAODHordeContainOwner::updatePathPositions()
{
	volatile float firstFlowDistance = m_firstFlowDistance;
	int pathIndex = 0;

	if (m_flowPointCount <= 0)
		return;

	float pathDistance = 0.0f;
	float previousAngle = -1.0f;
	int flowIndex = 0;
	float angleOffset = 0.0f;
	BfmeAODFlowPointView *flow = reinterpret_cast<BfmeAODFlowPointView *>(
		reinterpret_cast<unsigned char *>(this) + 0x618);
	do
	{
		float remaining = firstFlowDistance - reinterpret_cast<float *>(flow)[-1] - pathDistance;
		Coord3D delta;
		float length;
		BfmeAODPathPosition *current = &m_pathPositions[pathIndex];
		BfmeAODPathPosition *next = current + 1;

		if (pathIndex < m_pathPositionCount - 1)
		{
			for (;;)
			{
				next = &m_pathPositions[pathIndex + 1];
				current = next - 1;
				delta = next->m_position;
				delta.x -= current->m_position.x;
				delta.y -= current->m_position.y;
				length = (float)sqrt(delta.x * delta.x + delta.y * delta.y);

				if (length > remaining)
					break;

				++pathIndex;
				pathDistance += length;
				remaining -= length;
			}
		}

		current = &m_pathPositions[pathIndex];
		next = current + 1;
		length = (float)sqrt(delta.x * delta.x + delta.y * delta.y);
		float scale = remaining / length;

		if (length != length)
			scale = g_bfmeDefaultBU / length;

		flow->m_position.x = current->m_position.x + delta.x * scale;
		flow->m_position.y = current->m_position.y + delta.y * scale;
		flow->m_position.z = current->m_position.z + delta.z * scale;

		float frameDelta = 0.0f;
		if (pathIndex < m_pathPositionCount - 1)
			frameDelta = next->m_frame - current->m_frame;
		frameDelta = normalizeAngle(frameDelta);
		float desiredAngle = normalizeAngle(previousAngle / pathDistance * frameDelta + angleOffset);
		previousAngle = desiredAngle;
		float angleDelta = normalizeAngle(desiredAngle - flow->m_angle);
		if (angleDelta > g_bfmeAngleUpper)
			flow->m_angle = angleOffset + g_bfmeAngleUpper;
		else if (angleDelta < g_bfmeAngleLower)
 			flow->m_angle = angleOffset - g_bfmeAngleUpper;
		flow->m_angle = normalizeAngle(flow->m_angle);

		++flowIndex;
		flow = reinterpret_cast<BfmeAODFlowPointView *>(
			reinterpret_cast<unsigned char *>(flow) + 0x18);
	} while (flowIndex < m_flowPointCount);
}
