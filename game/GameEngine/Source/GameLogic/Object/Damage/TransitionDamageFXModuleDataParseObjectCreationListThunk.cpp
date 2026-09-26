// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWLib
// readable body of ?parseObjectCreationList@TransitionDamageFXModuleData@@: game/GameEngine/Source/GameLogic/Object/Damage/TransitionDamageFX.cpp

class INI;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/TransitionDamageFX.h
class TransitionDamageFXModuleData
{
public:
    static void parseObjectCreationList(INI *, void *, void *, const void *);
};

class TransitionDamageFXModuleDataParseObjectCreationListShim
{
public:
    static void parse(INI *ini, void *store, void *userData, const void *desc);
};

void TransitionDamageFXModuleData::parseObjectCreationList(INI *ini, void *store, void *userData, const void *desc)
{
    TransitionDamageFXModuleDataParseObjectCreationListShim::parse(ini, store, userData, desc);
}
