// ?Rva003FDCF0@Path@@QAEXAAUCoord3D@@@Z
// partial score=0.93 date=2026-09-11
//
// Owner confirmed: Path, via m_cpopRecentStart @ +0x10 and m_cachedPosition
// @ +0x14/+0x18/+0x1c matching the landed PathAdvanceCachedPoint.cpp /
// PathComputeFlightDistToGoal.cpp layout exactly. Method identity itself not
// recoverable; address-derived. t=35min model=Sonnet 5
//
// 148/153 bytes. Shape, fallback chain, guard tests and field offsets all
// exact. Residue: retail loads the default z with `fld [ecx+0x1c]` right
// after loading x into eax (BEFORE loading y), and leaves it live on the x87
// stack across the n==0/a==0 early-exit tests; both early-exit paths reuse
// that ST(0) value directly for the final store, and the first deep path
// (p = a->m_position) discards it with a bare `fstp st(0)` before loading a
// fresh z. Our compile always resolves the third float (x,y,z in declaration
// order) into a GPR (reusing eax after storing x), never promoting it to the
// FPU stack, so we pay 5 extra bytes storing+reloading through memory.
//
// Ruled out (all confirmed via tools/probe.py, masked-shape unequal):
//   - Statement-order permutations of the four default-seed assignments
//     (x,z,y / y,x,z / x,z,y-via-locals) via tools/shape_search.py
//     (4 explicit alternatives, build/choices_3fdcf0.json): none changed the
//     GPR/FPU allocation; scores 0.03-0.07, none reached the target shape.
//   - Separating x0/z0/y0 into individually declared locals in retail's own
//     materialization order before assigning into the Coord3D: identical
//     codegen to the plain struct-field-assignment form.
//   - Early-return restructuring (`if (n==0) { out=p; return; }` per guard
//     instead of nested if/fallthrough): worse, 175/153 bytes, moves the
//     divergence earlier and does not touch the fld-vs-mov choice.
//   - `Coord3D p = m_cachedPosition;` (aggregate init) and reading through a
//     `const Coord3D *def` pointer alias: both same 148/153 result.
// This reads as a genuine MSVC 7.1 register-pressure/x87-spill decision (the
// third float loses out to eax/edx/ecx already committed to x, y and the
// m_cpopRecentStart pointer chase) rather than a source-shape defect. An
// additional live GPR local was also tested after this bank and did not move
// the residue; keep the address-derived method and bank the honest near miss.
struct Coord3D
{
public:
	float x;
	float y;
	float z;
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
	float m_cachedDistance;
};

void Path::Rva003FDCF0(Coord3D &out)
{
	Coord3D p;
	p.x = m_cachedPosition.x;
	p.y = m_cachedPosition.y;
	p.z = m_cachedPosition.z;

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
		}
	}

	out = p;
}
