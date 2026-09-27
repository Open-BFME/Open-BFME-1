// Retail 0x00352810: full 153-byte PlayerScriptsList registration ctor.
// Four arguments and RET16; context/list at +0x0C/+0x10. Base vptr0107C7D0
// becomes derived vptr010E8538 after the string temporary is released.
// Literal VA010E8544 identifies the chunk, not the original class name.
// This is not the no-argument SidesList preparation method of the old dump.
// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringbaseascii/Common /Igame/Libraries/Source/WWVegas/WWLib

#include "AsciiString.h"

class UserParser;
class DataChunkInput;
struct DataChunkInfo;
typedef bool (*BfmeParserCallback)(DataChunkInput &, DataChunkInfo *, void *);

class DataChunkInput
{
public:
    UserParser *registerParser(const AsciiString &name, const AsciiString &label,
        BfmeParserCallback callback, void *userData);
    bool parse(void *userData);
};

class BfmeParserRegistrationVE
{
public:
    BfmeParserRegistrationVE(DataChunkInput *table, AsciiString *name,
        AsciiString *label)
    {
        m_vftable = (void *)0x0107C7D0;
        m_table = table;
        m_parser = table->registerParser(*name, *label,
            (BfmeParserCallback)0x0041579E, this);
    }
    ~BfmeParserRegistrationVE();

protected:
    void *m_vftable;
    DataChunkInput *m_table;
    UserParser *m_parser;
};

class Rva00352810ParserRegistration : public BfmeParserRegistrationVE
{
public:
    Rva00352810ParserRegistration(void *dataContext, void *localList,
        DataChunkInput *table, AsciiString *labelOverride);

    bool bfmeReadScripts_0035BFB0(DataChunkInput &file, const AsciiString &label);

private:
    void *m_0c;
    void *m_10;
};

Rva00352810ParserRegistration::Rva00352810ParserRegistration(
    void *dataContext, void *localList, DataChunkInput *table,
    AsciiString *labelOverride)
    : BfmeParserRegistrationVE(table,
        (AsciiString *)&AsciiString("PlayerScriptsList"),
        labelOverride ? labelOverride : &AsciiString::TheEmptyString)
{
    Rva00352810ParserRegistration *self = this;
    self->m_0c = dataContext;
    self->m_vftable = (void *)0x010E8538;
    self->m_10 = localList;
}

// Retail 0x0035BFB0: the parse slot this derived vtable (0x010E8538 slot 1)
// routes to through the ILT thunk 0x00035AAD, and the only caller of it,
// 0x001916F0, dispatches through that same vtable slot. It registers the
// nested "ScriptList" parser, parses, and hands the collected lists to the
// pair the constructor took: *m_10 is the count and m_0c the list array.
//
// The address is honest about what the body proves and the retail spelling is
// not guessed: the body is thiscall with two arguments and returns bool, so
// it is NOT the static three-argument ScriptList::ParseScriptsDataChunk the
// naked lift carried (that name mangles to RET 12 and a cdecl frame). The
// callback operand 0x00404877 is SafeDisc-stripped in the baseline image
// (0xCC there), so the parser it names is not identified here either.
struct BfmeScriptListReadInfo
{
    int m_numLists;
    void *m_readLists[32];
};

bool Rva00352810ParserRegistration::bfmeReadScripts_0035BFB0(
    DataChunkInput &file, const AsciiString &label)
{
    {
        AsciiString name("ScriptList");
        file.registerParser(name, label, (BfmeParserCallback)0x00404877, 0);
    }

    BfmeScriptListReadInfo readInfo;
    readInfo.m_numLists = 0;

    if (file.parse(&readInfo)) {
        *(int *)m_10 = readInfo.m_numLists;
        for (int i = 0; i < *(int *)m_10; i++)
            ((void **)m_0c)[i] = readInfo.m_readLists[i];
        return true;
    }

    return false;
}
