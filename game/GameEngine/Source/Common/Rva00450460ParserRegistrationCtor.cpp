// Retail 0x00450460, full 146-byte MPPositionList registration constructor.
// Same registration/lifetime structure as the matched 0x004502D0 witness;
// this derived view adds only the context at +0x0C, not its extra +0x10 field.
// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringbaseascii/Common /Igame/Libraries/Source/WWVegas/WWLib
// The string xref names MPPositionList. Retail writes 0x0107C7D0 during registration and 0x010F5E84 before return. No caller names the derived class, so the class keeps the retail address.

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

class Rva00450460ParserRegistration : public BfmeParserRegistrationVE
{
public:
    Rva00450460ParserRegistration(void *extra, DataChunkInput *table,
        AsciiString *labelOverride);

private:
    void *m_0c;
};

Rva00450460ParserRegistration::Rva00450460ParserRegistration(
    void *extra, DataChunkInput *table, AsciiString *labelOverride)
    : BfmeParserRegistrationVE(table,
        (AsciiString *)&AsciiString("MPPositionList"),
        labelOverride ? labelOverride : &AsciiString::TheEmptyString)
{
    Rva00450460ParserRegistration *self = this;
    self->m_0c = extra;
    self->m_vftable = (void *)0x010F5E84;
}
