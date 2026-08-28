// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DModelDraw.h
class ModelConditionInfo
{
public:
	// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DModelDraw.h
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
