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
private:
	unsigned char m_pad00[0x18];
	int m_layer;

	friend class ControlBarSchemeManager;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBarScheme.h
class ControlBarSchemeAnimation
{
public:
	ControlBarSchemeAnimation();

private:
	unsigned char m_pad00[8];
	ControlBarSchemeImage *m_animImage;
	unsigned char m_pad0c[0x18];

	friend class ControlBarSchemeManager;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBarScheme.h
class ControlBarScheme
{
private:
	unsigned char m_pad00[0x158];
	_STL::list<ControlBarSchemeImage *> m_layers[6];
	_STL::list<ControlBarSchemeAnimation *> m_animations;

	friend class ControlBarSchemeManager;
};

extern const unsigned char g_controlBarSchemeAnimationFieldParse[];

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBarScheme.h
class ControlBarSchemeManager
{
public:
	static void __cdecl parseAnimatingPart(INI *, void *, void *, const void *);
};

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
