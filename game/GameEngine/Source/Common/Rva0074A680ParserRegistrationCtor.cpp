// Retail 0x0074A680: 139-byte GlobalLighting scoped parser constructor.
// Two arguments and RET8; only the 12-byte registration base is present.
// Literal VA01121ACC and derived vptr01121B30 distinguish it from the
// neighboring context-bearing constructors. It does not delete triggers.
// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringbaseascii/Common /Igame/Libraries/Source/WWVegas/WWLib

#include "AsciiString.h"

// Retail vtable 0x0107C7D0, pinned as _bfmeVftVE (targets/game/reverse/symbols.csv);
// dir32_addresses.csv also records ??_7BfmeParserBindingBaseVE@@6B@ for the same address.
extern "C" int _bfmeVftVE[];

// Retail 0x0041579E, recorded as ?bfmeChunkParserVE@@YAXXZ
// (game/GameEngine/Source/Common/System/BfmeDataChunkParserBinding.cpp).
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

// Derived vtable 0x01121B30: no symbol in dir32_addresses.csv names it, so it
// stays address-derived.
extern void *g_01121B30[];

class Rva0074A680ParserRegistration : public BfmeParserRegistrationVE
{
public:
    Rva0074A680ParserRegistration(DataChunkInput *table,
        AsciiString *labelOverride);
};

Rva0074A680ParserRegistration::Rva0074A680ParserRegistration(
    DataChunkInput *table, AsciiString *labelOverride)
    : BfmeParserRegistrationVE(table,
        (AsciiString *)&AsciiString("GlobalLighting"),
        labelOverride ? labelOverride : &AsciiString::TheEmptyString)
{
    Rva0074A680ParserRegistration *self = this;
    self->m_vftable = g_01121B30;
}
