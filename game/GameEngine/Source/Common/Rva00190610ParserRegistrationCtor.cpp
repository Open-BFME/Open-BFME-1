// Retail 0x00190610: 146-byte PolygonTriggers parser constructor.
// Three args (context/table/label); context at +0x0C; RET12 at 0x0019069F.
// Literal VA0109BF28 and derived vptr0109BFB0 identify the chunk and view,
// but do not establish the original class name. Base vptr is 0107C7D0.
// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringbaseascii/Common /Igame/Libraries/Source/WWVegas/WWLib

#include "AsciiString.h"

// Retail vtable 0x0107C7D0, pinned as _bfmeVftVE (targets/game/reverse/symbols.csv).
extern "C" int _bfmeVftVE[];

// Retail 0x0041579E, recorded as ?bfmeChunkParserVE@@YAXXZ.
extern void __cdecl bfmeChunkParserVE(void);

class UserParser;
class DataChunkInput;
struct DataChunkInfo;
typedef bool (*BfmeParserCallback)(DataChunkInput &, DataChunkInfo *, void *);

class DataChunkInput
{
public:
    UserParser *registerParser(const AsciiString &name, const AsciiString &label,
        BfmeParserCallback callback, void *userData);
};

class BfmeParserRegistrationVE
{
public:
    BfmeParserRegistrationVE(DataChunkInput *table, AsciiString *name,
        AsciiString *label)
    {
        m_vftable = _bfmeVftVE;
        m_table = table;
        m_parser = table->registerParser(*name, *label,
            (BfmeParserCallback)bfmeChunkParserVE, this);
    }
    ~BfmeParserRegistrationVE();

protected:
    void *m_vftable;
    DataChunkInput *m_table;
    UserParser *m_parser;
};

// Derived vtable 0x0109BFB0: no symbol in dir32_addresses.csv names it.
extern void *g_0109BFB0[];

class Rva00190610ParserRegistration : public BfmeParserRegistrationVE
{
public:
    Rva00190610ParserRegistration(void *context, DataChunkInput *table,
        AsciiString *labelOverride);

private:
    void *m_0c;
};

Rva00190610ParserRegistration::Rva00190610ParserRegistration(
    void *context, DataChunkInput *table, AsciiString *labelOverride)
    : BfmeParserRegistrationVE(table,
        (AsciiString *)&AsciiString("PolygonTriggers"),
        labelOverride ? labelOverride : &AsciiString::TheEmptyString)
{
    Rva00190610ParserRegistration *self = this;
    self->m_0c = context;
    self->m_vftable = g_0109BFB0;
}
