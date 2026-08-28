// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// readable body of ?parseImagePart@ShellMenuSchemeManager@@: Code/GameEngine/Source/GameClient/GUI/Shell/ShellMenuScheme.cpp

#include <list>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *, const void *);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ShellMenuScheme.h
class ShellMenuSchemeImage
{
public:
	ShellMenuSchemeImage();

private:
	unsigned char m_name[4];
	int m_position[2];
	int m_size[2];
	void *m_image;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ShellMenuScheme.h
class ShellMenuScheme
{
private:
	unsigned char m_pad00[4];
	_STL::list<ShellMenuSchemeImage *> m_imageList;

	friend class ShellMenuSchemeManager;
};

extern const unsigned char g_shellMenuSchemeImageFieldParse[];

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ShellMenuScheme.h
class ShellMenuSchemeManager
{
public:
	static void __cdecl parseImagePart(INI *, void *, void *, const void *);
};

// ?parseImagePart@ShellMenuSchemeManager@@SAXPAVINI@@PAX1PBX@Z
void __cdecl ShellMenuSchemeManager::parseImagePart(INI *ini, void *instance,
	void *, const void *)
{
	ShellMenuSchemeImage *schemeImage = new ShellMenuSchemeImage;
	ini->initFromINI(schemeImage, g_shellMenuSchemeImageFieldParse);

	if (schemeImage != 0)
	{
		ShellMenuScheme *scheme = static_cast<ShellMenuScheme *>(instance);
		scheme->m_imageList.push_back(schemeImage);
	}
}
