// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail 0x00726DC0: reacquire the taint overlay render texture.
//
// TaintBuffer is a descriptive name, not a recovered EA one.  What the exe
// proves is the subject: the GlobalData FieldParse table at 0x00C77018 maps the
// INI keys TaintOn to +0xCF5, TaintAlpha to +0xCA0 and TaintColor to +0xC88
// (reverse/field_names.csv), every body in this family gates on TheWritableGlobalData
// ->m_taintOn, TaintBuffer::init drives TheTaintManager -- the literal at 0x79060 --
// and the shaders it feeds are shaders\terraintaint.pso and terraintaint2.pso.
// The object itself is the render-side cell buffer for that overlay: a cell grid
// sized from WorldHeightMap, a destination texture it reacquires, and a dirty-cell
// set, which is the same shape W3DShroud has for the shroud.  No __FILE__ literal
// reaches this code run, so the retail class name is still unknown.

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

class TaintBuffer
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

Bool TaintBuffer::ReAcquireResources(void)
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
