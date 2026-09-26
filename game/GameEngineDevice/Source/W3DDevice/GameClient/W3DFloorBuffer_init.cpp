// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// W3DFloorBuffer::init, retail 0x006F7400; the constructor is at 0x006F92D0.

typedef unsigned char Bool;

struct IDirect3DBaseTexture8;

class DX8VertexBufferClass
{
public:
	 enum UsageType { USAGE_DEFAULT = 0, USAGE_DYNAMIC = 1 };

	DX8VertexBufferClass(unsigned fvf, unsigned short count, UsageType usage,
		unsigned vertexSize);

private:
	char m_body[0x20];
};

class DX8IndexBufferClass
{
public:
	 enum UsageType { USAGE_DEFAULT = 0, USAGE_DYNAMIC = 1 };

	DX8IndexBufferClass(unsigned short count, UsageType usage);

private:
	char m_body[0x18];
};

class VertexMaterialClass
{
public:
	enum PresetType { PRESET_DEFAULT = 0 };
	static VertexMaterialClass *Get_Preset(PresetType preset);
};

class Rva006D6050
{
public:
	void init(int, int, int, int, int, int);
	void *m_p;
};

class TextureBaseClass
{
public:
	IDirect3DBaseTexture8 *Peek_D3D_Base_Texture(void) const;
};

class SurfaceResource
{
public:
	virtual void slot00(void);
	virtual void slot04(void);
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

class BfmeMsgIBD
{
public:
	virtual BfmeMsgIBD *slot00(const void *value);
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
	virtual BfmeMsgIBD *slot38(const void *value);
	virtual void slot3c(void);
	virtual void slot40(void);
	virtual void slot44(void);
	virtual void slot48(void);
	virtual void slot4c(int value);
};

class BfmeLogIBD
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
	virtual void slot48(void);
	virtual void slot4c(void);
	virtual void slot50(void);
	virtual void slot54(void);
	virtual void slot58(void);
	virtual void slot5c(void);
	virtual void slot60(void);
	virtual void slot64(void);
	virtual void slot68(void);
	virtual BfmeMsgIBD *slot6c(int first, int second);
};

extern BfmeLogIBD *g_BFMEIndexBufferDebug;
extern void _bfme_debugRecordCallsite(int kind);
extern void W3DRadarResetLock(void);
extern void W3DRadarResetUnlock(void);
extern void j_000315f2(void);
extern void Rva008FCE00SurfaceOperation(void);

static __forceinline void BFME_DX8_ErrorCode(int result)
{
	if (result != 0)
	{
		_bfme_debugRecordCallsite(1);
		g_BFMEIndexBufferDebug->slot60();
		g_BFMEIndexBufferDebug->slot6c(0, 0)->slot38((const void *)0x111d770)
			->slot00((const void *)result)->slot4c(1);
	}
}

class Rva006F92D0ResetGuard
{
public:
	Rva006F92D0ResetGuard(void) { W3DRadarResetLock(); }
	~Rva006F92D0ResetGuard(void) { W3DRadarResetUnlock(); }
};

class W3DFloorBuffer
{
public:
	void init(void);

private:
	void *m_vftable;
	DX8VertexBufferClass *m_04;
	DX8IndexBufferClass *m_08;
	VertexMaterialClass *m_0c;
	Rva006D6050 m_10;
	void *m_14;
	void *m_18;
	Rva006D6050 m_1c;
	void *m_20;
	void *m_24;
	Bool m_28;
	Bool m_29;
	Bool m_2a;
};

void W3DFloorBuffer::init(void)
{
	Rva006F92D0ResetGuard lock;

	if (m_04 || m_08)
	{
		typedef void (W3DFloorBuffer::*Cleanup)(void);
		union { void *asVoid; Cleanup asMember; } cleanup;
		cleanup.asVoid = reinterpret_cast<void *>(j_000315f2);
		(this->*cleanup.asMember)();
	}

	m_04 = new DX8VertexBufferClass(0x152, 0x3a9c,
		DX8VertexBufferClass::USAGE_DYNAMIC, 0);
	m_08 = new DX8IndexBufferClass(0x7534, DX8IndexBufferClass::USAGE_DYNAMIC);
	m_0c = VertexMaterialClass::Get_Preset((VertexMaterialClass::PresetType)0);
	m_14 = 0;
	m_18 = 0;
	reinterpret_cast<Rva006D6050 *>(&m_1c)->init(1, 1, 0x15, 1, 1, 0);

	TextureBaseClass *texture = reinterpret_cast<TextureBaseClass *>(&m_1c);
	if (texture->Peek_D3D_Base_Texture())
	{
		SurfaceResource *surface = 0;
		BfmeD3DTexture *d3dTexture =
			reinterpret_cast<BfmeD3DTexture *>(texture->Peek_D3D_Base_Texture());
		int result = d3dTexture->GetSurfaceLevel(0, &surface);
		BFME_DX8_ErrorCode(result);

		struct SurfaceOperationThunk { void Call(int, int, int); };
		typedef void (SurfaceOperationThunk::*SurfaceOperation)(int, int, int);
		union { void *asVoid; SurfaceOperation asMember; } operation;
		operation.asVoid = reinterpret_cast<void *>(Rva008FCE00SurfaceOperation);
		(reinterpret_cast<SurfaceOperationThunk *>(static_cast<W3DRadarResetSurface *>(W3DRadarResetSurface(surface)))->*operation.asMember)(0, 0, -1);
		surface->Release();
	}

	m_2a = 1;
}
