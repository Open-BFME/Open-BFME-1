// cl: /DNDEBUG /MD /EHsc
// stlport
// INI field parser for "AnimState: <cond> AnimTime: <dur> RiderOCL: <ocl>" records; owner class unproven.

#include <vector>
#include <string.h>

typedef int Int;
typedef unsigned int UnsignedInt;

extern "C" int __cdecl strcmp(const char *, const char *);
#pragma intrinsic(strcmp)

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
    const char *getNextToken(const char *seps = 0);

    static void parseDurationUnsignedInt(INI *, void *, void *, const void *);
    static void parseObjectCreationList(INI *, void *, void *, const void *);

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

int bfmeLookup_001c62b0(void *name);

// 320-bit model-condition mask, cleared wholesale on construction.
class BfmeConditionFlags
{
public:
    BfmeConditionFlags()
    {
        memset(m_bits, 0, sizeof(m_bits));
    }
    void set(UnsignedInt bit)
    {
        m_bits[bit >> 5] |= 1 << (bit & 31);
    }
    unsigned int m_bits[10];
};

// 48-byte element of the vector whose push_back is 0x0028DC90.
struct Gen_t_0028dc90_p48pod
{
    BfmeConditionFlags m_flags;
    UnsignedInt m_animTime;
    const void *m_ocl;
};

class Rva0028DDC0RiderInfoParser
{
public:
    static void parseRiderInfo(INI *, void *, void *, const void *);
};

// ?parseRiderInfo@Rva0028DDC0RiderInfoParser@@SAXPAVINI@@PAX1PBX@Z
void Rva0028DDC0RiderInfoParser::parseRiderInfo(INI *ini, void *instance, void *store, const void *)
{
    Gen_t_0028dc90_p48pod info;

    const char *token = ini->getNextToken(ini->getSepsColon());
    if (token == 0 || strcmp(token, "AnimState") != 0)
        throw INIException(3, "AnimState expected");

    int bit = bfmeLookup_001c62b0((void *)ini->getNextToken());
    BfmeConditionFlags flags;
    flags.set(bit);
    info.m_flags = flags;

    token = ini->getNextToken(ini->getSepsColon());
    if (token == 0 || strcmp(token, "AnimTime") != 0)
        throw INIException(3, "AnimDuration expected");
    INI::parseDurationUnsignedInt(ini, instance, &info.m_animTime, 0);

    token = ini->getNextToken(ini->getSepsColon());
    if (token == 0 || strcmp(token, "RiderOCL") != 0)
        throw INIException(3, "RiderOCL expected");
    INI::parseObjectCreationList(ini, instance, &info.m_ocl, 0);

    ((std::vector<Gen_t_0028dc90_p48pod> *)store)->push_back(info);
}
