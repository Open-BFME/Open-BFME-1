// ?advanceLeft@Rva007293E0Terrain@@QAE_NAAUICoord2D@@HHHH@Z
// partial score=0.55 date=2026-09-04
// cl: /DNDEBUG /MD
// Retail 0x007293E0: advance the left edge through a terrain tile.

typedef bool Bool;


// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct ICoord2D
{
	int x;
	int y;
};

struct Rva00729300Bytes
{
	unsigned char *m_begin;
	unsigned char *m_end;

	unsigned size() const { return (unsigned)(m_end - m_begin); }
	unsigned char operator[](int index) const { return m_begin[index]; }
};

class Rva00729300BitPlane
{
public:
	Bool test(int x, int y) const;

public:
	unsigned char m_pad00[0x08];
	int m_width;
	int m_height;
	unsigned char m_pad10[0x24];
	int m_stride;
	unsigned char m_pad38[0x0c];
	Rva00729300Bytes m_bits;
};

Bool Rva00729300BitPlane::test(int x, int y) const
{
	register const Rva00729300BitPlane *self = this;
	if (x < 0 || y < 0 || y >= self->m_height || x >= self->m_width)
		return 0;

	const int index = self->m_stride * y + (x >> 3);
	if ((unsigned)index >= self->m_bits.size())
		return 0;

	int mask = 1;
	mask <<= x & 7;
	unsigned char value = self->m_bits[index];
	Bool result = (value & mask) != 0;
	return result;
}

class Rva007293E0Terrain
{
public:
	Bool advanceLeft(ICoord2D &left, int xOffset, int yOffset,
		int width, int height);

private:
	unsigned char m_pad00[0x40];
	int m_xOrigin;
	int m_yOrigin;
	int m_width;
	Rva00729300BitPlane *m_map;
};

// ?advanceLeft@Rva007293E0Terrain@@QAE_NAAUICoord2D@@HHHH@Z
Bool Rva007293E0Terrain::advanceLeft(ICoord2D &left, int xOffset,
    int yOffset, int width, int height)
{
	int maxY = yOffset;
	Rva00729300BitPlane *map = m_map;
	int mapHeight = map->m_height;
	int yOrigin = m_yOrigin;
	int mapWidth = map->m_width;
	int xOrigin = m_xOrigin;
	int limitX = mapWidth - xOrigin;
	int limitY = mapHeight - yOrigin;
	maxY += height;
	limitX--;
	limitY--;
	if (left.y < maxY)
	{
		do
		{
			if (left.y >= limitY)
				break;
			left.y++;
			if (m_map->test(left.x + m_xOrigin,
				left.y + m_yOrigin))
				return 1;
		}
		while (left.y < maxY);
	}
	int maxX = xOffset + width - 1;
	if (left.x < maxX)
	{
		limitX--;
		do
		{
			if (left.x >= limitX)
				break;
			left.x++;
			if (m_map->test(left.x + m_xOrigin,
				left.y + m_yOrigin))
				return 1;
		}
		while (left.x < maxX);
	}
	return 0;
}
