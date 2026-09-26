// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWLib

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DModelDraw.h
class ModelConditionInfo
{
public:
	// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DModelDraw.h
	class HideShowSubObjInfo
	{
	public:
		~HideShowSubObjInfo();
	};
};

class ModelConditionInfoHideShowSubObjInfoDestructorShim
{
public:
	void destroy();
};

ModelConditionInfo::HideShowSubObjInfo::~HideShowSubObjInfo()
{
	((ModelConditionInfoHideShowSubObjInfoDestructorShim *)this)->destroy();
}
