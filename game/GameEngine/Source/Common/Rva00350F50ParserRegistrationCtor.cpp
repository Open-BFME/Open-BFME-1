// Retail 0x00350F50: full 153-byte Script parser registration constructor.
// Not ScriptList::ParseScriptListDataChunk: ECX is a 20-byte scoped local
// with four arguments, two installed vtables, EAX=this, and RET16.
// Caller 0x0035DD40 reaches this via ILT2D9C5 then tears it down via102610.
// The original derived registration-class spelling remains unproved.
// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringbaseascii/Common /Igame/Libraries/Source/WWVegas/WWLib

#include "AsciiString.h"

// Retail inlines ~AsciiString: temporaries are released by a direct call to
// StringBase<char>::releaseBuffer (0x00887940), not the ??1AsciiString stub.
inline AsciiString::~AsciiString() { ((StringBase<char> *)this)->releaseBuffer(); }

class UserParser;
class DataChunkInput;
struct DataChunkInfo;
extern "C" int _bfmeVftVE[];
extern "C" int g_010E84E4[];
extern void j_0001579e();
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
            (BfmeParserCallback)j_0001579e, this);
    }
    ~BfmeParserRegistrationVE();

protected:
    void *m_vftable;
    DataChunkInput *m_table;
    UserParser *m_parser;
};

class Rva00350F50ParserRegistration : public BfmeParserRegistrationVE
{
public:
    Rva00350F50ParserRegistration(void *dataContext, void *localList,
        DataChunkInput *table, AsciiString *labelOverride);

private:
    void *m_0c;
    void *m_10;
};

Rva00350F50ParserRegistration::Rva00350F50ParserRegistration(
    void *dataContext, void *localList, DataChunkInput *table,
    AsciiString *labelOverride)
    : BfmeParserRegistrationVE(table,
        (AsciiString *)&AsciiString("Script"),
        labelOverride ? labelOverride : &AsciiString::TheEmptyString)
{
    Rva00350F50ParserRegistration *self = this;
    self->m_0c = dataContext;
    self->m_vftable = g_010E84E4;
    self->m_10 = localList;
}
