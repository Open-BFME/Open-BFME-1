// ??0W3DLaserDraw@@QAE@PAVThing@@PBVModuleData@@@Z
// partial score=0.9 date=2026-09-14
// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
// BFME retail 0x00757E70: W3DLaserDraw::W3DLaserDraw.
// The shipped BFME class is larger than the Zero Hour reference header --
// m_texture became a texture-pointer vector and a 40-byte parameter block
// lives at +0x34 -- so the recovered layout stays local to this TU.

#include <vector>

#define TRUE 1

typedef char Char;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef float Real;
typedef int Color;

class AsciiString
{
public:
	Char *str(void) const
	{
		Char *s = m_data;
		if (s != NULL)
			s += 8;
		else
			s = (Char *)0x0107388b;
		return s;
	}

private:
	Char *m_data;
};

class TextureClass
{
public:
	void Add_Ref(void) { ++m_refCount; }
	void Release_Ref(void);

private:
	Int m_pad00;
	unsigned short m_refCount;
};

class W3DRadarResetTexture;
class W3DRadarResetSurface;

class SurfaceClass
{
public:
	struct SurfaceDescription
	{
		UnsignedInt m_format;
		UnsignedInt Width;
		UnsignedInt Height;
	};

	void Get_Description(SurfaceDescription &desc);
};

class W3DRadarResetSurface : public SurfaceClass
{
public:
	~W3DRadarResetSurface();
};

class W3DRadarResetTexture
{
public:
	TextureClass *m_texture;

	W3DRadarResetTexture(const W3DRadarResetTexture &other) :
		m_texture(other.m_texture)
	{
		if (m_texture)
			m_texture->Add_Ref();
	}

	W3DRadarResetTexture &operator=(const W3DRadarResetTexture &other)
	{
		m_texture = other.m_texture;
		if (m_texture)
			m_texture->Add_Ref();
		return *this;
	}

	~W3DRadarResetTexture(void)
	{
		if (m_texture)
			m_texture->Release_Ref();
	}

	W3DRadarResetSurface getSurfaceLevel(void);
};

class BFMEWaterTrackTextureHandle : public W3DRadarResetTexture
{
};

extern BFMEWaterTrackTextureHandle BFMEGetWaterTrackTexture(
	Char *name, Int mipCount, Int format);

class Thing;
class ModuleData
{
	char m_pad00[8];
};

class BfmeLaserDrawParams
{
public:
	BfmeLaserDrawParams(void)
	{
		m_f10 = 1; m_f14 = 1; m_f18 = 1;
		m_i1c = -1; m_i20 = -1;
		m_f00 = 1.0f; m_f04 = 1.0f; m_f08 = 1.0f;
		m_f0c = 0; m_i24 = 0;
	}

	Real m_f00;
	Real m_f04;
	Real m_f08;
	Real m_f0c;
	Int m_f10;
	Int m_f14;
	Int m_f18;
	Int m_i1c;
	Int m_i20;
	Int m_i24;
};

class W3DLaserDrawModuleData : public ModuleData
{
public:
	Color m_innerColor;
	Color m_outerColor;
	Real m_innerBeamWidth;
	Real m_outerBeamWidth;
	Real m_scrollRate;
	Bool m_tile;
	char m_pad1d[3];
	UnsignedInt m_numBeams;
	UnsignedInt m_maxIntensityFrames;
	UnsignedInt m_fadeFrames;
	std::vector<AsciiString> m_textureNames;
	UnsignedInt m_segments;
	Real m_arcHeight;
	Real m_segmentOverlapRatio;
	Real m_tilingScalar;
	Int m_field48;
	BfmeLaserDrawParams m_params;
};

class DrawableModule
{
public:
	virtual ~DrawableModule();

protected:
	W3DLaserDrawModuleData *m_moduleData;
	Int m_bfmeField;
};

class DrawModule : public DrawableModule
{
public:
	DrawModule(Thing *thing, const ModuleData *moduleData);
};

class LaserDrawInterface
{
public:
	virtual void bfmeLaserDrawInterfaceSlot(void);
};

class ShaderClass
{
public:
	Int m_bits;

	ShaderClass(const ShaderClass &other) { m_bits = other.m_bits; }
};

#define BfmeShaderPresetAdditive (*(ShaderClass *)0x012d6e0c)

class SegLineRendererClass
{
public:
	enum TextureMapMode
	{
		TILED_TEXTURE_MAP = 2
	};

	void Set_Texture(TextureClass *texture);
};

class Vector3
{
public:
	Vector3(Real x, Real y, Real z) : X(x), Y(y), Z(z) { }

	Real X;
	Real Y;
	Real Z;
};

class Vector2
{
public:
	Vector2(Real x, Real y) : X(x), Y(y) { }

	Real X;
	Real Y;
};

class SegmentedLineClass
{
public:
	SegmentedLineClass(void);

	char m_pad04[0x12c];

	virtual void bfmeVpad000();
	virtual void bfmeVpad001();
	virtual void bfmeVpad002();
	virtual void bfmeVpad003();
	virtual void bfmeVpad004();
	virtual void bfmeVpad005();
	virtual void bfmeVpad006();
	virtual void bfmeVpad007();
	virtual void bfmeVpad008();
	virtual void bfmeVpad009();
	virtual void bfmeVpad010();
	virtual void bfmeVpad011();
	virtual void bfmeVpad012();
	virtual void bfmeVpad013();
	virtual void bfmeVpad014();
	virtual void bfmeVpad015();
	virtual void bfmeVpad016();
	virtual void bfmeVpad017();
	virtual void bfmeVpad018();
	virtual void bfmeVpad019();
	virtual void bfmeVpad020();
	virtual void bfmeVpad021();
	virtual void bfmeVpad022();
	virtual void bfmeVpad023();
	virtual void bfmeVpad024();
	virtual void bfmeVpad025();
	virtual void bfmeVpad026();
	virtual void bfmeVpad027();
	virtual void bfmeVpad028();
	virtual void bfmeVpad029();
	virtual void bfmeVpad030();
	virtual void bfmeVpad031();
	virtual void bfmeVpad032();
	virtual void bfmeVpad033();
	virtual void bfmeVpad034();
	virtual void bfmeVpad035();
	virtual void bfmeVpad036();
	virtual void bfmeVpad037();
	virtual void bfmeVpad038();
	virtual void bfmeVpad039();
	virtual void bfmeVpad040();
	virtual void bfmeVpad041();
	virtual void bfmeVpad042();
	virtual void bfmeVpad043();
	virtual void bfmeVpad044();
	virtual void bfmeVpad045();
	virtual void bfmeVpad046();
	virtual void bfmeVpad047();
	virtual void bfmeVpad048();
	virtual void bfmeVpad049();
	virtual void bfmeVpad050();
	virtual void bfmeVpad051();
	virtual void bfmeVpad052();
	virtual void bfmeVpad053();
	virtual void bfmeVpad054();
	virtual void bfmeVpad055();
	virtual void bfmeVpad056();
	virtual void bfmeVpad057();
	virtual void bfmeVpad058();
	virtual void bfmeVpad059();
	virtual void bfmeVpad060();
	virtual void bfmeVpad061();
	virtual void bfmeVpad062();
	virtual void bfmeVpad063();
	virtual void bfmeVpad064();
	virtual void bfmeVpad065();
	virtual void bfmeVpad066();
	virtual void bfmeVpad067();
	virtual void bfmeVpad068();
	virtual void bfmeVpad069();
	virtual void bfmeVpad070();
	virtual void bfmeVpad071();
	virtual void bfmeVpad072();
	virtual void bfmeVpad073();
	virtual void bfmeVpad074();
	virtual void bfmeVpad075();
	virtual void bfmeVpad076();
	virtual void bfmeVpad077();
	virtual void bfmeVpad078();
	virtual void bfmeVpad079();
	virtual void bfmeVpad080();
	virtual void bfmeVpad081();
	virtual void bfmeVpad082();
	virtual void bfmeVpad083();
	virtual void bfmeVpad084();
	virtual void bfmeVpad085();
	virtual void bfmeVpad086();
	virtual void bfmeVpad087();
	virtual void bfmeVpad088();
	virtual void bfmeVpad089();
	virtual void bfmeVpad090();
	virtual void bfmeVpad091();
	virtual void bfmeVpad092();
	virtual void bfmeVpad093();
	virtual void bfmeVpad094();
	virtual void bfmeVpad095();
	virtual void bfmeVpad096();
	virtual void bfmeVpad097();
	virtual void bfmeVpad098();
	virtual void bfmeVpad099();
	virtual void bfmeVpad100();
	virtual void bfmeVpad101();
	virtual void bfmeVpad102();
	virtual void bfmeVpad103();
	virtual void Set_Visible(Int visible);

	void Set_Shader(ShaderClass shader);
	void Set_Width(Real width);
	void Set_Color(const Vector3 &color);
	void Set_UV_Offset_Rate(const Vector2 &rate);
	void Set_Texture_Mapping_Mode(SegLineRendererClass::TextureMapMode mode);
};

class RTS3DScene
{
public:
	virtual void bfmeSceneSlot0(void);
	virtual void bfmeSceneSlot1(void);
	virtual void Add_Render_Object(SegmentedLineClass *line);
};

class W3DDisplay
{
public:
	static RTS3DScene *m_3DScene;
};

#define BFME_3D_SCENE (*(RTS3DScene **)0x012f8058)

class W3DLaserDraw : public DrawModule, public LaserDrawInterface
{
public:
	W3DLaserDraw(Thing *thing, const ModuleData *moduleData);

protected:
	SegmentedLineClass **m_line3D;
	std::vector<BFMEWaterTrackTextureHandle> m_textureVector;
	Real m_textureAspectRatio;
	Bool m_selfDirty;
	char m_pad25[3];
	Int m_field28;
	Real m_field2c;
	Int m_field30;
	BfmeLaserDrawParams m_params;
};

extern void GameGetColorComponentsReal(
	Color color, Real *red, Real *green, Real *blue, Real *alpha);

W3DLaserDraw::W3DLaserDraw( Thing *thing, const ModuleData* moduleData ) :
	DrawModule( thing, moduleData ),
	m_line3D(NULL),
	m_textureAspectRatio(1.0f),
	m_selfDirty(TRUE),
	m_field28(0),
	m_field2c(1.0f),
	m_field30(m_moduleData->m_field48)
{
	const W3DLaserDrawModuleData *data = m_moduleData;

	m_params = data->m_params;

	Int numTextures = data->m_textureNames.size();
	for (Int i = 0; i < numTextures; i++)
	{
		Char *name = data->m_textureNames[i].str();
		BFMEWaterTrackTextureHandle handle = BFMEGetWaterTrackTexture(name, 0, 0);
		if (handle.m_texture)
		{
			SurfaceClass::SurfaceDescription surfaceDesc;
			handle.getSurfaceLevel().Get_Description(surfaceDesc);
			m_textureAspectRatio = (Real)surfaceDesc.Width/(Real)surfaceDesc.Height;
		}
		m_textureVector.push_back(handle);
	}

	Real innerRed, innerGreen, innerBlue, innerAlpha, outerRed, outerGreen, outerBlue, outerAlpha;
	GameGetColorComponentsReal( data->m_innerColor, &innerRed, &innerGreen, &innerBlue, &innerAlpha );
	GameGetColorComponentsReal( data->m_outerColor, &outerRed, &outerGreen, &outerBlue, &outerAlpha );

	m_line3D = new SegmentedLineClass *[ data->m_segments * data->m_numBeams ];

	for( UnsignedInt segment = 0; segment < data->m_segments; segment++ )
	{
		for( Int i = data->m_numBeams - 1; i >= 0; i-- )
		{
			Int index = segment * data->m_numBeams + i;

			Real red, green, blue, alpha, width;

			if( data->m_numBeams == 1 )
			{
				width = data->m_innerBeamWidth;
				alpha = innerAlpha;
				red = innerRed * innerAlpha;
				green = innerGreen * innerAlpha;
				blue = innerBlue * innerAlpha;
			}
			else
			{
				Real scale = i / ( data->m_numBeams - 1.0f);

				width		= data->m_innerBeamWidth	+ scale * (data->m_outerBeamWidth - data->m_innerBeamWidth);
				alpha		= innerAlpha							+ scale * (outerAlpha - innerAlpha);
				red			= innerRed								+ scale * (outerRed - innerRed) * innerAlpha;
				green		= innerGreen							+ scale * (outerGreen - innerGreen) * innerAlpha;
				blue		= innerBlue								+ scale * (outerBlue - innerBlue) * innerAlpha;
			}

			m_line3D[ index ] = new SegmentedLineClass;

			SegmentedLineClass *line = m_line3D[ index ];
			if( line )
			{
				((SegLineRendererClass *)line)->Set_Texture(
					(TextureClass *)m_textureVector.begin());
				line->Set_Shader( BfmeShaderPresetAdditive );
				line->Set_Width( width );
				line->Set_Color( Vector3( red, green, blue ) );
				line->Set_UV_Offset_Rate( Vector2(0.0f, data->m_scrollRate) );
				if( m_textureVector[0].m_texture )
				{
					line->Set_Texture_Mapping_Mode(SegLineRendererClass::TILED_TEXTURE_MAP);
				}

				BFME_3D_SCENE->Add_Render_Object( line );

				line->Set_Visible( 1 );
			}

		}  // end for i

	} //end segment loop

}
