// ?parseCastleToUnpackForFaction@Rva00374CF0Owner@@SAXPAVINI@@PAX1PBX@Z
//
// Retail 0x00374CF0 (410 bytes) is the INI field parser behind the
// CastleToUnpackForFaction field-table entry: it reads the faction name, keys it through
// TheNameKeyGenerator, reads the parsed text, optionally reads two unsigned
// fields from the remaining tokens and inserts the triple into the module's
// per-faction map, then appends the text to the side list.
//
// Identity: the field-table entry names the callback, but the descriptive
// decoration ?parseCastleToUnpackForFaction@CastleBehaviorModuleData@@... is
// refuted by retail's thunk table (ilt_oracle: outside every window of the
// target's slots 5491:5760-5765), as is its landed sibling parseFactionDecal.
// This body therefore lands under the address-derived owner Rva00374CF0Owner
// with the field-table name kept as the method name, pending independent
// naming evidence. Evidence: targets/game/reverse/identity_evidence/00374cf0-stl46-ilt-review.md
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
class Rva00374CF0Owner {
public:
    static void parseCastleToUnpackForFaction(INI *ini, void *instance, void *store, const void *userData);
};

// ?parseCastleToUnpackForFaction@Rva00374CF0Owner@@SAXPAVINI@@PAX1PBX@Z
void Rva00374CF0Owner::parseCastleToUnpackForFaction(INI *ini, void *, void *store, const void *)
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
