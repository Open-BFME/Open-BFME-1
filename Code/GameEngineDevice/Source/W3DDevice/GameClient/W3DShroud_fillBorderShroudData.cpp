// cl: /DNDEBUG /MD
//
// W3DShroud::fillBorderShroudData, retail 0x0071A5E0. Clamp the level to
// GlobalData shroud-alpha, pack a pixel, lock the surface, flood-fill, unlock.

typedef unsigned char UnsignedByte;
typedef unsigned short UnsignedShort;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
class GlobalData
{
public:
	char m_pad[0xc86];
	UnsignedByte m_shroudAlpha;
};

extern GlobalData *TheWritableGlobalData;

unsigned int packShroudPixel(UnsignedByte level);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/surfaceclass.h
class SurfaceClass
{
public:
	void *Lock(int *pitch, bool discard);
	void Unlock(void);
};

class W3DShroud
{
protected:
	void fillBorderShroudData(UnsignedByte level, SurfaceClass *surface);

private:
	char m_pad[0x20];
	int m_dstTextureWidth;
	int m_dstTextureHeight;
};

// ?fillBorderShroudData@W3DShroud@@IAEXEPAVSurfaceClass@@@Z
void W3DShroud::fillBorderShroudData(UnsignedByte level, SurfaceClass *surface)
{
	if (level < TheWritableGlobalData->m_shroudAlpha)
		level = TheWritableGlobalData->m_shroudAlpha;

	UnsignedShort pixel = (UnsignedShort)packShroudPixel(level);
	UnsignedShort *bits = (UnsignedShort *)surface->Lock((int *)&level, 0);

	for (int y = 0; y < m_dstTextureHeight; ++y)
	{
		for (int x = 0; x < m_dstTextureWidth; ++x)
			bits[x] = pixel;
		bits = (UnsignedShort *)((char *)bits + *(int *)&level);
	}

	surface->Unlock();
}
