// Retail 0x00352AB0: full 153-byte ScriptGroup parser registration ctor.
// Not ScriptGroup::addScript: this is ECX plus four arguments, RET16,
// and two vtable installations on the caller's 20-byte scoped object.
// Caller 0x0035DD40 constructs it via ILT0A759 and tears it down via102610.
// The exact original registration-class spelling remains unknown.
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

class Rva00352AB0ParserRegistration : public BfmeParserRegistrationVE
{
public:
    Rva00352AB0ParserRegistration(void *dataContext, void *localList,
        DataChunkInput *table, AsciiString *labelOverride);

private:
    void *m_0c;
    void *m_10;
};

Rva00352AB0ParserRegistration::Rva00352AB0ParserRegistration(
    void *dataContext, void *localList, DataChunkInput *table,
    AsciiString *labelOverride)
    : BfmeParserRegistrationVE(table,
        (AsciiString *)&AsciiString("ScriptGroup"),
        labelOverride ? labelOverride : &AsciiString::TheEmptyString)
{
    Rva00352AB0ParserRegistration *self = this;
    self->m_0c = dataContext;
    self->m_vftable = (void *)0x010E8580;
    self->m_10 = localList;
}
