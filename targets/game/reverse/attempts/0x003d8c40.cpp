// ?bfmePickBridge@Pathfinder@@QAE_NABVVector3@@0PAV2@@Z
// partial score=0.69 date=2026-09-28
// ?bfmePickBridge@Pathfinder@@QAE_NABVVector3@@0PAV2@@Z  retail 0x003D8C40
// TRUE EXTENT 1502 bytes (ledger row says 1494): jp at +0x5c9 targets the return-false
// tail xor eax,eax / add esp,0x6c / ret 0xc at +0x5d6..+0x5dd. Probe with --size 1502.
// Residue: this/bridge swapped (retail this=ebx bridge=edi) and loop-3 cell.x via eax->ebp.
// cl: /DNDEBUG /MD /EHs-c- /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib

#include "vector3.h"

typedef float Real;
typedef bool Bool;
typedef int Int;

struct ICoord2D { Int x, y; };
struct IRegion2D { ICoord2D lo, hi; };
struct Coord3D { Real x, y, z; };

enum PathfindLayerEnum { LAYER_INVALID = 0, LAYER_GROUND = 1, LAYER_LAST = 15 };

class PathfindCell
{
public:
	Int getType(void) const { return m_packed & 0x7; }
	Int getLayer(void) const { return (m_packed >> 6) & 0x3f; }
private:
	void *m_info;
	Int m_unused1;
	Int m_unused2;
	unsigned int m_packed;
};

class Bridge
{
public:
	Bool pickBridge(const Vector3 &from, const Vector3 &to, Vector3 *pos);
	Bridge *getNext(void) { return m_next; }
private:
	void *m_vtbl;
	Bridge *m_next;
};

class PathfindLayer
{
public:
	PathfindCell *getCell(Int x, Int y);
	Bool isBfmeActive3C(void) const { return m_active != 0; }
	Int getBfmeHeight40(void) const { return m_height; }
private:
	unsigned char m_prefix[0x3c];
	void *m_active;
	Int m_height;
};

class Pathfinder
{
public:
	Bool bfmePickBridge(const Vector3 &from, const Vector3 &to, Vector3 *pos);
	Bool worldToCell(const Coord3D *pos, ICoord2D *cell);

	PathfindCell *getCell(PathfindLayerEnum layer, Int x, Int y)
	{
		if (x >= m_extent.lo.x && x <= m_extent.hi.x &&
			y >= m_extent.lo.y && y <= m_extent.hi.y)
		{
			PathfindCell *cell = 0;
			if (layer > LAYER_GROUND && layer <= LAYER_LAST)
			{
				cell = m_layers[layer].getCell(x, y);
				if (cell)
					return cell;
			}
			return &m_map[x][y];
		}
		return 0;
	}

	PathfindCell *getCell(PathfindLayerEnum layer, const Coord3D *pos)
	{
		ICoord2D cell;
		Bool overflow = worldToCell(pos, &cell);
		if (overflow)
			return 0;
		return getCell(layer, cell.x, cell.y);
	}

private:
	unsigned char m_prefix[0x10];
	PathfindCell **m_map;
	IRegion2D m_extent;
	unsigned char m_mid[0x858 - 0x24];
	Bridge *m_bfmeBridges858;
	PathfindLayer m_layers[16];
	unsigned char m_gap[0x243f8 - 0xc9c];
	Int m_bfmeHeightCount243F8;
	Real m_bfmeHeights243FC[1];
};

Bool Pathfinder::bfmePickBridge(const Vector3 &from, const Vector3 &to, Vector3 *pos)
{
	Real bestDist = 3.402823466e+38f;
	for (Bridge *bridge = m_bfmeBridges858; bridge; bridge = bridge->getNext())
	{
		Vector3 curPos;
		if (bridge->pickBridge(from, to, &curPos))
		{
			Real dist = Vector3::Quick_Distance(curPos, from);
			if (dist < bestDist)
			{
				bestDist = dist;
				*pos = curPos;
			}
		}
	}

	Int i;
	for (i = 0; i < m_bfmeHeightCount243F8; i++)
	{
		Vector3 delta = to - from;
		Real t = (m_bfmeHeights243FC[i] - from.Z) / delta.Z;
		Vector3 hitPos = from + delta * t;
		Coord3D pt;
		pt.x = hitPos.X;
		pt.y = hitPos.Y;
		pt.z = hitPos.Z;
		PathfindCell *cell = getCell(LAYER_GROUND, &pt);
		if (cell && cell->getLayer() == i + 0x11 && cell->getType() == 0)
		{
			Real dist = Vector3::Quick_Distance(hitPos, from);
			if (dist < bestDist)
			{
				bestDist = dist;
				*pos = hitPos;
			}
		}
	}

	for (i = 2; i <= LAYER_LAST; i++)
	{
		if (!m_layers[i].isBfmeActive3C())
			continue;
		Vector3 delta = to - from;
		Real t = ((Real)m_layers[i].getBfmeHeight40() - from.Z) / delta.Z;
		Vector3 hitPos = from + delta * t;
		Coord3D pt;
		pt.x = hitPos.X;
		pt.y = hitPos.Y;
		pt.z = hitPos.Z;
		PathfindCell *cell = getCell((PathfindLayerEnum)i, &pt);
		if (cell && cell->getLayer() == i && cell->getType() == 0)
		{
			Real dist = Vector3::Quick_Distance(hitPos, from);
			if (dist < bestDist)
			{
				bestDist = dist;
				*pos = hitPos;
			}
		}
	}
	return bestDist < 3.402823466e+38f;
}
