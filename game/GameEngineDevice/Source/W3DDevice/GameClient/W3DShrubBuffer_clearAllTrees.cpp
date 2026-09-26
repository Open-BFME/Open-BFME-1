// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/bfmeheightmap /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
#define __PLACEMENT_VEC_NEW_INLINE  // always.h defines array placement-new itself
#define _STLP_USE_STATIC_LIB       // the retail floor list calls __node_alloc directly
// W3DShrubBuffer::clearAllTrees, retail 0x0071C7E0: Zero Hour's clearAllTrees on the shrub layout;
// the constructor at 0x00720820 and the destructor at 0x007206E0 call it.

typedef int Int;
typedef float Real;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/refcount.h
class RefCountClass
{
public:
	virtual void Delete_This(void);

	void Release_Ref(void)
	{
		--m_numRefs;
		if (m_numRefs == 0)
			Delete_This();
	}

private:
	int m_numRefs;
};

// Pinned at 0x009EB7A0: the BFME texture release these buffers call.
class BFMETextureRelease
{
public:
	void Release_Ref();
};

// The list members at +0xC0/+0xE8 (tree) and +0x1458/+0x1480 (shrub); constructor 0x0094D1E0.
class Rva0094D1E0List
{
public:
	void clear(bool reset);
};

struct TreeTypeMesh
{
	RefCountClass *m_mesh;
	char m_padding04[0x58];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameEngine.h
class GameEngine
{
private:
	char m_padding00[0x34];

public:
	Int m_field34;
};

extern GameEngine *TheGameEngine;

struct ShrubRecordMeshes
{
	char m_padding00[4];
	RefCountClass *m_first;
	RefCountClass *m_second;
	char m_padding0c[0x98];
};

class W3DShrubBuffer
{
public:
	void clearAllTrees();
};

// ?clearAllTrees@W3DShrubBuffer@@QAEXXZ
void W3DShrubBuffer::clearAllTrees()
{
	char *base = reinterpret_cast<char *>(this);
	ShrubRecordMeshes *entry =
		reinterpret_cast<ShrubRecordMeshes *>(base + 0x15dc);
	for (Int i = 0; i < *reinterpret_cast<Int *>(base + 0x1e1cc8);
		++i, ++entry) {
		if (entry->m_first) {
			entry->m_first->Release_Ref();
			entry->m_first = 0;
		}
		if (entry->m_second) {
			entry->m_second->Release_Ref();
			entry->m_second = 0;
		}
	}

	Int zero = 0;
	*reinterpret_cast<Int *>(base + 0x1e1cc8) = zero;
	*reinterpret_cast<Int *>(base + 0x1444) = zero;
	*reinterpret_cast<Int *>(base + 0x1440) = zero;
	*reinterpret_cast<Real *>(base + 0x144c) = 1.0f;
	*reinterpret_cast<Real *>(base + 0x1448) = 1.0f;
	BFMETextureRelease **texture =
		reinterpret_cast<BFMETextureRelease **>(base + 0x1450);
	if (*texture) {
		(*texture)->Release_Ref();
		*texture = 0;
	}
	texture = reinterpret_cast<BFMETextureRelease **>(base + 0x1454);
	if (*texture) {
		(*texture)->Release_Ref();
		*texture = 0;
	}
	reinterpret_cast<Rva0094D1E0List *>(base + 0x1458)->clear(false);
	reinterpret_cast<Rva0094D1E0List *>(base + 0x1480)->clear(false);
	*reinterpret_cast<Int *>(base + 0x14f8) = zero;
	*reinterpret_cast<UnsignedByte *>(base + 0x1e1ccc) = 1;

	TreeTypeMesh *type =
		reinterpret_cast<TreeTypeMesh *>(base + 0x1e1cd4);
	for (Int i = 0; i < 64; ++i, ++type) {
		if (type->m_mesh) {
			type->m_mesh->Release_Ref();
			type->m_mesh = 0;
		}
	}

	if (TheGameEngine) {
		*reinterpret_cast<Real *>(base + 0x1e3910) =
			static_cast<Real>(TheGameEngine->m_field34);
	}
	UnsignedInt *sentinel =
		reinterpret_cast<UnsignedInt *>(base + 0xb8);
	for (Int i = 0; i < 0x4e2; ++i) {
		sentinel[i] = 0xffffffff;
	}
	*reinterpret_cast<Int *>(base + 0x1e33d4) = zero;
}
