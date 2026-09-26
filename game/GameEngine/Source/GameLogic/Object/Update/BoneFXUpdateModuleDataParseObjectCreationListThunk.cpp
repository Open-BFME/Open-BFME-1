// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWLib
// readable body of ?parseObjectCreationList@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z: game/GameEngine/Source/GameLogic/Object/Update/BoneFXUpdate.cpp

class INI;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BoneFXUpdate.h
class BoneFXUpdateModuleData
{
public:
    static void parseObjectCreationList(INI *, void *, void *, const void *);
};

class BoneFXUpdateModuleDataParseObjectCreationListShim
{
public:
    static void parse(INI *ini, void *store, void *userData, const void *desc);
};

void BoneFXUpdateModuleData::parseObjectCreationList(INI *ini, void *store, void *userData, const void *desc)
{
    BoneFXUpdateModuleDataParseObjectCreationListShim::parse(ini, store, userData, desc);
}
