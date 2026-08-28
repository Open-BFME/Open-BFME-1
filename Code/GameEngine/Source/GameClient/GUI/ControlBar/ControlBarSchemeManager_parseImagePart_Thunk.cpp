// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

#include <list>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *, const void *);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBarScheme.h
class ControlBarSchemeImage
{
public:
	ControlBarSchemeImage();

private:
	unsigned char m_name[4];
	int m_position[2];
	int m_size[2];
	void *m_image;
	int m_layer;

	friend class ControlBarSchemeManager;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBarScheme.h
class ControlBarScheme
{
private:
	unsigned char m_pad00[0x158];
	_STL::list<ControlBarSchemeImage *> m_layers[6];

	friend class ControlBarSchemeManager;
};

extern const unsigned char g_controlBarSchemeImageFieldParse[];

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBarScheme.h
class ControlBarSchemeManager
{
public:
	static void __cdecl parseImagePart(INI *, void *, void *, const void *);
};

// ?parseImagePart@ControlBarSchemeManager@@SAXPAVINI@@PAX1PBX@Z
void __cdecl ControlBarSchemeManager::parseImagePart(INI *ini, void *instance,
	void *, const void *)
{
	ControlBarSchemeImage *schemeImage = new ControlBarSchemeImage;
	ini->initFromINI(schemeImage, g_controlBarSchemeImageFieldParse);

	if (schemeImage != 0)
	{
		if (schemeImage->m_layer < 0 || schemeImage->m_layer >= 6)
			schemeImage->m_layer = 0;

		ControlBarScheme *scheme = static_cast<ControlBarScheme *>(instance);
		scheme->m_layers[schemeImage->m_layer].push_back(schemeImage);
	}
}
