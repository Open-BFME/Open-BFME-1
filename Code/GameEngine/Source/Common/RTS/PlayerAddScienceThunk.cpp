// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib
// readable body of ?addScience@Player@@AAE_NW4ScienceType@@@Z: Code/GameEngine/Source/Common/RTS/Player.cpp

enum ScienceType
{
    ScienceType_Thunk
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
    bool addScience(ScienceType);
};

class PlayerAddScienceShim
{
public:
    bool add(ScienceType science);
};

bool Player::addScience(ScienceType science)
{
    return ((PlayerAddScienceShim *)this)->add(science);
}
