// cl: /DNDEBUG /MD /EHsc

// GenAlpha::h00024D2A, retail 0x007B9760, 139 bytes.
//
// Named by the already-matched S3 triple at 0x007B7680, whose REL32 lands
// on ILT 0x00024D2A and follows to this body. Scoped W3D radar lock, two
// COM Release()s on the globals at 0x01306F20 / 0x01306F1C, then
// Rva007ADB80Owner::releaseReferences on 0x01306DE8, retail's
// W3DBufferManager singleton, and a thiscall back
// through ILT 0x0003139A.

struct IDirect3DVertexBuffer8;
extern IDirect3DVertexBuffer8 *shadowVertexBufferD3D;
struct IDirect3DIndexBuffer8;
extern IDirect3DIndexBuffer8 *shadowIndexBufferD3D;

typedef unsigned long ULONG;

void W3DRadarResetLock(void);
char bfmeUnlock1179(void);

class BfmeRadarResetGuard
{
public:
	BfmeRadarResetGuard() { W3DRadarResetLock(); }
	~BfmeRadarResetGuard() { bfmeUnlock1179(); }
};

struct BfmeComUnknown
{
	virtual long __stdcall QueryInterface(void *riid, void **ppv) = 0;
	virtual ULONG __stdcall AddRef() = 0;
	virtual ULONG __stdcall Release() = 0;
};

class W3DBufferManager;

class Rva007ADB80Owner
{
public:
	void releaseReferences();
};

struct GenAlphaChunk
{
	char m_pad[0x68];
	GenAlphaChunk *m_next;
	char m_pad2[0x1200 - 0x6c];
	struct Vector
	{
		float x;
		float y;
		float z;
	};
	Vector m_vectors[0xa0];
};

class GenAlpha
{
public:
	void h00024D2A();
	void afterRelease();
	GenAlphaChunk *m_first;
};

			// 0x01306F20
			// 0x01306F1C
extern W3DBufferManager *TheW3DBufferManager;	// 0x01306DE8

// ?h00024D2A@GenAlpha@@QAEXXZ
void GenAlpha::h00024D2A()
{
	BfmeRadarResetGuard guard;
	if (((BfmeComUnknown *&)shadowIndexBufferD3D))
		((BfmeComUnknown *&)shadowIndexBufferD3D)->Release();
	if (((BfmeComUnknown *&)shadowVertexBufferD3D))
		((BfmeComUnknown *&)shadowVertexBufferD3D)->Release();
	Rva007ADB80Owner *owner = (Rva007ADB80Owner *)TheW3DBufferManager;
	((BfmeComUnknown *&)shadowIndexBufferD3D) = 0;
	((BfmeComUnknown *&)shadowVertexBufferD3D) = 0;
	if (owner)
	{
		owner->releaseReferences();
		afterRelease();
	}
}

// ?afterRelease@GenAlpha@@QAEXXZ
void GenAlpha::afterRelease()
{
	for (GenAlphaChunk *c = m_first; c; c = c->m_next) {
		float *z = &c->m_vectors[0].z;
		for (int i = 0; i < 0xa0; ++i) {
			z[-2] = 0.0f;
			z[-1] = 0.0f;
			z[0] = 0.0f;
			z += 3;
		}
	}
}
