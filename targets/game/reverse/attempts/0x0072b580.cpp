// ?fillVBRecursive@W3DTerrainBackground@@IAEXPAGPAUVertexFormatXYZDUV2@@HHH0AAH@Z
// partial score=0.25 date=2026-09-02
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// BFME-specific seven-argument terrain buffer recursion reconstructed from
// retail 0x0072B580.  Unlike the Zero Hour twin, BFME passes the vertex buffer
// as the second argument and performs vertex and index work in one traversal.

typedef unsigned short UnsignedShort;

struct ICoord2D
{
	int x;
	int y;
};

struct VertexFormatXYZDUV2;

class WorldHeightMap
{
public:
	int getHeight(int x, int y);
	bool getFlipState(int x, int y);

	int getXExtent() const { return m_width; }
	int getYExtent() const { return m_height; }

private:
	unsigned char m_opaque00[8];
	int m_width;
	int m_height;
};

class W3DTerrainBackground
{
protected:
	void fillVBRecursive(UnsignedShort *ib, VertexFormatXYZDUV2 *vb,
		int xOffset, int yOffset, int width, UnsignedShort *ndx,
		int &curIndex);

private:
	bool advanceLeft(ICoord2D &point, int xOffset, int yOffset, int width);
	bool advanceRight(ICoord2D &point, int xOffset, int yOffset, int width);

	unsigned char m_opaque00[0x40];
	int m_xOrigin;
	int m_yOrigin;
	int m_width;
	WorldHeightMap *m_map;
};

void W3DTerrainBackground::fillVBRecursive(UnsignedShort *ib,
	VertexFormatXYZDUV2 *vb, int xOffset, int yOffset, int width,
	UnsignedShort *ndx, int &curIndex)
{
	int *curIndexP = &curIndex;
	volatile float retailVertexLocals[23];
	int bottomLeftNdx;
	int topRightNdx;

	for (;;) {
		int limitX = m_map->getXExtent() - 1;
		int limitY = m_map->getYExtent() - 1;
		int minX = m_xOrigin + xOffset;
		int minY = m_yOrigin + yOffset;
		int localMaxX = xOffset + width;
		int localMaxY = yOffset + width;
		if (m_xOrigin + localMaxX > limitX)
			localMaxX = limitX - m_xOrigin;
		if (m_yOrigin + localMaxY > limitY)
			localMaxY = limitY - m_yOrigin;

		bottomLeftNdx = ndx[xOffset + yOffset * (m_width + 1)];
		topRightNdx = ndx[localMaxX + localMaxY * (m_width + 1)];

		bool terminal = width <= 1;
		if (!terminal) {
			int half = width / 2;
			terminal = m_map->getFlipState(m_xOrigin + xOffset + half,
				m_yOrigin + yOffset + half);
		}

		if (minX >= limitX || minY >= limitY)
			return;
		if (width == m_width || terminal)
			break;

		int halfWidth = width / 2;
		fillVBRecursive(ib, vb, xOffset, yOffset, halfWidth, ndx, *curIndexP);
		fillVBRecursive(ib, vb, xOffset, yOffset + halfWidth, halfWidth, ndx, *curIndexP);
		fillVBRecursive(ib, vb, xOffset + halfWidth, yOffset, halfWidth, ndx, *curIndexP);
		xOffset += halfWidth;
		yOffset += halfWidth;
		width = halfWidth;
	}
	retailVertexLocals[0] = 0.0f;

	UnsignedShort prevNdxLeft;
	UnsignedShort prevNdxRight;
	ICoord2D left = { xOffset, yOffset };
	ICoord2D right = { xOffset, yOffset };
	advanceLeft(left, xOffset, yOffset, width);
	advanceRight(right, xOffset, yOffset, width);

	if (ib)
		ib[*curIndexP] = (UnsignedShort)bottomLeftNdx;
	++*curIndexP;

	prevNdxRight = ndx[right.x + right.y * (m_width + 1)];
	if (ib)
		ib[*curIndexP] = prevNdxRight;
	++*curIndexP;

	prevNdxLeft = ndx[left.x + left.y * (m_width + 1)];
	if (ib)
		ib[*curIndexP] = prevNdxLeft;
	++*curIndexP;

	bool didLeft = true;
	bool didRight = true;
	while (didLeft || didRight) {
		didLeft = advanceLeft(left, xOffset, yOffset, width);
		if (didLeft) {
			if (ib) ib[*curIndexP] = prevNdxLeft;
			++*curIndexP;
			if (ib) ib[*curIndexP] = prevNdxRight;
			++*curIndexP;
			prevNdxLeft = ndx[left.x + left.y * (m_width + 1)];
			if (ib) ib[*curIndexP] = prevNdxLeft;
			++*curIndexP;
		}

		didRight = advanceRight(right, xOffset, yOffset, width);
		if (didRight) {
			if (ib) ib[*curIndexP] = prevNdxLeft;
			++*curIndexP;
			if (ib) ib[*curIndexP] = prevNdxRight;
			++*curIndexP;
			prevNdxRight = ndx[right.x + right.y * (m_width + 1)];
			if (ib) ib[*curIndexP] = prevNdxRight;
			++*curIndexP;
		}
	}

	if (ib) ib[*curIndexP] = prevNdxLeft;
	++*curIndexP;
	if (ib) ib[*curIndexP] = prevNdxRight;
	++*curIndexP;
	if (ib) ib[*curIndexP] = (UnsignedShort)topRightNdx;
	++*curIndexP;
}
