// cl: /DNDEBUG /MD /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWLib
// BFME's HLodDefClass::Load_W3D returns bool in the retail ABI.  Keep this
// ABI view local: the shared ZH header still declares the method as
// WW3DErrorType, which gives a different decorated name and return shape.

#include "winbase_shim.h"
#include "chunkio.h"
#include "w3d_file.h"

// This is the original HLodDef layout, with the empty W3DMPO base omitted.
// The surrounding methods are already recovered in the shared HLOD TU; only
// this ABI-correct loader is intentionally defined here.
class HLodDefClass
{
private:
	class SubObjectArrayClass
	{
	public:
		bool Load_W3D(ChunkLoadClass &cload);
		bool Save_W3D(ChunkSaveClass &csave);

		float MaxScreenSize;
		int ModelCount;
		char **ModelName;
		int *BoneIndex;
	};

public:
	bool Load_W3D(ChunkLoadClass &cload);
	bool Save(ChunkSaveClass &csave);

private:
	char *Name;
	char *HierarchyTreeName;
	int LodCount;
	SubObjectArrayClass *Lod;
	SubObjectArrayClass Aggregates;
	void *ProxyArray;

	void Free(void);
	bool read_header(ChunkLoadClass &cload);
	bool read_proxy_array(ChunkLoadClass &cload);

protected:
	bool Save_Header(ChunkSaveClass &csave);
	bool Save_Lod_Array(ChunkSaveClass &csave);
};

bool HLodDefClass::Load_W3D(ChunkLoadClass &cload)
{
	Free();

	if (read_header(cload) == FALSE) {
		return false;
	}

	for (int iLOD = 0; iLOD < LodCount; iLOD++) {
		if (!cload.Open_Chunk()) return false;

		if (cload.Cur_Chunk_ID() != W3D_CHUNK_HLOD_LOD_ARRAY) {
			return false;
		}

		Lod[iLOD].Load_W3D(cload);
		cload.Close_Chunk();
	}

	while (cload.Open_Chunk()) {
		switch(cload.Cur_Chunk_ID())
		{
			case W3D_CHUNK_HLOD_AGGREGATE_ARRAY:
				Aggregates.Load_W3D(cload);
				break;
			case W3D_CHUNK_HLOD_PROXY_ARRAY:
				read_proxy_array(cload);
				break;
		}
		cload.Close_Chunk();
	}

	return true;
}

bool HLodDefClass::Save(ChunkSaveClass &csave)
{
	bool ret_val = false;
	if (csave.Begin_Chunk(W3D_CHUNK_HLOD) == TRUE) {
		if ((Save_Header(csave) == true) && (Save_Lod_Array(csave) == true)) {
			ret_val = true;
		}
		csave.End_Chunk();
	}
	return ret_val;
}

bool HLodDefClass::Save_Header(ChunkSaveClass &csave)
{
	bool ret_val = false;
	if (csave.Begin_Chunk(W3D_CHUNK_HLOD_HEADER) == TRUE) {
		W3dHLodHeaderStruct header = { 0 };
		header.Version = W3D_CURRENT_HLOD_VERSION;
		header.LodCount = LodCount;
		::lstrcpyn(header.Name, Name, sizeof(header.Name));
		header.Name[sizeof(header.Name) - 1] = 0;
		::lstrcpyn(header.HierarchyName, HierarchyTreeName, sizeof(header.HierarchyName));
		header.HierarchyName[sizeof(header.HierarchyName) - 1] = 0;
		if (csave.Write(&header, sizeof(header)) == sizeof(header)) {
			ret_val = true;
		}
		csave.End_Chunk();
	}
	return ret_val;
}

bool HLodDefClass::Save_Lod_Array(ChunkSaveClass &csave)
{
	bool success = true;
	for (int lod_index = 0; (lod_index < LodCount) && success; lod_index++) {
		success = Lod[lod_index].Save_W3D(csave);
	}
	return success;
}
