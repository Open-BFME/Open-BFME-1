// cl: /DNDEBUG /MD /EHsc
// Retail 0x007D3760: ScreenCrossFadeFilter::init, vtable 0x01128A50 slot 0.
// The constructor at 0x007D3740 installs that table; its slot 2 is the
// matched CrossFade preRender at 0x007D36B0 and slot 0 reaches this body
// through ILT 0x00044BCF.  BFME's texture loader returns a four-byte,
// reference-counted handle rather than the Zero Hour TextureClass pointer.

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

class Gen_00920a60
{
public:
	void m(int value);
};

class ShroudFilter : public Gen_00920a60
{
public:
	char m_padding00[0x0c];
	int m_uAddress;
	int m_vAddress;
};

class ShroudTexture
{
public:
	TextureClass *m_texture;
	ShroudFilter *getFilter(void);
	__forceinline void bind(const BFMEWaterTrackTextureHandle &texture)
	{
		if (texture.m_texture)
			++*(unsigned short *)((char *)texture.m_texture + 4);
		if (m_texture)
			((BFMEWaterTrackTexture *)m_texture)->Release_Ref();
		m_texture = texture.m_texture;
	}
};

extern void *TheDisplay;
extern int g_bfmeGateBT;
extern volatile int g_bfmeProbeBT;
extern ShroudTexture g_bfmeCurrentCZ;

class ScreenCrossFadeFilterUpdateFadeLevelShim
{
public:
	static int m_curFadeFrame;
};

class W3DFilterInterface
{
public:
	virtual int init(void);
};

class ScreenCrossFadeFilter : public W3DFilterInterface
{
public:
	int init(void);
};

extern W3DFilterInterface *W3DFilters[];
extern ScreenCrossFadeFilter screenCrossFadeFilter;

// ?init@ScreenCrossFadeFilter@@UAEHXZ
int ScreenCrossFadeFilter::init(void)
{
	if (!TheDisplay)
		return 0;

	ScreenCrossFadeFilterUpdateFadeLevelShim::m_curFadeFrame = 0;

	if (!g_bfmeGateBT)
		return 0;
	if (!g_bfmeProbeBT)
		return 0;

	g_bfmeCurrentCZ.bind(
		BFMEGetWaterTrackTexture((char *)"exmask_g.tga", 0, 0));

	if (!g_bfmeCurrentCZ.m_texture)
		return 0;

	int result = 1;
	g_bfmeCurrentCZ.getFilter()->m_uAddress = result;
	g_bfmeCurrentCZ.getFilter()->m_vAddress = result;
	g_bfmeCurrentCZ.getFilter()->m(0);

	W3DFilters[4] = &screenCrossFadeFilter;
	return result;
}
