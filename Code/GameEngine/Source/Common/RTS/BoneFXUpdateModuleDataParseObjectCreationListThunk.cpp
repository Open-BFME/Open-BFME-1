// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib
// readable body of ?parseObjectCreationList@BoneFXUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z: Code/GameEngine/Source/GameLogic/Object/Update/BoneFXUpdate.cpp

class INI;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BoneFXUpdate.h
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
