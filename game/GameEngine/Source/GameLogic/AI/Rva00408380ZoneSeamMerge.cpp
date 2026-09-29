// cl: /DNDEBUG /MD

// Retail 0x00408380 (199 bytes, ret 0x14), reached only through ILT
// 0x0000A0F1.  A zone block seam pass: unless the block's +0x05 flag is
// already set, it pairs every cell on the leading edge of region `a` with its
// neighbour one step back through PairMerge00406EC0::merge (ILT 0x0001EA06),
// then marks the block done.  With `vertical` set the edge is the row at
// a->lo.y (walked from lo.x to hi.x, taken only when a->lo.y > b->lo.y);
// otherwise it is the column at a->lo.x (lo.y to hi.y, when a->lo.x >
// b->lo.x).  Cells are 16 bytes, reached through a column-pointer array.
// IDENTITY IS NOT RECOVERED: owner and method keep the address.

struct Cell00406EC0;

class PairMerge00406EC0
{
public:
	void merge(const Cell00406EC0 *a, const Cell00406EC0 *b);
};

struct Rva00408380Cell
{
	char m_bytes[0x10];
};

struct Rva00408380Region
{
	int loX;
	int loY;
	int hiX;
	int hiY;
};

class Rva00408380Block
{
public:
	void mergeSeam(Rva00408380Cell **cells, int vertical, const Rva00408380Region *a,
		const Rva00408380Region *b, PairMerge00406EC0 *merger);

private:
	char m_pad00[5];
	bool m_seamDone;
};

void Rva00408380Block::mergeSeam(Rva00408380Cell **cells, int vertical,
	const Rva00408380Region *a, const Rva00408380Region *b, PairMerge00406EC0 *merger)
{
	if (m_seamDone)
		return;

	if (vertical)
	{
		if (a->loY > b->loY)
		{
			for (int i = a->loX; i <= a->hiX; i++)
				merger->merge((const Cell00406EC0 *)&cells[i][a->loY],
					(const Cell00406EC0 *)&cells[i][a->loY - 1]);
		}
	}
	else
	{
		if (a->loX > b->loX)
		{
			for (int j = a->loY; j <= a->hiY; j++)
				merger->merge((const Cell00406EC0 *)&cells[a->loX][j],
					(const Cell00406EC0 *)&cells[a->loX - 1][j]);
		}
	}
	m_seamDone = true;
}
