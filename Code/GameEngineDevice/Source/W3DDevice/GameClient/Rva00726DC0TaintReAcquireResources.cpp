// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail 0x00726DC0: reacquire the taint overlay render texture.

typedef unsigned char Bool;

struct IDirect3DBaseTexture8;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
class GlobalData
{
public:
	char m_pad00[0xcf5];
	unsigned char m_taintOn;
};

extern GlobalData *TheWritableGlobalData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/texture.h
class TextureBaseClass
{
public:
	void Release_Ref();
	IDirect3DBaseTexture8 *Peek_D3D_Base_Texture() const;
};

class ShroudFilter
{
public:
	char m_pad00[0x0c];
	int m_uAddress;
	int m_vAddress;
	void setMipMapping(int mode);
};

class ShroudTexture
{
public:
	ShroudFilter *getFilter();

	TextureBaseClass *m_p;
};

class Rva006D6050
{
public:
	void init(int width, int height, int format, int mipLevels, int pool, int renderTarget);
};

class Gen_00920a60
{
public:
	void m(int value);
};

void W3DRadarResetLock(void);
void W3DRadarResetUnlock(void);

class Rva00726DC0TaintBuf
{
public:
	Bool ReAcquireResources(void);

private:
	char m_pad00[0x1c];
	ShroudTexture m_dstTexture;
	int m_dstTextureWidth;
	int m_dstTextureHeight;
	char m_pad2c[13];
	unsigned char m_clearDstTexture;
};

Bool Rva00726DC0TaintBuf::ReAcquireResources(void)
{
	if (!m_dstTextureWidth)
		return 1;

	W3DRadarResetLock();

	if (TheWritableGlobalData && TheWritableGlobalData->m_taintOn)
	{
		reinterpret_cast<Rva006D6050 *>(&m_dstTexture)->init(
			m_dstTextureWidth, m_dstTextureHeight, 0x15, 1, 1, 0);
	}

	ShroudTexture *dstTexture = &m_dstTexture;
	TextureBaseClass *texture = reinterpret_cast<TextureBaseClass *>(dstTexture);
	if (!texture->Peek_D3D_Base_Texture())
	{
		if (dstTexture->m_p)
		{
			dstTexture->m_p->Release_Ref();
			dstTexture->m_p = 0;
		}
		m_dstTextureWidth = 0;
		m_dstTextureHeight = 0;
		return 0;
	}

	dstTexture->getFilter()->m_uAddress = 1;
	dstTexture->getFilter()->m_vAddress = 1;
	reinterpret_cast<Gen_00920a60 *>(dstTexture->getFilter())->m(0);
	m_clearDstTexture = 1;
	W3DRadarResetUnlock();
	return 1;
}
