// ?checkEdges@Rva00729D30Terrain@@QAEXHHHPA_N000@Z
// partial score=0.98 date=2026-09-03
// cl: /DNDEBUG /MD
// Retail 0x00729D30: test the four edge midpoints of a terrain tile.

class Rva00729300BitPlane
{
public:
	bool getFlipState(int x, int y) const;

	public:
	unsigned char m_pad00[8];
	int m_width;
	int m_height;
	unsigned char m_pad10[0x24];
	int m_stride;
	unsigned char m_pad38[0x0c];
	unsigned char *m_begin;
	unsigned char *m_end;
};

class Rva00729D30Terrain
{
public:
	void checkEdges(int xOffset, int yOffset, int width,
		bool *top, bool *right, bool *bottom, bool *left);

private:
	unsigned char m_pad00[0x40];
	int m_xOrigin;
	int m_yOrigin;
	int m_width;
	Rva00729300BitPlane *m_map;
};

// ?checkEdges@Rva00729D30Terrain@@QAEXHHHPA_N000@Z
void Rva00729D30Terrain::checkEdges(int xOffset, int yOffset, int width,
	bool *top, bool *right, bool *bottom, bool *left)
{
	int xOrigin = m_xOrigin;
	Rva00729300BitPlane *map = m_map;
	int limitX = map->m_width - 1;
	int limitY = map->m_height - 1;
	int minX = xOrigin + xOffset;
	int minY = m_yOrigin + yOffset;
	int maxX = xOffset + width;
	if (m_xOrigin + maxX > limitX)
		maxX = limitX - m_xOrigin;
	register int maxY = yOffset + width;
	if (m_yOrigin + maxY > limitY)
		maxY = limitY - m_yOrigin;

	int halfX = (maxX - xOffset) / 2;
	int halfY = (maxY - yOffset) / 2;
	int centerX = xOffset + halfX;
	int centerY = yOffset + halfY;
	*top = *right = *bottom = *left = false;
	if (!m_map->getFlipState(minX, m_yOrigin + centerY))
	{
		*top = true;
	}
	if (!m_map->getFlipState(m_xOrigin + centerX, m_yOrigin + maxY))
	{
		*right = true;
	}
	if (!m_map->getFlipState(m_xOrigin + maxX, m_yOrigin + centerY))
	{
		*bottom = true;
	}
	if (!m_map->getFlipState(m_xOrigin + centerX, minY))
	{
		*left = true;
	}
}
