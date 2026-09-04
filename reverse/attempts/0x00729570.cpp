// ?advanceRight@Rva00729570Terrain@@QAE_NAAUICoord2D@@HHHH@Z
// partial score=0.5 date=2026-09-04
// cl: /DNDEBUG /MD
// Retail 0x00729570: advance the right edge through a terrain tile.

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

class Rva00729570Terrain
{
public:
	Bool advanceRight(ICoord2D &right, int xOffset, int yOffset,
		int width, int height);

private:
	unsigned char m_pad00[0x40];
	int m_xOrigin;
	int m_yOrigin;
	int m_width;
	Rva00729300BitPlane *m_map;
};

// ?advanceRight@Rva00729570Terrain@@QAE_NAAUICoord2D@@HHHH@Z
Bool Rva00729570Terrain::advanceRight(ICoord2D &right, int xOffset,
	int yOffset, int width, int height)
{
	int maxX = width + xOffset;
	Rva00729300BitPlane *map = m_map;
	int mapWidth = map->m_width;
	int mapHeight = map->m_height;
	int yOrigin = m_yOrigin;
	int limitX = mapWidth - m_xOrigin;
	int limitY = mapHeight - yOrigin;
	limitX--;
	limitY--;
	if (right.x < maxX)
	{
		do
		{
			if (right.x >= limitX)
				break;
			right.x++;
			if (m_map->test(right.x + m_xOrigin,
				right.y + m_yOrigin))
				return 1;
		}
		while (right.x < maxX);
	}
	int maxY = yOffset + maxX - 1;
	if (right.y < maxY)
	{
		limitY--;
		do
		{
			if (right.y >= limitY)
				break;
			right.y++;
			if (m_map->test(right.x + m_xOrigin,
				right.y + m_yOrigin))
				return 1;
		}
		while (right.y < maxY);
	}
	return 0;
}
