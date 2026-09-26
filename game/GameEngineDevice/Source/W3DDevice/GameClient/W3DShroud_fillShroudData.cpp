// cl: /DNDEBUG /MD
//
// Retail 0x0071A520. Fill the BFME packed shroud pixels and logical levels.
// The reference W3DShroud::fillShroudData name and neighboring BFME methods
// prove the field layout used here.

typedef unsigned char UnsignedByte;
typedef unsigned short UnsignedShort;

class GlobalData
{
	char m_pad[0xc86];

public:
	UnsignedByte m_shroudAlpha;
};

extern GlobalData *TheWritableGlobalData;

unsigned int packShroudPixel(UnsignedByte level);

class W3DShroud
{
public:
	void fillShroudData(UnsignedByte level);

private:
	int m_numCellsX;
	int m_numCellsY;
	char m_padding08[0x10];
	UnsignedShort *m_shroudData;
	char m_padding1c[0x1c];
	UnsignedByte *m_finalFogData;
};

// ?fillShroudData@W3DShroud@@QAEXE@Z
void W3DShroud::fillShroudData(UnsignedByte level)
{
	int x;
	int y;
	UnsignedShort pixel;
	UnsignedShort *shroud;
	UnsignedByte *fog;

	if (level < TheWritableGlobalData->m_shroudAlpha)
		level = TheWritableGlobalData->m_shroudAlpha;

	pixel = (UnsignedShort)packShroudPixel(level);
	shroud = m_shroudData;
	for (y = 0; y < m_numCellsY; ++y)
	{
		for (x = 0; x < m_numCellsX; )
		{
			*shroud = pixel;
			++x;
			++shroud;
		}
	}

	fog = m_finalFogData;
	for (y = 0; y < m_numCellsY; ++y)
	{
		for (x = 0; x < m_numCellsX; ++x)
		{
			fog[x] = level;
		}
	}
}
