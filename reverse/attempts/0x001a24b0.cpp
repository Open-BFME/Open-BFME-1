// ?isCellOnEnd@Bridge@@QAE_NPBURegion2D@@@Z
// partial score=0.71 date=2026-09-04
// cl: /DNDEBUG /MD /EHs-c-
// Bridge::isCellOnEnd, retail 0x001A24B0 size 431.
// ZH twin in TerrainLogic.cpp; BFME adds a second end-vector when m_extra is set.
//
// Recovered: +0x28 fromLeft / +0x34 fromRight / +0x40 toLeft / +0x4C toRight /
// +0x8C extra. First normalize is the inlined x87 length/scale; the extra
// path calls Coord3D::normalize out of line. LineInRegion is cdecl 3-arg.
// Closest build: 462B vs 431B. Prologue + inline normalize match through
// fxch (DIR32 0.0/1.0/10.0). Remaining: extra-load vs *10 interleave,
// fromLeft/fromRight materialization, LineInRegion arg shuffle, setne tail.

#include <math.h>

struct Coord2D
{
	float x;
	float y;
};

struct Coord3D
{
	float x;
	float y;
	float z;
	void normalize();
};

struct Region2D
{
	Coord2D lo;
	Coord2D hi;
};

bool LineInRegion(const Coord2D *p1, const Coord2D *p2, const Region2D *clipRegion);

class Bridge
{
public:
	bool isCellOnEnd(const Region2D *cell);

private:
	void *m_vptr;
	void *m_next;
	void *m_templateName;
	char m_infoPad[0x1C];
	Coord3D m_fromLeft;
	Coord3D m_fromRight;
	Coord3D m_toLeft;
	Coord3D m_toRight;
	char m_infoTail[0x8C - 0x58];
	void *m_extra;
};

bool Bridge::isCellOnEnd(const Region2D *cell)
{
	struct Work
	{
		Coord3D fromLeft;
		Coord3D endVector;
		Coord3D fromRight;
		Coord3D toLeft;
		Coord3D toRight;
	} w;

	w.endVector.y = m_fromRight.y;
	w.endVector.z = m_fromRight.z;
	float dx = m_fromRight.x - m_fromLeft.x;
	float dy = w.endVector.y - m_fromLeft.y;
	float dz = w.endVector.z - m_fromLeft.z;
	{
		float len = (float)sqrt(dz * dz + dy * dy + dx * dx);
		if (len != 0.0f)
		{
			float scale = 1.0f / len;
			dx *= scale;
			dy *= scale;
		}
	}

	void *extra = m_extra;
	dx *= 10.0f;
	dy *= 10.0f;
	w.endVector.x = dx;
	w.endVector.y = dy;

	w.fromLeft = m_fromLeft;
	w.fromLeft.x += w.endVector.x;
	w.fromLeft.y += w.endVector.y;

	w.fromRight = m_fromRight;
	w.fromRight.x -= w.endVector.x;
	w.fromRight.y -= w.endVector.y;

	if (extra)
	{
		w.endVector = m_toRight;
		w.endVector.x -= m_toLeft.x;
		w.endVector.y -= m_toLeft.y;
		w.endVector.z -= m_toLeft.z;
		w.endVector.normalize();
		w.endVector.x *= 10.0f;
		w.endVector.y *= 10.0f;
	}

	w.toLeft = m_toLeft;
	w.toLeft.x += w.endVector.x;
	w.toLeft.y += w.endVector.y;

	w.toRight = m_toRight;
	w.toRight.x -= w.endVector.x;
	w.toRight.y -= w.endVector.y;

	if (LineInRegion((Coord2D *)&w.fromLeft, (Coord2D *)&w.fromRight, cell))
		return true;
	if (LineInRegion((Coord2D *)&w.toLeft, (Coord2D *)&w.toRight, cell))
		return true;
	return false;
}
