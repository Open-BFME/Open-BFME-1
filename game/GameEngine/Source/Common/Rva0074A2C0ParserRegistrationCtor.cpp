// Retail 0x0074A2C0: full 146-byte HeightMapData registration constructor.
// Three stack arguments; context at +0x0C; base vptr 0x0107C7D0 and derived
// vptr 0x01121AF0. No caller names this derived class: retain its address.
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

class Rva0074A2C0ParserRegistration : public BfmeParserRegistrationVE
{
public:
    Rva0074A2C0ParserRegistration(void *context, DataChunkInput *table,
        AsciiString *labelOverride);

private:
    void *m_0c;
};

Rva0074A2C0ParserRegistration::Rva0074A2C0ParserRegistration(
    void *context, DataChunkInput *table, AsciiString *labelOverride)
    : BfmeParserRegistrationVE(table,
        (AsciiString *)&AsciiString("HeightMapData"),
        labelOverride ? labelOverride : &AsciiString::TheEmptyString)
{
    Rva0074A2C0ParserRegistration *self = this;
    self->m_0c = context;
    self->m_vftable = (void *)0x01121AF0;
}
