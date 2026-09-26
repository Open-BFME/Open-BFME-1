// ?bfmeNudge@Gen_001EFCE0@@QAEXPAVObject@@@Z
// partial score=0.42 date=2026-09-04
// cl: /DNDEBUG /MD /O2 /Ob2 /GX-
// Open-BFME5: retail 0x001EFB20 size 356, dump d_001e7c30.
// Same +0x44/+0x48 12-byte vector as Gen_001EFCE0::bfmeCost.
// Probe last: 297 vs 356, frame 0x24 vs 0x1c, edi vs ebp for other,
// finish-before-start, add/lea last-index. x87 spill of origin+delta
// plus bfmeIntersects test Coord3D is the frame wall. Do not add a
// third Coord3D local. Retail interleaves push ebx/esi inside the /6
// magic and keeps ecx=this until after pick.

typedef float Real;
typedef bool Bool;

extern Real g_bfmeScaleBK;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class GeometryInfo
{
public:
	Bool bfmeIntersects(const Coord3D &thisPosition, Real thisAngle,
		const GeometryInfo &otherGeometry, const Coord3D &otherPosition,
		Real otherAngle) const;
};

class Object
{
public:
	void setPosition(const Coord3D *pos);

	char m_pad000[0x38];
	Coord3D m_position;
	Real m_orientation;
	char m_pad048[0xac - 0x48];
	GeometryInfo m_geometryInfo;
};

class Gen_001EFCE0
{
public:
	void bfmeNudge(Object *other);

	char m_pad00[8];
	Object *m_source;
	char m_pad0c[0x44 - 0x0c];
	Coord3D *m_start;
	Coord3D *m_finish;
	char m_pad4c[0x70 - 0x4c];
	int m_index;
};

// ?bfmeNudge@Gen_001EFCE0@@QAEXPAVObject@@@Z
void Gen_001EFCE0::bfmeNudge(Object *other)
{
	if (!other)
		return;

	int last = (int)(m_finish - m_start) - 1;
	int pick;
	if ((unsigned)last >= (unsigned)m_index)
		pick = m_index;
	else
		pick = (int)(m_finish - m_start) - 1;

	Object *src = m_source;
	Coord3D pos;
	pos.x = src->m_position.x;
	pos.y = src->m_position.y;
	pos.z = src->m_position.z;

	pick = pick - 1;
	if (pick < 0)
		pick = 0;

	const Coord3D *pt = &m_start[pick];
	Coord3D delta;
	delta.x = (pt->x - pos.x) * g_bfmeScaleBK;
	delta.y = (pt->y - pos.y) * g_bfmeScaleBK;
	delta.z = (pt->z - pos.z) * g_bfmeScaleBK;

	Real thisAngle = src->m_orientation;
	int n = 0;
	while (n <= 12)
	{
		n++;
		Coord3D test;
		test.x = pos.x + delta.x;
		test.y = pos.y + delta.y;
		test.z = pos.z + delta.z;
		if (!src->m_geometryInfo.bfmeIntersects(test, thisAngle,
			other->m_geometryInfo, other->m_position, other->m_orientation))
			break;
	}

	pos.x -= delta.x;
	pos.y -= delta.y;
	pos.z -= delta.z;
	src->setPosition(&pos);
}
