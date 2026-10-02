// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringbaseascii/Common /Igame/Libraries/Source/WWVegas/WWLib
// The string xref names MPPositionInfo. Retail writes 0x0107C7D0 during registration and 0x010F5E78 before return. No caller names the derived class, so the class keeps the retail address.

#include "AsciiString.h"

// Retail vtable 0x0107C7D0: BfmeParserBindingBaseVE's vftable, i.e.
// ??_7BfmeParserBindingBaseVE@@6B@ (targets/game/reverse/dir32_addresses.csv).
// The declaration carries no C++ name: __identifier spells the retail symbol
// exactly, so the store below references the defining name.
extern "C" int __identifier("??_7BfmeParserBindingBaseVE@@6B@")[];

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
        m_vftable = __identifier("??_7BfmeParserBindingBaseVE@@6B@");
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

// Derived vtable 0x010F5E78: no symbol in dir32_addresses.csv names it.
extern void *g_010F5E78[];

class Gen004502D0ParserRegistration : public BfmeParserRegistrationVE
{
public:
    Gen004502D0ParserRegistration(void *extra, DataChunkInput *table,
        AsciiString *labelOverride);

private:
    void *m_0c;
    int m_10;
};

Gen004502D0ParserRegistration::Gen004502D0ParserRegistration(
    void *extra, DataChunkInput *table, AsciiString *labelOverride)
    : BfmeParserRegistrationVE(table,
        (AsciiString *)&AsciiString("MPPositionInfo"),
        labelOverride ? labelOverride : &AsciiString::TheEmptyString)
{
    Gen004502D0ParserRegistration *self = this;
    self->m_0c = extra;
    self->m_vftable = g_010F5E78;
    self->m_10 = 0;
}
