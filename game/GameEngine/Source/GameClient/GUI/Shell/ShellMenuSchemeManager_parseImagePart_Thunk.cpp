// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// readable body of ?parseImagePart@ShellMenuSchemeManager@@: game/GameEngine/Source/GameClient/GUI/Shell/ShellMenuScheme.cpp

#include <list>

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *, const void *);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ShellMenuScheme.h
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

class ShellMenuSchemeLine
{
public:
	ShellMenuSchemeLine()
	{
		m_startPos[0] = m_startPos[1] = 0;
		m_endPos[0] = m_endPos[1] = 0;
		m_color = 0x00ffffff;
		m_width = 1;
	}

private:
	int m_startPos[2];
	int m_endPos[2];
	int m_width;
	unsigned int m_color;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ShellMenuScheme.h
class ShellMenuScheme
{
private:
	unsigned char m_pad00[4];
	_STL::list<ShellMenuSchemeImage *> m_imageList;
	_STL::list<ShellMenuSchemeLine *> m_lineList;

	friend class ShellMenuSchemeManager;
};

extern const unsigned char g_shellMenuSchemeImageFieldParse[];
extern const unsigned char g_shellMenuSchemeLineFieldParse[];

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ShellMenuScheme.h
class ShellMenuSchemeManager
{
public:
	static void __cdecl parseImagePart(INI *, void *, void *, const void *);
	static void __cdecl parseLinePart(INI *, void *, void *, const void *);
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

// ?parseLinePart@ShellMenuSchemeManager@@SAXPAVINI@@PAX1PBX@Z
void __cdecl ShellMenuSchemeManager::parseLinePart(INI *ini, void *instance,
	void *, const void *)
{
	ShellMenuSchemeLine *schemeLine = new ShellMenuSchemeLine;
	ini->initFromINI(schemeLine, g_shellMenuSchemeLineFieldParse);

	if (schemeLine != 0)
	{
		ShellMenuScheme *scheme = static_cast<ShellMenuScheme *>(instance);
		scheme->m_lineList.push_back(schemeLine);
	}
}
