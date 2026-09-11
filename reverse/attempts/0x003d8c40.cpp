// "?d_003d8c40@@YAXXZ"
// partial score=0.25 date=2026-09-11
// cl: /DNDEBUG /MD /EHs-c- /Ireference/shims/pathfind /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib
// BFME Pathfinder bridge and elevated-layer picker.

#include "vector3.h"
#include "GameLogic/AIPathfind.h"

typedef float Real;
typedef bool Bool;

class Bridge
{
public:
	Bool pickBridge(const Vector3 &from, const Vector3 &to, Vector3 *pos);
};

struct Rva003D8C40PathfindLayer
{
	unsigned char m_prefix[0x3c];
	void *m_active;
	Int m_height;
};

class Rva003D8C40Pathfinder
{
public:
	Bool bfmePickBridge(const Vector3 &from, const Vector3 &to, Vector3 *pos);

private:
	unsigned char m_prefix[0x10];
	PathfindCell **m_map;
	IRegion2D m_extent;
	unsigned char m_toBridgeList[0x858 - 0x24];
	Bridge *m_bridgeList;
	Rva003D8C40PathfindLayer m_layers[16];
	unsigned char m_toBridgeHeights[0x243f8 - 0xc9c];
	Int m_bridgeHeightCount;
	Real *m_bridgeHeights;
};

#define BFME_PICK_BEST_LIMIT (*(const Real *)0x01084C3C)

// ?bfmePickBridge@Pathfinder@@QAE_NABVVector3@@0PAV2@@Z
Bool Rva003D8C40Pathfinder::bfmePickBridge(const Vector3 &from,
	const Vector3 &to, Vector3 *pos)
{
	Bridge *bridge = m_bridgeList;
	Real bestMetric = 3.402823466e+38f;

	while (bridge != 0)
	{
		Vector3 bridgePos;
		if (bridge->pickBridge(from, to, &bridgePos))
		{
			Real metric = Vector3::Quick_Distance(bridgePos, from);
			if (metric < bestMetric)
			{
				bestMetric = metric;
				*pos = bridgePos;
			}
		}
		bridge = *(Bridge **)((unsigned char *)bridge + 4);
	}

	Int index = 0;
	if (index < m_bridgeHeightCount)
	{
		Real *height = m_bridgeHeights;
		do
		{
			Real heightValue = *height;
			Vector3 candidate;
			Vector3 delta;
			Vector3::Subtract(to, from, &delta);
			Real t = (heightValue - from.Z) / delta.Z;
			delta *= t;
			Vector3::Add(from, delta, &candidate);
			Coord3D worldPosition = *reinterpret_cast<const Coord3D *>(&candidate);

			ICoord2D cellCoord;
			if (!worldToCell(&worldPosition, &cellCoord) &&
				cellCoord.x >= m_extent.lo.x && cellCoord.x <= m_extent.hi.x &&
				cellCoord.y >= m_extent.lo.y && cellCoord.y <= m_extent.hi.y)
			{
				PathfindCell *cell = &m_map[cellCoord.x][cellCoord.y];
				if (cell != 0)
				{
					unsigned int bits = *(unsigned int *)((unsigned char *)cell + 0x0c);
					if (((bits >> 6) & 0x3f) == index + 0x11 && (bits & 7) == 0)
					{
						Real metric = Vector3::Quick_Distance(candidate, from);
						if (metric < bestMetric)
						{
							bestMetric = metric;
							*pos = candidate;
						}
					}
				}
			}
			++index;
			++height;
		} while (index < m_bridgeHeightCount);
	}

	for (Int index = 2; index <= 15; ++index)
	{
		Rva003D8C40PathfindLayer *layer = &m_layers[index];
		if (layer->m_active == 0)
			continue;

		Real height = (Real)layer->m_height;
		Vector3 candidate;
		Vector3 delta;
		Vector3::Subtract(to, from, &delta);
		Real t = (height - from.Z) / delta.Z;
		delta *= t;
		Vector3::Add(from, delta, &candidate);
		Coord3D worldPosition = *reinterpret_cast<const Coord3D *>(&candidate);

		ICoord2D cellCoord;
		if (worldToCell(&worldPosition, &cellCoord))
			continue;
		if (cellCoord.x < m_extent.lo.x || cellCoord.x > m_extent.hi.x ||
			cellCoord.y < m_extent.lo.y || cellCoord.y > m_extent.hi.y)
			continue;

		PathfindCell *cell;
		if (index > 1 && index <= 15)
			cell = reinterpret_cast<PathfindLayer *>(&m_layers[index])->getCell(
				cellCoord.x, cellCoord.y);
		else
			cell = &m_map[cellCoord.x][cellCoord.y];
		if (cell == 0)
			continue;
		unsigned int bits = *(unsigned int *)((unsigned char *)cell + 0x0c);
		if (((bits >> 6) & 0x3f) != (unsigned int)index || (bits & 7) != 0)
			continue;

		Real metric = Vector3::Quick_Distance(candidate, from);
		if (metric < bestMetric)
		{
			bestMetric = metric;
			*pos = candidate;
		}
	}

	if (bestMetric < BFME_PICK_BEST_LIMIT)
		return true;
	return false;
}
