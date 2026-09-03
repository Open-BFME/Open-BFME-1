// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail 0x00719FB0 (151 bytes). BFME W3DShroud resource reacquisition.

typedef unsigned char Bool;

struct IDirect3DBaseTexture8;

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

class W3DShroud
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

Bool W3DShroud::ReAcquireResources(void)
{
	if (!m_dstTextureWidth)
		return 1;

	W3DRadarResetLock();

	reinterpret_cast<Rva006D6050 *>(&m_dstTexture)->init(
		m_dstTextureWidth, m_dstTextureHeight, 0x1a, 1, 1, 0);
	if (!reinterpret_cast<TextureBaseClass *>(&m_dstTexture)->Peek_D3D_Base_Texture())
	{
		if (m_dstTexture.m_p)
		{
			m_dstTexture.m_p->Release_Ref();
			m_dstTexture.m_p = 0;
		}
		m_dstTextureWidth = 0;
		m_dstTextureHeight = 0;
		return 0;
	}

	m_dstTexture.getFilter()->m_uAddress = 1;
	m_dstTexture.getFilter()->m_vAddress = 1;
	reinterpret_cast<Gen_00920a60 *>(m_dstTexture.getFilter())->m(0);
	m_clearDstTexture = 1;
	W3DRadarResetUnlock();
	return 1;
}
