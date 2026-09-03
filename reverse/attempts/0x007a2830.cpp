// ?loadSetting@WaterRenderObjClass@@IAEXPAUSetting@1@W4TimeOfDay@@@Z
// partial score=0.7 date=2026-09-03
// cl: /DNDEBUG /MD /EHsc
// Clean BFME reconstruction of WaterRenderObjClass::loadSetting at 0x007A2830.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;
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

	~BFMEWaterTrackTextureHandle()
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

class W3DRadarResetSurface : public SurfaceClass
{
public:
	~W3DRadarResetSurface();

private:
	void *m_surface;
};

class W3DRadarResetTexture
{
public:
	W3DRadarResetSurface getSurfaceLevel(void);

	TextureClass *m_texture;
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

class WaterSetting
{
public:
	virtual ~WaterSetting(void);

	AsciiString m_skyTextureFile;
	AsciiString m_waterTextureFile;
	Int m_waterRepeatCount;
	Real m_skyTexelsPerUnit;
	UnsignedInt m_vertex00Diffuse[4];
	UnsignedInt m_vertex10Diffuse[4];
	UnsignedInt m_vertex11Diffuse[4];
	UnsignedInt m_vertex01Diffuse[4];
	UnsignedInt m_waterDiffuseColor[4];
	UnsignedInt m_transparentWaterDiffuse[4];
	Real m_uScrollPerMs;
	Real m_vScrollPerMs;
};

enum TimeOfDay
{
	TIME_OF_DAY_MORNING = 0,
	TIME_OF_DAY_AFTERNOON,
	TIME_OF_DAY_EVENING,
	TIME_OF_DAY_NIGHT
};

static WaterSetting * const BFMEWaterSettings = (WaterSetting *)0x012f1608;

class WaterRenderObjClass
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
	void loadSetting(Setting *setting, TimeOfDay timeOfDay);
};

void WaterRenderObjClass::loadSetting(Setting *setting, TimeOfDay timeOfDay)
{
	BFMEAssignWaterTrackTexture(
		setting->skyTexture,
		BFMEGetWaterTrackTexture(BFMEWaterSettings[timeOfDay].m_skyTextureFile.str(), 0, 0));
	BFMEAssignWaterTrackTexture(
		setting->waterTexture.m_texture,
		BFMEGetWaterTrackTexture(BFMEWaterSettings[timeOfDay].m_waterTextureFile.str(), 0, 0));

	setting->skyTexelsPerUnit = BFMEWaterSettings[timeOfDay].m_skyTexelsPerUnit;
	SurfaceClass::SurfaceDescription surfaceDesc;
	setting->waterTexture.getSurfaceLevel().Get_Description(surfaceDesc);
	setting->skyTexelsPerUnit /= (Real)surfaceDesc.Width;

	setting->waterRepeatCount = BFMEWaterSettings[timeOfDay].m_waterRepeatCount;
	setting->uScrollPerMs = BFMEWaterSettings[timeOfDay].m_uScrollPerMs;
	setting->vScrollPerMs = BFMEWaterSettings[timeOfDay].m_vScrollPerMs;

	setting->vertex00Diffuse = (BFMEWaterSettings[timeOfDay].m_vertex00Diffuse[0] << 16) |
		(BFMEWaterSettings[timeOfDay].m_vertex00Diffuse[1] << 8) |
		BFMEWaterSettings[timeOfDay].m_vertex00Diffuse[2];
	setting->vertex01Diffuse = (BFMEWaterSettings[timeOfDay].m_vertex01Diffuse[0] << 16) |
		(BFMEWaterSettings[timeOfDay].m_vertex01Diffuse[1] << 8) |
		BFMEWaterSettings[timeOfDay].m_vertex01Diffuse[2];
	setting->vertex10Diffuse = (BFMEWaterSettings[timeOfDay].m_vertex10Diffuse[0] << 16) |
		(BFMEWaterSettings[timeOfDay].m_vertex10Diffuse[1] << 8) |
		BFMEWaterSettings[timeOfDay].m_vertex10Diffuse[2];
	setting->vertex11Diffuse = (BFMEWaterSettings[timeOfDay].m_vertex11Diffuse[0] << 16) |
		(BFMEWaterSettings[timeOfDay].m_vertex11Diffuse[1] << 8) |
		BFMEWaterSettings[timeOfDay].m_vertex11Diffuse[2];
	setting->waterDiffuse = (BFMEWaterSettings[timeOfDay].m_waterDiffuseColor[3] << 24) |
		(BFMEWaterSettings[timeOfDay].m_waterDiffuseColor[0] << 16) |
		(BFMEWaterSettings[timeOfDay].m_waterDiffuseColor[1] << 8) |
		BFMEWaterSettings[timeOfDay].m_waterDiffuseColor[2];
	setting->transparentWaterDiffuse = (BFMEWaterSettings[timeOfDay].m_transparentWaterDiffuse[3] << 24) |
		(BFMEWaterSettings[timeOfDay].m_transparentWaterDiffuse[0] << 16) |
		(BFMEWaterSettings[timeOfDay].m_transparentWaterDiffuse[1] << 8) |
		BFMEWaterSettings[timeOfDay].m_transparentWaterDiffuse[2];
}
