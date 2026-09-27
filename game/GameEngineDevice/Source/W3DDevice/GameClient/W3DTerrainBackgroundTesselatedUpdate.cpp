// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWDebug /Igame/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/shims/sweep
// stlport
// Retail 0x0072C7F0: W3DTerrainBackground::doTesselatedUpdate, the Zero Hour
// twin in W3DTerrainBackground.cpp (GeneralsMD). Identity: the named lift row
// this body replaces, the Zero Hour call sequence (flip-count pass, vertex
// buffer refill, two fillVBRecursive passes, bounds, flat texture) and RET12.
//
// BFME differences from Zero Hour:
//  - the update range is clamped to the map extent instead of calling setFlip,
//    and the dirty byte at +0x52 is cleared;
//  - the index scratch is zeroed after allocation, and the whole refill runs
//    under the DX8 lock pair (0x00903090/0x00905B10);
//  - fillVBRecursive (0x0072B580) takes seven arguments;
//  - heights are 16-bit and read through an inline bounds-checked lookup, and
//    the vertex pass inlines the flip-state bit test the counting pass calls;
//  - one fewer terrain texture: only +0x30 is released, and the flat texture
//    (0x0074C4F0, returned as an owning handle) is DXT1 when the client global
//    at 0x012F1464 exists, otherwise format 0x19 followed by 0x0090F050.
// Layout is the BFME one the sibling W3DTerrainBackground*.cpp bodies use.
#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE
#define BFME_DYNAMIC_IB_UINT_CTOR_ABI
#include "winbase_shim.h"
#include "dx8vertexbuffer.h"
#include "dx8indexbuffer.h"
#include "dx8fvf.h"
#include "aabox.h"
#include <string.h>
#define _STLP_NO_EXCEPTIONS 1
#include <vector>

typedef bool Bool;
typedef int Int;
typedef float Real;
typedef unsigned short UnsignedShort;

struct IRegion2D
{
	struct { Int x, y; } lo, hi;
};

// Scoped DX8 lock: retail brackets the refill with this pair.
void W3DRadarResetLock( void );
void W3DRadarResetUnlock( void );
struct BfmeDX8ScopedLock
{
	BfmeDX8ScopedLock() { W3DRadarResetLock(); }
	~BfmeDX8ScopedLock() { W3DRadarResetUnlock(); }
};

class TextureFilterClass;
class ShroudFilter
{
public:
	unsigned char m_pad00[0x0c];
	int m_uAddrMode;								// +0x0c
	int m_vAddrMode;								// +0x10
};

class TextureClass
{
public:
	void Release_Ref( void );

	void *m_vtable;
	short m_refs;									// +0x04
};

// The owning texture handle BFME keeps at +0x2c and WorldHeightMap returns.
class ShroudTexture
{
public:
	ShroudTexture() : m_texture( 0 ) {}
	~ShroudTexture() { if (m_texture) m_texture->Release_Ref(); }
	ShroudTexture &operator=( const ShroudTexture &o )
	{
		if (o.m_texture)
			o.m_texture->m_refs++;
		if (m_texture)
			m_texture->Release_Ref();
		m_texture = o.m_texture;
		return *this;
	}
	ShroudFilter *getFilter( void );
	bool isNull( void ) const { return m_texture == 0; }

	TextureClass *m_texture;
};

class ClientRoot4120;
extern ClientRoot4120 *TheGameClient;
void Rva0090F050( void );

class Rva00729300BitPlane
{
public:
	bool test( int x, int y ) const;
};

class BfmeA1087
{
public:
	int getStaticDiffuse( int x, int y );
};
extern BfmeA1087 *g_bfmeA1087;

class WorldHeightMap
{
public:
	virtual void Delete_This( void );

	Int getXExtent( void ) const { return m_width; }
	Int getYExtent( void ) const { return m_height; }
	Int getBorderSizeInline( void ) const { return m_borderSize; }
	UnsignedShort getHeight( Int x, Int y ) const
	{
		Int ndx = m_width * y + x;
		if (ndx < 0 || ndx >= m_dataSize || m_data == 0)
			return 0;
		return m_data[ndx];
	}
	bool getFlipState( Int x, Int y ) const
	{
		if (x < 0 || y < 0 || y >= m_height || x >= m_width)
			return false;
		unsigned ndx = m_flipStride * y + (x >> 3);
		if (ndx >= m_flipBits.size())
			return false;
		return (m_flipBits[ndx] & (1 << (x & 7))) != 0;
	}
	bool testFlip( Int x, Int y ) const { return ((const Rva00729300BitPlane *)this)->test( x, y ); }
	ShroudTexture rva0074C4F0( Int xOrigin, Int yOrigin, Int width, Int pixelsPerGrid, Int format );

	Int m_refs;										// +0x04
	Int m_width;									// +0x08
	Int m_height;									// +0x0c
	Int m_borderSize;								// +0x10
	unsigned char m_pad14[0x20 - 0x14];
	Int m_dataSize;									// +0x20
	UnsignedShort *m_data;							// +0x24
	unsigned char m_pad28[0x34 - 0x28];
	Int m_flipStride;								// +0x34
	unsigned char m_pad38[0x44 - 0x38];
	_STL::vector<unsigned char> m_flipBits;		// +0x44
};

#define MAP_XY_FACTOR 10.0f
#define MAP_HEIGHT_SCALE (MAP_XY_FACTOR/256.0f)

class W3DTerrainBackground
{
public:
	void doTesselatedUpdate( const IRegion2D &partialRange, WorldHeightMap *htMap, Bool doTextures );

protected:
	void rva0072B580( UnsignedShort *ib, Int a, Int b, Int c, Int width, UnsignedShort *ndx, Int &count );

private:
	Int m_cullStatus;								// +0x00
	AABoxClass m_bounds;							// +0x04
	DX8VertexBufferClass *m_vertexTerrain;			// +0x1c
	Int m_vertexTerrainSize;						// +0x20
	DX8IndexBufferClass *m_indexTerrain;			// +0x24
	Int m_indexTerrainSize;							// +0x28
	ShroudTexture m_terrainTexture;					// +0x2c
	TextureClass *m_terrainTexture2X;				// +0x30
	Int m_texMultiplier;							// +0x34
	Int m_curNumTerrainVertices;					// +0x38
	Int m_curNumTerrainIndices;						// +0x3c
	Int m_xOrigin;									// +0x40
	Int m_yOrigin;									// +0x44
	Int m_width;									// +0x48
	WorldHeightMap *m_map;							// +0x4c
	Bool m_initialized;								// +0x50
	Bool m_option51;								// +0x51
	Bool m_dirty52;									// +0x52
};

void W3DTerrainBackground::doTesselatedUpdate( const IRegion2D &partialRange, WorldHeightMap *htMap, Bool doTextures )
{
	if (m_map == NULL) return;
	if (htMap) {
		htMap->m_refs++;
		WorldHeightMap *old = m_map;
		if (old && --old->m_refs == 0)
			old->Delete_This();
		m_map = htMap;
	}
	if (!m_initialized) {
		return;
	}
	Int minX = m_xOrigin;
	Int minY = m_yOrigin;
	Int maxX = m_xOrigin + m_width;
	Int maxY = m_yOrigin + m_width;
	m_dirty52 = false;
	Int limitX = m_map->getXExtent()-1;
	Int limitY = m_map->getYExtent()-1;
	if (maxX > limitX) maxX = limitX;
	if (maxY > limitY) maxY = limitY;

	if (partialRange.lo.x > maxX) return;
	if (partialRange.lo.y > maxY) return;
	if (partialRange.hi.x < minX) return;
	if (partialRange.hi.y < minY) return;

	Int count = (m_width+1)*(m_width+1);

	UnsignedShort *ndx = new UnsignedShort[count];
	memset( ndx, 0, count*sizeof(UnsignedShort) );

	Int requiredVertex = 0;
	Int i, j;
	for (j=minY; j<=maxY; j++) {
		for (i=minX; i<=maxX; i++) {
			Int ndxNdx = i-minX + (m_width+1)*(j-minY);
			ndx[ndxNdx] = 0;
			if (m_map->testFlip(i, j)) {
				requiredVertex++;
			}
		}
	}

	BfmeDX8ScopedLock dx8Lock;

	if (m_vertexTerrainSize<requiredVertex || m_vertexTerrain==NULL) {
		m_vertexTerrainSize = requiredVertex;
		REF_PTR_RELEASE(m_vertexTerrain);
		m_vertexTerrain=NEW_REF(DX8VertexBufferClass,(DX8_FVF_XYZDUV2,m_vertexTerrainSize+4,DX8VertexBufferClass::USAGE_DEFAULT));
	}

	m_curNumTerrainVertices = 0;
	VertexFormatXYZDUV2 *vb;
	// Lock the buffer.
	DX8VertexBufferClass::WriteLockClass lockVtxBuffer(m_vertexTerrain);
	vb=(VertexFormatXYZDUV2*)lockVtxBuffer.Get_Vertex_Array();
	VertexFormatXYZDUV2 *curVb = vb;
	// Add to the vertex buffer.
	for (j=minY; j<=maxY; j++) {
		for (i=minX; i<=maxX; i++) {
			if (m_map->getFlipState(i, j)) {
				Int diffuse = g_bfmeA1087->getStaticDiffuse(i,j);
				Vector3 pos;
				Int k = i<limitX?i:limitX;
				Int l = j<limitY?j:limitY;
				pos.Z = ((float)m_map->getHeight(k,l)*MAP_HEIGHT_SCALE);
				pos.X = (i)*MAP_XY_FACTOR - m_map->getBorderSizeInline()*MAP_XY_FACTOR;
				pos.Y = (j)*MAP_XY_FACTOR - m_map->getBorderSizeInline()*MAP_XY_FACTOR;
				curVb->diffuse = (0<<24)|diffuse;
				curVb->u1 = (float)(i-minX)/(float)(m_width);
				curVb->v1 = 1.0f - (float)(j-minY)/(float)(m_width);
				curVb->x = pos.X;
				curVb->y = pos.Y;
				curVb->z = pos.Z;
				curVb++;
				Int ndxNdx = i-minX + (m_width+1)*(j-minY);
				ndx[ndxNdx] = m_curNumTerrainVertices;
				m_curNumTerrainVertices++;
			}
		}
	}

	Int requiredIndex = 0;

	rva0072B580(NULL, 0, 0, 0, m_width, ndx, requiredIndex);

	if (m_indexTerrainSize<requiredIndex || m_indexTerrain==NULL) {
		m_indexTerrainSize = requiredIndex;
		REF_PTR_RELEASE(m_indexTerrain);
		m_indexTerrain=NEW_REF(DX8IndexBufferClass,((unsigned)(m_indexTerrainSize+4),DX8IndexBufferClass::USAGE_DEFAULT));
	}

	m_curNumTerrainIndices = 0;

	UnsignedShort *ib;
	DX8IndexBufferClass::WriteLockClass lockIdxBuffer(m_indexTerrain);
	ib = lockIdxBuffer.Get_Index_Array();
	rva0072B580(ib, 0, 0, 0, m_width, ndx, m_curNumTerrainIndices);
	delete [] ndx;
	ndx = NULL;

	MinMaxAABoxClass bounds;
	bounds.Init_Empty();

	for (j=minY; j<=maxY; j+=1) {
		for (i=minX; i<=maxX; i+=1) {
			Vector3 pos;
			Int k = i<limitX?i:limitX;
			Int l = j<limitY?j:limitY;
			pos.Z = ((float)m_map->getHeight(k,l)*MAP_HEIGHT_SCALE);
			pos.X = (i)*MAP_XY_FACTOR - m_map->getBorderSizeInline()*MAP_XY_FACTOR;
			pos.Y = (j)*MAP_XY_FACTOR - m_map->getBorderSizeInline()*MAP_XY_FACTOR;
			bounds.Add_Point(pos);
		}
	}
	m_bounds.Init(bounds);

	if (m_terrainTexture.isNull() || doTextures) {
		if (m_terrainTexture2X) {
			m_terrainTexture2X->Release_Ref();
			m_terrainTexture2X = NULL;
		}
		if (TheGameClient) {
			m_terrainTexture = m_map->rva0074C4F0(m_xOrigin, m_yOrigin, m_width, 16, 0x31545844);
		} else {
			m_terrainTexture = m_map->rva0074C4F0(m_xOrigin, m_yOrigin, m_width, 16, 0x19);
			Rva0090F050();
		}
		m_terrainTexture.getFilter()->m_uAddrMode = 1;
		m_terrainTexture.getFilter()->m_vAddrMode = 1;
	}
}
