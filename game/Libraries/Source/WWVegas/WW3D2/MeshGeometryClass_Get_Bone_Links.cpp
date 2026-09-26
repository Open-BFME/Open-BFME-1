// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/Wwutil /Igame/Libraries/Source/WWVegas/WWDownload /Igame/Libraries/Source/Compression /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep
// Open-BFME5: BFME MeshGeometryClass::get_bone_links ABI slice.
// Retail keeps VertexCount at +0x28 and VertexBoneLink at +0x58.  Four
// uint16 links are reserved per vertex; keep those retail offsets local so
// the shared MeshGeometry declaration remains usable by its other bodies.

#include "always.h"
#include "sharebuf.h"

class MeshGeometryClass
{
	char _padding[0x58];
	ShareBufferClass<unsigned short> *VertexBoneLink;

protected:
	unsigned short *get_bone_links(bool create);
};

// ?get_bone_links@MeshGeometryClass@@IAEPAG_N@Z
unsigned short *MeshGeometryClass::get_bone_links(bool create)
{
	if (create && !VertexBoneLink) {
		VertexBoneLink = NEW_REF(ShareBufferClass<unsigned short>,
			(*reinterpret_cast<int *>(reinterpret_cast<char *>(this) + 0x28) * 4,
			 "MeshGeometryClass::VertexBoneLink"));
	}
	if (VertexBoneLink) {
		return VertexBoneLink->Get_Array();
	}
	return NULL;
}
