// ?iniParseAnim@Rva00268340Contain@@SAXPAVINI@@PAX1PBX@Z
// partial score=0.95 date=2026-09-05
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/stringbaseascii /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WWLib
//
// True ICF twin of ?iniParseAnim@TransportContain@@SAXPAVINI@@PAX1PBX@Z at
// 0x0022CF60 (TransportContainIniParseAnim.cpp): every byte AND every
// relocation target (getNextToken, the bfmeLookup thunk, __CxxThrowException,
// the exception-info global, the throw-continuation thunk, and the
// "ModelConditionState"/message string literals) is identical -- none of
// those callees or literals depend on the enclosing class name, so this is a
// second real source-level function with byte-for-byte identical object
// code, not a template instantiation. No name is provable for this second
// site, so it is claimed address-derived.

typedef int Int;

extern "C" int __cdecl strcmp(const char *, const char *);
#pragma intrinsic(strcmp)

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
    const char *getNextToken(const char *seps = 0);

    const char *getSepsColon() const
    {
        return *(const char **)((const char *)this + 0x41C);
    }
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INIException.h
class INIException
{
public:
    INIException(Int, const char *, ...);
    INIException(const INIException &);

private:
    Int m_code;
    const char *m_message;
};

class Rva00268340Contain
{
public:
    static void iniParseAnim(INI *, void *, void *, const void *);
};

int bfmeLookup_001c62b0(void *name);

void Rva00268340Contain::iniParseAnim(INI *ini, void *, void *store, const void *)
{
    const char *token = ini->getNextToken(ini->getSepsColon());

    if (token == 0 || strcmp(token, "ModelConditionState") != 0)
        throw INIException(3, "AnimState expected for TransportContain::iniParseAnim");

    token = ini->getNextToken();
    *(int *)store = bfmeLookup_001c62b0((void *)token);
}
