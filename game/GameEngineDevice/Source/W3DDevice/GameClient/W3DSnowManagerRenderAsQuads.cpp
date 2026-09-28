// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWDebug /Igame/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/shims/sweep
// Retail 0x00724A20..0x00725373, full 2388-byte RET20 body with an EH frame.
// W3DSnowManager::renderAsQuads: the matched W3DSnowManager::render (0x00725710)
// calls it through ILT 0x000499B8 when point sprites are unavailable. The body
// is the GeneralsMD W3DSnow.cpp quad path (noise-table heights, fmod, inlined
// WWMath::Fast_Sin sway, four quad corners with the ZH UVs per flake) with the
// BFME changes shared by renderSubBox: integer emitter-spacing steps, a grey
// diffuse from the +0x98 gate, and the 0x00723C50 random helper.
// BFME builds the quads in world space instead of view space: the corner
// offsets are the camera's X axis plus/minus world up, scaled by
// m_quadSize*0.707f, and the world transform is the terrain transform.
// The box is split into m_40 x m_40 tiles (at least one); only the first tile
// is filled and each batch is redrawn once per tile with the terrain
// transform's translation offset by the tile position.
// Both four-step loops are rolled in retail; MSVC 7.1 fully unrolls the
// equivalent for loops, so they are written as do/while.
#define Matrix4x4 Matrix4
#include "winbase_shim.h"
#include "dx8wrapper.h"
#include "dx8fvf.h"
#include "rinfo.h"
#include "camera.h"
#include "wwmath.h"
#include "vector2.h"
#include "vector3.h"
#include "matrix4.h"

#define MAXIMUM_CAMERA_DISTANCE 100000
#define MODPOW2(x,y) ((x) & (y-1))
enum { SNOW_NOISE_X = 64, SNOW_NOISE_Y = 64 };
#define SNOW_BATCH_SIZE 2048

class BoxDynamicVBAccessClass
{
	const FVFInfoClass &FVFInfo;
	unsigned int Type;
	unsigned int FVF;
	unsigned int Start;
	unsigned short VertexCount;
	unsigned short VertexBufferOffset;
	VertexBufferClass *VertexBuffer;
public:
	BoxDynamicVBAccessClass(unsigned int type, unsigned int fvf, unsigned short vertex_count, unsigned int buffer);
	~BoxDynamicVBAccessClass(void);
	class WriteLockClass
	{
		BoxDynamicVBAccessClass *DynamicVBAccess;
		VertexFormatXYZNDUV2 *Vertices;
	public:
		WriteLockClass(BoxDynamicVBAccessClass *vb_access);
		~WriteLockClass(void);
		VertexFormatXYZNDUV2 *Get_Formatted_Vertex_Array(void) { return Vertices; }
	};
};

// Retail calls 0x00723C50 on this W3DSnowManager (thunk 0x00038C4E); the
// ledger still names it by its address-derived class.
class BfmeA1137
{
public:
	float cachedRandom();
};

class BaseHeightMapRenderObjClass;
extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;

class W3DSnowManager
{
public:
	void renderAsQuads(RenderInfoClass &, int, int, int, int);
private:
	char pad00[8];
	float *m_startingHeights;
	float m_time, m_velocity, m_fullTimePeriod;
	float m_frequencyScaleX, m_frequencyScaleY, m_amplitude;
	float m_pointSize, m_maxPointSize, m_minPointSize, m_quadSize;
	float m_boxDimensions, m_emitterSpacing;
	unsigned char m_isVisible, m_flag3D;
	char pad3E[0x40 - 0x3E];
	int m_40;	// tile repeat count, clamped to at least 1 here
	char pad44[0x68 - 0x44];
	IndexBufferClass *m_indexBuffer;
	TextureBaseClass *m_snowTexture;
	void *m_vertexBuffer;
	int m_dwBase, m_dwFlush, m_dwDiscard, m_leafDim;
	float m_snowCeiling, m_heightTraveled;
	int m_totalRendered;
	float m_cullOverscan;
	int m_94;
	int m_98;
};

void W3DSnowManager::renderAsQuads(RenderInfoClass &rinfo, int cubeOriginX, int cubeOriginY, int cubeDimX, int cubeDimY)
{
	Matrix3D view;	// fetched as in ZH; BFME no longer uses it
	Vector3 snowCenter;

	CameraClass &camera = rinfo.Camera;
	camera.Get_View_Matrix(&view);

	const Matrix3D &ctm = camera.Get_Transform();
	Vector3 right;
	right.X = ctm[0][0];
	right.Y = ctm[1][0];
	right.Z = ctm[2][0];
	Vector3 up(0.0f, 0.0f, 1.0f);
	Vector3 vertex_offsets[4] = {
		-right + up,
		-right - up,
		right - up,
		right + up
	};
	Vector2 quad_uvs[4] = {
		Vector2(0.0f, 0.0f),
		Vector2(0.0f, 1.0f),
		Vector2(1.0f, 1.0f),
		Vector2(1.0f, 0.0f)
	};

	int i = 0;
	do {
		vertex_offsets[i] *= m_quadSize * 0.707f;
	} while (++i < 4);

	Matrix3D terrainTm = ((RenderObjClass *)TheTerrainRenderObject)->Get_Transform();
	DX8Wrapper::Set_Transform(D3DTS_WORLD, terrainTm);
	DX8Wrapper::Set_Index_Buffer(m_indexBuffer, 0);

	int tiles = m_40;
	if (tiles < 1)
		tiles = 1;
	int stepX = (cubeDimX - cubeOriginX) / tiles;
	int stepY = (cubeDimY - cubeOriginY) / tiles;
	int y = cubeOriginY;
	int cubeOriginXRemainder = cubeOriginX;
	int endY = cubeOriginY + stepY;
	int endX = cubeOriginX + stepX;
	int totalPart = stepY * stepX;
	int spacing = (int)m_emitterSpacing;
	if (spacing < 1)
		spacing = 1;
	totalPart /= spacing * spacing;
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
		if (batchSize > SNOW_BATCH_SIZE)
			batchSize = SNOW_BATCH_SIZE;

		int numberInBatch = 0;
		BoxDynamicVBAccessClass vb_access(2, 5, batchSize * 4, 0);
		{
			BoxDynamicVBAccessClass::WriteLockClass lock(&vb_access);
			VertexFormatXYZNDUV2 *verts = lock.Get_Formatted_Vertex_Array();

			for (; y < endY; y += spacing)
			{
				for (int x = cubeOriginXRemainder; x < endX; x += spacing)
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
					snowCenter = Vector3((float)x, (float)y, h0);
					if (m_amplitude > 0.0f)
					{
						snowCenter.X += m_amplitude * WWMath::Fast_Sin(h0 * m_frequencyScaleX + (float)x);
						snowCenter.Y += m_amplitude * WWMath::Fast_Sin(h0 * m_frequencyScaleY + (float)y);
					}
					i = 0;
					do
					{
						*(Vector3 *)verts = snowCenter + vertex_offsets[i];
						verts->nx = 0;
						verts->ny = 0;
						verts->nz = 0;
						verts->diffuse = color;
						verts->u1 = quad_uvs[i].X;
						verts->v1 = quad_uvs[i].Y;
						verts->u2 = 0;
						verts->v2 = 0;
						verts++;
					} while (++i < 4);
					numberInBatch++;
				}
				cubeOriginXRemainder = cubeOriginX;
			}
flush_particles:
			;
		}

		if (numberInBatch)
		{
			// DX8Wrapper::Set_Vertex_Buffer(const DynamicVBAccessClass &) receives the BFME access object.
			DX8Wrapper::Set_Vertex_Buffer(*(DynamicVBAccessClass *)&vb_access);
			for (i = 0; i < tiles; i++)
			{
				for (int j = 0; j < tiles; j++)
				{
					Matrix3D tm = terrainTm;
					Vector3 pos = terrainTm.Get_Translation();
					pos += Vector3((float)(j * stepX), (float)(i * stepY), 0.0f);
					tm.Set_Translation(pos);
					DX8Wrapper::Set_Transform(D3DTS_WORLD, tm);
					DX8Wrapper::Draw_Triangles(0, numberInBatch * 2, 0, numberInBatch * 4);
				}
			}
			totalPart -= numberInBatch;
		}
	}
}
