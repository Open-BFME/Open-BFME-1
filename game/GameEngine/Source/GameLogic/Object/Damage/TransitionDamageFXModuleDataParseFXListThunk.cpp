// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWLib
// readable body of ?parseFXList@TransitionDamageFXModuleData@@: game/GameEngine/Source/GameLogic/Object/Damage/TransitionDamageFX.cpp

class INI;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/TransitionDamageFX.h
class TransitionDamageFXModuleData
{
public:
    static void parseFXList(INI *, void *, void *, const void *);
};

class TransitionDamageFXModuleDataParseFXListShim
{
public:
    static void parse(INI *ini, void *store, void *userData, const void *desc);
};

void TransitionDamageFXModuleData::parseFXList(INI *ini, void *store, void *userData, const void *desc)
{
    TransitionDamageFXModuleDataParseFXListShim::parse(ini, store, userData, desc);
}
