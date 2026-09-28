// ?queue007B4FE0@W3DProjectedShadowManager@@QAEXPAUShadow007B6D30@@HH@Z
// partial score=0.868 date=2026-09-28
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas
// stlport
#define _STLP_NO_EXCEPTIONS 1
#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>
#include <math.h>
// File-static helpers of BFME's W3DProjectedShadow.cpp TU (retail
// 0x007AF710 / 0x007AF940), the eventual home of the projected-shadow
// family (callers 0x007B23F0 and 0x007B4FE0). MSVC 7.1 gives a file-static
// function whose address is not taken a private register convention when its
// caller is in the same TU: 0x007AF710 takes four stack floats and returns a
// Vector2 through a hidden pointer in ECX; 0x007AF940 takes axisA in ECX,
// axisB in EAX, xr in EDI, yr in ESI plus four stack floats, and its caller
// pops the stack. Both conventions come out of the compiler by themselves
// here (docs/shape_levers.md, "Compiler-private ABI").
// Types: the callers pass two adjacent 12-byte vectors (Vector3, frame of
// six 12-byte objects at 0x48) and zero two adjacent 8-byte outputs (Vector2).
// The names keep the address: no caller, string or Zero Hour twin names them.
#include "vector2.h"
#include "vector3.h"
#include "matrix3d.h"

// Retail 0x007AF7E0 (EXACT here; claimed by another lane, not landed): Zero Hour queueDecal's decal axes from the object
// transform (x axis flattened and normalised, v = u rotated by -90 degrees;
// falls back to the y axis, then to (0,-1,0)).
static void decalAxesRva007AF7E0(const Matrix3D &objXform, Vector3 &uVector, Vector3 &vVector)
{
	uVector = objXform.Get_X_Vector();
	uVector.Z = 0.0f;
	float vecLength = uVector.Length();
	if (vecLength != 0.0f) {
		uVector *= 1.0f / vecLength;
		vVector.Set(uVector.Y, -uVector.X, 0.0f);
	} else {
		vVector = objXform.Get_Y_Vector();
		vVector.Z = 0.0f;
		vecLength = vVector.Length();
		if (vecLength != 0.0f)
			vVector *= 1.0f / vecLength;
		else
			vVector.Set(0.0f, -1.0f, 0.0f);
		uVector.Set(-vVector.Y, vVector.X, 0.0f);
	}
}

static Vector2 minMax4Rva007AF710(float a, float b, float c, float d)
{
	float lo, hi;
	if (a < b) {
		lo = a;
		hi = b;
	} else {
		lo = b;
		hi = a;
	}
	if (c < d) {
		if (c < lo)
			lo = c;
		if (d > hi)
			hi = d;
	} else {
		if (d < lo)
			lo = d;
		if (c > hi)
			hi = c;
	}
	return Vector2(lo, hi);
}

static void projectRangesRva007AF940(const Vector3 &axisA, const Vector3 &axisB, float sizeA, float sizeB,
	float offA, float offB, Vector2 &xr, Vector2 &yr)
{
	Vector3 a0 = -((offA + 0.5f) * sizeA) * axisA;
	Vector3 a1 = (0.5f - offA) * sizeA * axisA;
	Vector3 b0 = -((offB + 0.5f) * sizeB) * axisB;
	Vector3 b1 = (0.5f - offB) * sizeB * axisB;
	Vector3 c0 = b0 + a0;
	Vector3 c1 = b0 + a1;
	Vector3 c2 = b1 + a1;
	Vector3 c3 = b1 + a0;
	xr = minMax4Rva007AF710(c0.X, c1.X, c2.X, c3.X);
	yr = minMax4Rva007AF710(c0.Y, c1.Y, c2.Y, c3.Y);
}



// ---------------------------------------------------------------------------
// Retail 0x007B4FE0 (4341 B, ret 0x0C): BFME's queueDecal. renderShadows
// (0x007B6D30) calls it through ILT 0x00034FD6 with (shadow, 1, 0).
// MILESTONE 1 (banked): full structure, 4376 B vs 4341, probe shape 0.868.
// Zero Hour queueDecal gives the terrain half; BFME adds a partition query
// for up to 16 nearby drawables whose meshes also receive the decal.

__forceinline long fastFloatToLong007B4FE0(float value)
{
	long result;
	__asm
	{
		fld [value]
		fistp [result]
	}
	return result;
}
#define REAL_TO_INT_FLOOR(x) fastFloatToLong007B4FE0((float)floor((double)(x)))
#define REAL_TO_INT_CEIL(x) fastFloatToLong007B4FE0((float)ceil((double)(x)))

#define MAP_XY_FACTOR 10.0f
#define MAP_HEIGHT_SCALE 0.0390625f

struct Coord3D
{
	float x, y, z;
	float GetLengthSqrd() const;
};

class AABoxClass
{
public:
	AABoxClass() {}
	AABoxClass(const Vector3 &center, const Vector3 &extent) : Center(center), Extent(extent) {}
	Vector3 Center;
	Vector3 Extent;
};

class CollisionMath
{
public:
	enum OverlapType { POS = 0x01, NEG = 0x02, ON = 0x04, BOTH = 0x08, OUTSIDE = POS };
	static OverlapType Overlap_Test(const AABoxClass &box, const AABoxClass &box2);
};

template<unsigned N> class BitFlags
{
	unsigned words[N / 32];
public:
	enum BogusInitType { kInit = 0 };
	BitFlags(BogusInitType, int);
};
extern const BitFlags<192> KINDOFMASK_NONE;

class Object;
class PartitionFilter
{
public:
	virtual ~PartitionFilter() {}
	virtual bool allow(Object *) = 0;
	virtual int getPlayerMask();
	PartitionFilter *m_next;
};
class PartitionFilterAcceptByKindOf : public PartitionFilter
{
	BitFlags<192> a, b;
public:
	PartitionFilterAcceptByKindOf(const BitFlags<192> &, const BitFlags<192> &);
	virtual ~PartitionFilterAcceptByKindOf() {}
	virtual bool allow(Object *);
};

enum IterOrderType { ITER_FASTEST, ITER_SORTED_NEAR_TO_FAR };

struct Rva0025ED50Entry
{
	Object *object;
	unsigned int unknown04;
};
struct Rva0025ED50ResultData
{
	std::vector<Rva0025ED50Entry> entries;
	Rva0025ED50Entry *current;
	int references;
};
struct Rva0025ED50WideResult
{
	Rva0025ED50ResultData *value;
	Rva0025ED50WideResult();
	Rva0025ED50WideResult(const Rva0025ED50WideResult &);
	~Rva0025ED50WideResult()
	{
		if (--value->references == 0)
			delete value;
	}
	Object *next()
	{
		if (value->current == value->entries.end())
			return 0;
		return (value->current++)->object;
	}
};
class PartitionManager
{
public:
	Rva0025ED50WideResult iterate(const Coord3D *, float, IterOrderType, PartitionFilter *, bool);
};
extern PartitionManager *ThePartitionManager;

enum DrawableID { INVALID_DRAWABLE_ID = 0 };
class Drawable
{
public:
	DrawableID getID() const;
};
class Object
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09();
	virtual Drawable *getDrawable() const;
};
class GameClient007B4FE0
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10();
	virtual Drawable *findDrawableByID(DrawableID id);
};
extern GameClient007B4FE0 *TheGameClient;

// The four render-object getters the drawable offers (ledger names).
class RenderObjClass;
class Rva00413770 { public: char anyAccepts(void *, void *, void *); };
class Rva004137E0 { public: char anyAccepts(void *, void *, void *); };
class BfmeOwner1158 { public: int bfmeSubIAny1158(); int bfmeSubJAny1158(); };

template<class T> struct ShareBuffer007B4FE0
{
	char pad00[0xc];
	T *Array;
	T *Get_Array() { return Array; }
};
struct TriIndex007B4FE0 { unsigned short I, J, K; };
struct MeshGeometry007B4FE0
{
	char pad00[0x24];
	int PolyCount;
	int VertexCount;
	ShareBuffer007B4FE0<TriIndex007B4FE0> *Poly;
	ShareBuffer007B4FE0<Vector3> *Vertex;
};

static inline int decrementRef007B4FE0(int *p) { return --*p; }

class RenderObjClass
{
public:
	virtual void Delete_This();
	virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void Validate_Transform() const;
	virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24();
	virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28();
	virtual void v29(); virtual void v30(); virtual void v31(); virtual void v32();
	virtual void v33(); virtual void v34(); virtual void v35(); virtual void v36();
	virtual void v37(); virtual void v38(); virtual void v39(); virtual void v40();
	virtual void v41(); virtual void v42(); virtual void v43(); virtual void v44();
	virtual void v45(); virtual void v46(); virtual void v47(); virtual void v48();
	virtual void v49(); virtual void v50(); virtual void v51(); virtual void v52();
	virtual void v53(); virtual void v54(); virtual void v55(); virtual void v56();
	virtual void v57(); virtual void v58(); virtual void v59(); virtual void v60();
	virtual void v61(); virtual void v62(); virtual void v63(); virtual void v64();
	virtual const AABoxClass &Get_Bounding_Box() const;

	int NumRefs;
	unsigned char pad08[0x10];
	Matrix3D Transform;
	unsigned char pad48[0x80];
	MeshGeometry007B4FE0 *Model;

	void Release_Ref()
	{
		decrementRef007B4FE0(&NumRefs);
		if (NumRefs == 0)
			Delete_This();
	}
	const Matrix3D &Get_Transform() const
	{
		Validate_Transform();
		return Transform;
	}
	Vector3 Get_Position() const;
};

class TerrainLogic007B4FE0
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06();
	virtual float layerHeight1C(float x, float y, int a, int b, int c);
};
extern TerrainLogic007B4FE0 *TheTerrainLogic;

// BFME heights are 16-bit; the bounds helper returns 0 outside the map.
class WorldHeightMap007B4FE0
{
public:
	char pad00[8];
	int m_width;
	char pad0c[4];
	int m_borderSize;
	char pad14[0xc];
	int m_dataSize;
	unsigned short *m_data;
	int getBorderSize() const { return m_borderSize; }
	unsigned short getHeight(int x, int y) const
	{
		int idx = x + y * m_width;
		if (idx < 0 || idx >= m_dataSize || !m_data)
			return 0;
		return m_data[idx];
	}
};
class Gen_0074B410 { public: bool bfmeBitA(int, int) const; };
class TerrainRenderObject007B4FE0
{
public:
	char pad0000[0x2ff4];
	WorldHeightMap007B4FE0 *m_map;
	WorldHeightMap007B4FE0 *getMap() { return m_map; }
};
extern TerrainRenderObject007B4FE0 *TheTerrainRenderObject;

struct GlobalData007B4FE0
{
	char pad000[0xa77];
	bool m_bfmeA77;
	float m_bfmeA78;
};
extern GlobalData007B4FE0 *TheWritableGlobalData;

struct SHADOW_DECAL_VERTEX
{
	float x, y, z;
	unsigned int diffuse;
	float u, v;
	float u2, v2;
};
class ShadowDecalBuffer007B4FE0
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10();
	virtual long __stdcall Lock(unsigned int offset, unsigned int size, void **data, unsigned int flags);
	virtual long __stdcall Unlock();
};
extern ShadowDecalBuffer007B4FE0 *shadowDecalVertexBufferD3D;
extern ShadowDecalBuffer007B4FE0 *shadowDecalIndexBufferD3D;
extern int nShadowDecalVertsInBuf;
extern int nShadowDecalStartBatchVertex;
extern int nShadowDecalIndicesInBuf;
extern int nShadowDecalStartBatchIndex;
extern int nShadowDecalPolysInBatch;
extern int nShadowDecalVertsInBatch;
extern int drawEdgeX, drawEdgeY, drawStartX, drawStartY;

#define SHADOW_DECAL_VERTEX_SIZE 32768
#define SHADOW_DECAL_INDEX_SIZE 65536
#define D3DLOCK_NOOVERWRITE 0x1000
#define D3DLOCK_DISCARD 0x2000

struct ShadowTexture007B6D30;

// Offsets witnessed by this body; names keep the offset.
struct Shadow007B6D30
{
	char pad00[8];
	float m_x08, m_y0c, m_z10;
	char pad14[0xc];
	float m_localAngle20;
	char pad24[4];
	unsigned int m_diffuse28;
	char pad2c[4];
	bool m_flag30;
	char pad31[3];
	unsigned int m_type34;
	char pad38[0x20];
	float m_decalSizeX58, m_decalSizeY5c;
	float m_height60;
	bool m_flag64;
	char pad65[3];
	ShadowTexture007B6D30 *m_texture68;
	ShadowTexture007B6D30 *m_texture6c;
	RenderObjClass *m_robj70;
	char pad74[4];
	float m_offsetU78, m_offsetV7c;
	char pad80[8];
	Coord3D m_lastPos88;
	DrawableID m_drawables94[16];
};

class W3DProjectedShadowManager
{
public:
	void flush007B14A0(unsigned, ShadowTexture007B6D30 *, ShadowTexture007B6D30 *, int);
	void queue007B4FE0(Shadow007B6D30 *shadow, int flagA, int flagB);
};

void W3DProjectedShadowManager::queue007B4FE0(Shadow007B6D30 *shadow, int flagA, int flagB)
{
	Vector3 objPos;
	Matrix3D objXform(true);
	RenderObjClass *robj = shadow->m_robj70;

	if (shadow->m_decalSizeX58 == 0.0f || shadow->m_decalSizeY5c == 0.0f)
		return;

	if (robj) {
		objPos = robj->Get_Position();
		if (shadow->m_flag30)
			objXform = robj->Get_Transform();
	} else {
		objPos.Set(shadow->m_x08, shadow->m_y0c, shadow->m_z10);
		if (shadow->m_flag30)
			objXform.Rotate_Z(shadow->m_localAngle20);
	}

	float layerHeight = 0.0f;
	if (TheTerrainLogic)
		layerHeight = TheTerrainLogic->layerHeight1C(objPos.X, objPos.Y, 1, 0, 1);

	bool onLayer = false;
	if (shadow->m_flag64) {
		onLayer = true;
		objPos.Z = layerHeight;
	}

	Vector3 uVector, vVector;
	decalAxesRva007AF7E0(objXform, uVector, vVector);
	Vector2 xRange(0.0f, 0.0f);
	Vector2 yRange(0.0f, 0.0f);
	projectRangesRva007AF940(uVector, vVector, shadow->m_decalSizeX58, shadow->m_decalSizeY5c,
		shadow->m_offsetU78, shadow->m_offsetV7c, xRange, yRange);
	xRange.X += objPos.X;
	xRange.Y += objPos.X;
	yRange.X += objPos.Y;
	yRange.Y += objPos.Y;

	if (shadow->m_decalSizeX58 == 0.0f)
		uVector.Set(0.0f, 0.0f, 0.0f);
	else
		uVector /= shadow->m_decalSizeX58;
	if (shadow->m_decalSizeY5c == 0.0f)
		vVector.Set(0.0f, 0.0f, 0.0f);
	else
		vVector /= shadow->m_decalSizeY5c;

	float uOffset = shadow->m_offsetU78 + 0.5f;
	float vOffset = shadow->m_offsetV7c + 0.5f;
	unsigned int diffuse = shadow->m_diffuse28;
	if (shadow->m_type34 == 0x1000 && TheWritableGlobalData->m_bfmeA77) {
		int alpha = (int)(TheWritableGlobalData->m_bfmeA78 * 255.0f);
		if (alpha < 0)
			alpha = 0;
		else if (alpha > 255)
			alpha = 255;
		diffuse = (alpha << 24) | (diffuse & 0xffffff);
	}

	Coord3D decalPos;
	decalPos.x = objPos.X;
	decalPos.y = objPos.Y;
	decalPos.z = objPos.Z;

	if (!onLayer) {
		// Project onto the meshes of nearby objects that ask for decals.
		AABoxClass box(objPos, Vector3(shadow->m_decalSizeX58, shadow->m_decalSizeY5c, shadow->m_height60));
		Coord3D delta;
		delta.x = shadow->m_lastPos88.x - objPos.X;
		delta.y = shadow->m_lastPos88.y - objPos.Y;
		delta.z = shadow->m_lastPos88.z - objPos.Z;
		if (!flagB && ThePartitionManager && delta.GetLengthSqrd() > 2500.0f) {
			float radius = sqrtf(shadow->m_decalSizeX58 * shadow->m_decalSizeX58 +
				shadow->m_decalSizeY5c * shadow->m_decalSizeY5c) + 50.0f;
			Rva0025ED50WideResult iter = ThePartitionManager->iterate(&decalPos, radius,
				ITER_SORTED_NEAR_TO_FAR,
				&PartitionFilterAcceptByKindOf(BitFlags<192>(BitFlags<192>::kInit, 0x3b), KINDOFMASK_NONE),
				false);
			int i;
			for (i = 0; i < 16; ++i) {
				Object *obj = iter.next();
				if (!obj)
					break;
				shadow->m_drawables94[i] = obj->getDrawable()->getID();
			}
			if (i < 16)
				shadow->m_drawables94[i] = INVALID_DRAWABLE_ID;
			shadow->m_lastPos88 = decalPos;
		}

		DrawableID *ids = shadow->m_drawables94;
		for (int k = 0; k < 16; ++k, ++ids) {
			if (!*ids)
				break;
			Drawable *draw = TheGameClient->findDrawableByID(*ids);
			if (!draw)
				continue;
			for (int m = 0; m < 4; ++m) {
				RenderObjClass *ro = 0;
				if (m == 0)
					((Rva00413770 *)draw)->anyAccepts(0, 0, &ro);
				else if (m == 1)
					((Rva004137E0 *)draw)->anyAccepts(0, 0, &ro);
				else if (m == 2)
					ro = (RenderObjClass *)((BfmeOwner1158 *)draw)->bfmeSubIAny1158();
				else
					ro = (RenderObjClass *)((BfmeOwner1158 *)draw)->bfmeSubJAny1158();
				if (!ro)
					continue;
				if (CollisionMath::Overlap_Test(box, ro->Get_Bounding_Box()) == CollisionMath::OUTSIDE) {
					ro->Release_Ref();
					continue;
				}

				MeshGeometry007B4FE0 *geom = ro->Model;
				int numPolys = geom->PolyCount;
				int numVerts = geom->VertexCount;
				int numIndex = numPolys * 3;
				bool discard = false;
				if (nShadowDecalVertsInBuf + numVerts > SHADOW_DECAL_VERTEX_SIZE ||
					nShadowDecalIndicesInBuf + numIndex > SHADOW_DECAL_INDEX_SIZE) {
					flush007B14A0(shadow->m_type34, shadow->m_texture68, shadow->m_texture6c, flagB);
					nShadowDecalStartBatchVertex = 0;
					nShadowDecalStartBatchIndex = 0;
					nShadowDecalPolysInBatch = 0;
					nShadowDecalVertsInBatch = 0;
					nShadowDecalVertsInBuf = 0;
					nShadowDecalIndicesInBuf = 0;
					discard = true;
				}
				unsigned int lockFlags = discard ? D3DLOCK_DISCARD : D3DLOCK_NOOVERWRITE;
				SHADOW_DECAL_VERTEX *pvVertices;
				unsigned short *pvIndices;
				if (shadowDecalVertexBufferD3D->Lock(nShadowDecalVertsInBuf * sizeof(SHADOW_DECAL_VERTEX),
						numVerts * sizeof(SHADOW_DECAL_VERTEX), (void **)&pvVertices, lockFlags) < 0) {
					ro->Release_Ref();
					return;
				}
				if (shadowDecalIndexBufferD3D->Lock(nShadowDecalIndicesInBuf * sizeof(short),
						numIndex * sizeof(short), (void **)&pvIndices, lockFlags) < 0) {
					ro->Release_Ref();
					return;
				}

				if (pvVertices) {
					Vector3 *src = geom->Vertex->Get_Array();
					const Matrix3D &tm = ro->Get_Transform();
					for (int n = 0; n < numVerts; ++n, ++src) {
						Vector3 world;
						Matrix3D::Transform_Vector(tm, *src, &world);
						Vector3 d = world - objPos;
						pvVertices->x = world.X;
						pvVertices->y = world.Y;
						pvVertices->z = world.Z;
						pvVertices->diffuse = diffuse;
						pvVertices->u = Vector3::Dot_Product(uVector, d) + uOffset;
						pvVertices->v = Vector3::Dot_Product(vVector, d) + vOffset;
						pvVertices->u2 = 0.0f;
						pvVertices->v2 = 0.0f;
						++pvVertices;
					}
				}
				if (pvIndices) {
					TriIndex007B4FE0 *tri = geom->Poly->Get_Array();
					for (int n = 0; n < numPolys; ++n, ++tri) {
						pvIndices[0] = tri->I + nShadowDecalVertsInBatch;
						pvIndices[1] = tri->J + nShadowDecalVertsInBatch;
						pvIndices[2] = tri->K + nShadowDecalVertsInBatch;
						pvIndices += 3;
					}
				}
				shadowDecalVertexBufferD3D->Unlock();
				shadowDecalIndexBufferD3D->Unlock();
				nShadowDecalPolysInBatch += numPolys;
				nShadowDecalVertsInBuf += numVerts;
				nShadowDecalVertsInBatch += numVerts;
				nShadowDecalIndicesInBuf += numIndex;
				ro->Release_Ref();
			}
		}

		if (!(decalPos.z - layerHeight < shadow->m_height60))
			return;
	}

	// Project onto the terrain cells under the decal.
	WorldHeightMap007B4FE0 *hmap = TheTerrainRenderObject->getMap();
	int borderSize = hmap->getBorderSize();
	float mapScaleInv = 1.0f / MAP_XY_FACTOR;
	int startX = REAL_TO_INT_FLOOR(xRange.X * mapScaleInv) + borderSize;
	int endX = REAL_TO_INT_CEIL(xRange.Y * mapScaleInv) + borderSize;
	int startY = REAL_TO_INT_FLOOR(yRange.X * mapScaleInv) + borderSize;
	int endY = REAL_TO_INT_CEIL(yRange.Y * mapScaleInv) + borderSize;

	startX = __max(startX, drawStartX);
	startX = __min(startX, drawEdgeX);
	startY = __max(startY, drawStartY);
	startY = __min(startY, drawEdgeY);
	endX = __max(endX, drawStartX);
	endX = __min(endX, drawEdgeX);
	endY = __max(endY, drawStartY);
	endY = __min(endY, drawEdgeY);

	int numExtraX = (endX - startX + 1) - 104;
	if (numExtraX > 0) {
		int numStartExtraX = REAL_TO_INT_FLOOR((float)numExtraX * 0.5f);
		int numEdgeExtraX = numExtraX - numStartExtraX;
		startX += numStartExtraX;
		endX -= numEdgeExtraX;
	}
	int numExtraY = (endY - startY + 1) - 104;
	if (numExtraY > 0) {
		int numStartExtraY = REAL_TO_INT_FLOOR((float)numExtraY * 0.5f);
		int numEdgeExtraY = numExtraY - numStartExtraY;
		startY += numStartExtraY;
		endY -= numEdgeExtraY;
	}

	int vertsPerRow = endX - startX + 1;
	int vertsPerColumn = endY - startY + 1;
	if (vertsPerRow <= 1 || vertsPerColumn <= 1)
		return;

	int numVerts = vertsPerRow * vertsPerColumn;
	int numPolys = (endY - startY) * (endX - startX) * 2;
	int numIndex = numPolys * 3;
	bool discard = false;
	if (nShadowDecalVertsInBuf + numVerts > SHADOW_DECAL_VERTEX_SIZE ||
		nShadowDecalIndicesInBuf + numIndex > SHADOW_DECAL_INDEX_SIZE) {
		flush007B14A0(shadow->m_type34, shadow->m_texture68, shadow->m_texture6c, flagB);
		nShadowDecalStartBatchVertex = 0;
		nShadowDecalStartBatchIndex = 0;
		nShadowDecalPolysInBatch = 0;
		nShadowDecalVertsInBatch = 0;
		nShadowDecalVertsInBuf = 0;
		nShadowDecalIndicesInBuf = 0;
		discard = true;
	}
	unsigned int lockFlags = discard ? D3DLOCK_DISCARD : D3DLOCK_NOOVERWRITE;
	SHADOW_DECAL_VERTEX *pvVertices;
	unsigned short *pvIndices;
	if (shadowDecalVertexBufferD3D->Lock(nShadowDecalVertsInBuf * sizeof(SHADOW_DECAL_VERTEX),
			numVerts * sizeof(SHADOW_DECAL_VERTEX), (void **)&pvVertices, lockFlags) < 0)
		return;
	if (shadowDecalIndexBufferD3D->Lock(nShadowDecalIndicesInBuf * sizeof(short),
			numIndex * sizeof(short), (void **)&pvIndices, lockFlags) < 0)
		return;

	int i, j;
	Vector3 hmapVertex;
	if (pvVertices) {
		for (j = startY; j <= endY; j++) {
			hmapVertex.Y = (float)(j - borderSize) * MAP_XY_FACTOR;
			for (i = startX; i <= endX; i++) {
				hmapVertex.X = (float)(i - borderSize) * MAP_XY_FACTOR;
				hmapVertex.Z = (float)hmap->getHeight(i, j) * MAP_HEIGHT_SCALE;
				pvVertices->x = hmapVertex.X;
				pvVertices->y = hmapVertex.Y;
				pvVertices->z = hmapVertex.Z;
				pvVertices->diffuse = diffuse;
				pvVertices->u = Vector3::Dot_Product(uVector, hmapVertex - objPos) + uOffset;
				pvVertices->v = Vector3::Dot_Product(vVector, hmapVertex - objPos) + vOffset;
				pvVertices->u2 = 0.0f;
				pvVertices->v2 = 0.0f;
				pvVertices++;
			}
		}
	}

	if (pvIndices) {
		int rowStart;
		int k;
		for (j = startY, rowStart = 0; j < endY; j++, rowStart += vertsPerRow) {
			for (i = rowStart, k = startX; k < endX; i++, k++) {
				if (((const Gen_0074B410 *)hmap)->bfmeBitA(k, j)) {
					pvIndices[0] = i + 1 + nShadowDecalVertsInBatch;
					pvIndices[1] = i + vertsPerRow + nShadowDecalVertsInBatch;
					pvIndices[2] = i + nShadowDecalVertsInBatch;
					pvIndices[3] = i + 1 + nShadowDecalVertsInBatch;
					pvIndices[4] = i + 1 + vertsPerRow + nShadowDecalVertsInBatch;
					pvIndices[5] = i + vertsPerRow + nShadowDecalVertsInBatch;
				} else {
					pvIndices[0] = i + nShadowDecalVertsInBatch;
					pvIndices[1] = i + 1 + vertsPerRow + nShadowDecalVertsInBatch;
					pvIndices[2] = i + vertsPerRow + nShadowDecalVertsInBatch;
					pvIndices[3] = i + nShadowDecalVertsInBatch;
					pvIndices[4] = i + 1 + nShadowDecalVertsInBatch;
					pvIndices[5] = i + 1 + vertsPerRow + nShadowDecalVertsInBatch;
				}
				pvIndices += 6;
			}
		}
	}

	shadowDecalVertexBufferD3D->Unlock();
	shadowDecalIndexBufferD3D->Unlock();
	nShadowDecalPolysInBatch += numPolys;
	nShadowDecalVertsInBuf += numVerts;
	nShadowDecalVertsInBatch += numVerts;
	nShadowDecalIndicesInBuf += numIndex;
	(void)flagA;
}
