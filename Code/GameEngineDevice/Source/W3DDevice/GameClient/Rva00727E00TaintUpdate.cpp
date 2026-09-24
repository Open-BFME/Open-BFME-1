// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Include /ICode/Libraries/Source/WWVegas /ICode/Libraries/Source/WWVegas/WWLib
// Retail 0x00727E00 (684 bytes, RET4): per-frame taint surface update that follows the
// statement order of Zero Hour W3DShroud::render. Owner and method stay address-derived.

#include <string.h>
#include "basetype.h"

extern "C" __declspec(dllimport) double __cdecl floor(double value);

class GlobalData
{
public:
	unsigned char m_pad00[0xCF5];
	unsigned char m_taintOn;
};

extern GlobalData *TheWritableGlobalData;

class BfmeTaintManager
{
};

extern BfmeTaintManager *TheTaintManager;

class Gen_00880e30
{
public:
	void m(void);
};

class BaseHeightMapResetShroud
{
public:
	void reset30BC(void);
};

class Bfme5TextureHolderB
{
public:
	void bfmeDropTexture(void);
};

class SurfaceClass
{
public:
	void *Lock(int *pitch, int left, int top, int right, int bottom);
	void Unlock(void);
};

class W3DRadarResetSurface
{
public:
	~W3DRadarResetSurface();

private:
	void *m_surface;
};

class W3DRadarResetTexture
{
public:
	W3DRadarResetSurface getSurfaceLevel(void);
};

class ShroudFilter
{
public:
	int getMagFilter(void) const { return m_filter4; }
	void setMagFilter(int filter) { m_filter4 = filter; }
	void setMinFilter(int filter) { m_filter0 = filter; }
	int m_filter0;
	int m_filter4;
};

class ShroudTexture
{
public:
	ShroudFilter *getFilter(void);

	void *m_texture;
};

class TaintBuffer
{
public:
	void init(class WorldHeightMap *map, float cellWidth, float cellHeight);
	void fillTaintSurface(unsigned char alpha, SurfaceClass *surface);
};

class HeightMapRenderObjClass;
extern HeightMapRenderObjClass *TheTerrainRenderObject;

class Rva00727E00Map
{
public:
	int getBorderSize(void) const { return m_field10; }
	int getDrawOrgX(void) const { return m_field120E0; }
	int getDrawOrgY(void) const { return m_field120E4; }
	int getDrawWidth(void) const { return m_field120E8; }
	int getDrawHeight(void) const { return m_field120EC; }
	unsigned char m_pad00[0x10];
	int m_field10;
	unsigned char m_pad14[0x120E0 - 0x14];
	int m_field120E0;
	int m_field120E4;
	int m_field120E8;
	int m_field120EC;
};

class Rva00727E00TerrainView
{
public:
	unsigned char m_pad00[0x2FF4];
	Rva00727E00Map *m_map;
};

struct Rva00727E00DeviceVtable
{
	void *m_slot00;
	void *m_slot04;
	void *m_slot08;
	long (__stdcall *testCooperativeLevel)(void *device);
};

struct Rva00727E00Device
{
	Rva00727E00DeviceVtable *m_vtable;
};

extern Rva00727E00Device *g_device01340534;

struct Rva00727E00Record
{
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
};

class Rva00727A80
{
public:
	void update(const void *record);
};

class CameraClass;
class Rva00727E00
{
public:
	void update(CameraClass *unused);

	int m_width;
	int m_height;
	int m_08;
	int m_0C;
	float m_cellWidth;
	float m_cellHeight;
	void *m_data;
	ShroudTexture m_texture;
	int m_20;
	int m_24;
	int m_filter;
	float m_drawOriginX;
	float m_drawOriginY;
	unsigned char m_taintOn;
	unsigned char m_clear;
	unsigned char m_borderLevel;
	unsigned char m_pad37;
	void *m_38;
	void *m_3C;
};

// Caller 0x006EB500+0xC1 passes W3DView+0x104, witnessed m_3DCamera.
// ?update@Rva00727E00@@QAEXPAVCameraClass@@@Z
void Rva00727E00::update(CameraClass *unused)
{
	if (m_data == 0)
		return;

	ShroudTexture *texture = &m_texture;
	if (texture->m_texture == 0)
		return;

	Rva00727E00Device *device = g_device01340534;
	if (device != 0 &&
		device->m_vtable->testCooperativeLevel(device) != 0)
		return;

	if (TheWritableGlobalData != 0 &&
		TheWritableGlobalData->m_taintOn != m_taintOn)
	{
		reinterpret_cast<BaseHeightMapResetShroud *>(this)->reset30BC();
		reinterpret_cast<Bfme5TextureHolderB *>(this)->bfmeDropTexture();

		Rva00727E00Map *map =
			reinterpret_cast<Rva00727E00TerrainView *>(TheTerrainRenderObject)->m_map;
		reinterpret_cast<TaintBuffer *>(this)->init(
			reinterpret_cast<WorldHeightMap *>(map), m_cellWidth, m_cellHeight);

		if (TheTaintManager != 0)
			reinterpret_cast<Gen_00880e30 *>(TheTaintManager)->m();

		m_taintOn = TheWritableGlobalData->m_taintOn;
		m_clear = 1;
		if (m_data == 0)
			return;
	}

	Rva00727E00Map *map =
		reinterpret_cast<Rva00727E00TerrainView *>(TheTerrainRenderObject)->m_map;
	int visStartX = fast_float2long_round((float)floor((double)(
		((float)(map->getDrawOrgX() - map->getBorderSize()) / m_cellWidth) * 10.0f)));
	if (visStartX < 0)
		visStartX = 0;
	int visStartY = fast_float2long_round((float)floor((double)(
		((float)(map->getDrawOrgY() - map->getBorderSize()) / m_cellHeight) * 10.0f)));
	if (visStartY < 0)
		visStartY = 0;

	visStartX = 0;
	visStartY = 0;

	int width = visStartX + fast_float2long_round((float)floor((double)(
		((float)(map->getDrawWidth() - 1) / m_cellWidth) * 10.0f))) + 1;
	int height = visStartY + fast_float2long_round((float)floor((double)(
		((float)(map->getDrawHeight() - 1) / m_cellHeight) * 10.0f))) + 1;

	width = m_width;
	height = m_height;

	if (width > m_width)
	{
		visStartX -= width - m_width;
		if (visStartX < 0)
			visStartX = 0;
		width = m_width;
	}

	if (height > m_height)
	{
		visStartY -= height - m_height;
		if (visStartY < 0)
			visStartY = 0;
		height = m_height;
	}

	m_drawOriginX = (float)visStartX * m_cellWidth;
	m_drawOriginY = (float)visStartY * m_cellHeight;

	if (texture->getFilter()->getMagFilter() != m_filter)
	{
		texture->getFilter()->setMagFilter(m_filter);
		texture->getFilter()->setMinFilter(m_filter);
	}

	Rva00727E00Record record;
	W3DRadarResetSurface surface =
		reinterpret_cast<W3DRadarResetTexture *>(texture)->getSurfaceLevel();
	reinterpret_cast<Rva00727A80 *>(this)->update(&record);

	if (m_clear != 0)
	{
		m_clear = 0;
		reinterpret_cast<TaintBuffer *>(this)->fillTaintSurface(
			m_borderLevel, reinterpret_cast<SurfaceClass *>(&surface));
	}

	{
		unsigned char *source = reinterpret_cast<unsigned char *>(m_data);
		int pitch;
		unsigned char *destination = reinterpret_cast<unsigned char *>(
			reinterpret_cast<SurfaceClass *>(&surface)->Lock(
				&pitch, 1, 1, width + 1, height + 1));
		for (int y = 0; y < height; ++y)
		{
			memcpy(destination, source, width * 4);
			source += m_width * 4;
			destination += pitch;
		}
		reinterpret_cast<SurfaceClass *>(&surface)->Unlock();
	}
}
