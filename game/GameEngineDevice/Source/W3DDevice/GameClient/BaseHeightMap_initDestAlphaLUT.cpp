// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class SurfaceClass
{
public:
	void *m_surface;

	void *Lock(int *pitch, bool discard);
	void Unlock(void);
};

class W3DRadarResetSurface
{
public:
	~W3DRadarResetSurface();

	void *m_surface;
};

class W3DRadarResetTexture
{
public:
	void *m_texture;

	W3DRadarResetSurface getSurfaceLevel(void);
};

class ShroudFilter
{
public:
	unsigned char m_pad[0xc];
	int m_uAddress;
	int m_vAddress;
};

class ShroudTexture
{
public:
	ShroudFilter *getFilter(void);
};

extern float g_bfmeScaleB3;
extern void W3DRadarResetLock(void);
extern char bfmeUnlock1179(void);

class BaseHeightMapRenderObjClass
{
	protected:
	void initDestAlphaLUT(void);

private:
	unsigned char m_pad301c[0x301c];
	volatile float m_minWaterOpacity;
	unsigned char m_pad3020To3090[0x3090 - 0x3020];
	W3DRadarResetTexture m_destAlphaTexture;
	unsigned char m_pad3094To30cc[0x30cc - 0x3094];
	float m_currentMinWaterOpacity;
};

// ?initDestAlphaLUT@BaseHeightMapRenderObjClass@@IAEXXZ
void BaseHeightMapRenderObjClass::initDestAlphaLUT(void)
{
	if (!m_destAlphaTexture.m_texture)
		return;

	W3DRadarResetLock();
	{
		W3DRadarResetSurface surface = m_destAlphaTexture.getSurfaceLevel();
		if (surface.m_surface)
		{
			int pitch;
			unsigned int *data = (unsigned int *)((SurfaceClass *)&surface)->Lock(&pitch, false);
			int maxOpacity = (int)(m_minWaterOpacity * g_bfmeScaleB3);
			if (data)
			{
				for (int x = 0; x < 256; ++x)
				{
					int alpha = x;
					if (alpha > maxOpacity)
						alpha = maxOpacity;
					*data = (alpha << 24) | 0x00ffffff;
					++data;
				}
				((SurfaceClass *)&surface)->Unlock();
			}

			ShroudTexture *texture = (ShroudTexture *)&m_destAlphaTexture;
			texture->getFilter()->m_uAddress = 1;
			texture->getFilter()->m_vAddress = 1;
			m_currentMinWaterOpacity = m_minWaterOpacity;
		}
	}

	bfmeUnlock1179();
}
