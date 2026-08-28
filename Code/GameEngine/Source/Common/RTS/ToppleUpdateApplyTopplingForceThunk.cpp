// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /Code/GameEngine/Include /Code/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib
// readable body of ?applyTopplingForce@ToppleUpdate@@: Code/GameEngine/Source/GameLogic/Object/Update/ToppleUpdate.cpp

struct Coord3D;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ToppleUpdate.h
class ToppleUpdate
{
public:
    void applyTopplingForce(const Coord3D *, float, unsigned int);
};

class ToppleUpdateApplyTopplingForceShim
{
public:
    void apply(const Coord3D *dir, float speed, unsigned int options);
};

void ToppleUpdate::applyTopplingForce(const Coord3D *dir, float speed, unsigned int options)
{
    ((ToppleUpdateApplyTopplingForceShim *)this)->apply(dir, speed, options);
}
