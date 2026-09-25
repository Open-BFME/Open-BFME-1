// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// W3DTreeBuffer constructor, retail 0x00736720: installs vtable 0x01121608, whose name getter
// returns "W3DTreeBuffer"; the terrain stores the result at +0x3094 (identity_evidence/00720820.md).

#include <string.h>

typedef int Int;
typedef float Real;
typedef bool Bool;

class GameEngine;
class GlobalData;
extern GameEngine *TheGameEngine;
extern GlobalData *TheWritableGlobalData;

class Rva0094D1E0List
{
public:
	Rva0094D1E0List(Int capacity, Int extra);
	~Rva0094D1E0List(void);

private:
	unsigned char m_body[0x28];
};

#pragma comment(linker, "/alternatename:??0Rva0094D1E0List@@QAE@HH@Z=?d_0094d1e0@@YAXXZ")
#pragma comment(linker, "/alternatename:??1Rva0094D1E0List@@QAE@XZ=??1Gen_uwm_0094cdf0@@QAE@XZ")

class Rva00736590TreeRecord
{
public:
	Rva00736590TreeRecord(void);
	~Rva00736590TreeRecord(void);

private:
	unsigned char m_body[0xe8];
};

class Rva00735D80TreeType
{
public:
	Rva00735D80TreeType(void);
	~Rva00735D80TreeType(void);

	void *m_mesh;

private:
	unsigned char m_body[0x58];
};

// The array helpers receive the ILT entries retail pushes; the type constructor is its own ledger row.
#pragma comment(linker, "/alternatename:??0Rva00736590TreeRecord@@QAE@XZ=?j_0000985e@@YAXXZ")
#pragma comment(linker, "/alternatename:??1Rva00736590TreeRecord@@QAE@XZ=?j_0003a495@@YAXXZ")
#pragma comment(linker, "/alternatename:??1Rva00735D80TreeType@@QAE@XZ=?j_00008247@@YAXXZ")

class TextureClass;

class BfmeHandleCX
{
public:
	BfmeHandleCX(void) : m_p(0) {}
	~BfmeHandleCX(void);

	TextureClass *m_p;
};

class Xfer;

class __declspec(novtable) Snapshot
{
public:
	Snapshot(void) {}
	virtual ~Snapshot(void);

protected:
	virtual void loadPostProcess(void) = 0;
	virtual const char *getSnapshotName(void) const = 0;
	virtual void xfer(Xfer *xfer) = 0;
};

class W3DTreeBuffer : public Snapshot
{
public:
	W3DTreeBuffer(Bool useSmallBuffers);
	virtual ~W3DTreeBuffer(void);

	void clearAllTrees(void);
	void allocateTreeBuffers(void);

protected:
	virtual void loadPostProcess(void);
	virtual const char *getSnapshotName(void) const;
	virtual void xfer(Xfer *xfer);

private:
	void *m_vertexTree[20];
	void *m_indexTree[20];
	void *m_resource0;
	void *m_resource1;
	void *m_resource2;
	void *m_resource3;
	void *m_resource4;
	BfmeHandleCX m_textureB8;
	BfmeHandleCX m_textureBC;
	Rva0094D1E0List m_resetListC0;
	Rva0094D1E0List m_resetListE8;
	Int m_curNumTreeVertices[20];
	Int m_curNumTreeIndices[20];
	Rva00736590TreeRecord m_trees[12000];
	unsigned char m_pad2a7cb0[7];
	Bool m_initialized;
	unsigned char m_pad2a7cb8[4];
	Rva00735D80TreeType m_treeTypes[64];
	unsigned char m_pad2a93bc[0x2a987c - 0x2a93bc];
	Int m_curSwayVersion;
	unsigned char m_pad2a9880[0x2a98f8 - 0x2a9880];
	Real m_swayPeriod;
	unsigned char m_pad2a98fc[4];
	Int m_treeIndexStep;
	BfmeHandleCX m_treeTexture;
	Int m_numBuffers;
	Bool m_field2a990c;
	Bool m_useSmallBuffers;
};

// ??0W3DTreeBuffer@@QAE@_N@Z
W3DTreeBuffer::W3DTreeBuffer(Bool useSmallBuffers)
	: m_resetListC0(0x800, 0x15),
	  m_resetListE8(0x400, 0x31545844)
{
	m_initialized = false;
	m_numBuffers = 3 + (useSmallBuffers == 0 ? 0 : 17);
	m_useSmallBuffers = useSmallBuffers;

	for (Int i = 0; i < m_numBuffers; ++i) {
		m_vertexTree[i] = 0;
		m_indexTree[i] = 0;
		m_curNumTreeVertices[i] = 0;
		m_curNumTreeIndices[i] = 0;
	}

	for (Int i = 0; i < 64; ++i)
		m_treeTypes[i].m_mesh = 0;

	m_resource1 = 0;
	m_resource0 = 0;
	m_resource2 = 0;
	m_resource3 = 0;
	m_resource4 = 0;

	clearAllTrees();
	allocateTreeBuffers();
	m_initialized = true;
	m_curSwayVersion = -1;

	if (TheGameEngine != 0)
		m_swayPeriod = (Real)*(const Int *)((const char *)TheGameEngine + 0x34);
	else
		m_swayPeriod = 1.0f;

	memset(m_trees, 0, sizeof(m_trees));
	m_treeIndexStep = ((const unsigned char *)TheWritableGlobalData)[0x1b];
	m_field2a990c = false;
}
