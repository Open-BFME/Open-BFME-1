// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWDebug /Igame/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/shims/sweep
// Retail 0x00724570..0x00724923, full 948-byte RET20 body.
// W3DSnowManager::renderSubBox: the matched W3DSnowManager::render (0x00725710)
// calls it through ILT 0x000440DF, and the body is the leaf half of the
// GeneralsMD W3DSnow.cpp renderSubBox (starting-height noise table, fmod,
// two inlined WWMath::Fast_Sin, batched D3D point-list flushes).
// BFME drops the frustum-culling recursion, steps x/y by an integer emitter
// spacing (so the particle count is divided by spacing squared), writes a
// 16-byte XYZ+diffuse vertex whose grey level comes from the +0x98 gate, and
// records statistics against ShaderClass::_PresetAlphaShader.
// Member layout follows the matched render/ReAcquireResources views.
#define Matrix4x4 Matrix4
#include "winbase_shim.h"
#include "dx8wrapper.h"
#include "statistics.h"
#include "wwmath.h"
#include "vector3.h"

#define MAXIMUM_CAMERA_DISTANCE 100000
#define MODPOW2(x,y) ((x) & (y-1))
enum { SNOW_NOISE_X = 64, SNOW_NOISE_Y = 64 };

struct POINTVERTEX
{
	Vector3 v;
	unsigned int diffuse;
};

// Retail calls 0x00723C50 on this W3DSnowManager (thunk 0x00038C4E); the
// ledger still names it by its address-derived class.
class BfmeA1137
{
public:
	float cachedRandom();
};

struct Rva00724570VertexBuffer;
struct Rva00724570VertexBufferVtable
{
	void *slots00[11];
	long (__stdcall *Lock)(Rva00724570VertexBuffer *, unsigned, unsigned, void **, unsigned);
	long (__stdcall *Unlock)(Rva00724570VertexBuffer *);
};
struct Rva00724570VertexBuffer { Rva00724570VertexBufferVtable *vtable; };

// BFME binds a D3D9 device: DrawPrimitive is slot 81.
struct Rva00724570Device;
struct Rva00724570DeviceVtable
{
	void *slots00[81];
	long (__stdcall *DrawPrimitive)(Rva00724570Device *, unsigned, unsigned, unsigned);
};
struct Rva00724570Device { Rva00724570DeviceVtable *vtable; };

class W3DSnowManager
{
public:
	void renderSubBox(RenderInfoClass &, int, int, int, int);
private:
	char pad00[8];
	float *m_startingHeights;
	float m_time, m_velocity, m_fullTimePeriod;
	float m_frequencyScaleX, m_frequencyScaleY, m_amplitude;
	float m_pointSize, m_maxPointSize, m_minPointSize, m_quadSize;
	float m_boxDimensions, m_emitterSpacing;
	unsigned char m_isVisible, m_flag3D;
	char pad3E[0x68 - 0x3E];
	void *m_indexBuffer;
	TextureBaseClass *m_snowTexture;
	Rva00724570VertexBuffer *m_vertexBuffer;
	int m_dwBase, m_dwFlush, m_dwDiscard, m_leafDim;
	float m_snowCeiling, m_heightTraveled;
	int m_totalRendered;
	float m_cullOverscan;
	int m_94;
	int m_98;
};

void W3DSnowManager::renderSubBox(RenderInfoClass &rinfo, int originX, int originY, int cubeDimX, int cubeDimY)
{
	int y = originY;
	int totalPart = (cubeDimX - originX) * (cubeDimY - originY);
	int spacing = (int)m_emitterSpacing;
	if (spacing < 1)
		spacing = 1;
	totalPart /= spacing * spacing;
	int cubeOriginXRemainder = originX;
	m_totalRendered += totalPart;

	int gray;
	if (m_98)
		gray = (int)(((BfmeA1137 *)this)->cachedRandom() * 255.0f);
	else
		gray = 255;
	unsigned int color = gray * 0x10101 + 0xFF000000;

	while (totalPart)
	{
		int batchSize = totalPart;
		if (batchSize > m_dwFlush)
			batchSize = m_dwFlush;
		if (m_dwBase + batchSize > m_dwDiscard)
			m_dwBase = 0;

		POINTVERTEX *verts;
		if (m_vertexBuffer->vtable->Lock(m_vertexBuffer, m_dwBase * sizeof(POINTVERTEX), batchSize * sizeof(POINTVERTEX),
			(void **)&verts, m_dwBase ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD) != D3D_OK)
			return;

		int numberInBatch = 0;
		for (; y < cubeDimY; y += spacing)
		{
			for (int x = cubeOriginXRemainder; x < cubeDimX; x += spacing)
			{
				if (numberInBatch >= batchSize)
				{
					cubeOriginXRemainder = x;
					goto flush_particles;
				}
				int noiseOffset = MODPOW2(x + MAXIMUM_CAMERA_DISTANCE, SNOW_NOISE_X) +
					MODPOW2(y + MAXIMUM_CAMERA_DISTANCE, SNOW_NOISE_Y) * SNOW_NOISE_X;
				if (noiseOffset > SNOW_NOISE_X * SNOW_NOISE_Y)
					noiseOffset = 0;
				float h0 = m_snowCeiling - fmod(m_startingHeights[noiseOffset] + m_heightTraveled, m_boxDimensions);
				Vector3 snowCenter;
				snowCenter.Set((float)x, (float)y, h0);
				snowCenter.X += m_amplitude * WWMath::Fast_Sin(h0 * m_frequencyScaleX + (float)x);
				snowCenter.Y += m_amplitude * WWMath::Fast_Sin(h0 * m_frequencyScaleY + (float)y);
				verts->v = snowCenter;
				verts->diffuse = color;
				verts++;
				numberInBatch++;
			}
			cubeOriginXRemainder = originX;
		}

flush_particles:
		m_vertexBuffer->vtable->Unlock(m_vertexBuffer);
		if (numberInBatch)
		{
			Debug_Statistics::Record_DX8_Polys_And_Vertices(numberInBatch * 2, numberInBatch * 4, ShaderClass::_PresetAlphaShader);
			Rva00724570Device *device = (Rva00724570Device *)DX8Wrapper::_Get_D3D_Device8();
			device->vtable->DrawPrimitive(device, D3DPT_POINTLIST, m_dwBase, numberInBatch);
			totalPart -= numberInBatch;
			m_dwBase += numberInBatch;
		}
	}
}
