// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

typedef int Int;
typedef unsigned int UnsignedInt;
typedef char Char;
typedef float Real;

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
	Char *name, Int mipCount, Int format);

static inline void BFMEAssignWaterTrackTexture(
	TextureClass *&destination,
	const BFMEWaterTrackTextureHandle &texture)
{
	if (texture.m_texture)
		++*(unsigned short *)((char *)texture.m_texture + 4);
	if (destination)
		((BFMEWaterTrackTexture *)destination)->Release_Ref();
	destination = texture.m_texture;
}

class SurfaceClass
{
public:
	struct SurfaceDescription
	{
		UnsignedInt Format;
		UnsignedInt Width;
		UnsignedInt Height;
	};

	void Get_Description(SurfaceDescription &surfaceDesc);
};

class SurfaceResource
{
public:
	virtual void slot00(void);
	virtual unsigned long __stdcall addRef(void);
	virtual unsigned long __stdcall release(void);
};

class W3DRadarResetSurface : public SurfaceClass
{
public:
	W3DRadarResetSurface(void) : m_surface(0) {}
	W3DRadarResetSurface(SurfaceResource *surface);
	__forceinline W3DRadarResetSurface(const W3DRadarResetSurface &other) :
		m_surface(other.m_surface)
	{
		if (m_surface)
			m_surface->addRef();
	}
	~W3DRadarResetSurface(void);

private:
	SurfaceResource *m_surface;
};

class W3DRadarResetTexture
{
public:
	W3DRadarResetSurface getSurfaceLevel(void);

	TextureClass *m_texture;
};

class Rva007A2830Color
{
public:
	UnsignedInt red;
	UnsignedInt green;
	UnsignedInt blue;
	UnsignedInt alpha;
};

class AsciiString
{
public:
	Char *m_data;

	Char *str(void) const
	{
		if (m_data)
			return m_data + 8;
		return (Char *)0x0107388b;
	}
};

class Rva007A2830WaterSetting
{
public:
	virtual ~Rva007A2830WaterSetting(void);

	AsciiString m_skyTextureFile;
	AsciiString m_waterTextureFile;
	Int m_waterRepeatCount;
	Real m_skyTexelsPerUnit;
	Rva007A2830Color m_vertex00Diffuse;
	Rva007A2830Color m_vertex10Diffuse;
	Rva007A2830Color m_vertex11Diffuse;
	Rva007A2830Color m_vertex01Diffuse;
	Rva007A2830Color m_waterDiffuseColor;
	Rva007A2830Color m_transparentWaterDiffuse;
	Real m_uScrollPerMs;
	Real m_vScrollPerMs;
};

enum Rva007A2830TimeOfDay
{
	RVA007A2830_TIME_OF_DAY_MORNING = 0,
	RVA007A2830_TIME_OF_DAY_AFTERNOON,
	RVA007A2830_TIME_OF_DAY_EVENING,
	RVA007A2830_TIME_OF_DAY_NIGHT
};

class Rva007A2830WaterRenderObjClass
{
public:
	struct Setting
	{
		TextureClass *skyTexture;
		W3DRadarResetTexture waterTexture;
		Int waterRepeatCount;
		Real skyTexelsPerUnit;
		UnsignedInt vertex00Diffuse;
		UnsignedInt vertex10Diffuse;
		UnsignedInt vertex11Diffuse;
		UnsignedInt vertex01Diffuse;
		UnsignedInt waterDiffuse;
		UnsignedInt transparentWaterDiffuse;
		Real uScrollPerMs;
		Real vScrollPerMs;
	};

protected:
	void loadSetting(Setting *setting, Rva007A2830TimeOfDay timeOfDay);
};

// ?loadSetting@WaterRenderObjClass@@IAEXPAUSetting@1@W4TimeOfDay@@@Z
void Rva007A2830WaterRenderObjClass::loadSetting(
	Setting *setting, Rva007A2830TimeOfDay timeOfDay)
{
	const unsigned int waterOffset = (unsigned int)timeOfDay * 0x7c;

	BFMEAssignWaterTrackTexture(
		setting->skyTexture,
		BFMEGetWaterTrackTexture(
			(*(Rva007A2830WaterSetting *)((char *)0x012f1608 + waterOffset)).m_skyTextureFile.str(), 0, 0));
	BFMEAssignWaterTrackTexture(
		setting->waterTexture.m_texture,
		BFMEGetWaterTrackTexture(
			(*(Rva007A2830WaterSetting *)((char *)0x012f1608 + waterOffset)).m_waterTextureFile.str(), 0, 0));

	setting->skyTexelsPerUnit = (*(Rva007A2830WaterSetting *)((char *)0x012f1608 + waterOffset)).m_skyTexelsPerUnit;
	SurfaceClass::SurfaceDescription surfaceDesc;
	setting->waterTexture.getSurfaceLevel().Get_Description(surfaceDesc);
	setting->skyTexelsPerUnit /= (Real)surfaceDesc.Width;

	setting->waterRepeatCount = (*(Rva007A2830WaterSetting *)((char *)0x012f1608 + waterOffset)).m_waterRepeatCount;
	setting->uScrollPerMs = (*(Rva007A2830WaterSetting *)((char *)0x012f1608 + waterOffset)).m_uScrollPerMs;
	setting->vScrollPerMs = (*(Rva007A2830WaterSetting *)((char *)0x012f1608 + waterOffset)).m_vScrollPerMs;

	setting->vertex00Diffuse =
		((*(Rva007A2830WaterSetting *)((char *)0x012f1608 + waterOffset)).m_vertex00Diffuse.red << 16) |
		((*(Rva007A2830WaterSetting *)((char *)0x012f1608 + waterOffset)).m_vertex00Diffuse.green << 8) |
		(*(Rva007A2830WaterSetting *)((char *)0x012f1608 + waterOffset)).m_vertex00Diffuse.blue;
	setting->vertex01Diffuse =
		((*(Rva007A2830WaterSetting *)((char *)0x012f1608 + waterOffset)).m_vertex01Diffuse.red << 16) |
		((*(Rva007A2830WaterSetting *)((char *)0x012f1608 + waterOffset)).m_vertex01Diffuse.green << 8) |
		(*(Rva007A2830WaterSetting *)((char *)0x012f1608 + waterOffset)).m_vertex01Diffuse.blue;
	setting->vertex10Diffuse =
		((*(Rva007A2830WaterSetting *)((char *)0x012f1608 + waterOffset)).m_vertex10Diffuse.red << 16) |
		((*(Rva007A2830WaterSetting *)((char *)0x012f1608 + waterOffset)).m_vertex10Diffuse.green << 8) |
		(*(Rva007A2830WaterSetting *)((char *)0x012f1608 + waterOffset)).m_vertex10Diffuse.blue;
	setting->vertex11Diffuse =
		((*(Rva007A2830WaterSetting *)((char *)0x012f1608 + waterOffset)).m_vertex11Diffuse.red << 16) |
		((*(Rva007A2830WaterSetting *)((char *)0x012f1608 + waterOffset)).m_vertex11Diffuse.green << 8) |
		(*(Rva007A2830WaterSetting *)((char *)0x012f1608 + waterOffset)).m_vertex11Diffuse.blue;
	setting->waterDiffuse =
		((*(Rva007A2830WaterSetting *)((char *)0x012f1608 + waterOffset)).m_waterDiffuseColor.alpha << 24) |
		((*(Rva007A2830WaterSetting *)((char *)0x012f1608 + waterOffset)).m_waterDiffuseColor.red << 16) |
		((*(Rva007A2830WaterSetting *)((char *)0x012f1608 + waterOffset)).m_waterDiffuseColor.green << 8) |
		(*(Rva007A2830WaterSetting *)((char *)0x012f1608 + waterOffset)).m_waterDiffuseColor.blue;
	setting->transparentWaterDiffuse =
		((*(Rva007A2830WaterSetting *)((char *)0x012f1608 + waterOffset)).m_transparentWaterDiffuse.alpha << 24) |
		((*(Rva007A2830WaterSetting *)((char *)0x012f1608 + waterOffset)).m_transparentWaterDiffuse.red << 16) |
		((*(Rva007A2830WaterSetting *)((char *)0x012f1608 + waterOffset)).m_transparentWaterDiffuse.green << 8) |
		(*(Rva007A2830WaterSetting *)((char *)0x012f1608 + waterOffset)).m_transparentWaterDiffuse.blue;
}
