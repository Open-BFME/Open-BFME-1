// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Retail 0x00723FB0.  The 16-byte caller at 0x00725600 first invokes the
// matched SnowManager::init body and then tail-jumps here.  The anonymous
// class name is intentional: this is the address-derived callee pin already
// used by that tail-pair family.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	const Overridable *getFinalOverride(void) const;

	void *m_vtable;
	const Overridable *m_nextOverride;
};

class BfmeSnowOverride : public Overridable
{
public:
	unsigned char m_pad08[4];
	const char *m_snowTextureData;
	unsigned char m_pad10[0x38 - 0x10];
	unsigned char m_usePointSprites;
	unsigned char m_snowEnabled;

	const char *snowTextureName(void) const
	{
		return m_snowTextureData ? m_snowTextureData + 8 :
			(const char *)0x0107388B;
	}
};

extern BfmeSnowOverride *g_bfmeGlo012F15F8;

void W3DRadarResetLock(void);
void W3DRadarResetUnlock(void);
void __cdecl j_000491c5(void);

static const BfmeSnowOverride *walkSnowOverride(const BfmeSnowOverride *d)
{
	if (d == 0)
		return 0;
	if (d->m_nextOverride)
		return (const BfmeSnowOverride *)
			((const Overridable *)d->m_nextOverride)->getFinalOverride();
	return d;
}

class BfmeRadarResetLock
{
public:
	BfmeRadarResetLock(void) { W3DRadarResetLock(); }
	~BfmeRadarResetLock(void) { W3DRadarResetUnlock(); }
};

class BFMEDeviceCaps
{
	unsigned char m_pad[0x273];

public:
	unsigned char m_supportPointSprites;
};

extern BFMEDeviceCaps *g_bfmeCaps1340578;

class BFMEDevice
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
	virtual int __stdcall CreateVertexBuffer(unsigned length, unsigned usage,
		unsigned fvf, unsigned pool, void **vertexBuffer, void *sharedHandle);
};

extern BFMEDevice *g_bfmeDevice1340534;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/texture.h
class TextureClass
{
public:
	void Release_Ref(void);
};

class BFMEWaterTrackTexture
{
public:
	void Release_Ref(void);
};

class BFMEWaterTrackTextureHandle
{
public:
	TextureClass *m_texture;

	~BFMEWaterTrackTextureHandle(void)
	{
		if (m_texture)
			((BFMEWaterTrackTexture *)m_texture)->Release_Ref();
	}
};

extern BFMEWaterTrackTextureHandle BFMEGetWaterTrackTexture(
	char *name, int mipCount, int format);

static inline void BFMEAssignSnowTexture(
	TextureClass *&destination, const BFMEWaterTrackTextureHandle &texture)
{
	if (texture.m_texture)
		++*(unsigned short *)((char *)texture.m_texture + 4);
	if (destination)
		((BFMEWaterTrackTexture *)destination)->Release_Ref();
	destination = texture.m_texture;
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8indexbuffer.h
class IndexBufferClass
{
public:
	class WriteLockClass
	{
		IndexBufferClass *indexBuffer;
		unsigned short *indices;

	public:
		WriteLockClass(IndexBufferClass *indexBuffer, int flags = 0);
		~WriteLockClass(void);

		unsigned short *Get_Index_Array(void) { return indices; }
	};
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8indexbuffer.h
class DX8IndexBufferClass
{
	unsigned char m_body[0x18];

public:
	enum UsageType
	{
		USAGE_DEFAULT = 0
	};

	DX8IndexBufferClass(unsigned short indexCount,
		UsageType usage = USAGE_DEFAULT);
};

class Gen0045A970_00723FB0
{
	unsigned char m_pad00[0x3d];
	unsigned char m_visible;
	unsigned char m_pad3e[0x68 - 0x3e];
	DX8IndexBufferClass *m_indexBuffer;
	TextureClass *m_snowTexture;
	void *m_vertexBufferD3D;
	int m_dwBase;
	int m_dwFlush;
	int m_dwDiscard;

public:
	void releaseResources(void);
	bool gen00723FB0(void);
};

#pragma comment(linker, "/alternatename:?releaseResources@Gen0045A970_00723FB0@@QAEXXZ=?j_000491c5@@YAXXZ")

bool Gen0045A970_00723FB0::gen00723FB0(void)
{
	BfmeRadarResetLock lock;
	releaseResources();

	register const BfmeSnowOverride *base = g_bfmeGlo012F15F8;
	register const BfmeSnowOverride *setting = walkSnowOverride(base);
	if (setting->m_snowEnabled == 0 || m_visible == 0)
		return true;

	setting = walkSnowOverride(base);
	register const BfmeSnowOverride *d = base;
	if (setting->m_usePointSprites != 0 &&
		g_bfmeCaps1340578->m_supportPointSprites != 0)
	{
		BFMEDevice *device = g_bfmeDevice1340534;
		if (m_vertexBufferD3D == 0)
		{
			if (device->CreateVertexBuffer(
				0x10000, 0x248, 0x42, 0, &m_vertexBufferD3D, 0) < 0)
				return false;
			d = g_bfmeGlo012F15F8;
		}
	}
	else
	{
		m_indexBuffer = new DX8IndexBufferClass(
			0x3000, DX8IndexBufferClass::USAGE_DEFAULT);

		{
			IndexBufferClass::WriteLockClass lockIndex(
				(IndexBufferClass *)m_indexBuffer, 0);
			unsigned short *ib = lockIndex.Get_Index_Array();
			int vbCount = 0;
			for (int i = 0; i < 0x800; ++i)
			{
				ib[0] = (unsigned short)(vbCount + 3);
				ib[1] = (unsigned short)vbCount;
				ib[2] = (unsigned short)(vbCount + 2);
				ib[3] = (unsigned short)(vbCount + 2);
				ib[4] = (unsigned short)vbCount;
				ib[5] = (unsigned short)(vbCount + 1);
				vbCount += 4;
				ib += 6;
			}
		}
		d = g_bfmeGlo012F15F8;
	}

	register const BfmeSnowOverride *f = walkSnowOverride(d);
	BFMEAssignSnowTexture(
		m_snowTexture,
		BFMEGetWaterTrackTexture((char *)f->snowTextureName(), 0, 0));
	m_dwBase = 0x1000;
	m_dwDiscard = 0x1000;
	m_dwFlush = 0x800;
	return true;
}
