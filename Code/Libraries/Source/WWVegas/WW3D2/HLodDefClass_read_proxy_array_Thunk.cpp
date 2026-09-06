// cl: /DNDEBUG /MD /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
#define Matrix4x4 Matrix4

// Open-BFME7: retail built this TU with the array/scalar delete declared nothrow (no EH-state
// reset after vector-constructor iterators; see docs/shape_levers.md).
void __cdecl operator delete[](void *) throw();
void __cdecl operator delete(void *) throw();
#include "hlod.h"
#include "chunkio.h"

class ProxyRecordClass
{
public:
	ProxyRecordClass() : BoneIndex(0) { memset(Name, 0, sizeof(Name)); }
	bool operator==(const ProxyRecordClass &) { return false; }
	bool operator!=(const ProxyRecordClass &that) { return !(*this == that); }
	void Init(const W3dHLodSubObjectStruct &data)
	{
		BoneIndex = data.BoneIndex;
		strncpy(Name, data.Name, sizeof(Name));
	}
protected:
	int BoneIndex;
	char Name[2 * W3D_NAME_LEN];
};

class ProxyArrayClass : public VectorClass<ProxyRecordClass>, public RefCountClass
{
public:
	ProxyArrayClass(int size) : VectorClass<ProxyRecordClass>(size) {}
};

// Open-BFME5: replace the opcode dump with the original C++ loader.
bool HLodDefClass::read_proxy_array(ChunkLoadClass &cload)
{
	REF_PTR_RELEASE(ProxyArray);

	if (!cload.Open_Chunk())
		return false;
	if (cload.Cur_Chunk_ID() != W3D_CHUNK_HLOD_SUB_OBJECT_ARRAY_HEADER)
		return false;

	W3dHLodArrayHeaderStruct header;
	if (cload.Read(&header, sizeof(header)) != sizeof(header))
		return false;
	if (!cload.Close_Chunk())
		return false;

	ProxyArray = NEW_REF(ProxyArrayClass, (header.ModelCount));

	for (int imodel = 0; imodel < ProxyArray->Length(); ++imodel) {
		if (!cload.Open_Chunk())
			return false;
		if (cload.Cur_Chunk_ID() != W3D_CHUNK_HLOD_SUB_OBJECT)
			return false;

		W3dHLodSubObjectStruct subobjdef;
		if (cload.Read(&subobjdef, sizeof(subobjdef)) != sizeof(subobjdef))
			return false;
		if (!cload.Close_Chunk())
			return false;

		(*ProxyArray)[imodel].Init(subobjdef);
	}
	return true;
}
