// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// BFME retail 0x006CB8D0: BaseHeightMapResetTerrain::updateMacroTexture.

typedef bool Bool;

class BaseHeightMapResetAsciiString;

template <class CharType>
class StringBase
{
public:
	void set(const StringBase &other);

	CharType *m_data;

private:
	~StringBase();

	friend class BaseHeightMapResetAsciiString;
};

class BaseHeightMapResetAsciiString : public StringBase<char>
{
public:
	~BaseHeightMapResetAsciiString() {}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/texture.h
class TextureClass
{
public:
	void Release_Ref();
};

class BFMEWaterTrackTexture
{
public:
	void Release_Ref();
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
	char *name, int mipCount, int format);

static inline void BFMEAssignWaterTrackTexture(
	TextureClass *&destination, const BFMEWaterTrackTextureHandle &texture)
{
	if (texture.m_texture)
		++*(unsigned short *)((char *)texture.m_texture + 4);
	if (destination)
		((BFMEWaterTrackTexture *)destination)->Release_Ref();
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

	TextureClass *m_texture;
};

class BaseHeightMapResetTerrain
{
public:
	void updateMacroTexture(BaseHeightMapResetAsciiString textureName, Bool force);

private:
	char m_padding00[0x305c];
	ShroudTexture m_stageThreeTexture;
	char m_padding3060[0x0c];
	Bool m_force;
	char m_padding306d[3];
	BaseHeightMapResetAsciiString m_macroTextureName;
	char m_padding3074[0x0c];
	BaseHeightMapResetAsciiString m_defaultTextureName;
};

void BaseHeightMapResetTerrain::updateMacroTexture(
	BaseHeightMapResetAsciiString textureName, Bool force)
{
	if (textureName.m_data == 0 ||
		*(unsigned short *)((char *)textureName.m_data + 4) == 0)
	{
		textureName.set(m_defaultTextureName);
	}

	ShroudTexture &stageThree = m_stageThreeTexture;
	TextureClass *&stageThreeTexture = stageThree.m_texture;
	if (stageThreeTexture)
	{
		((BFMEWaterTrackTexture *)stageThreeTexture)->Release_Ref();
		stageThreeTexture = 0;
	}

	m_force = force;
	StringBase<char> &macroTextureName = m_macroTextureName;
	macroTextureName.set(textureName);

	const char *name;
	if (macroTextureName.m_data)
		name = (const char *)macroTextureName.m_data + 8;
	else
		name = (const char *)0x0107388b;

	BFMEAssignWaterTrackTexture(
		stageThreeTexture,
		BFMEGetWaterTrackTexture((char *)name, 0, 0));

	stageThree.getFilter()->m_minFilter = 2;
	stageThree.getFilter()->m_magFilter = 2;
	stageThree.getFilter()->m_mipFilter = 0;
	stageThree.getFilter()->m_anisotropy = 0;
}
