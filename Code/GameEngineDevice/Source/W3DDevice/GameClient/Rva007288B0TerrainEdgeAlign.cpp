// cl: /DNDEBUG /MD
// Retail 0x007288B0: classify a terrain tile edge against the active map.

typedef bool Bool;

class Rva007288B0HeightMap
{
public:
	unsigned char m_pad00[0x08];
	int m_width;
	int m_height;
};

class Rva007288B0Terrain
{
public:
	Bool isEdgeAligned(int yArg, int xArg, int requested);

private:
	unsigned char m_pad00[0x40];
	int m_xOrigin;
	int m_yOrigin;
	int m_width;
	Rva007288B0HeightMap *m_map;
	unsigned char m_pad50[0x28];
	int m_78;
	unsigned char m_pad7c[0x1c];
	int m_98;
	int m_9c;
	int m_a0;
	int m_a4;
	int m_a8;
	int m_ac;
	int m_b0;
	int m_b4;
	int m_b8;
};

// ?isEdgeAligned@Rva007288B0Terrain@@QAE_NHHH@Z
Bool Rva007288B0Terrain::isEdgeAligned(int x, int y, int requested)
{
	int yValue = y;
	Rva007288B0HeightMap *map = m_map;
	int limitY = map->m_height - 1;
	if (yValue != 0)
		goto afterMapRightEdge;
	{
		int limitX = map->m_width - 1;
		if (m_xOrigin + x == limitX)
			goto resultTrue;
	}

afterMapRightEdge:
	if (x != 0)
		goto afterMapBottomEdge;
	if (m_yOrigin + yValue == limitY)
		goto resultTrue;
	if (yValue == 0)
		goto resultTrue;

afterMapBottomEdge:
	{
		int width = m_width;
		if (x == width)
		{
			if (yValue == width)
				goto resultTrue;
		}
		if (x == 0)
		{
			if (yValue == width)
				goto resultTrue;
		}
		if (x == width)
		{
			if (yValue == 0)
				goto resultTrue;
		}
	}

	int divisor;
	if (x == 0)
	{
		int feature = m_98;
		if (feature == 0)
		{
			divisor = m_78;
			goto divideY;
		}
		int enabled = m_b8;
		if (enabled != 0)
		{
			divisor = m_9c;
			goto divideY;
		}
		divisor = feature;
		goto divideY;
	}
	if (yValue == 0)
	{
		int feature = m_b0;
		if (feature == 0)
		{
			divisor = m_78;
			goto divideX;
		}
		int enabled = m_b8;
		if (enabled != 0)
		{
			divisor = m_b4;
			goto divideX;
		}
		divisor = feature;
		goto divideX;
	}
	if (x == m_width)
	{
		int feature = m_a8;
		if (feature == 0)
		{
			divisor = m_78;
			goto divideY;
		}
		int enabled = m_b8;
		if (enabled != 0)
		{
			divisor = m_ac;
			goto divideY;
		}
		divisor = feature;
		goto divideY;
	}
	if (yValue == m_width)
	{
		int feature = m_a0;
		if (feature == 0)
		{
			divisor = m_78;
			goto divideX;
		}
		int enabled = m_b8;
		if (enabled != 0)
		{
			divisor = m_a4;
			goto divideX;
		}
		divisor = feature;
		goto divideX;
	}
	goto resultTrue;

divideY:
	if (requested >= divisor)
		goto resultTrue;
	if (yValue % divisor == 0)
		goto resultTrue;
	return 0;

divideX:
	if (requested >= divisor)
		goto resultTrue;
	if (x % divisor == 0)
		goto resultTrue;
	return 0;

resultTrue:
	return 1;
}
