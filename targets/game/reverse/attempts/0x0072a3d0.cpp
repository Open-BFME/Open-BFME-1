// ?rva0072A3D0@Rva0072A3D0Owner@@QAEXPAGPAMHHHH0AAH@Z
// partial score=0.9628 date=2026-10-09
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWDebug /Igame/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/shims/sweep
// ?rva0072A3D0@Rva0072A3D0Owner@@QAEXPAGPAMHHHH0AAH@Z
// Retail terrain edge fan with independently decoded map and helper layouts.
#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE
#include <vector3.h>

typedef unsigned char Byte;
typedef bool Bool;
typedef int Int;
typedef unsigned short UnsignedShort;

struct ICoord2D { Int x; Int y; };
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

inline bool Rva00729300BitPlane::test( int x, int y ) const
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

class WorldHeightMap {
public:
    Int getXExtent(void) const { return m_width; }
    Int getYExtent(void) const { return m_height; }
    Int getBorderSizeInline(void) const { return m_borderSize; }
    UnsignedShort getHeight(Int x, Int y) const {
        Int index = m_width * y + x;
        if (index < 0 || index >= m_dataSize || m_data == 0) return 0;
        return m_data[index];
    }
    void *m_vptr;
    Int m_refs;
    Int m_width;
    Int m_height;
    Int m_borderSize;
    unsigned char m_pad14[0x0c];
    Int m_dataSize;
    UnsignedShort *m_data;
};
class W3DTerrainBackground {
    friend class Rva0072A3D0Owner;
public:
    Bool advanceRight(ICoord2D &point, Int xOffset, Int yOffset, Int width, Int height);
    void getTriangleIntersection(float *records, Int xOrigin, Int yOrigin, Int outerEnd, Int innerEnd, const Vector3 *first, const Vector3 *second, const Vector3 *third);
protected:
    __declspec(noinline) Bool advanceLeft(ICoord2D &point, Int xOffset, Int yOffset, Int width, Int height);
private:
    unsigned char m_pad00[0x40];
    int m_xOrigin;
    int m_yOrigin;
    int m_width;
    Rva00729300BitPlane *m_map;
};
class Rva00729570Terrain {
public:
    __declspec(noinline) Bool advanceRight(ICoord2D &point, Int xOffset, Int yOffset, Int width, Int height);
private:
    unsigned char m_pad00[0x40];
    int m_xOrigin;
    int m_yOrigin;
    int m_width;
    Rva00729300BitPlane *m_map;
};
// ?advanceRight@W3DTerrainBackground@@QAE_NAAUICoord2D@@HHHH@Z absent-from-retail
inline Bool W3DTerrainBackground::advanceRight(ICoord2D &point, Int xOffset, Int yOffset, Int width, Int height) {
    return ((Rva00729570Terrain *)this)->advanceRight(point, xOffset, yOffset, width, height);
}
class Rva00729F60Owner {
public:
    // ?rva00729F60@Rva00729F60Owner@@QAEXPAMHHHHPBVVector3@@11@Z absent-from-retail
    void rva00729F60(float *records, Int xOrigin, Int yOrigin, Int outerEnd, Int innerEnd, const Vector3 *first, const Vector3 *second, const Vector3 *third) {
        ((W3DTerrainBackground *)this)->getTriangleIntersection(records, xOrigin, yOrigin, outerEnd, innerEnd, first, second, third);
    }
};
class Rva0072A3D0Owner {
public:
    void rva0072A3D0(UnsignedShort *ib, float *records, Int xOffset, Int yOffset, Int xWidth, Int yWidth, UnsignedShort *ndx, Int &curIndex);
private:
    unsigned char m_pad00[0x40];
    Int m_xOrigin;
    Int m_yOrigin;
    Int m_width;
    WorldHeightMap *m_map;
};

inline __declspec(noinline) Bool W3DTerrainBackground::advanceLeft( ICoord2D &left, int xOffset,
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
inline __declspec(noinline) bool Rva00729570Terrain::advanceRight( ICoord2D &right, int xOffset,
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


void Rva0072A3D0Owner::rva0072A3D0(UnsignedShort *ib, float *records, Int xOffset, Int yOffset, Int xWidth, Int yWidth, UnsignedShort *ndx, Int &curIndex)
{
    Int minX = m_xOrigin + xOffset;
    Int minY = m_yOrigin + yOffset;
    Int limitX = m_map->getXExtent() - 1;
    Int limitY = m_map->getYExtent() - 1;
    Int maxX = xOffset + xWidth;
    if (m_xOrigin + maxX > limitX) maxX = limitX - m_xOrigin;
    Int maxY = yOffset + yWidth;
    if (m_yOrigin + maxY > limitY) maxY = limitY - m_yOrigin;
    Bool topRightFlip = ((Rva00729300BitPlane *)m_map)->test(m_xOrigin + maxX, m_yOrigin + maxY);
    Int topRightNdx = ndx[maxX + maxY * (m_width + 1)];
    ICoord2D left;
    left.x = xOffset;
    left.y = yOffset;
    ICoord2D right;
    right.x = xOffset;
    right.y = yOffset;
    W3DTerrainBackground *terrain = (W3DTerrainBackground *)this;
    terrain->advanceLeft(left, xOffset, yOffset, xWidth, yWidth);
    terrain->advanceRight(right, xOffset, yOffset, xWidth, yWidth);
    Bool bottomLeftFlip = ((Rva00729300BitPlane *)m_map)->test(minX, minY);
    UnsignedShort leftNdx;
    UnsignedShort rightNdx;
    Rva00729F60Owner *helper = (Rva00729F60Owner *)this;
    if (bottomLeftFlip) {
        if (ib) ib[curIndex] = ndx[xOffset + yOffset * (m_width + 1)];
        ++curIndex;
        rightNdx = ndx[right.x + right.y * (m_width + 1)];
        if (ib) ib[curIndex] = rightNdx;
        ++curIndex;
        leftNdx = ndx[left.x + left.y * (m_width + 1)];
        if (ib) ib[curIndex] = leftNdx;
        ++curIndex;
        if (records) {
            Vector3 p0;
            p0.X = (float)minX * 10.0f - (float)m_map->getBorderSizeInline() * 10.0f;
            p0.Y = (float)minY * 10.0f - (float)m_map->getBorderSizeInline() * 10.0f;
            p0.Z = (float)m_map->getHeight(minX, minY) * 0.0390625f;
            Vector3 p1;
            p1.X = (float)(m_xOrigin + right.x) * 10.0f - (float)m_map->getBorderSizeInline() * 10.0f;
            p1.Y = (float)(m_yOrigin + right.y) * 10.0f - (float)m_map->getBorderSizeInline() * 10.0f;
            p1.Z = (float)m_map->getHeight(m_xOrigin + right.x, m_yOrigin + right.y) * 0.0390625f;
            Vector3 p2;
            p2.X = (float)(m_xOrigin + left.x) * 10.0f - (float)m_map->getBorderSizeInline() * 10.0f;
            p2.Y = (float)(m_yOrigin + left.y) * 10.0f - (float)m_map->getBorderSizeInline() * 10.0f;
            p2.Z = (float)m_map->getHeight(m_xOrigin + left.x, m_yOrigin + left.y) * 0.0390625f;
            helper->rva00729F60(records, xOffset, yOffset, xWidth, yWidth, &p0, &p1, &p2);
        }
    } else {
        rightNdx = ndx[right.x + right.y * (m_width + 1)];
        leftNdx = ndx[left.x + left.y * (m_width + 1)];
        curIndex += 3;
    }
    Bool didLeft = true;
    Bool didRight = true;
    while (didLeft || didRight) {
        ICoord2D previousLeft = left;
        didLeft = terrain->advanceLeft(left, xOffset, yOffset, xWidth, yWidth);
        if (didLeft) {
            if (ib) ib[curIndex] = leftNdx;
            ++curIndex;
            if (ib) ib[curIndex] = rightNdx;
            ++curIndex;
            leftNdx = ndx[left.x + left.y * (m_width + 1)];
            if (ib) ib[curIndex] = leftNdx;
            ++curIndex;
            if (records) {
                Vector3 p0;
                p0.X = (float)(m_xOrigin + previousLeft.x) * 10.0f - (float)m_map->getBorderSizeInline() * 10.0f;
                p0.Y = (float)(m_yOrigin + previousLeft.y) * 10.0f - (float)m_map->getBorderSizeInline() * 10.0f;
                p0.Z = (float)m_map->getHeight(m_xOrigin + previousLeft.x, m_yOrigin + previousLeft.y) * 0.0390625f;
                Vector3 p1;
                p1.X = (float)(m_xOrigin + right.x) * 10.0f - (float)m_map->getBorderSizeInline() * 10.0f;
                p1.Y = (float)(m_yOrigin + right.y) * 10.0f - (float)m_map->getBorderSizeInline() * 10.0f;
                p1.Z = (float)m_map->getHeight(m_xOrigin + right.x, m_yOrigin + right.y) * 0.0390625f;
                Vector3 p2;
                p2.X = (float)(m_xOrigin + left.x) * 10.0f - (float)m_map->getBorderSizeInline() * 10.0f;
                p2.Y = (float)(m_yOrigin + left.y) * 10.0f - (float)m_map->getBorderSizeInline() * 10.0f;
                p2.Z = (float)m_map->getHeight(m_xOrigin + left.x, m_yOrigin + left.y) * 0.0390625f;
                helper->rva00729F60(records, xOffset, yOffset, xWidth, yWidth, &p0, &p1, &p2);
            }
        }
        ICoord2D previousRight = right;
        didRight = terrain->advanceRight(right, xOffset, yOffset, xWidth, yWidth);
        if (didRight) {
            if (ib) ib[curIndex] = leftNdx;
            ++curIndex;
            if (ib) ib[curIndex] = rightNdx;
            ++curIndex;
            rightNdx = ndx[right.x + right.y * (m_width + 1)];
            if (ib) ib[curIndex] = rightNdx;
            ++curIndex;
            if (records) {
                Vector3 p0;
                p0.X = (float)(m_xOrigin + left.x) * 10.0f - (float)m_map->getBorderSizeInline() * 10.0f;
                p0.Y = (float)(m_yOrigin + left.y) * 10.0f - (float)m_map->getBorderSizeInline() * 10.0f;
                p0.Z = (float)m_map->getHeight(m_xOrigin + left.x, m_yOrigin + left.y) * 0.0390625f;
                Vector3 p1;
                p1.X = (float)(m_xOrigin + previousRight.x) * 10.0f - (float)m_map->getBorderSizeInline() * 10.0f;
                p1.Y = (float)(m_yOrigin + previousRight.y) * 10.0f - (float)m_map->getBorderSizeInline() * 10.0f;
                p1.Z = (float)m_map->getHeight(m_xOrigin + previousRight.x, m_yOrigin + previousRight.y) * 0.0390625f;
                Vector3 p2;
                p2.X = (float)(m_xOrigin + right.x) * 10.0f - (float)m_map->getBorderSizeInline() * 10.0f;
                p2.Y = (float)(m_yOrigin + right.y) * 10.0f - (float)m_map->getBorderSizeInline() * 10.0f;
                p2.Z = (float)m_map->getHeight(m_xOrigin + right.x, m_yOrigin + right.y) * 0.0390625f;
                helper->rva00729F60(records, xOffset, yOffset, xWidth, yWidth, &p0, &p1, &p2);
            }
        }
    }
    if (topRightFlip) {
        if (ib) ib[curIndex] = leftNdx;
        ++curIndex;
        if (ib) ib[curIndex] = rightNdx;
        ++curIndex;
        if (ib) ib[curIndex] = (UnsignedShort)topRightNdx;
        ++curIndex;
        if (records) {
            Vector3 p0;
            p0.X = (float)(m_xOrigin + left.x) * 10.0f - (float)m_map->getBorderSizeInline() * 10.0f;
            p0.Y = (float)(m_yOrigin + left.y) * 10.0f - (float)m_map->getBorderSizeInline() * 10.0f;
            p0.Z = (float)m_map->getHeight(m_xOrigin + left.x, m_yOrigin + left.y) * 0.0390625f;
            Vector3 p1;
            p1.X = (float)(m_xOrigin + right.x) * 10.0f - (float)m_map->getBorderSizeInline() * 10.0f;
            p1.Y = (float)(m_xOrigin + right.y) * 10.0f - (float)m_map->getBorderSizeInline() * 10.0f;
            p1.Z = (float)m_map->getHeight(m_xOrigin + right.x, m_yOrigin + right.y) * 0.0390625f;
            Vector3 p2;
            p2.X = (float)(minX + xWidth) * 10.0f - (float)m_map->getBorderSizeInline() * 10.0f;
            p2.Y = (float)(minY + xWidth) * 10.0f - (float)m_map->getBorderSizeInline() * 10.0f;
            p2.Z = (float)m_map->getHeight(minX + xWidth, minY + xWidth) * 0.0390625f;
            helper->rva00729F60(records, xOffset, yOffset, xWidth, yWidth, &p0, &p1, &p2);
        }
    }
}
