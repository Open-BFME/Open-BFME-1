// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Retail 0x00727610: update one BFME taint cell and its terrain pixel.

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>

typedef unsigned char UnsignedByte;

class GlobalData
{
	unsigned char m_pad00[0xc88];

public:
	float m_lowRed;
	float m_lowGreen;
	float m_lowBlue;
	float m_highRed;
	float m_highGreen;
	float m_highBlue;
	unsigned char m_padca0[0xcf5 - 0xca0];
	UnsignedByte m_taintOn;
};

extern GlobalData *TheWritableGlobalData;

class W3DShroud
{
public:
	UnsignedByte getShroudLevel(int x, int y);
};

class BaseHeightMapRenderObjClass
{
	unsigned char m_pad00[0x30b8];

public:
	W3DShroud *m_shroud;
};

extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;

class BaseHeightMapResetShroud
{
public:
	void setShroudLevel30BC(int x, int y, UnsignedByte level, bool textureOnly);

private:
	int m_numCellsX;
	int m_numCellsY;
	unsigned char m_padding08[0x10];
	unsigned int *m_taintData;
	unsigned char m_padding1c[0x1c];
	UnsignedByte *m_38;
	UnsignedByte *m_3c;
	UnsignedByte m_40;
	unsigned char m_padding41[3];
	_STL::set<int> m_dirty;
};

// ?setShroudLevel30BC@BaseHeightMapResetShroud@@QAEXHHE_N@Z
void BaseHeightMapResetShroud::setShroudLevel30BC(int x, int y,
	UnsignedByte level, bool textureOnly)
{
	if (m_taintData == 0)
		return;
	if (x >= m_numCellsX)
		return;
	int maxY = m_numCellsY;
	if (y >= maxY)
		return;

	if (TheWritableGlobalData == 0)
		return;
	if (!TheWritableGlobalData->m_taintOn)
		return;

	if (!textureOnly)
	{
		int cell = x + y * m_numCellsX;
		m_38[cell] = level;
		if (m_40)
			m_dirty.insert(cell);
	}

	int yForColor = y;
	register int levelValue = level;
	float red;
	float green;
	float blue;
	if (level < 0x80)
	{
		int delta = 0x80 - levelValue;
		float fraction = (float)delta;
		int xMod5 = x % 5;
		fraction *= *(const float *)0x010888f4;
		float base = 1.0f - fraction;
		float redAdjustment;
		float greenAdjustment;
		float blueAdjustment;

		if (xMod5 == 0 && yForColor % 2 == 0)
			redAdjustment = *(const float *)0x01075354;
		else
			redAdjustment = *(const float *)0x01121290;

		if (x % 3 == 0 && yForColor % 5 == 0)
			greenAdjustment = *(const float *)0x01121290;
		else
			greenAdjustment = *(const float *)0x01075354;

		if (x % 2 == 0 && yForColor % 3 == 0)
			blueAdjustment = *(const float *)0x0112128c;
		else
			blueAdjustment = *(const float *)0x0107c6ec;

		red = base + fraction * (TheWritableGlobalData->m_lowRed + redAdjustment);
		green = base + fraction * (TheWritableGlobalData->m_lowGreen + greenAdjustment);
		blue = base + fraction * (TheWritableGlobalData->m_lowBlue + blueAdjustment);
	}
	else if (level > 0x80)
	{
		int delta = levelValue - 0x80;
		float fraction = (float)delta;
		int xMod5 = x % 5;
		fraction *= *(const float *)0x01121288;
		float base = 1.0f - fraction;
		float redAdjustment;
		float greenAdjustment;
		float blueAdjustment;

		if (xMod5 == 0 && yForColor % 2 == 0)
			redAdjustment = *(const float *)0x01075354;
		else
			redAdjustment = *(const float *)0x01121290;

		if (x % 3 == 0 && yForColor % 5 == 0)
			greenAdjustment = *(const float *)0x01121290;
		else
			greenAdjustment = *(const float *)0x01075354;

		if (x % 2 == 0 && yForColor % 3 == 0)
			blueAdjustment = *(const float *)0x0112128c;
		else
			blueAdjustment = *(const float *)0x0107c6ec;

		red = base + fraction * (TheWritableGlobalData->m_highRed + redAdjustment);
		green = base + fraction * (TheWritableGlobalData->m_highGreen + greenAdjustment);
		blue = base + fraction * (TheWritableGlobalData->m_highBlue + blueAdjustment);
	}
	else
	{
		red = 1.0f;
		green = 1.0f;
		blue = 1.0f;
	}

	int currentShroudLevel = 0xff;
	W3DShroud *shroud = TheTerrainRenderObject->m_shroud;
	if (shroud)
		currentShroudLevel = shroud->getShroudLevel(x, yForColor);

	unsigned int redPixel =
		(unsigned int)(red * (float)currentShroudLevel);
	unsigned int greenPixel =
		(unsigned int)(green * (float)currentShroudLevel);
	unsigned int bluePixel =
		(unsigned int)(blue * (float)currentShroudLevel);
	unsigned int pixel = redPixel & 0xff;
	pixel |= (unsigned int)levelValue << 8;
	pixel <<= 8;
	pixel |= greenPixel & 0xff;
	pixel <<= 8;
	pixel |= bluePixel & 0xff;
	m_taintData[x + m_numCellsX * yForColor] = pixel;
}
