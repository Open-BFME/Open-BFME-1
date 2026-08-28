// cl: /DNDEBUG /MD /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// Lift the MeshGeometryClass::read_user_text machine-code scaffold to clean C++.
//
// This is one handler in MeshGeometryClass::read_chunks' dispatch table,
// the same table read_vertex_shade_indices (0x9255B0, already landed)
// belongs to. Every handler in that table is called with its status
// captured as `mov bl, al` -- only AL is read -- so retail declares this
// handler bool, not the WW3DErrorType the vendored ZH source uses.
//
// It also does not touch the field the public Get_User_Text/Set_User_Text
// pair uses: Get_User_Text (0x924C30, already landed) proves that field
// lives at this+0x10. This handler instead stores the freshly read
// ShareBufferClass<char> at this+0x14 -- the exact slot Get_Name/Set_Name
// use for MeshName (both already landed at 0x924D00/0x924D10). Retail's
// user-text loader really does write through the mesh-name slot; that is
// not a modelling convenience, it is what both landed sibling accessors
// and this body's own bytes agree on.
//
// The buffer construction sequence (operator new, ShareBufferClass<char>
// ctor via NEW_REF, ??_U string-literal setup) is copied verbatim from
// the already-landed Set_Name/Get_User_Text family in meshgeometry.cpp,
// so the real headers are used rather than a hand-rolled replica.

#include "chunkio.h"
#include "sharebuf.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/meshgeometry.h
class MeshGeometryClass
{
protected:
	bool read_user_text(ChunkLoadClass & cload);

private:
	char pad_00[0x14];
	ShareBufferClass<char> *NameSlot;			///< retail this+0x14 (MeshName's slot)
};

// ?read_user_text@MeshGeometryClass@@IAE_NAAVChunkLoadClass@@@Z
bool MeshGeometryClass::read_user_text(ChunkLoadClass & cload)
{
	unsigned int textlen = cload.Cur_Chunk_Length();

	if (NameSlot != NULL) {
		return true;
	}

	NameSlot = NEW_REF(ShareBufferClass<char>,(textlen, "MeshGeometryClass::UserText"));

	if (cload.Read(NameSlot->Get_Array(),textlen) != textlen) {
		return false;
	}
	return true;
}
