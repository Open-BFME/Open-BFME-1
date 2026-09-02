// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x007D2390: filter init that loads shaders\monochromezoom.nvp and
// circleFade.tga.  Same device-global / chipset ladder as ScreenBWFilter::init
// plus a texture-handle member at this+8.

class BFMEWaterTrackTexture
{
public:
	void Release_Ref();
};

class BFMEWaterTrackTextureHandle
{
public:
	BFMEWaterTrackTexture *m_texture;
	~BFMEWaterTrackTextureHandle()
	{
		if (m_texture)
			m_texture->Release_Ref();
	}
};

BFMEWaterTrackTextureHandle BFMEGetWaterTrackTexture(char *name, int mipCount, int format);

class TextureHolder
{
public:
	void bind(const BFMEWaterTrackTextureHandle &h);
};

extern int *g_bfmeA986B;
extern int *g_bfmeB986B;
extern int g_bfmeZero986B;
extern char *g_bfmePtr986B;
extern char g_bfmeTarget986B[];

int bfmeCheck986B(void);

class BfmeShaderLoader16
{
public:
	static int LoadAndCreateD3DShader(const char *filename, unsigned int *shader);
};

class ScreenZoomFilter
{
public:
	virtual int init();

private:
	unsigned int m_shader;
	TextureHolder m_tex;
};

int ScreenZoomFilter::init()
{
	int res;
	int hr;

	m_shader = 0;
	g_bfmeZero986B = 0;

	if (g_bfmeA986B != 0 && g_bfmeB986B != 0)
	{
		if ((res = bfmeCheck986B()) != 0)
		{
			if (res >= 3)
			{
				hr = BfmeShaderLoader16::LoadAndCreateD3DShader("shaders\\monochromezoom.nvp", &m_shader);
				if (hr < 0)
					return 0;
				g_bfmePtr986B = g_bfmeTarget986B;
				m_tex.bind(BFMEGetWaterTrackTexture("circleFade.tga", 0, 0));
				return 1;
			}
		}
	}
	return 0;
}
