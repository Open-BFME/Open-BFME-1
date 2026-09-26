// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWDebug
#define private public

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

#include "pointgr.h"
#include "dx8indexbuffer.h"
#include "refcount.h"
#include "simplevec.h"
#include "sortingrenderer.h"
#include "vertmaterial.h"

extern VectorClass<Vector3> VertexLoc;
extern VectorClass<Vector4> VertexDiffuse;
extern VectorClass<Vector2> VertexUV;
extern DX8IndexBufferClass *Tris;
extern DX8IndexBufferClass *Quads;
extern SortingIndexBufferClass *SortingTris;
extern SortingIndexBufferClass *SortingQuads;

// The retail body at 0x00912CF0 is PointGroupClass::_Shutdown. BFME keeps the
// same static tables as the Zero Hour implementation, but the ledger uses an
// address-derived name until the BFME source name is independently recovered.
void Rva00912CF0(void)
{
	for (int i = 0; i < 5; i++) {
		delete [] PointGroupClass::_TriVertexUVFrameTable[i];
		delete [] PointGroupClass::_QuadVertexUVFrameTable[i];
	}
	if (PointGroupClass::PointMaterial) {
		PointGroupClass::PointMaterial->Release_Ref();
		PointGroupClass::PointMaterial = NULL;
	}
	_ReadWriteBarrier();
	SortingIndexBufferClass *sorting_quads = SortingQuads;
	if (sorting_quads) {
		RefCountClass *object = sorting_quads;
		int *count = reinterpret_cast<int *>(reinterpret_cast<char *>(object) + 4);
		--*count;
		if (*count == 0) {
			object->Delete_This();
		}
		SortingQuads = NULL;
	}
	_ReadWriteBarrier();
	SortingIndexBufferClass *sorting_tris = SortingTris;
	if (sorting_tris) {
		RefCountClass *object = sorting_tris;
		int *count = reinterpret_cast<int *>(reinterpret_cast<char *>(object) + 4);
		--*count;
		if (*count == 0) {
			object->Delete_This();
		}
		SortingTris = NULL;
	}
	_ReadWriteBarrier();
	DX8IndexBufferClass *quads = Quads;
	if (quads) {
		RefCountClass *object = quads;
		int *count = reinterpret_cast<int *>(reinterpret_cast<char *>(object) + 4);
		--*count;
		if (*count == 0) {
			object->Delete_This();
		}
		Quads = NULL;
	}
	_ReadWriteBarrier();
	DX8IndexBufferClass *tris = Tris;
	if (tris) {
		RefCountClass *object = tris;
		int *count = reinterpret_cast<int *>(reinterpret_cast<char *>(object) + 4);
		--*count;
		if (*count == 0) {
			object->Delete_This();
		}
		Tris = NULL;
	}
	PointGroupClass::transformed_loc.Clear();
	VertexLoc.Clear();
	VertexDiffuse.Clear();
	VertexUV.Clear();
}
