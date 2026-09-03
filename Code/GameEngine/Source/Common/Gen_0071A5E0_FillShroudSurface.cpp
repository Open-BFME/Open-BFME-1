// cl: /DNDEBUG /MD
//
// Retail 0x0071A5E0. Clamp the level to GlobalData shroud-alpha, pack a pixel,
// lock the given surface, flood-fill m_width x m_height shorts, unlock.

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

class BaseHeightMapResetShroud
{
public:
	void fillShroudSurface(UnsignedByte level, SurfaceClass *surface);

private:
	char m_pad[0x20];
	int m_width;
	int m_height;
};

void BaseHeightMapResetShroud::fillShroudSurface(UnsignedByte level, SurfaceClass *surface)
{
	if (level < TheWritableGlobalData->m_shroudAlpha)
		level = TheWritableGlobalData->m_shroudAlpha;

	UnsignedShort pixel = (UnsignedShort)packShroudPixel(level);
	UnsignedShort *bits = (UnsignedShort *)surface->Lock((int *)&level, 0);

	for (int y = 0; y < m_height; ++y)
	{
		for (int x = 0; x < m_width; ++x)
			bits[x] = pixel;
		bits = (UnsignedShort *)((char *)bits + *(int *)&level);
	}

	surface->Unlock();
}
