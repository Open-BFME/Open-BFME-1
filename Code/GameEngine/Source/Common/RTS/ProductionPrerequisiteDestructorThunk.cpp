// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib
// readable body of ??1ProductionPrerequisite@@QAE@XZ: Code/GameEngine/Source/Common/RTS/ProductionPrerequisite.cpp

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ProductionPrerequisite.h
class ProductionPrerequisite
{
public:
	~ProductionPrerequisite();
};

class ProductionPrerequisiteDestructorShim
{
public:
	void destroy();
};

ProductionPrerequisite::~ProductionPrerequisite()
{
	((ProductionPrerequisiteDestructorShim *)this)->destroy();
}
