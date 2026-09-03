// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/stringbaseascii /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWLib
typedef int Int;

extern "C" int __cdecl strcmp(const char *, const char *);
#pragma intrinsic(strcmp)

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
    const char *getNextToken(const char *seps = 0);

    const char *getSepsColon() const
    {
        return *(const char **)((const char *)this + 0x41C);
    }
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INIException.h
class INIException
{
public:
    INIException(Int, const char *, ...);
    INIException(const INIException &);

private:
    Int m_code;
    const char *m_message;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/TransportContain.h
class TransportContain
{
public:
    static void iniParseAnim(INI *, void *, void *, const void *);
};

int bfmeLookup_001c62b0(void *name);

void TransportContain::iniParseAnim(INI *ini, void *, void *store, const void *)
{
    const char *token = ini->getNextToken(ini->getSepsColon());

    if (token == 0 || strcmp(token, "ModelConditionState") != 0)
        throw INIException(3, "AnimState expected for TransportContain::iniParseAnim");

    token = ini->getNextToken();
    *(int *)store = bfmeLookup_001c62b0((void *)token);
}
