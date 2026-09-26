// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWLib
// readable body of ??1W3DAnimationInfo@@QAE@XZ: game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DModelDraw.cpp

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DModelDraw.h
class W3DAnimationInfo
{
public:
	~W3DAnimationInfo();
};

class W3DAnimationInfoDestructorShim
{
public:
	void destroy();
};

W3DAnimationInfo::~W3DAnimationInfo()
{
	((W3DAnimationInfoDestructorShim *)this)->destroy();
}
