// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /Code/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib

class INI;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Eva.h
class Eva
{
public:
    __declspec(dllexport) static void parseEvaMessageFromIni(INI *, void *, void *, const void *);
};

class EvaParseMessageFromIniShim
{
public:
    static void parse(INI *ini, void *store, void *userData, const void *desc);
};

void Eva::parseEvaMessageFromIni(INI *ini, void *store, void *userData, const void *desc)
{
    EvaParseMessageFromIniShim::parse(ini, store, userData, desc);
}
