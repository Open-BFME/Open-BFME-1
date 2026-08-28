// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/decalsys.h
class MultiFixedPoolDecalSystemClass
{
public:
	// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/decalsys.h
	class LogicalDecalClass
	{
	public:
		~LogicalDecalClass();
	};
};

class MultiFixedPoolDecalSystemClassLogicalDecalClassDestructorShim
{
public:
	void destroy();
};

MultiFixedPoolDecalSystemClass::LogicalDecalClass::~LogicalDecalClass()
{
	((MultiFixedPoolDecalSystemClassLogicalDecalClassDestructorShim *)this)->destroy();
}
