// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Retail 0x00710620, 1380 bytes, ret 0x24: W3DRoadBuffer::drawRoads (BFME).
// Identity: Zero Hour twin W3DRoadBuffer.cpp drawRoads -- m_initialized guard,
// bounds = min/max * MAP_XY_FACTOR, maxStacking scan over the 0x24-byte road
// types, ST_ROAD_BASE/NOISE1/NOISE2/NOISE12 (7..10) selection, visibilityChanged
// gating loadBuffers, stacking x road-type loop with Draw_Triangles(0,
// numIndices/3, 0, numVertices) per pass and resetShader, m_curRoadType = 0 --
// on W3DRoadBuffer's witnessed layout (m_initialized +0xC, m_curUniqueID +0x28,
// m_curRoadType +0x2C, m_maxRoadTypes +0x44, m_updateBuffers +0x50), calling
// the matched W3DRoadBuffer::visibilityChanged and
// W3DRoadBuffer::loadRoadsInVertexAndIndexBuffers on this; it follows the
// matched loadRoads (0x007105D0) directly, as in the ZH file. Caller 0x006D3480
// reaches it through ILT 0x00017193 with nine stack arguments.
// BFME differences: textures arrive as ref-counted TextureHandles (16-bit
// count at +4, TextureBaseClass::Release_Ref), the shader texture table is the
// handle array at 0x012F9D28 (setShroudTex / Install_Materials model), stage 1
// takes the buffer's own texture unless setShroudTex(1) succeeds, every road
// texture name is reported through an AssetList (WaterPolygonInitialize.cpp
// model) and 0x009EBAC0, and each branch sets one of two road shaders.

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <new>
#include <set>

class IndexBufferClass;
class VertexBufferClass;
class CameraClass;
class RenderObjClass;
template <class T> class RefMultiListIterator;
typedef RefMultiListIterator<RenderObjClass> RefRenderObjListIterator;

#define MAP_XY_FACTOR (10.0f)

// Texture reference: vtable, then the 16-bit reference count at +4.
class TextureBaseClass
{
public:
	virtual const char *slot0(void);	// first virtual; non-null result is the asset name
	void Release_Ref();

	unsigned short m_word4; // incremented on copy; Release_Ref drops it
};

class TextureHandle
{
public:
	TextureHandle() : m_p(0) {}
	~TextureHandle()
	{
		if (m_p)
			m_p->Release_Ref();
	}

	const TextureHandle &operator=(const TextureHandle &other)
	{
		if (other.m_p)
			++other.m_p->m_word4;
		if (m_p)
			m_p->Release_Ref();
		m_p = other.m_p;
		return *this;
	}

	operator TextureBaseClass *&() { return m_p; }

	TextureBaseClass *m_p;
};

// The handle the matched getter at 0x00707000 returns.
class RefCountedHandle
{
public:
	~RefCountedHandle()
	{
		if (m_p)
			m_p->Release_Ref();
	}

	TextureBaseClass *m_p;
};

class Rva00707000Owner
{
public:
	RefCountedHandle getHandle() const;
};

// retail 0x012F9D28: the shader texture-handle table (BfmeHandleCX[8]),
// defined by Rva00C6C520StaticInit.cpp. Declared by its defining name; the
// table's 4-byte slots are written through the TextureHandle view this TU uses.
class BfmeHandleCX;
extern BfmeHandleCX g_bfmeTableDU[8];

class W3DShaderManager
{
public:
	enum ShaderTypes
	{
		ST_ROAD_BASE = 7,
		ST_ROAD_BASE_NOISE1 = 8,
		ST_ROAD_BASE_NOISE2 = 9,
		ST_ROAD_BASE_NOISE12 = 10
	};
	static int setShroudTex(int stage);
	static int setShader(ShaderTypes shader, int pass);
	static void resetShader(ShaderTypes shader);
	static void setTexture(int stage, const TextureHandle &texture) { ((TextureHandle *)&g_bfmeTableDU)[stage] = texture; }
};

extern int Rva00716970Lookup(int shader);	// passes for a shader type

class StringClass
{
	char *m_Buffer;
	static char *m_EmptyString;
	static char m_NullChar;

	void Get_String(int length, bool is_temp);
	void Free_String(void);

public:
	__forceinline StringClass(int initial_len = 0, bool hint_temporary = false)
		: m_Buffer(m_EmptyString)
	{
		Get_String(initial_len, hint_temporary);
		m_Buffer[0] = m_NullChar;
	}

	~StringClass(void)
	{
		Free_String();
	}
};

class ShaderClass
{
public:
	static bool ShaderDirty;
	unsigned ShaderBits;
};

struct RenderStateStruct
{
	ShaderClass shader;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8wrapper.h
class DX8Wrapper
{
public:
	static void Set_Index_Buffer(const IndexBufferClass *buffer, unsigned short index_base_offset);
	static void Set_Vertex_Buffer(const VertexBufferClass *buffer, unsigned stream = 0);
	static void Draw_Triangles(unsigned short start_index, unsigned short polygon_count, unsigned short min_vertex_index, unsigned short vertex_count);

	// BFME builds with MESH_RENDER_SNAPSHOT_ENABLED: the snapshot string survives.
	static void Set_Shader(const ShaderClass &shader)
	{
		if (!ShaderClass::ShaderDirty && ((unsigned &)shader == (unsigned &)render_state.shader)) {
			return;
		}
		render_state.shader = shader;
		render_state_changed |= 0x8000;	// SHADER_CHANGED
		StringClass str;
	}

private:
	static RenderStateStruct render_state;
	static unsigned render_state_changed;
};

void __cdecl BoxSetTexture(unsigned stage, TextureBaseClass *&texture);

// The two road shaders (ZH detailAlphaShader / detailShader file statics).
extern ShaderClass g_roadShader012BAD1C;
extern ShaderClass g_roadShader012BAD20;

struct Glo012ED5C8Type
{
	char m_pad00[0x38];
	bool m_flag38;	// cloud texture enabled
	char m_pad39[0x0b];
	bool m_flag44;	// noise texture enabled
};
extern Glo012ED5C8Type *TheWritableGlobalData;

extern void *bfmeGoEMEb(void *name);
extern void Rva009EBAC0(int assets);

struct Rva0013FA60Target;
typedef Rva0013FA60Target *Rva0013FA60Key;

typedef _STL::_Rb_tree<Rva0013FA60Key,
	Rva0013FA60Key,
	_STL::_Identity<Rva0013FA60Key>,
	_STL::less<Rva0013FA60Key>,
	_STL::allocator<Rva0013FA60Key> > Rva0013FA60Tree;

typedef _STL::pair<Rva0013FA60Tree::iterator, bool> Rva00710620InsertResult;

// Matched out of line at 0x0013FA60; declared so this TU calls it.
template <>
Rva00710620InsertResult Rva0013FA60Tree::insert_unique(const Rva0013FA60Key &key);

struct Rva00710620TreeHeader
{
	unsigned char m_color;
	unsigned char m_padding01[3];
	void *m_parent;
	void *m_left;
	void *m_right;
};

struct Rva0013FA60Set
{
	__forceinline Rva00710620InsertResult insert(const Rva0013FA60Key &key)
	{
		return reinterpret_cast<Rva0013FA60Tree *>(this)->insert_unique(key);
	}

	Rva00710620TreeHeader *m_header;
	unsigned int m_nodeCount;
	unsigned int m_keyCompare;
};

struct Rva001408C0Target;
typedef Rva001408C0Target *Rva001408C0Key;

typedef _STL::_Rb_tree<Rva001408C0Key,
	Rva001408C0Key,
	_STL::_Identity<Rva001408C0Key>,
	_STL::less<Rva001408C0Key>,
	_STL::allocator<Rva001408C0Key> > Rva001408C0Tree;

// Matched out of line at 0x00140950; declared so this TU calls it.
template <>
Rva001408C0Tree::~_Rb_tree();

// BFME AssetList, as WaterPolygonInitialize.cpp models it.
struct Rva00710620AssetList
{
	__forceinline Rva00710620AssetList(void)
	{
		m_prototypes.m_header = 0;
		m_prototypes.m_header = (Rva00710620TreeHeader *)
			_STL::__node_alloc<true, 0>::allocate(0x14);
		m_prototypes.m_nodeCount = 0;
		m_prototypes.m_header->m_color = 0;
		m_prototypes.m_header->m_parent = 0;
		m_prototypes.m_header->m_left = m_prototypes.m_header;
		m_prototypes.m_header->m_right = m_prototypes.m_header;
		m_treeLayoutPad = 0;
		m_changed = true;
	}

	__forceinline ~Rva00710620AssetList(void)
	{
		reinterpret_cast<Rva001408C0Tree *>(&m_prototypes)->~Rva001408C0Tree();
	}

	__forceinline void addName(const char *name)
	{
		Rva0013FA60Key prototype = (Rva0013FA60Key)bfmeGoEMEb(
			(void *)name);
		Rva00710620InsertResult inserted = m_prototypes.insert(prototype);
		if (inserted.second)
			m_changed = true;
	}

	__forceinline void addTexture(TextureBaseClass *texture)
	{
		if (texture) {
			const char *name = texture->slot0();
			if (name)
				addName(name);
		}
	}

	Rva0013FA60Set m_prototypes;
	unsigned int m_treeLayoutPad;
	bool m_changed;
};

struct ICoord2D
{
	int x;
	int y;
};

struct IRegion2D
{
	ICoord2D lo;
	ICoord2D hi;
};

class DX8VertexBufferClass;
class DX8IndexBufferClass;

// upstream layout: inputs/reference/shims/w3droadbuffer/W3DDevice/GameClient/W3DRoadBuffer.h (LOAD_TEST_ASSETS)
class RoadType
{
public:
	TextureHandle m_roadTexture;
	DX8VertexBufferClass *m_vertexRoad;
	DX8IndexBufferClass *m_indexRoad;
	int m_numRoadVertices;
	int m_numRoadIndices;
	int m_uniqueID;
	bool m_isAutoLoaded;
	int m_stackingOrder;
	char m_texturePath[4];

	int getStacking(void) { return m_stackingOrder; }
	int getUniqueID(void) { return m_uniqueID; }
	int getNumVertices(void) { return m_numRoadVertices; }
	int getNumIndices(void) { return m_numRoadIndices; }
	void applyTexture(void)
	{
		W3DShaderManager::setTexture(0, m_roadTexture);
		DX8Wrapper::Set_Index_Buffer((const IndexBufferClass *)m_indexRoad, 0);
		DX8Wrapper::Set_Vertex_Buffer((const VertexBufferClass *)m_vertexRoad, 0);
	}
};

class W3DRoadBuffer
{
public:
	void drawRoads(CameraClass *camera, const TextureHandle &cloudTexture,
		const TextureHandle &noiseTexture, bool wireframe,
		int minX, int maxX, int minY, int maxY, RefRenderObjListIterator *pDynamicLightsIterator);

protected:
	RoadType *m_roadTypes;
	void *m_roads;
	int m_numRoads;
	bool m_initialized;
	void *m_map;
	RefRenderObjListIterator *m_lightsIterator;
	char unused18[0x10];	// not touched here
	// This body stores the road type's unique ID at +0x28 and the road-type
	// index at +0x2C (0 on exit), ZH's m_curUniqueID / m_curRoadType.
	int m_curUniqueID;
	int m_curRoadType;
	char unused30[0x14];	// not touched here
	int m_maxRoadTypes;
	char unused48[8];	// not touched here
	bool m_updateBuffers;
	bool m_bfmeFlag51;	// BFME: gates the visibilityChanged test
	TextureHandle m_bfmeTexture54;	// BFME: stage-1 texture when setShroudTex(1) fails

	void loadRoadsInVertexAndIndexBuffers(void);
	bool visibilityChanged(const IRegion2D &bounds);
};

void W3DRoadBuffer::drawRoads(CameraClass *camera, const TextureHandle &cloudTexture,
	const TextureHandle &noiseTexture, bool wireframe,
	int minX, int maxX, int minY, int maxY, RefRenderObjListIterator *pDynamicLightsIterator)
{
	if (!m_initialized) {
		return;
	}
	int i;
	int maxStacking;
	int stacking;
	int st;
	int devicePasses;
	bool loadBuffers;
	// Retail reuses the bounds slot for the AssetList insert result, so the
	// bounds live in a block that closes before the asset list is built.
	{
		IRegion2D bounds;
		bounds.lo.x = minX*MAP_XY_FACTOR;
		bounds.hi.x = maxX*MAP_XY_FACTOR;
		bounds.lo.y = minY*MAP_XY_FACTOR;
		bounds.hi.y = maxY*MAP_XY_FACTOR;

		maxStacking = 0;
		for (i=0; i<m_maxRoadTypes; i++) {
			if (m_roadTypes[i].getStacking() > maxStacking) {
				maxStacking = m_roadTypes[i].getStacking();
			}
		}
		st = W3DShaderManager::ST_ROAD_BASE;
		if (cloudTexture.m_p && TheWritableGlobalData->m_flag38) {
			st = W3DShaderManager::ST_ROAD_BASE_NOISE1;
			if (noiseTexture.m_p && TheWritableGlobalData->m_flag44)
				st = W3DShaderManager::ST_ROAD_BASE_NOISE12;
		}
		else
		if (noiseTexture.m_p && TheWritableGlobalData->m_flag44)
			st = W3DShaderManager::ST_ROAD_BASE_NOISE2;

		devicePasses = 1;
		devicePasses = Rva00716970Lookup(st);

		if (!W3DShaderManager::setShroudTex(1))
			W3DShaderManager::setTexture(1, m_bfmeTexture54);
		W3DShaderManager::setTexture(2, cloudTexture);
		W3DShaderManager::setTexture(3, noiseTexture);

		loadBuffers = false;
		if (m_bfmeFlag51) {
			if (visibilityChanged(bounds)) {
				loadBuffers = true;
			}
		}
		if (m_updateBuffers) {
			loadBuffers = true;
		}
		m_updateBuffers = false;
		m_bfmeFlag51 = false;
	}

	Rva00710620AssetList assets;
	for (i=0; i<m_maxRoadTypes; i++) {
		assets.addTexture(((const Rva00707000Owner *)&m_roadTypes[i])->getHandle().m_p);
	}
	assets.addTexture(cloudTexture.m_p);
	assets.addTexture(noiseTexture.m_p);
	Rva009EBAC0((int)&assets);

	for (stacking=0; stacking <= maxStacking; stacking++) {
		for (i=0; i<m_maxRoadTypes; i++) {
			if (stacking != m_roadTypes[i].getStacking()) {
				continue;
			}
			m_curUniqueID = m_roadTypes[i].getUniqueID();
			m_curRoadType = i;
			if (loadBuffers) loadRoadsInVertexAndIndexBuffers();
			if (m_roadTypes[i].getNumIndices() == 0) continue;
			if (wireframe) {
				m_roadTypes[i].applyTexture();
				BoxSetTexture(0, TextureHandle());
				DX8Wrapper::Set_Shader(g_roadShader012BAD20);
			} else {
				m_roadTypes[i].applyTexture();
				DX8Wrapper::Set_Shader(g_roadShader012BAD1C);
			}
			for (int pass=0; pass < devicePasses; pass++)
			{
				if (!wireframe)
		 			W3DShaderManager::setShader((W3DShaderManager::ShaderTypes)st, pass);
				DX8Wrapper::Draw_Triangles(	0, m_roadTypes[i].getNumIndices()/3, 0,	m_roadTypes[i].getNumVertices());
			}

			if (!wireframe)
 				W3DShaderManager::resetShader((W3DShaderManager::ShaderTypes)st);
		}
	}
	m_curRoadType = 0;
}
