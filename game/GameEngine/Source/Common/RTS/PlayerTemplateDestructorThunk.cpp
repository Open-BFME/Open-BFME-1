// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWLib

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/PlayerTemplate.h
class PlayerTemplate
{
public:
	~PlayerTemplate();
};

class PlayerTemplateDestructorShim
{
public:
	void destroy();
};

PlayerTemplate::~PlayerTemplate()
{
	((PlayerTemplateDestructorShim *)this)->destroy();
}
