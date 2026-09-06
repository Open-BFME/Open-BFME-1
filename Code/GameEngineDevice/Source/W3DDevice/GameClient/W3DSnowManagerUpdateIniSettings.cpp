// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Retail 0x00724240 -- W3DSnowManager::updateIniSettings, the BFME-layout snow
// settings refresh.  reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/
// GameEngineDevice/Source/W3DDevice/GameClient/W3DSnow.cpp:145 is the same
// three steps in the same order: chain up to SnowManager::updateIniSettings
// (here the link thunk j_00038c49), then, if a snow texture is loaded, compare
// its name with TheWeatherSetting's final override and re-fetch it when they
// differ.  m_snowTexture sits at +0x6c, next to the +0x68 index buffer that
// W3DSnowManagerReAcquireResources.cpp fills.
//
// updateIniSettings is virtual upstream, but the shim keeps it non-virtual: one
// virtual here would emit a ??_7W3DSnowManager@@6B@ COMDAT whose single slot
// disagrees with the one W3DSnowManagerUpdate.cpp emits.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	const Overridable *getFinalOverride(void) const;

	void *m_vtable;
	const Overridable *m_nextOverride;
};

class BfmeAsciiString
{
	unsigned char m_pad00[4];

public:
	const char *m_data;
};

class BfmeOverride1137 : public Overridable
{
public:
	BfmeAsciiString m_snowTexture;
};

extern BfmeOverride1137 *g_bfmeGlo012F15F8;

void j_00038c49(void);

static const BfmeOverride1137 *walkSnowOverride(const BfmeOverride1137 *d)
{
	if (d && d->m_nextOverride)
		return (const BfmeOverride1137 *)d->m_nextOverride->getFinalOverride();
	return d;
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/texture.h
class TextureClass
{
public:
	virtual const char *Get_Texture_Name(void);
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

static inline void BFMEAssignSnowTexture(
	TextureClass *&destination, const BFMEWaterTrackTextureHandle &texture)
{
	if (texture.m_texture)
		++*(unsigned short *)((char *)texture.m_texture + 4);
	if (destination)
		((BFMEWaterTrackTexture *)destination)->Release_Ref();
	destination = texture.m_texture;
}

extern "C" __declspec(dllimport) int __cdecl stricmp(const char *, const char *);

class W3DSnowManager
{
public:
	void updateIniSettings(void);

	private:
	unsigned char m_pad00[0x6c];
	TextureClass *m_snowTexture;
};

void W3DSnowManager::updateIniSettings(void)
{
	j_00038c49();

	if (m_snowTexture)
	{
		const BfmeOverride1137 *setting =
			walkSnowOverride(g_bfmeGlo012F15F8);
		const char *name;
		if (setting->m_snowTexture.m_data)
			name = setting->m_snowTexture.m_data + 8;
		else
			name = (const char *)0x0107388B;

		TextureClass *texture = m_snowTexture;
		const char *textureName = texture ? texture->Get_Texture_Name() : 0;
		if (stricmp(textureName, name) != 0)
		{
			const BfmeOverride1137 *replacement =
				walkSnowOverride(g_bfmeGlo012F15F8);
			const char *replacementName = replacement->m_snowTexture.m_data;
			if (replacementName)
				replacementName += 8;
			else
				replacementName = (const char *)0x0107388B;

			BFMEAssignSnowTexture(
				m_snowTexture,
				BFMEGetWaterTrackTexture((char *)replacementName, 0, 0));
		}
	}
}
