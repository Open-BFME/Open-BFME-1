// ?bfmeNotifyPlain@PathfindLayer@@AAEXXZ
// partial score=0.72 date=2026-09-08
// cl: /DNDEBUG /MD /EHsc

// BFME's bridge-less PathfindLayer reclassification pass.  PathfindLayer's
// field offsets are shared with the exact init, reset, apply-zone and
// setDestroyed bodies; setDestroyed reaches this body through ILT 0x0003A03F.

typedef int Int;

struct Coord2D
{
	float x;
	float y;
	float z;
};

class PathfindCell
{
public:
	void reset();
	void setType(Int type);

	unsigned char m_pad00[0x0C];
	unsigned int m_flags;
};

extern float g_bfmePathfindCellSize;

class PathfindLayer
{
private:
	void bfmeNotifyPlain();
	bool bfmeContainsPoint(const Coord2D *point);

	unsigned char m_pad00[4];
	PathfindCell **m_cells;       // +0x04
	Int m_width;                  // +0x08
	Int m_height;                 // +0x0C
	Int m_xOrigin;                // +0x10
	Int m_yOrigin;                // +0x14
	Int m_startX;                 // +0x18
	Int m_startY;                 // +0x1C
	Int m_endX;                   // +0x20
	Int m_endY;                   // +0x24
	Int m_layer;                  // +0x28
};

// ?bfmeNotifyPlain@PathfindLayer@@AAEXXZ
void PathfindLayer::bfmeNotifyPlain()
{
	m_startX = -1;
	m_startY = -1;
	m_endX = -1;
	m_endY = -1;

	for (Int x = 0; x < m_width; ++x)
	{
		for (Int y = 0; y < m_height; ++y)
		{
			PathfindCell *cell = &m_cells[x][y];
			cell->m_flags &= 0xFFFC0FFF;
			cell->m_flags = cell->m_flags ^
				((cell->m_flags ^ (m_layer << 6)) & 0xFC0);

			Coord2D topLeft;
			topLeft.x = (x + m_xOrigin) * g_bfmePathfindCellSize;
			topLeft.y = (y + m_yOrigin) * g_bfmePathfindCellSize;
			Coord2D bottomRight;
			bottomRight.x = topLeft.x + g_bfmePathfindCellSize;
			bottomRight.y = topLeft.y + g_bfmePathfindCellSize;

			Int count = 0;
			if (bfmeContainsPoint(&topLeft))
				++count;
			Coord2D point = topLeft;
			point.y = bottomRight.y;
			if (bfmeContainsPoint(&point))
				++count;
			if (bfmeContainsPoint(&bottomRight))
				++count;
			point = topLeft;
			point.x = bottomRight.x;
			if (bfmeContainsPoint(&point))
				++count;

			cell->reset();
			cell->m_flags = cell->m_flags ^
				((cell->m_flags ^ (m_layer << 6)) & 0xFC0);
			cell->setType(5);
			if (count > 0)
				cell->setType(0);
		}
	}
}
