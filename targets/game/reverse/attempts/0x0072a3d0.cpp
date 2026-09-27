// ?rva0072A3D0@Rva0072A3D0Owner@@QAEXPAGPAMHHHH0AAH@Z
// partial score=0.35 date=2026-09-27
// Opaque terrain-cell emitter trial for retail 0x0072A3D0.
// Receiver fields and helper ABIs come from adjacent landed terrain bodies.
// This is an untracked probe candidate, not a production claim.

#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE
typedef bool Bool;
typedef int Int;
typedef unsigned short UnsignedShort;

class Vector3
{
public:
	float X;
	float Y;
	float Z;
};

struct ICoord2D
{
	Int x;
	Int y;
};

class Rva00729300BitPlane
{
public:
	Bool test(Int x, Int y) const;
};

class WorldHeightMap
{
public:
	Int getXExtent(void) const { return m_width; }
	Int getYExtent(void) const { return m_height; }
	Int getBorderSizeInline(void) const { return m_borderSize; }
	UnsignedShort getHeight(Int x, Int y) const
	{
		Int index = m_width * y + x;
		if (index < 0 || index >= m_dataSize || m_data == 0)
			return 0;
		return m_data[index];
	}

	Int m_refs;
	Int m_width;
	Int m_height;
	Int m_borderSize;
	unsigned char m_pad14[0x0c];
	Int m_dataSize;
	UnsignedShort *m_data;
};

class W3DTerrainBackground
{
public:
	Bool advanceLeft(ICoord2D &point, Int xOffset, Int yOffset, Int width);
	Bool advanceRight(ICoord2D &point, Int xOffset, Int yOffset, Int width);
};

class Rva00729F60Owner
{
public:
	void rva00729F60(float *records, Int xOrigin, Int yOrigin,
		Int outerEnd, Int innerEnd, const Vector3 *first,
		const Vector3 *second, const Vector3 *third);
};

class Rva0072A3D0Owner
{
public:
	void rva0072A3D0(UnsignedShort *ib, float *records, Int xOffset,
		Int yOffset, Int xWidth, Int yWidth, UnsignedShort *ndx,
		Int &curIndex);

private:
	unsigned char m_pad00[0x40];
	Int m_xOrigin;
	Int m_yOrigin;
	Int m_width;
	WorldHeightMap *m_map;
};

static Vector3 rva0072A3D0Point(WorldHeightMap *map, Int x, Int y)
{
	Vector3 point;
	Int limitX = map->getXExtent() - 1;
	Int limitY = map->getYExtent() - 1;
	Int k = x < limitX ? x : limitX;
	Int l = y < limitY ? y : limitY;
	point.X = (float)x * 10.0f - (float)map->getBorderSizeInline() * 10.0f;
	point.Y = (float)y * 10.0f - (float)map->getBorderSizeInline() * 10.0f;
	point.Z = (float)map->getHeight(k, l) * (10.0f / 256.0f);
	return point;
}

void Rva0072A3D0Owner::rva0072A3D0(UnsignedShort *ib, float *records,
	Int xOffset, Int yOffset, Int xWidth, Int yWidth, UnsignedShort *ndx,
	Int &curIndex)
{
	WorldHeightMap *map = m_map;
	Int limitX = map->getXExtent() - 1;
	Int limitY = map->getYExtent() - 1;
	Int maxX = xOffset + xWidth;
	Int maxY = yOffset + yWidth;
	if (m_xOrigin + maxX > limitX)
		maxX = limitX - m_xOrigin;
	if (m_yOrigin + maxY > limitY)
		maxY = limitY - m_yOrigin;

	Int stride = m_width + 1;
	Rva00729300BitPlane *flipMap = (Rva00729300BitPlane *)map;
	Bool topRightFlip = flipMap->test(m_xOrigin + maxX, m_yOrigin + maxY);
	Int topRightNdx = ndx[maxX + maxY * stride];

	W3DTerrainBackground *terrain = (W3DTerrainBackground *)this;
	ICoord2D left = {xOffset, yOffset};
	ICoord2D right = {xOffset, yOffset};
	Bool leftFound = terrain->advanceLeft(left, xOffset, yOffset, xWidth);
	Bool rightFound = terrain->advanceRight(right, xOffset, yOffset, xWidth);
	Bool bottomLeftFlip = flipMap->test(m_xOrigin + left.x,
		m_yOrigin + left.y);
	Int bottomLeftNdx = ndx[xOffset + yOffset * stride];
	Int leftNdx = ndx[left.x + left.y * stride];
	Int rightNdx = ndx[right.x + right.y * stride];

	Rva00729F60Owner *helper = (Rva00729F60Owner *)this;
	if (topRightFlip) {
		if (ib)
			ib[curIndex] = (UnsignedShort)bottomLeftNdx;
		++curIndex;
		if (ib)
			ib[curIndex] = (UnsignedShort)rightNdx;
		++curIndex;
		if (ib)
			ib[curIndex] = (UnsignedShort)leftNdx;
		++curIndex;
		if (records) {
			Vector3 p0 = rva0072A3D0Point(map, m_xOrigin + xOffset,
				m_yOrigin + yOffset);
			Vector3 p1 = rva0072A3D0Point(map, m_xOrigin + right.x,
				m_yOrigin + right.y);
			Vector3 p2 = rva0072A3D0Point(map, m_xOrigin + left.x,
				m_yOrigin + left.y);
			helper->rva00729F60(records, xOffset, yOffset, xWidth, yWidth,
				&p0, &p1, &p2);
		}
	} else {
		if (ib)
			ib[curIndex] = (UnsignedShort)bottomLeftNdx;
		++curIndex;
		if (ib)
			ib[curIndex] = (UnsignedShort)leftNdx;
		++curIndex;
		if (ib)
			ib[curIndex] = (UnsignedShort)rightNdx;
		++curIndex;
	}

	Bool didLeft = leftFound;
	Bool didRight = rightFound;
	while (didLeft || didRight) {
		didLeft = terrain->advanceLeft(left, xOffset, yOffset, xWidth);
		if (didLeft) {
			if (ib)
				ib[curIndex] = (UnsignedShort)leftNdx;
			++curIndex;
			if (ib)
				ib[curIndex] = (UnsignedShort)rightNdx;
			++curIndex;
			leftNdx = ndx[left.x + left.y * stride];
			if (ib)
				ib[curIndex] = (UnsignedShort)leftNdx;
			++curIndex;
			if (records) {
				Vector3 p0 = rva0072A3D0Point(map, m_xOrigin + left.x,
					m_yOrigin + left.y);
				Vector3 p1 = rva0072A3D0Point(map, m_xOrigin + right.x,
					m_yOrigin + right.y);
				Vector3 p2 = rva0072A3D0Point(map, m_xOrigin + left.x,
					m_yOrigin + left.y);
				helper->rva00729F60(records, xOffset, yOffset, xWidth, yWidth,
					&p0, &p1, &p2);
			}
		}
		didRight = terrain->advanceRight(right, xOffset, yOffset, xWidth);
		if (didRight) {
			if (ib)
				ib[curIndex] = (UnsignedShort)leftNdx;
			++curIndex;
			if (ib)
				ib[curIndex] = (UnsignedShort)rightNdx;
			++curIndex;
			rightNdx = ndx[right.x + right.y * stride];
			if (ib)
				ib[curIndex] = (UnsignedShort)rightNdx;
			++curIndex;
			if (records) {
				Vector3 p0 = rva0072A3D0Point(map, m_xOrigin + left.x,
					m_yOrigin + left.y);
				Vector3 p1 = rva0072A3D0Point(map, m_xOrigin + right.x,
					m_yOrigin + right.y);
				Vector3 p2 = rva0072A3D0Point(map, m_xOrigin + right.x,
					m_yOrigin + right.y);
				helper->rva00729F60(records, xOffset, yOffset, xWidth, yWidth,
					&p0, &p1, &p2);
			}
		}
	}

	if (ib)
		ib[curIndex] = (UnsignedShort)leftNdx;
	++curIndex;
	if (ib)
		ib[curIndex] = (UnsignedShort)rightNdx;
	++curIndex;
	if (ib)
		ib[curIndex] = (UnsignedShort)topRightNdx;
	++curIndex;
	if (records && bottomLeftFlip) {
		Vector3 p0 = rva0072A3D0Point(map, m_xOrigin + left.x,
			m_yOrigin + left.y);
		Vector3 p1 = rva0072A3D0Point(map, m_xOrigin + right.x,
			m_yOrigin + right.y);
		Vector3 p2 = rva0072A3D0Point(map, m_xOrigin + maxX,
			m_yOrigin + maxY);
		helper->rva00729F60(records, xOffset, yOffset, xWidth, yWidth,
			&p0, &p1, &p2);
	}
}
