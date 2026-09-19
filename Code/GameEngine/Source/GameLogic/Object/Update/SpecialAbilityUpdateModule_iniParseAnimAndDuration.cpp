// Open-BFME5: clean C++ reconstruction of the retail INI animation parser.
// The BFME INI layout was checked with tools/bfme_layout.py INI: m_seps is at
// +0x414 and the colon separator mirror used here is at +0x41C.
// cl: /DNDEBUG /MD /EHsc

typedef int Int;

extern "C" int __cdecl strcmp(const char *, const char *);
#pragma intrinsic(strcmp)

class INI
{
public:
    const char *getNextToken(const char *seps = 0);
    const char *getNextTokenOrNull(const char *seps = 0);

    static void parseDurationUnsignedInt(INI *, void *, void *, const void *);

    const char *getSepsColon() const
    {
        return *(const char **)((const char *)this + 0x41C);
    }
};

class INIException
{
public:
    INIException(Int, const char *, ...);
    INIException(const INIException &);

private:
    Int m_code;
    const char *m_message;
};

class SpecialAbilityUpdateModule
{
public:
    static void iniParseAnimAndDuration(INI *, void *, void *, const void *);
};

int bfmeLookup_001c62b0(void *name);

// ?iniParseAnimAndDuration@SpecialAbilityUpdateModule@@SAXPAVINI@@PAX1PBX@Z
void SpecialAbilityUpdateModule::iniParseAnimAndDuration(
    INI *ini, void *instance, void *store, const void *)
{
    const char *token = ini->getNextToken(ini->getSepsColon());

    if (token == 0 || strcmp(token, "AnimState") != 0)
        throw INIException(
            3,
            "AnimState expected for SpecialAbilityUpdateModule::iniParseAnimAndDuration");

    token = ini->getNextToken();
    *(int *)store = bfmeLookup_001c62b0((void *)token);

    token = ini->getNextToken(ini->getSepsColon());
    if (token == 0 || strcmp(token, "AnimTime") != 0)
        throw INIException(
            3,
            "AnimTime expected for SpecialAbilityUpdateModule::iniParseAnimAndDuration");

    INI::parseDurationUnsignedInt(ini, instance, (char *)store + 4, 0);

    token = ini->getNextTokenOrNull(ini->getSepsColon());
    if (token != 0 && strcmp(token, "TriggerTime") == 0)
        INI::parseDurationUnsignedInt(ini, instance, (char *)store + 8, 0);
}
