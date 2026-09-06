// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Near-twin of ?allocateTreeBuffers@W3DTreeBuffer@@QAEXXZ (0x00732B00,
// W3DTreeBufferBfmeAllocate.cpp): byte-identical body except (1) the free
// path installs the retail thunk at 0x0000A2C2 (?j_0000a2c2, thunks_004.cpp)
// instead of 0x00732960, (2) the vertex/index buffer ctors are called with
// usage=USAGE_DEFAULT(0) here vs USAGE_DYNAMIC(1) in the twin ("push ebx"
// where the twin has "push 1", twice), and (3) the tree-texture/count fields
// sit at this+0x1E3914/+0x1E3918 -- the same real W3DTreeBuffer offsets used
// by the landed freeTreeBuffers (0x0071C2D0,
// Gen_0071C2D0_W3DTreeBuffer_FreeTreeBuffers.cpp) -- instead of the other
// twin's placeholder 0x2A9904/+0x2A9908, so this is believed to be the real
// retail W3DTreeBuffer::allocateTreeBuffers and the other landed body a
// second, differently-padded compile of the same source (base Generals vs
// Zero Hour tree code, or a debug/release split).
//
// String-ref verify caught a real content difference: the darken/lighten
// vertex shader filenames here are "shaders\Shrubs_darken.vs" and
// "shaders\Shrubs_lighten.vs", not the twin's "Trees_darken.vso"/
// "Trees_lighten.vso" -- so this instance is a sibling vegetation buffer
// class (shrubs, not trees) that shares the tree code verbatim including
// its "Trees.vso"/"Trees.pso" base shader names; class kept as
// W3DTreeBuffer here only because the real sibling class name/header are
// unknown, per address-derived identity policy.

typedef int Int;

struct IDirect3DBaseTexture8;

struct BfmeVertexElement
{
	unsigned short stream;
	unsigned short offset;
	unsigned char type;
	unsigned char method;
	unsigned char usage;
	unsigned char usageIndex;
};

class BfmeDX8VertexBuffer
{
public:
	enum UsageType { USAGE_DEFAULT = 0, USAGE_DYNAMIC = 1 };

	BfmeDX8VertexBuffer(unsigned fvf, unsigned short count, UsageType usage, unsigned size);

private:
	unsigned char m_bfmeBody[0x20];
};

class BfmeDX8IndexBuffer
{
public:
	enum UsageType { USAGE_DEFAULT = 0, USAGE_DYNAMIC = 1 };

	BfmeDX8IndexBuffer(unsigned short count, UsageType usage);

private:
	unsigned char m_bfmeBody[0x18];
};

class BfmeShaderResource
{
public:
	virtual long __stdcall slot0(void);
	virtual long __stdcall slot4(void);
	virtual long __stdcall Release_Ref(void);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/texture.h
class TextureBaseClass
{
public:
	IDirect3DBaseTexture8 *Peek_D3D_Base_Texture(void) const;
};

class Rva006D6050
{
public:
	void init(int width, int height, int format, int mipLevels, int pool, int renderTarget);
};

struct BfmeTreeTexture
{
	TextureBaseClass *m_p;
};

class SurfaceResource
{
public:
	virtual void slot0(void);
	virtual void slot4(void);
	virtual void __stdcall Release(void);
};

class BfmeD3DTexture
{
public:
	virtual void slot00(void);
	virtual void slot04(void);
	virtual void slot08(void);
	virtual void slot0c(void);
	virtual void slot10(void);
	virtual void slot14(void);
	virtual void slot18(void);
	virtual void slot1c(void);
	virtual void slot20(void);
	virtual void slot24(void);
	virtual void slot28(void);
	virtual void slot2c(void);
	virtual void slot30(void);
	virtual void slot34(void);
	virtual void slot38(void);
	virtual void slot3c(void);
	virtual void slot40(void);
	virtual void slot44(void);
	virtual int __stdcall GetSurfaceLevel(unsigned level, SurfaceResource **surface);
};

class W3DRadarResetSurface
{
public:
	W3DRadarResetSurface(SurfaceResource *surface);
	~W3DRadarResetSurface(void);
	operator W3DRadarResetSurface *(void) { return this; }

private:
	SurfaceResource *m_surface;
};

extern void Rva008FCE00SurfaceOperation(void);
extern void j_0000a2c2(void);

class BFMEIndexBufferDebugStream
{
public:
	virtual BFMEIndexBufferDebugStream *Put_Unsigned(unsigned value);
	virtual void Slot04(void);
	virtual void Slot08(void);
	virtual void Slot0C(void);
	virtual void Slot10(void);
	virtual void Slot14(void);
	virtual void Slot18(void);
	virtual void Slot1C(void);
	virtual void Slot20(void);
	virtual void Slot24(void);
	virtual void Slot28(void);
	virtual void Slot2C(void);
	virtual void Slot30(void);
	virtual void Slot34(void);
	virtual BFMEIndexBufferDebugStream *Put_String(const char *text);
	virtual void Slot3C(void);
	virtual void Slot40(void);
	virtual void Slot44(void);
	virtual void Slot48(void);
	virtual BFMEIndexBufferDebugStream *Finish(int report);
};

class BFMEIndexBufferDebugClass
{
public:
	virtual void Slot00(void); virtual void Slot04(void); virtual void Slot08(void); virtual void Slot0C(void);
	virtual void Slot10(void); virtual void Slot14(void); virtual void Slot18(void); virtual void Slot1C(void);
	virtual void Slot20(void); virtual void Slot24(void); virtual void Slot28(void); virtual void Slot2C(void);
	virtual void Slot30(void); virtual void Slot34(void); virtual void Slot38(void); virtual void Slot3C(void);
	virtual void Slot40(void); virtual void Slot44(void); virtual void Slot48(void); virtual void Slot4C(void);
	virtual void Slot50(void); virtual void Slot54(void); virtual void Slot58(void); virtual void Slot5C(void);
	virtual void Begin_Report(void);
	virtual void Slot64(void); virtual void Slot68(void);
	virtual BFMEIndexBufferDebugStream *Get_Stream(void *owner, void *context);
};

class BfmeD3DDevice
{
public:
	virtual void slot00(void); virtual void slot04(void); virtual void slot08(void); virtual void slot0c(void);
	virtual void slot10(void); virtual void slot14(void); virtual void slot18(void); virtual void slot1c(void);
	virtual void slot20(void); virtual void slot24(void); virtual void slot28(void); virtual void slot2c(void);
	virtual void slot30(void); virtual void slot34(void); virtual void slot38(void); virtual void slot3c(void);
	virtual void slot40(void); virtual void slot44(void); virtual void slot48(void); virtual void slot4c(void);
	virtual void slot50(void); virtual void slot54(void); virtual void slot58(void); virtual void slot5c(void);
	virtual void slot60(void); virtual void slot64(void); virtual void slot68(void); virtual void slot6c(void);
	virtual void slot70(void); virtual void slot74(void); virtual void slot78(void); virtual void slot7c(void);
	virtual void slot80(void); virtual void slot84(void); virtual void slot88(void); virtual void slot8c(void);
	virtual void slot90(void); virtual void slot94(void); virtual void slot98(void); virtual void slot9c(void);
	virtual void slota0(void); virtual void slota4(void); virtual void slota8(void); virtual void slotac(void);
	virtual void slotb0(void); virtual void slotb4(void); virtual void slotb8(void); virtual void slotbc(void);
	virtual void slotc0(void); virtual void slotc4(void); virtual void slotc8(void); virtual void slotcc(void);
	virtual void slotd0(void); virtual void slotd4(void); virtual void slotd8(void); virtual void slotdc(void);
	virtual void slote0(void); virtual void slote4(void); virtual void slote8(void); virtual void slotec(void);
	virtual void slotf0(void); virtual void slotf4(void); virtual void slotf8(void); virtual void slotfc(void);
	virtual void slot100(void); virtual void slot104(void); virtual void slot108(void); virtual void slot10c(void);
	virtual void slot110(void); virtual void slot114(void); virtual void slot118(void); virtual void slot11c(void);
	virtual void slot120(void); virtual void slot124(void); virtual void slot128(void); virtual void slot12c(void);
	virtual void slot130(void); virtual void slot134(void); virtual void slot138(void); virtual void slot13c(void);
	virtual void slot140(void); virtual void slot144(void); virtual void slot148(void); virtual void slot14c(void);
	virtual void slot150(void); virtual void slot154(void);
	virtual int __stdcall CreateVertexShader(const BfmeVertexElement *declaration, BfmeShaderResource **shader);
};

extern BfmeD3DDevice *g_BfmeD3DDevice;
extern BFMEIndexBufferDebugClass *g_BFMEIndexBufferDebug;
extern void _bfme_debugRecordCallsite(int kind);
extern void W3DRadarResetLock(void);
extern void W3DRadarResetUnlock(void);
extern int bfmeCheck986B(void);

class BfmeShaderLoader
{
public:
	static long LoadAndCreateD3DShader(const char *filename, unsigned long *shader);
};

class BfmeVertexShaderLoader
{
public:
	static long LoadAndCreateD3DShader(const char *filename, unsigned long *shader);
};

static __forceinline void BFME_DX8_ErrorCode(unsigned result)
{
	if (result != 0) {
		_bfme_debugRecordCallsite(1);
		g_BFMEIndexBufferDebug->Begin_Report();
		BFMEIndexBufferDebugStream *stream = g_BFMEIndexBufferDebug->Get_Stream(0, 0);
		stream->Put_String("DX8 error ")->Put_Unsigned(result)->Finish(1);
	}
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DTreeBuffer.h
class W3DTreeBuffer
{
public:
	void allocateTreeBuffersRva0071C470(void);
	void freeTreeBuffers(void);

private:
	char m_pad00[4];
	BfmeDX8VertexBuffer *m_vertexTree[20];
	BfmeDX8IndexBuffer *m_indexTree[20];
	BfmeShaderResource *m_resource0;
	BfmeShaderResource *m_resource1;
	BfmeShaderResource *m_resource2;
	BfmeShaderResource *m_resource3;
	BfmeShaderResource *m_resource4;
	char m_padB8[0x14a8 - 0xb8];
	Int m_curNumTreeVertices[20];
	Int m_curNumTreeIndices[20];
	char m_pad1548[0x1e3914 - 0x1548];
	BfmeTreeTexture m_treeTexture;
	Int m_numBuffers;
};

struct BfmeTreeBufferFreeThunk { void Call(void); };
typedef void (BfmeTreeBufferFreeThunk::*BfmeTreeBufferFreeOperation)(void);

class BfmeRadarResetGuard
{
public:
	BfmeRadarResetGuard(void) { W3DRadarResetLock(); }
	~BfmeRadarResetGuard(void) { W3DRadarResetUnlock(); }
};

void W3DTreeBuffer::allocateTreeBuffersRva0071C470(void)
{
	union { void *asVoid; BfmeTreeBufferFreeOperation asMember; } freeCast;
	freeCast.asVoid = reinterpret_cast<void *>(j_0000a2c2);
	(reinterpret_cast<BfmeTreeBufferFreeThunk *>(this)->*freeCast.asMember)();
	BfmeRadarResetGuard lock;

	Int i;
	Int zero = 0;
	for (i = 0; i < m_numBuffers; ++i) {
		m_vertexTree[i] = new BfmeDX8VertexBuffer(0x152, 0x7534, BfmeDX8VertexBuffer::USAGE_DEFAULT, 0);
		m_indexTree[i] = new BfmeDX8IndexBuffer(0xea64, BfmeDX8IndexBuffer::USAGE_DEFAULT);
		m_curNumTreeVertices[i] = 0;
		m_curNumTreeIndices[i] = 0;
	}

	reinterpret_cast<Rva006D6050 *>(&m_treeTexture)->init(1, 1, 0x15, 1, 1, 0);
	TextureBaseClass *treeTexture = reinterpret_cast<TextureBaseClass *>(&m_treeTexture);
	if (treeTexture->Peek_D3D_Base_Texture()) {
		SurfaceResource *surface = 0;
		BfmeD3DTexture *texture = reinterpret_cast<BfmeD3DTexture *>(treeTexture->Peek_D3D_Base_Texture());
		int result = texture->GetSurfaceLevel(0, &surface);
		BFME_DX8_ErrorCode(result);
		struct BfmeSurfaceOperationThunk { void Call(int, int, int); };
		typedef void (BfmeSurfaceOperationThunk::*BfmeSurfaceOperation)(int, int, int);
		union { void *asVoid; BfmeSurfaceOperation asMember; } operationCast;
		operationCast.asVoid = reinterpret_cast<void *>(Rva008FCE00SurfaceOperation);
		(reinterpret_cast<BfmeSurfaceOperationThunk *>(static_cast<W3DRadarResetSurface *>(W3DRadarResetSurface(surface)))->*operationCast.asMember)(0, 0, -1);
		surface->Release();
	}

	if (bfmeCheck986B() < 3)
		return;

	BfmeVertexElement declaration[] = {
		{ 0, 0, 2, 0, 0, 0 },
		{ 0, 0x0c, 2, 0, 3, 0 },
		{ 0, 0x18, 4, 0, 10, 0 },
		{ 0, 0x1c, 1, 0, 5, 0 },
		{ 0xff, 0, 0x11, 0, 0, 0 }
	};

	if (!m_resource4) {
		Int result = g_BfmeD3DDevice->CreateVertexShader(declaration, &m_resource4);
		if (result < zero)
			return;
	}
	{
		Int result = BfmeVertexShaderLoader::LoadAndCreateD3DShader("shaders\\Trees.vso", reinterpret_cast<unsigned long *>(&m_resource1));
		if (result < zero)
			return;
	}
	{
		Int result = BfmeShaderLoader::LoadAndCreateD3DShader("shaders\\Trees.pso", reinterpret_cast<unsigned long *>(&m_resource0));
		if (result < zero)
			return;
	}
	{
		Int result = BfmeVertexShaderLoader::LoadAndCreateD3DShader("shaders\\Shrubs_darken.vs", reinterpret_cast<unsigned long *>(&m_resource2));
		if (result < zero)
			return;
	}
	{
		Int result = BfmeVertexShaderLoader::LoadAndCreateD3DShader("shaders\\Shrubs_lighten.vs", reinterpret_cast<unsigned long *>(&m_resource3));
		if (result < zero)
			return;
	}
}
