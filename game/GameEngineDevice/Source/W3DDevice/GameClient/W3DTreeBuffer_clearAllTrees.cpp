// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/bfmeheightmap /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
#define __PLACEMENT_VEC_NEW_INLINE  // always.h defines array placement-new itself
#define _STLP_USE_STATIC_LIB       // the retail floor list calls __node_alloc directly
// W3DTreeBuffer::clearAllTrees, retail 0x00732E70: Zero Hour's clearAllTrees on BFME's tree layout,
// under the radar reset lock; the constructor at 0x00736720 calls it before allocateTreeBuffers.

typedef int Int;
typedef float Real;
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

void W3DRadarResetLock(void);
void W3DRadarResetUnlock(void);

class BfmeRadarResetGuard
{
public:
	BfmeRadarResetGuard() { W3DRadarResetLock(); }
	~BfmeRadarResetGuard() { W3DRadarResetUnlock(); }
};

class W3DTreeBuffer
{
public:
	void clearAllTrees();
};

// ?clearAllTrees@W3DTreeBuffer@@QAEXXZ
void W3DTreeBuffer::clearAllTrees()
{
	BfmeRadarResetGuard guard;
	char *base = reinterpret_cast<char *>(this);
	Int zero = 0;

	*reinterpret_cast<Int *>(base + 0x2a7cb0) = zero;
	BFMETextureRelease **texture =
		reinterpret_cast<BFMETextureRelease **>(base + 0xb8);
	if (*texture) {
		(*texture)->Release_Ref();
		*texture = 0;
	}
	texture = reinterpret_cast<BFMETextureRelease **>(base + 0xbc);
	if (*texture) {
		(*texture)->Release_Ref();
		*texture = 0;
	}
	reinterpret_cast<Rva0094D1E0List *>(base + 0xc0)->clear(false);
	reinterpret_cast<Rva0094D1E0List *>(base + 0xe8)->clear(false);
	*reinterpret_cast<Int *>(base + 0x160) = zero;
	*reinterpret_cast<UnsignedByte *>(base + 0x2a7cb4) = 1;

	TreeTypeMesh *type =
		reinterpret_cast<TreeTypeMesh *>(base + 0x2a7cbc);
	for (Int i = 0; i < 64; ++i, ++type) {
		if (type->m_mesh) {
			type->m_mesh->Release_Ref();
			type->m_mesh = 0;
		}
	}

	if (TheGameEngine) {
		*reinterpret_cast<Real *>(base + 0x2a98f8) =
			static_cast<Real>(TheGameEngine->m_field34);
	}
	*reinterpret_cast<Int *>(base + 0x2a93bc) = zero;
}
