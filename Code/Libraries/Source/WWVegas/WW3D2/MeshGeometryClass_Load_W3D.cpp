// cl: /DNDEBUG /MD /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// Open-BFME: BFME ABI-slice reconstruction of MeshGeometryClass::Load_W3D.
//
// The retail MeshGeometry layout puts UserText at +0x10 and moves the
// geometry/bounds members four bytes before the vendored Zero Hour header.
// Keep this TU's class slice explicit so the source follows the retail field
// offsets used by the slot body.  The three-argument Reset_Geometry call is a
// BFME ABI detail: its exact body returns with ret 0xc.

#include "always.h"
#include "refcount.h"
#include "bittype.h"
#include "sharebuf.h"
#include "vector3.h"
#include "vector3i.h"
#include "vector4.h"
#include "sphere.h"
#include "multilist.h"
#include "w3derr.h"
#include "w3d_file.h"
#include "chunkio.h"
#include "wwdebug.h"
#include <string.h>

class AABTreeClass;

class MeshGeometryClass : public W3DMPO, public RefCountClass, public MultiListObjectClass
{
public:
	virtual bool Load_W3D(ChunkLoadClass & cload);

	void Reset_Geometry(int polycount, int vertcount, bool bfme_header);
	void Set_User_Text(char * usertext);

	void Set_Flag(int flag, bool onoff) { if (onoff) { Flags |= flag; } else { Flags &= ~flag; } }
	int Get_Flag(int flag) { return Flags & flag; }
	int Get_Vertex_Count(void) { return VertexCount; }

protected:
	WW3DErrorType read_chunks(ChunkLoadClass & cload);
	uint16 * get_bone_links(bool create = true);
	void Generate_Culling_Tree(void);

	void * UserText;
	void * MeshName;
	int Flags;
	char SortLevel;
	uint32 W3dAttributes;
	int PolyCount;
	int VertexCount;
	void * Poly;
	void * Vertex;
	void * Slot34;
	void * Slot38;
	void * Slot3c;
	void * Slot40;
	void * Slot44;
	void * Slot48;
	void * Slot4c;
	void * Slot50;
	void * Slot54;
	void * Slot58;
	void * Slot5c;
	void * Slot60;
	void * Slot64;
	Vector3 BoundBoxMin;
	Vector3 BoundBoxMax;
	Vector3 BoundSphereCenter;
	float BoundSphereRadius;
	AABTreeClass * CullTree;
};

bool MeshGeometryClass::Load_W3D(ChunkLoadClass & cload)
{
	cload.Open_Chunk();
	if (cload.Cur_Chunk_ID() != W3D_CHUNK_MESH_HEADER3) {
		WWDEBUG_SAY(("Old format mesh mesh, no longer supported.\n"));
		goto Error;
	}

	W3dMeshHeader3Struct header;
	if (cload.Read(&header, sizeof(W3dMeshHeader3Struct)) != sizeof(W3dMeshHeader3Struct)) {
		goto Error;
	}
	cload.Close_Chunk();

	char * tmpname;
	int namelen;

	Reset_Geometry(header.NumTris, header.NumVertices,
		(header.Attributes & W3D_MESH_FLAG_GEOMETRY_TYPE_MASK) == W3D_MESH_FLAG_GEOMETRY_TYPE_SKIN);

	namelen = strlen(header.ContainerName);
	namelen += strlen(header.MeshName);
	namelen += 2;
	W3dAttributes = header.Attributes;
	SortLevel = header.SortLevel;
	tmpname = W3DNEWARRAY char[namelen];
	memset(tmpname, 0, namelen);

	if (strlen(header.ContainerName) > 0) {
		strcpy(tmpname, header.ContainerName);
		strcat(tmpname, ".");
	}
	strcat(tmpname, header.MeshName);

	Set_User_Text(tmpname);
	delete[] tmpname;
	tmpname = NULL;

	BoundBoxMin.Set(header.Min.X, header.Min.Y, header.Min.Z);
	BoundBoxMax.Set(header.Max.X, header.Max.Y, header.Max.Z);
	BoundSphereCenter.Set(header.SphCenter.X, header.SphCenter.Y, header.SphCenter.Z);
	BoundSphereRadius = header.SphRadius;

	if (header.Version >= W3D_MAKE_VERSION(4, 1)) {
		int geometry_type = header.Attributes & W3D_MESH_FLAG_GEOMETRY_TYPE_MASK;
		switch (geometry_type) {
			case W3D_MESH_FLAG_GEOMETRY_TYPE_NORMAL:
				break;
			case W3D_MESH_FLAG_GEOMETRY_TYPE_CAMERA_ALIGNED:
				Set_Flag(0x200, true);
				break;
			case W3D_MESH_FLAG_GEOMETRY_TYPE_CAMERA_ORIENTED:
				Set_Flag(0x800, true);
				break;
			case W3D_MESH_FLAG_GEOMETRY_TYPE_SKIN:
				Set_Flag(0x400, true);
				break;
		}
	}

	if (header.Attributes & W3D_MESH_FLAG_TWO_SIDED) {
		Set_Flag(0x100, true);
	}
	if (header.Attributes & W3D_MESH_FLAG_CAST_SHADOW) {
		Set_Flag(0x1000, true);
	}

	read_chunks(cload);

	if ((header.Version < W3D_MAKE_VERSION(3, 0)) && (Get_Flag(0x400))) {
		uint16 * links = get_bone_links();
		WWASSERT(links);
		for (int bi = 0; bi < Get_Vertex_Count(); bi++) {
			links[bi] += 1;
		}
	}

	if ((((W3dAttributes & W3D_MESH_FLAG_COLLISION_TYPE_MASK) >> W3D_MESH_FLAG_COLLISION_TYPE_SHIFT) != 0) &&
		(CullTree == NULL)) {
		Generate_Culling_Tree();
	}

	return true;

Error:
	return false;
}
