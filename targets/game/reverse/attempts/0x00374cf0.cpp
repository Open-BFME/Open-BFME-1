// ?parseCastleToUnpackForFaction@CastleBehaviorModuleData@@SAXPAVINI@@PAX1PBX@Z
// partial score=1.0 date=2026-10-09
// ?parseCastleToUnpackForFaction@CastleBehaviorModuleData@@SAXPAVINI@@PAX1PBX@Z
// cl: /DNDEBUG /MD /EHsc /D_OPERATOR_NEW_DEFINED_ /DWIN32 /D_WINDOWS /Iinputs/reference/shims/zhcanonascii /Iinputs/reference/shims/namekeygenerator /Iinputs/reference/shims/ini_noinline /Iinputs/reference/shims/iniexception /Iinputs/reference/shims/sweep /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas
// stlport

#include "Common/INI.h"
#include <map>
#include "Common/NameKeyGenerator.h"

struct Rva0036DEF0Payload {
    AsciiString m_text;
    unsigned int m_first;
    unsigned int m_second;
    Rva0036DEF0Payload() : m_first(0), m_second(0) {}
};
typedef _STL::map<int, Rva0036DEF0Payload> Rva00372570Tree;
class SidesList;
extern SidesList *TheSidesList;
class Rva00197930StringListOwner {
public:
    void appendUnique(const AsciiString &name);
};
class CastleBehaviorModuleData {
public:
    static void parseCastleToUnpackForFaction(INI *ini, void *instance, void *store, const void *userData);
};

// ?parseCastleToUnpackForFaction@CastleBehaviorModuleData@@SAXPAVINI@@PAX1PBX@Z
void CastleBehaviorModuleData::parseCastleToUnpackForFaction(INI *ini, void *, void *store, const void *)
{
    AsciiString factionName("");
    INI::parseAsciiString(ini, 0, &factionName, 0);
    int factionKey = TheNameKeyGenerator->nameToKey(factionName.str());
    AsciiString parsedText("");
    INI::parseAsciiString(ini, 0, &parsedText, 0);
    Rva0036DEF0Payload payload;
    payload.m_text = parsedText;
    payload.m_first = 0;
    const char *token = ini->getNextTokenOrNull();
    if (token)
        payload.m_first = INI::scanUnsignedInt(token);
    token = ini->getNextTokenOrNull();
    if (token)
        payload.m_second = INI::scanUnsignedInt(token);
    ((Rva00372570Tree *)store)->insert(_STL::make_pair(factionKey, payload));
    ((Rva00197930StringListOwner *)TheSidesList)->appendUnique(parsedText);
}
