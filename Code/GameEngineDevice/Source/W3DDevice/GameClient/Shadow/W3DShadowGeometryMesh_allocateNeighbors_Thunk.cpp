// cl: /DNDEBUG /MD /EHs-c-
// readable body of ?allocateNeighbors@W3DShadowGeometryMesh@@IAE_NH@Z: Code/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DVolumetricShadow.cpp
// Open-BFME5: W3DShadowGeometryMesh::allocateNeighbors, retail 0x007B81D0,
// zh_sweep packet 007b81d0.
//
// The Zero Hour body unchanged. Compiled against the vendored class it landed
// on every byte except two: retail writes m_polyNeighbors at [this+0x24] and
// m_numPolyNeighbors at [this+0x28], where the flat layout puts them at +0x20
// and +0x24. A uniform four-byte shift of the trailing members is what a vptr
// at +0x00 looks like, and this class has a switch for exactly that -- the
// reference declares GetPolygonIndex and its neighbours `virtual` under
// DO_TERRAIN_SHADOW_VOLUMES. BFME builds the polymorphic spelling.
//
// It gets its own TU because W3DVolumetricShadow.cpp has 55 other matched rows
// standing on the flat layout; defining that macro there would move all of
// them at once. The one virtual below is a placeholder for whichever method
// BFME made virtual: this body proves the vptr exists, not which slot is what.
//
// sizeof(PolyNeighbor) is 22, which retail confirms with `imul eax,eax,0x16`,
// so the array allocation is unchanged too -- a POD array, no cookie, straight
// to operator new[] at 0x00881F70.

// Declared so `new T[]` picks the array form. Without it MSVC lowers the POD
// array allocation to scalar operator new, which is a different callee.
void *operator new[]( unsigned int size );				///< ??_U@YAPAXI@Z at 0x00881F70

typedef int Int;
typedef bool Bool;
typedef short Short;
typedef unsigned char Byte;

typedef struct _NeighborEdge
{
	Short neighborIndex;
	Short neighborEdgeIndex[ 2 ];
} NeighborEdge;

const Int MAX_POLYGON_NEIGHBORS = 3;

struct PolyNeighbor
{
	Short myIndex;
	Byte status;
	NeighborEdge neighbor[ MAX_POLYGON_NEIGHBORS ];
};

class MeshClass;
class Vector3;
class TriIndex;

class W3DShadowGeometryMesh
{
public:
	// Placeholder for the method BFME declares virtual here. Only its effect
	// on the layout is proven: a vptr at +0x00.
	virtual void polymorphic_placeholder( void ) = 0;

protected:
	Bool allocateNeighbors( Int numPolys );

	MeshClass *m_mesh;						///< +0x04
	Int m_meshRobjIndex;					///< +0x08
	const Vector3 *m_verts;					///< +0x0C
	Vector3 *m_polygonNormals;				///< +0x10
	Int m_numVerts;							///< +0x14
	Int m_numPolygons;						///< +0x18
	const TriIndex *m_polygons;				///< +0x1C
	unsigned short *m_parentVerts;			///< +0x20
	PolyNeighbor *m_polyNeighbors;			///< +0x24
	Int m_numPolyNeighbors;					///< +0x28
};

// ?allocateNeighbors@W3DShadowGeometryMesh@@IAE_NH@Z
Bool W3DShadowGeometryMesh::allocateNeighbors( Int numPolys )
{

	// allocate the list
	m_polyNeighbors = ::new PolyNeighbor[ numPolys ];
	if( m_polyNeighbors == 0 )
	{

		return false;

	}  // end if

	// list is now acutally allocated
	m_numPolyNeighbors = numPolys;

	return true;

}
