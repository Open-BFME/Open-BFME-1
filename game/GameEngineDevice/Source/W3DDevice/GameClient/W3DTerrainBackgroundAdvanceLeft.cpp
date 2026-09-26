// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// Retail 0x007293E0: W3DTerrainBackground::advanceLeft. Zero Hour twin in
// W3DTerrainBackground.cpp walks left.y then left.x testing the map flip bit;
// BFME adds a separate y extent and clamps both walks to the map extent.

typedef unsigned char Byte;
typedef bool Bool;

struct ICoord2D
{
	int x;
	int y;
};

struct Rva00729300Bytes
{
	Byte *m_begin;
	Byte *m_end;

	unsigned size() const { return (unsigned)(m_end - m_begin); }
	Byte operator[]( int index ) const { return m_begin[index]; }
};

// Same map layout and flip-bit test as the out-of-line copy at 0x00729300
// (Code/GameEngine/Source/Common/Rva00729300BitPlanes.cpp); inlined here.
class Rva00729300BitPlane
{
public:
	Bool test( int x, int y ) const
	{
		register const Rva00729300BitPlane *self = this;
		if( x < 0 || y < 0 || y >= self->m_height || x >= self->m_width )
		{
			return false;
		}

		const int index = self->m_stride * y + (x >> 3);
		if( (unsigned)index >= self->m_bits.size() )
		{
			return false;
		}

		int mask = 1;
		mask <<= x & 7;
		Byte value = self->m_bits[index];
		Bool result = (value & mask) != 0;
		return result;
	}

public:
	Byte m_opaque00[0x08];
	int m_width;
	int m_height;
	Byte m_opaque10[0x24];
	int m_stride;
	Byte m_opaque38[0x0c];
	Rva00729300Bytes m_bits;
};

class W3DTerrainBackground
{
protected:
	Bool advanceLeft( ICoord2D &left, int xOffset, int yOffset,
		int width, int height );

	Byte m_opaque00[0x40];
	int m_xOrigin;
	int m_yOrigin;
	int m_width;
	Rva00729300BitPlane *m_map;
};

Bool W3DTerrainBackground::advanceLeft( ICoord2D &left, int xOffset,
	int yOffset, int width, int height )
{
	Rva00729300BitPlane *map = m_map;
	int mapHeight = map->m_height;
	int yOrigin = m_yOrigin;
	int mapWidth = map->m_width;
	int xOrigin = m_xOrigin;
	int limitX = mapWidth - xOrigin;
	int limitY = mapHeight - yOrigin;
	limitX--;
	limitY--;
	while( left.y < yOffset + height && left.y < limitY )
	{
		left.y++;
		if( m_map->test( left.x + m_xOrigin, left.y + m_yOrigin ) )
			return true;
	}
	while( left.x < xOffset + width - 1 && left.x < limitX - 1 )
	{
		left.x++;
		if( m_map->test( left.x + m_xOrigin, left.y + m_yOrigin ) )
			return true;
	}
	return false;
}
