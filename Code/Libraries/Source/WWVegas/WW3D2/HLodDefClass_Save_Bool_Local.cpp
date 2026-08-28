// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib
// The BFME HLod save entry points return a one-byte bool.  This TU keeps that
// ABI view local because the shared ZH declaration still uses WW3DErrorType.

#include "winbase_shim.h"
#include "chunkio.h"
#include "w3d_file.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/hlod.h
class HLodDefClass
{
private:
	// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/hlod.h
	class SubObjectArrayClass
	{
	public:
		bool Save_W3D(ChunkSaveClass &csave);

		float MaxScreenSize;
		int ModelCount;
		char **ModelName;
		int *BoneIndex;
	};

public:
	bool Save(ChunkSaveClass &csave);

protected:
	bool Save_Header(ChunkSaveClass &csave);
	bool Save_Lod_Array(ChunkSaveClass &csave);

	char *Name;
	char *HierarchyTreeName;
	int LodCount;
	SubObjectArrayClass *Lod;
};

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
