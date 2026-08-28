// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /Code/GameEngine/Include /Code/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib
// readable body of ?updateUpgradeModules@Object@@QAEXXZ: Code/GameEngine/Source/GameLogic/Object/Object.cpp

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
    void updateUpgradeModules();
};

class ObjectUpdateUpgradeModulesShim
{
public:
    void update();
};

void Object::updateUpgradeModules()
{
    ((ObjectUpdateUpgradeModulesShim *)this)->update();
}
