// ?apply@Rva00710620@@QAEXPAVCameraClass@@ABVBfmeHandleCX@@1_NHHHHPAX@Z
// partial score=0.21231884057971015 date=2026-09-25
// Retail 0x00710620, caller-backed road rendering body.
// The owner remains address-derived because no unique class owner is proven.
// The handle, road-type, set, and helper ABIs are witnessed independently.

// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/w3droadbuffer /Ireference/shims/stringbaseascii /Ireference/shims/asciistring_downloadmanager /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport

#define __PLACEMENT_VEC_NEW_INLINE
#include "always.h"
#include "Common/MapObject.h"
#include <set>
#include "common/GlobalData.h"
#include "W3DDevice/GameClient/W3DShaderManager.h"
#include "WW3D2/DX8Wrapper.h"
#include "WW3D2/Camera.h"
#include "texture.h"

class TextureClass;
class CameraClass;
class DX8VertexBufferClass;
class DX8IndexBufferClass;

class BFMETextureRelease
{
public:
	void Release_Ref(void);
};

class BfmeHandleCX
{
public:
	~BfmeHandleCX(void)
	{
		if (m_texture)
			m_texture->Release_Ref();
	}

	operator TextureBaseClass *&(void)
	{
		return *(TextureBaseClass **)&m_texture;
	}

	BFMETextureRelease *m_texture;
};

class RefCountedTarget
{
public:
	int m_first;
	unsigned short m_refCount;
	unsigned short m_pad;
};

class Rva00707000Owner
{
public:
	RefCountedTarget *m_target;
	BfmeHandleCX getHandle(void) const;
};

struct Rva0013FA60Target
{
	virtual void *slot0(void) = 0;
};

struct RvaRoadType
{
	Rva00707000Owner m_handleOwner;
	DX8VertexBufferClass *m_vertexRoad;
	DX8IndexBufferClass *m_indexRoad;
	int m_numRoadVertices;
	int m_numRoadIndices;
	int m_uniqueID;
	unsigned char m_isAutoLoaded;
	unsigned char m_pad1d[3];
	int m_stackingOrder;
	unsigned char m_texturePath[4];
};

struct RvaCoord2D
{
	int x;
	int y;
};

struct RvaRegion2D
{
	RvaCoord2D lo;
	RvaCoord2D hi;
	unsigned char m_unused[4];
};

class W3DRoadBuffer
{
public:
	void loadRoadsInVertexAndIndexBuffers(void);
	bool visibilityChanged(const RvaRegion2D &bounds);
};

extern void BoxSetTexture(unsigned int stage, TextureBaseClass *&texture);
extern int Rva00716970Lookup(int shader);
extern void Rva009EBAC0(int value);
extern void *bfmeGoEMEb(void *value);

struct Rva00710620Fields
{
	RvaRoadType *m_roadTypes;
	void *m_roads;
	int m_numRoads;
	unsigned char m_initialized;
	unsigned char m_pad0d[3];
	void *m_map;
	void *m_lightsIterator;
	int m_bfmeUnk18;
	int m_bfmeUnk1c;
	int m_bfmeUnk20;
	int m_bfmeUnk24;
	int m_curUniqueID;
	int m_curRoadType;
	int m_maxUID;
	int m_curOpenRoad;
	int m_maxRoadSegments;
	int m_maxRoadVertex;
	int m_maxRoadIndex;
	int m_maxRoadTypes;
	int m_curNumRoadVertices;
	int m_curNumRoadIndices;
	unsigned char m_updateBuffers;
	unsigned char m_visibilityDirty;
	unsigned char m_pad52[2];
	BFMETextureRelease *m_texture;
};

typedef _STL::set<Rva0013FA60Target *> RvaAssetSet;

class Rva00710620
{
public:
	RvaRoadType *m_roadTypes;
	void *m_roads;
	int m_numRoads;
	unsigned char m_initialized;
	unsigned char m_pad0d[3];
	void *m_map;
	void *m_lightsIterator;
	int m_bfmeUnk18;
	int m_bfmeUnk1c;
	int m_bfmeUnk20;
	int m_bfmeUnk24;
	int m_curUniqueID;
	int m_curRoadType;
	int m_maxUID;
	int m_curOpenRoad;
	int m_maxRoadSegments;
	int m_maxRoadVertex;
	int m_maxRoadIndex;
	int m_maxRoadTypes;
	int m_curNumRoadVertices;
	int m_curNumRoadIndices;
	unsigned char m_updateBuffers;
	unsigned char m_visibilityDirty;
	unsigned char m_pad52[2];
	BFMETextureRelease *m_texture;
	void apply(CameraClass *camera, const BfmeHandleCX &cloudTexture,
		const BfmeHandleCX &noiseTexture, bool wireframe,
		int minX, int maxX, int minY, int maxY, void *pDynamicLightsIterator);
};

static void retainTexture(BFMETextureRelease *texture)
{
	if (texture)
		++*(unsigned short *)((char *)texture + 4);
}

void Rva00710620::apply(CameraClass *, const BfmeHandleCX &cloudTexture,
	const BfmeHandleCX &noiseTexture, bool wireframe,
	int minX, int maxX, int minY, int maxY, void *)
{
	int boundsWords[5];
	if (!m_initialized)
		return;

	boundsWords[0] = minX * MAP_XY_FACTOR;
	boundsWords[2] = maxX * MAP_XY_FACTOR;
	boundsWords[1] = minY * MAP_XY_FACTOR;
	boundsWords[3] = maxY * MAP_XY_FACTOR;

	int maxStacking = 0;
	for (int i = 0; i < m_maxRoadTypes; ++i)
	{
		if (m_roadTypes[i].m_stackingOrder > maxStacking)
			maxStacking = m_roadTypes[i].m_stackingOrder;
	}

	int one = 1;
	int devicePasses = one;
	unsigned char *globalData = (unsigned char *)TheWritableGlobalData;
	int shader = W3DShaderManager::ST_ROAD_BASE;
	if (cloudTexture.m_texture)
	{
		if (globalData[0x38])
		{
			shader = W3DShaderManager::ST_ROAD_BASE_NOISE1;
			if (noiseTexture.m_texture && globalData[0x44])
				shader = W3DShaderManager::ST_ROAD_BASE_NOISE12;
		}
	}
	else if (noiseTexture.m_texture)
	{
		if (globalData[0x44])
			shader = W3DShaderManager::ST_ROAD_BASE_NOISE2;
	}
	shader = Rva00716970Lookup(shader);
	if (!W3DShaderManager::setShroudTex(one))
	{
		BFMETextureRelease *texture = m_texture;
		retainTexture(texture);
		BFMETextureRelease *&global = *(BFMETextureRelease **)0x012F9D2C;
		if (global)
			global->Release_Ref();
		global = texture;

		texture = (BFMETextureRelease *)cloudTexture.m_texture;
		retainTexture(texture);
		BFMETextureRelease *&globalCloud = *(BFMETextureRelease **)0x012F9D30;
		if (globalCloud)
			globalCloud->Release_Ref();
		globalCloud = texture;

		texture = (BFMETextureRelease *)noiseTexture.m_texture;
		retainTexture(texture);
		BFMETextureRelease *&globalNoise = *(BFMETextureRelease **)0x012F9D34;
		if (globalNoise)
			globalNoise->Release_Ref();
		globalNoise = texture;
	}

	bool loadBuffers = false;
	if (m_visibilityDirty)
	{
		if (((W3DRoadBuffer *)this)->visibilityChanged(*(RvaRegion2D *)boundsWords))
			loadBuffers = (one != 0);
	}
	if (m_updateBuffers)
	{
		loadBuffers = (one != 0);
		m_updateBuffers = 0;
		m_visibilityDirty = 0;

		RvaAssetSet assets;
		for (int i = 0; i < m_maxRoadTypes; ++i)
		{
			BfmeHandleCX handle = m_roadTypes[i].m_handleOwner.getHandle();
			if (handle.m_texture)
			{
				Rva0013FA60Target *target = (Rva0013FA60Target *)handle.m_texture;
				void *value = target->slot0();
				if (value)
				{
					Rva0013FA60Target *key = (Rva0013FA60Target *)bfmeGoEMEb(value);
					if (assets.insert(key).second)
						loadBuffers = (one != 0);
				}
			}
		}

		if (cloudTexture.m_texture)
		{
			Rva0013FA60Target *target = (Rva0013FA60Target *)cloudTexture.m_texture;
			void *value = target->slot0();
			if (value)
			{
				Rva0013FA60Target *key = (Rva0013FA60Target *)bfmeGoEMEb(value);
				if (assets.insert(key).second)
					loadBuffers = (one != 0);
			}
		}

		if (noiseTexture.m_texture)
		{
			Rva0013FA60Target *target = (Rva0013FA60Target *)noiseTexture.m_texture;
			void *value = target->slot0();
			if (value)
			{
				Rva0013FA60Target *key = (Rva0013FA60Target *)bfmeGoEMEb(value);
				if (assets.insert(key).second)
					loadBuffers = (one != 0);
			}
		}
		Rva009EBAC0((int)&assets);
	}

	int stacking = 0;
	for (; stacking <= maxStacking; ++stacking)
	{
		for (int i = 0; i < m_maxRoadTypes; ++i)
		{
			RvaRoadType *road = m_roadTypes + i;
			if (stacking != road->m_stackingOrder)
				continue;
			m_curUniqueID = road->m_uniqueID;
			m_curRoadType = i;
			if (loadBuffers)
				((W3DRoadBuffer *)this)->loadRoadsInVertexAndIndexBuffers();
			if (road->m_numRoadIndices == 0)
				continue;

			BFMETextureRelease *roadTexture = (BFMETextureRelease *)road->m_handleOwner.m_target;
			if (!wireframe)
			{
				retainTexture(roadTexture);
				BFMETextureRelease *&global = *(BFMETextureRelease **)0x012F9D28;
				if (global)
					global->Release_Ref();
				global = roadTexture;
				DX8Wrapper::Set_Index_Buffer(road->m_indexRoad, 0);
				DX8Wrapper::Set_Vertex_Buffer(road->m_vertexRoad, 0);
				TextureBaseClass *stageTexture = 0;
				BoxSetTexture(0, stageTexture);
				DX8Wrapper::Apply_Render_State_Changes();
				for (int pass = 0; pass < devicePasses; ++pass)
				{
					W3DShaderManager::setShader((W3DShaderManager::ShaderTypes)shader, pass);
					DX8Wrapper::Draw_Triangles(0, road->m_numRoadIndices / 3, 0,
						road->m_numRoadVertices);
				}
				W3DShaderManager::resetShader((W3DShaderManager::ShaderTypes)shader);
			}
			else
			{
				retainTexture(roadTexture);
				BFMETextureRelease *&global = *(BFMETextureRelease **)0x012F9D28;
				if (global)
					global->Release_Ref();
				global = roadTexture;
				DX8Wrapper::Set_Index_Buffer(road->m_indexRoad, 0);
				DX8Wrapper::Set_Vertex_Buffer(road->m_vertexRoad, 0);
				DX8Wrapper::Apply_Render_State_Changes();
				for (int pass = 0; pass < devicePasses; ++pass)
				{
					DX8Wrapper::Draw_Triangles(0, road->m_numRoadIndices / 3, 0,
						road->m_numRoadVertices);
				}
			}
		}
	}

	m_curRoadType = 0;
}
