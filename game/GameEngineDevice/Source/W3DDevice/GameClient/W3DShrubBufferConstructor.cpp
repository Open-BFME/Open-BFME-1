// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// W3DShrubBuffer constructor, retail 0x00720820: installs vtable 0x01120F94, whose name getter
// returns "W3DShrubBuffer"; the terrain stores the result at +0x3098.

typedef int Int;
typedef float Real;
typedef unsigned char Bool;

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

class TTreeType
{
public:
	TTreeType(void);
	~TTreeType(void);

private:
	unsigned char m_body[0x5c];
};

class TextureClass
{
public:
	void Release_Ref(void);
};

class BfmeHandleCX
{
public:
	BfmeHandleCX(void) : m_p(0) {}
	~BfmeHandleCX(void);

	TextureClass *m_p;
};

class __declspec(novtable) Snapshot
{
public:
	Snapshot(void) {}
	virtual ~Snapshot(void);
	virtual void slot04(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot0c(void) = 0;

private:
};

class W3DShrubBuffer : public Snapshot
{
public:
	virtual void slot04(void);
	virtual void slot08(void);
	virtual void slot0c(void);

	W3DShrubBuffer(Bool useSmallBuffers);
	void clearAllTrees(void);
	void allocateTreeBuffers(void);

private:
	void *m_vertexTree[20];
	void *m_indexTree[20];
	void *m_resource0;
	void *m_resource1;
	void *m_resource2;
	void *m_resource3;
	void *m_resource4;
	unsigned char m_pad00b8[0x1450 - 0xb8];
	BfmeHandleCX m_texture1450;
	BfmeHandleCX m_texture1454;
	Rva0094D1E0List m_resetList1458;
	Rva0094D1E0List m_resetList1480;
	Int m_curNumTreeVertices[20];
	Int m_curNumTreeIndices[20];
	unsigned char m_pad1548[0x1e1ccf - 0x1548];
	Bool m_needToUpdateTexture;
	unsigned char m_pad1e1cd0[4];
	TTreeType m_treeTypes[64];
	unsigned char m_pad1e33d4[0x1e3894 - 0x1e33d4];
	Int m_curSwayVersion;
	unsigned char m_pad1e3898[0x1e3910 - 0x1e3898];
	Real m_swayPeriod;
	BfmeHandleCX m_treeTexture;
	Int m_numBuffers;
	unsigned char m_pad1e391c[4];
	Int m_globalBufferCount;
	Int m_field1e3924;
};

W3DShrubBuffer::W3DShrubBuffer(Bool useSmallBuffers)
	: m_resetList1458(0x800, 0x15),
	  m_resetList1480(0x400, 0x35545844)
{
	m_field1e3924 = 0;
	m_needToUpdateTexture = 0;
	m_numBuffers = 5 + (useSmallBuffers == 0 ? 0 : 15);

	for (Int i = 0; i < m_numBuffers; ++i) {
		m_vertexTree[i] = 0;
		m_indexTree[i] = 0;
		m_curNumTreeVertices[i] = 0;
		m_curNumTreeIndices[i] = 0;
	}

	for (Int i = 0; i < 64; ++i)
		*(Int *)((unsigned char *)m_treeTypes + i * 0x5c) = 0;

	m_resource1 = 0;
	m_resource0 = 0;
	m_resource2 = 0;
	m_resource3 = 0;
	m_resource4 = 0;

	clearAllTrees();
	allocateTreeBuffers();
	m_needToUpdateTexture = 1;
	m_curSwayVersion = -1;

	Int *gameEngine = *(Int **)0x012ED524;
	if (gameEngine != 0)
		m_swayPeriod = (Real)gameEngine[0x34 / sizeof(Int)];
	else
		m_swayPeriod = 1.0f;

	unsigned char *globalData = *(unsigned char **)0x012ED5C8;
	m_globalBufferCount = globalData[0x1b];
}
