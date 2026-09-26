// ?bfmeFindDirection001A12D0@Rva001A12D0Owner@@QAE_NPAUVector3@@@Z
// partial score=0.27 date=2026-09-21
// cl: /DNDEBUG /MD /EHsc

// Open-BFME: carved body at retail 0x001A12D0 (312 B). Six callers, two
// resolved Point_In_Triangle_2D callees and a usePluralShadowName guard;
// address-derived owner (no proven class). Incremental grid-search state
// machine: the object keeps its own (curX, curY) cursor across calls
// (both fields pre-incremented on entry, never reset by this body except
// curY on a column wrap), walking curX in [.., m_maxX] and, for each
// column, curY in [m_loopStartY, m_maxY]. For every grid point it builds a
// 2D point (curX*weight, curY*weight) and either tests it against two
// triangles (tri0/tri1a/tri2 and tri0/tri1b/tri2) when
// usePluralShadowName() is true, or falls back to a squared-distance vs.
// weight^2 test around (originX, originY). A hit stores the grid point
// into *out and returns true; exhausting curX without a hit returns false.

typedef bool Bool;

struct Vector3
{
	float x, y, z;
};

extern bool __cdecl Point_In_Triangle_2D(const Vector3 &p0, const Vector3 &p1,
	const Vector3 &p2, const Vector3 &point, int, int, Bool &edge);

class BfmeThingTemplateShadowSelector
{
public:
	Bool usePluralShadowName() const;
};

class Rva001A12D0Owner
{
public:
	Bool bfmeFindDirection001A12D0(Vector3 *out);

	unsigned char m_pad00[0x10];
	float m_weight;                     // +0x10
	unsigned char m_pad14[0x4c];
	float m_originX;                    // +0x60
	float m_originY;                    // +0x64
	unsigned char m_pad68[0x08];
	int m_loopStartY;                   // +0x70
	int m_maxX;                         // +0x74
	int m_maxY;                         // +0x78
	Vector3 m_tri0;                     // +0x7c
	Vector3 m_tri1a;                    // +0x88
	Vector3 m_tri1b;                    // +0x94
	Vector3 m_tri2;                     // +0xa0
	int m_curX;                         // +0xac
	int m_curY;                         // +0xb0
};

extern float g_bfmeDirectionWeight1285;

Bool Rva001A12D0Owner::bfmeFindDirection001A12D0(Vector3 *out)
{
	for (;;)
	{
		if (++m_curY > m_maxY)
		{
			int maxX = m_maxX;
			for (;;)
			{
				if (++m_curX > maxX)
					return false;

				m_curY = m_loopStartY;
				if (m_loopStartY <= m_maxY)
					break;
			}
		}

		Bool edge;
		Vector3 pt;
		pt.z = 0.0f;
		pt.x = (float)m_curX * g_bfmeDirectionWeight1285;
		pt.y = (float)m_curY * g_bfmeDirectionWeight1285;

		if (((BfmeThingTemplateShadowSelector *)this)->usePluralShadowName())
		{
			if (Point_In_Triangle_2D(m_tri0, m_tri1a, m_tri2, pt, 0, 1, edge) ||
				Point_In_Triangle_2D(m_tri1a, m_tri1b, m_tri2, pt, 0, 1, edge))
			{
				out->x = pt.x;
				out->y = pt.y;
				return true;
			}
		}
		else
		{
			float dx = pt.x - m_originX;
			float dy = pt.y - m_originY;
			if (dx * dx + dy * dy < m_weight * m_weight)
			{
				out->x = pt.x;
				out->y = pt.y;
				return true;
			}
		}
	}
}
