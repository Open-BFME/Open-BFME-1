// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// Open-BFME: BFME ABI-slice reconstruction of MeshModelClass::Load_W3D.
//
// The retail BFME mesh loader keeps the MeshGeometry fields at the offsets
// below, adds the skin argument to Reset, and returns a byte-sized status.
// This TU deliberately models only the ABI slice used by this body; the
// complete engine declarations remain in meshmdl.h for the other methods.

#include "always.h"
#include "bittype.h"
#include "vector3.h"
#include "w3derr.h"
#include "w3d_file.h"
#include "chunkio.h"
#include "wwdebug.h"
#include "ww3d.h"

#include <string.h>

class MeshLoadContextClass
{
public:
	class AlternateMatDescSlice
	{
		char _padding[0x24];
		int VertexCount;
		int PolygonCount;

	public:
		void Set_Vertex_Count(int count) { VertexCount = count; }
		void Set_Polygon_Count(int count) { PolygonCount = count; }
	};

	W3dMeshHeader3Struct Header;
	void * TexCoords;
	W3dMaterialInfoStruct MatInfo;
	uint32 PrelitChunkID;
	char _before_alternate[0x60];
	AlternateMatDescSlice AlternateMatDesc;
	char _tail[0xf8];

	friend class MeshModelClass;

	private:
	MeshLoadContextClass(void);
	~MeshLoadContextClass(void);
};

class MeshGeometryClass
{
public:
	virtual bool Load_W3D(ChunkLoadClass & cload);

	void Set_User_Text(char * usertext);
	protected:
	uint16 * get_bone_links(bool create = true);
	void Generate_Culling_Tree(void);

protected:
	char _base[0x18 - 4];
	int Flags;
	char SortLevel;
	uint8 _sort_padding[3];
	uint32 W3dAttributes;
	int PolyCount;
	int VertexCount;
	char _geometry_padding[0x68 - 0x2c];
	Vector3 BoundBoxMin;
	Vector3 BoundBoxMax;
	Vector3 BoundSphereCenter;
	float BoundSphereRadius;
	void * CullTree;
};

class MeshModelClass : public MeshGeometryClass
{
public:
	virtual bool Load_W3D(ChunkLoadClass & cload);

	void Reset(int polycount, int vertcount, int passcount, bool skin);

	protected:
	WW3DErrorType read_chunks(ChunkLoadClass & cload, MeshLoadContextClass * context);
	void install_materials(MeshLoadContextClass * context);
	void post_process(void);

	void Set_Flag(int flag, bool onoff)
	{
		if (onoff) {
			Flags |= flag;
		} else {
			Flags &= ~flag;
		}
	}

	int Get_Flag(int flag)
	{
		return Flags & flag;
	}
};

bool MeshModelClass::Load_W3D(ChunkLoadClass & cload)
{
	MeshLoadContextClass * context = NULL;

	cload.Open_Chunk();
	if (cload.Cur_Chunk_ID() != W3D_CHUNK_MESH_HEADER3) {
		WWDEBUG_SAY(("Old format mesh mesh, no longer supported.\n"));
		goto Error;
	}

	context = new MeshLoadContextClass;
	if (cload.Read(&(context->Header), sizeof(W3dMeshHeader3Struct)) != sizeof(W3dMeshHeader3Struct)) {
		goto Error;
	}
	cload.Close_Chunk();

	Reset(context->Header.NumTris, context->Header.NumVertices, 1,
		(context->Header.Attributes & W3D_MESH_FLAG_GEOMETRY_TYPE_MASK) == W3D_MESH_FLAG_GEOMETRY_TYPE_SKIN);

	char * tmpname;
	int namelen;
	namelen = strlen(context->Header.ContainerName);
	namelen += strlen(context->Header.MeshName);
	namelen += 2;
	W3dAttributes = context->Header.Attributes;
	SortLevel = context->Header.SortLevel;
	tmpname = W3DNEWARRAY char[namelen];
	memset(tmpname, 0, namelen);

	if (strlen(context->Header.ContainerName) > 0) {
		strcpy(tmpname, context->Header.ContainerName);
		strcat(tmpname, ".");
	}
	strcat(tmpname, context->Header.MeshName);

	Set_User_Text(tmpname);
	delete[] tmpname;
	tmpname = NULL;

	context->AlternateMatDesc.Set_Vertex_Count(VertexCount);
	context->AlternateMatDesc.Set_Polygon_Count(PolyCount);

	BoundBoxMin.Set(context->Header.Min.X, context->Header.Min.Y, context->Header.Min.Z);
	BoundBoxMax.Set(context->Header.Max.X, context->Header.Max.Y, context->Header.Max.Z);
	BoundSphereCenter.Set(context->Header.SphCenter.X, context->Header.SphCenter.Y, context->Header.SphCenter.Z);
	BoundSphereRadius = context->Header.SphRadius;

	if (context->Header.Version >= W3D_MAKE_VERSION(4, 1)) {
		int geometry_type = context->Header.Attributes & W3D_MESH_FLAG_GEOMETRY_TYPE_MASK;
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
			Set_Flag(0x10400, true);
			break;
		}
	}

	if (context->Header.Attributes & W3D_MESH_FLAG_TWO_SIDED) {
		Set_Flag(0x100, true);
	}
	if (context->Header.Attributes & W3D_MESH_FLAG_CAST_SHADOW) {
		Set_Flag(0x1000, true);
	}
	if (context->Header.Attributes & W3D_MESH_FLAG_NPATCHABLE) {
		Set_Flag(0x10000, true);
	}

	if (context->Header.Attributes & W3D_MESH_FLAG_PRELIT_MASK) {
		switch (WW3D::Get_Prelit_Mode()) {
		case WW3D::PRELIT_MODE_LIGHTMAP_MULTI_TEXTURE:
			if (context->Header.Attributes & W3D_MESH_FLAG_PRELIT_LIGHTMAP_MULTI_TEXTURE) {
				context->PrelitChunkID = W3D_CHUNK_PRELIT_LIGHTMAP_MULTI_TEXTURE;
				Set_Flag(0x8000, true);
				break;
			}
		case WW3D::PRELIT_MODE_LIGHTMAP_MULTI_PASS:
			if (context->Header.Attributes & W3D_MESH_FLAG_PRELIT_LIGHTMAP_MULTI_PASS) {
				context->PrelitChunkID = W3D_CHUNK_PRELIT_LIGHTMAP_MULTI_PASS;
				Set_Flag(0x4000, true);
				break;
			}
		case WW3D::PRELIT_MODE_VERTEX:
			if (context->Header.Attributes & W3D_MESH_FLAG_PRELIT_VERTEX) {
				context->PrelitChunkID = W3D_CHUNK_PRELIT_VERTEX;
				Set_Flag(0x2000, true);
				break;
			}
		default:
			WWASSERT(context->Header.Attributes & W3D_MESH_FLAG_PRELIT_UNLIT);
			context->PrelitChunkID = W3D_CHUNK_PRELIT_UNLIT;
			break;
		}
	} else {
		if (context->Header.Attributes & OBSOLETE_W3D_MESH_FLAG_LIGHTMAPPED) {
			Set_Flag(0x4000, true);
		}
	}

	read_chunks(cload, context);

	if ((context->Header.Version < W3D_MAKE_VERSION(3, 0)) && (Get_Flag(0x400))) {
		uint16 * links = get_bone_links();
		WWASSERT(links);
		for (int bi = 0; bi < VertexCount; bi++) {
			links[bi] += 1;
		}
	}

	if ((((W3dAttributes & W3D_MESH_FLAG_COLLISION_TYPE_MASK) >> W3D_MESH_FLAG_COLLISION_TYPE_SHIFT) != 0) &&
		(CullTree == NULL)) {
		Generate_Culling_Tree();
	}

	install_materials(context);
	delete context;
	post_process();
	return true;

Error:
	return false;
}
