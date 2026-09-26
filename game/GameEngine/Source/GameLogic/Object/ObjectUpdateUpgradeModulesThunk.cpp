// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/GameEngine/Source/Common/System /game/GameEngine/Include /game/GameEngine/Include/Precompiled /game/Libraries/Source/WWVegas/WWLib
// readable body of ?updateUpgradeModules@Object@@QAEXXZ: game/GameEngine/Source/GameLogic/Object/Object.cpp

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
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
