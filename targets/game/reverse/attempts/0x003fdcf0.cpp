// ?Rva003FDCF0@Path@@QAEXAAUCoord3D@@@Z
// partial score=0.8431 date=2026-09-25
// ?Rva003FDCF0@Path@@QAEXAAUCoord3D@@@Z
// partial: 153/153 bytes, every opcode and branch identical to retail; the
// 24 remaining bytes are ECX/EDX register letters in the three node copies.
//
// Owner Path: m_cpopRecentStart +0x10 and m_cachedPosition +0x14 match the
// landed PathAdvanceCachedPoint.cpp / PathComputeFlightDistToGoal.cpp layout;
// PathNode +0x08 m_nextOpti is name_oracle witnessed. Method name unproven, so
// the address token stays. Sole caller: Locomotor_rva001B7200.cpp via ILT
// 0x0002E2A3.
//
// Lever that closed the x87 residue every earlier bank hit: the cached z is a
// separate Real, refreshed from p.z after the node copies, and out is written
// member by member. Retail's fld [ecx+0x1c] kept on the x87 stack across the
// early exits, the fstp st(0) in the first deep path and the fld [esp+8] at the
// join all follow from that.
typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class PathNode
{
public:
	unsigned char m_head[8];
	PathNode *m_nextOpti;
	Coord3D m_position;
	unsigned char m_gap[8];
	int m_waypointID;
};

class Path
{
public:
	void Rva003FDCF0(Coord3D &out);

private:
	unsigned char m_head[4];
	PathNode *m_path;
	PathNode *m_pathTail;
	int m_isOptimized;
	PathNode *m_cpopRecentStart;
	Coord3D m_cachedPosition;
	Real m_cachedDistance;
};

void Path::Rva003FDCF0(Coord3D &out)
{
	Coord3D p;
	p.x = m_cachedPosition.x;
	p.y = m_cachedPosition.y;
	Real z = m_cachedPosition.z;

	PathNode *n = m_cpopRecentStart;
	if (n != 0)
	{
		PathNode *a = n->m_nextOpti;
		if (a != 0)
		{
			p = a->m_position;
			PathNode *b = a->m_nextOpti;
			if (b != 0)
			{
				p = b->m_position;
				PathNode *c = b->m_nextOpti;
				if (c != 0 && c->m_waypointID != 0x7fffffff)
					p = c->m_position;
			}
			z = p.z;
		}
	}

	out.x = p.x;
	out.y = p.y;
	out.z = z;
}
