// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-

typedef unsigned char Byte;

struct Rva00729300Bytes
{
	Byte *m_begin;
	Byte *m_end;

	unsigned size() const { return (unsigned)(m_end - m_begin); }
	Byte operator[]( int index ) const { return m_begin[index]; }
};

class Rva00729300BitPlane
{
public:
	bool test( int x, int y ) const;

public:
	Byte m_opaque00[0x08];
	int m_width;
	int m_height;
	Byte m_opaque10[0x24];
	int m_stride;
	Byte m_opaque38[0x0c];
	Rva00729300Bytes m_bits;
};

class Rva00729370BitPlane
{
public:
	bool test( int x, int y ) const;

public:
	Byte m_opaque00[0x08];
	int m_width;
	int m_height;
	Byte m_opaque10[0x24];
	int m_stride;
	Byte m_opaque38[0x18];
	Rva00729300Bytes m_bits;
};

bool Rva00729300BitPlane::test( int x, int y ) const
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
	bool result = (value & mask) != 0;
	return result;
}

bool Rva00729370BitPlane::test( int x, int y ) const
{
	register const Rva00729370BitPlane *self = this;
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
	bool result = (value & mask) != 0;
	return result;
}

class Rva00729D30Terrain
{
public:
	void checkEdges( int xOffset, int yOffset, int width,
		bool *top, bool *right, bool *bottom, bool *left );

private:
	Byte m_opaque00[0x40];
	int m_xOrigin;
	int m_yOrigin;
	int m_width;
	Rva00729300BitPlane *m_map;
};

void Rva00729D30Terrain::checkEdges( int xOffset, int yOffset, int width,
	bool *top, bool *right, bool *bottom, bool *left )
{
	int xOrigin = m_xOrigin;
	Rva00729300BitPlane *map = m_map;
	int limitX = map->m_width - 1;
	int limitY = map->m_height - 1;
	int minX = xOrigin + xOffset;
	int minY = m_yOrigin + yOffset;
	int maxX = xOffset + width;
	if( m_xOrigin + maxX > limitX )
		maxX = limitX - m_xOrigin;
	register int maxY = yOffset + width;
	if( m_yOrigin + maxY > limitY )
		maxY = limitY - m_yOrigin;

	int halfX = (maxX - xOffset) / 2;
	int halfY = (maxY - yOffset) / 2;
	int centerX = xOffset + halfX;
	int centerY = yOffset + halfY;
	*top = *right = *bottom = *left = false;
	if( !m_map->test( minX, m_yOrigin + centerY ) )
		*top = true;
	if( !m_map->test( m_xOrigin + centerX, maxY + m_yOrigin ) )
		*right = true;
	if( !m_map->test( m_xOrigin + maxX, m_yOrigin + centerY ) )
		*bottom = true;
	if( !m_map->test( m_xOrigin + centerX, minY ) )
		*left = true;
}

struct ICoord2D
{
	int x;
	int y;
};

class Rva00729570Terrain
{
public:
	bool advanceRight( ICoord2D &right, int xOffset, int yOffset,
		int width, int height );

private:
	Byte m_pad00[0x40];
	int m_xOrigin;
	int m_yOrigin;
	int m_width;
	Rva00729300BitPlane *m_map;
};

bool Rva00729570Terrain::advanceRight( ICoord2D &right, int xOffset,
	int yOffset, int width, int height )
{
	Rva00729300BitPlane *map = m_map;
	int mapWidth = map->m_width;
	int mapHeight = map->m_height;
	int yOrigin = m_yOrigin;
	int limitX = mapWidth - m_xOrigin;
	int limitY = mapHeight - yOrigin;
	limitX--;
	limitY--;
	while( right.x < width + xOffset && right.x < limitX )
	{
		right.x++;
		if( m_map->test( right.x + m_xOrigin, right.y + m_yOrigin ) )
			return true;
	}
	while( right.y < yOffset + height - 1 && right.y < limitY - 1 )
	{
		right.y++;
		if( m_map->test( right.x + m_xOrigin, right.y + m_yOrigin ) )
			return true;
	}
	return false;
}
