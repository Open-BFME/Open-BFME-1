// Retail 0x0074A4A0: full 146-byte BlendTileData registration constructor.
// Three stack arguments; context at +0x0C; base vptr 0x0107C7D0 and derived
// vptr 0x01121B08. No caller names this derived class: retain its address.
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

// Derived vtable 0x01121B08: no symbol in dir32_addresses.csv names it, so it
// stays address-derived.
extern void *g_01121B08[];

class Rva0074A4A0ParserRegistration : public BfmeParserRegistrationVE
{
public:
    Rva0074A4A0ParserRegistration(void *context, DataChunkInput *table,
        AsciiString *labelOverride);

private:
    void *m_0c;
};

Rva0074A4A0ParserRegistration::Rva0074A4A0ParserRegistration(
    void *context, DataChunkInput *table, AsciiString *labelOverride)
    : BfmeParserRegistrationVE(table,
        (AsciiString *)&AsciiString("BlendTileData"),
        labelOverride ? labelOverride : &AsciiString::TheEmptyString)
{
    Rva0074A4A0ParserRegistration *self = this;
    self->m_0c = context;
    self->m_vftable = g_01121B08;
}
