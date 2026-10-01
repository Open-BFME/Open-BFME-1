// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// BaseHeightMapRenderObjClass::updateMacroTexture, retail 0x006CB8D0: BFME's two-argument form, called
// on the terrain by reset() and ParseEnvironmentData; it reloads the stage-three texture by name.

typedef bool Bool;

class AsciiString;
extern char Rva006A16B0Empty[];

template <class CharType>
class StringBase
{
public:
	void set(const StringBase &other);

	CharType *m_data;

private:
	~StringBase();

	friend class AsciiString;
};

class AsciiString : public StringBase<char>
{
public:
	~AsciiString() {}
};

// The release leaf at 0x009EB7A0 is TextureBaseClass::Release_Ref in the real
// WW3D2 header, so the stage pointer uses that type rather than a stand-in.
#include <texture.h>

class BFMEWaterTrackTextureHandle
{
public:
	TextureBaseClass *m_texture;

	~BFMEWaterTrackTextureHandle()
	{
		if (m_texture)
			m_texture->Release_Ref();
	}
};

extern BFMEWaterTrackTextureHandle BFMEGetWaterTrackTexture(
	char *name, int mipCount, int format);

static inline void BFMEAssignWaterTrackTexture(
	TextureBaseClass *&destination, const BFMEWaterTrackTextureHandle &texture)
{
	if (texture.m_texture)
		++*(unsigned short *)((char *)texture.m_texture + 4);
	if (destination)
		destination->Release_Ref();
	destination = texture.m_texture;
}

class ShroudFilter
{
public:
	int m_minFilter;
	int m_magFilter;
	int m_unused08;
	int m_mipFilter;
	int m_anisotropy;
};

class ShroudTexture
{
public:
	ShroudFilter *getFilter();

	TextureBaseClass *m_texture;
};

class BaseHeightMapRenderObjClass
{
public:
	void updateMacroTexture(AsciiString textureName, Bool force);

private:
	char m_padding00[0x305c];
	ShroudTexture m_stageThreeTexture;
	char m_padding3060[0x0c];
	Bool m_force;
	char m_padding306d[3];
	AsciiString m_macroTextureName;
	char m_padding3074[0x0c];
	AsciiString m_defaultTextureName;
};

void BaseHeightMapRenderObjClass::updateMacroTexture(
	AsciiString textureName, Bool force)
{
	if (textureName.m_data == 0 ||
		*(unsigned short *)((char *)textureName.m_data + 4) == 0)
	{
		textureName.set(m_defaultTextureName);
	}

	ShroudTexture &stageThree = m_stageThreeTexture;
	TextureBaseClass *&stageThreeTexture = stageThree.m_texture;
	if (stageThreeTexture)
	{
		stageThreeTexture->Release_Ref();
		stageThreeTexture = 0;
	}

	m_force = force;
	StringBase<char> &macroTextureName = m_macroTextureName;
	macroTextureName.set(textureName);

	const char *name;
	if (macroTextureName.m_data)
		name = (const char *)macroTextureName.m_data + 8;
	else
		name = (const char *)Rva006A16B0Empty;

	BFMEAssignWaterTrackTexture(
		stageThreeTexture,
		BFMEGetWaterTrackTexture((char *)name, 0, 0));

	stageThree.getFilter()->m_minFilter = 2;
	stageThree.getFilter()->m_magFilter = 2;
	stageThree.getFilter()->m_mipFilter = 0;
	stageThree.getFilter()->m_anisotropy = 0;
}
