// cl: /O2 /Ob2 /G6

// Retail 0x001DE2A0, reached only through ILT 0x00004D27 from the landed
// BfmeCellGrid sweep 0x001B1AD0, which passes the cell centre, the grid cell
// size, a sample index and an opaque parameter block.  The body forms the same
// m_first[index]*p[+8] - m_second[index]*p[+4] difference as the landed
// S3FloatPredicates siblings, clamps it to [0, p[+0x10]], normalises it, and
// hands two {1, ratio, 1/0} triples by value to the empty retail body at
// 0x006E6E50 (a 1-byte ret reached through ILT 0x000243AC, caller-cleaned).
// Neither callee nor caller names the method, so the address stays in the
// names.

typedef int Int;
typedef float Real;

extern const Real BfmeZeroRange;		// retail 0x01075350

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

struct Rva006E6E50Triple
{
	Real first;
	Real second;
	Real third;
};

void rva006E6E50(const Coord3D *position, Real size, Int frames,
	Rva006E6E50Triple triple);

struct Rva001DE2A0Parameters
{
	char m_bfmeHead[0x04];
	Real m_bfme0004;						// +0x04
	Real m_bfme0008;						// +0x08
	Real m_bfme000C;						// +0x0C
	Real m_bfme0010;						// +0x10
};

class BfmeCell
{
public:
	void rva001DE2A0(const Coord3D *position, Real cellSize,
		Int index, void *parameters);

private:
	Real m_first[16];
	Real m_second[16];
};

void BfmeCell::rva001DE2A0(const Coord3D *position, Real cellSize,
	Int index, void *parameters)
{
	const Rva001DE2A0Parameters *p = (const Rva001DE2A0Parameters *)parameters;
	Real value = m_first[index] * p->m_bfme0008 - m_second[index] * p->m_bfme0004;
	if (!(value > BfmeZeroRange))
		value = BfmeZeroRange;
	if (!(value < p->m_bfme0010))
		value = p->m_bfme0010;
	Real ratio = value / p->m_bfme0010;

	Rva006E6E50Triple triple;
	triple.first = 1.0f;
	triple.second = ratio;
	triple.third = 1.0f;
	rva006E6E50(position, cellSize, 6, triple);

	triple.third = 0.0f;
	rva006E6E50(position, cellSize - 20.0f, 6, triple);
}
