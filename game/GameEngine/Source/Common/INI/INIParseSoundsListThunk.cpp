// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWLib
// readable body of ?parseSoundsList@INI@@: game/GameEngine/Source/Common/INI/INI_stl.cpp
// readable body of ?parseSoundsList@INI@@SAXPAV1@PAX1PBX@Z: game/GameEngine/Source/Common/INI/ini.cpp

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
    __declspec(dllexport) static void parseSoundsList(INI *, void *, void *, const void *);
};

class INIParseSoundsListShim
{
public:
    static void parse(INI *ini, void *store, void *userData, const void *desc);
};

void INI::parseSoundsList(INI *ini, void *store, void *userData, const void *desc)
{
    INIParseSoundsListShim::parse(ini, store, userData, desc);
}
