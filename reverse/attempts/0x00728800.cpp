// ?clearFlipStates@W3DTerrainBackground@@QAEXXZ
// partial score=0.55 date=2026-09-02
// cl: /DNDEBUG /MD
//
// Retail 0x00728800: walk the tile in [m_xOrigin, m_xOrigin+m_width] x
// [m_yOrigin, m_yOrigin+m_width], clamp each cell to the map extents, and
// clear the flip bit.  Same fields as allocateTerrainBuffers (m_width at
// +0x48, m_map at +0x4C).  WorldHeightMap extents sit at +0x08/+0x0C.

class WorldHeightMap
{
public:
	void setFlipState(int x, int y, bool value);

	unsigned char m_pad[8];
	int m_xExtent;
	int m_yExtent;
};

class W3DTerrainBackground
{
public:
	void clearFlipStates(void);

private:
	unsigned char m_pad00[0x40];
	int m_xOrigin;
	int m_yOrigin;
	int m_width;
	WorldHeightMap *m_map;
};

void W3DTerrainBackground::clearFlipStates(void)
{
	WorldHeightMap *map = m_map;
	int limitX = map->m_xExtent;
	int limitY = map->m_yExtent;
	int xOrig = m_xOrigin;
	int yOrig = m_yOrigin;
	limitX--;
	int width = m_width;
	int i = 0;
	limitY--;
	if (width >= 0)
	{
		do
		{
			int j = 0;
			if (width >= 0)
			{
				int x = xOrig + i;
				do
				{
					int cx = x;
					if (cx >= limitX)
						cx = limitX;
					int y = yOrig + j;
					if (y >= limitY)
						y = limitY;
					m_map->setFlipState(cx, y, false);
					width = m_width;
					j++;
				} while (j <= width);
			}
			width = m_width;
			i++;
		} while (i <= width);
	}
}
