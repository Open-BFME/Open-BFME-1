// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
//
// Two consecutive ControlBarSchemeManager parser bodies sit at 0x004AE920 and
// 0x004AEA00, in the order they were written:
//
//   parseImagePart            0x004AE920  172 B  SAX (static)
//   parseAnimatingPart        0x004AEA00  219 B  SAX (static)
//
// The two parsers are the INI hooks that build a scheme's artwork: each makes
// one part, hands it to INI::initFromINI to be filled from the block being
// read, clamps the layer it asks for into 0..5 and files it under that layer.
// The animating one additionally keeps the animation itself on the scheme's
// animation list.
//
// Split apart, ControlBarSchemeImage was 0x18 anonymous bytes and a layer in
// one file and five named fields and a layer in the next -- the same 0x18, one
// file just declining to say what was in it -- and ControlBarScheme was a bare
// destructor declaration in the third. Declared once, an image is what it says
// it is, and the scheme carries both lists the parsers file into.

#include <list>

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *, const void *);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBarScheme.h
class ControlBarSchemeImage
{
public:
	ControlBarSchemeImage();

private:
	unsigned char m_name[4];
	int m_position[2];
	int m_size[2];
	void *m_image;
	int m_layer;						// +0x18

	friend class ControlBarSchemeManager;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBarScheme.h
class ControlBarSchemeAnimation
{
public:
	ControlBarSchemeAnimation();

private:
	unsigned char m_pad00[8];
	ControlBarSchemeImage *m_animImage;			// +0x08
	unsigned char m_pad0c[0x18];

	friend class ControlBarSchemeManager;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBarScheme.h
class ControlBarScheme
{
public:
	~ControlBarScheme();

private:
	unsigned char m_pad00[0x158];
	_STL::list<ControlBarSchemeImage *> m_layers[6];		// +0x158
	_STL::list<ControlBarSchemeAnimation *> m_animations;

	friend class ControlBarSchemeManager;
};

extern const unsigned char g_controlBarSchemeImageFieldParse[];
extern const unsigned char g_controlBarSchemeAnimationFieldParse[];

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBarScheme.h
class ControlBarSchemeManager
{
public:
	static void __cdecl parseImagePart(INI *, void *, void *, const void *);
	static void __cdecl parseAnimatingPart(INI *, void *, void *, const void *);

private:
	ControlBarScheme *m_currentScheme;
	float m_multiplierX;
	float m_multiplierY;
	_STL::list<ControlBarScheme *> m_schemeList;
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

// ?parseAnimatingPart@ControlBarSchemeManager@@SAXPAVINI@@PAX1PBX@Z
void __cdecl ControlBarSchemeManager::parseAnimatingPart(INI *ini,
	void *instance, void *, const void *)
{
	ControlBarSchemeAnimation *animation = new ControlBarSchemeAnimation;
	ini->initFromINI(animation, g_controlBarSchemeAnimationFieldParse);

	ControlBarScheme *scheme = static_cast<ControlBarScheme *>(instance);
	if (animation != 0)
		scheme->m_animations.push_back(animation);

	ControlBarSchemeImage *image = animation->m_animImage;
	if (image != 0)
	{
		if (image->m_layer < 0 || image->m_layer >= 6)
			image->m_layer = 0;
		scheme->m_layers[image->m_layer].push_back(image);
	}
}
