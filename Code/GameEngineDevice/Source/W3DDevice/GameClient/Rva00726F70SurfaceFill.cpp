// cl: /DNDEBUG /MD
// Retail 0x00726F70: fill a locked surface with the requested taint color.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
class GlobalData
{
public:
	unsigned char m_pad00[0xCF5];
	unsigned char m_taintOn;
};

extern GlobalData *TheWritableGlobalData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/surfaceclass.h
class SurfaceClass
{
public:
	void *Lock(int *pitch, bool discard);
	void Unlock(void);
};

class Rva00726F70SurfaceFill
{
public:
	void fill(unsigned char alpha, SurfaceClass *surface);

private:
	unsigned char m_pad00[0x20];
	int m_width;
	int m_height;
};

// ?fill@Rva00726F70SurfaceFill@@QAEXEPAVSurfaceClass@@@Z
void Rva00726F70SurfaceFill::fill(unsigned char alpha, SurfaceClass *surface)
{
	GlobalData *g = TheWritableGlobalData;
	if (!g)
		return;
	if (!g->m_taintOn)
		return;

	unsigned int color = alpha;
	color = (color << 8) | alpha;
	color = (color << 8) | alpha;
	color = (color << 8) | alpha;

	int pitch;
	unsigned int *pixels = (unsigned int *)surface->Lock(&pitch, false);
	for (int y = 0; y < m_height; y++)
	{
		for (int x = 0; x < m_width; x++)
			pixels[x] = color;
		pixels = (unsigned int *)((unsigned char *)pixels + pitch);
	}
	surface->Unlock();
}
