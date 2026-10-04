// Retail 0x00352AB0: full 153-byte ScriptGroup parser registration ctor.
// Not ScriptGroup::addScript: this is ECX plus four arguments, RET16,
// and two vtable installations on the caller's 20-byte scoped object.
// Caller 0x0035DD40 constructs it via ILT0A759 and tears it down via102610.
// The exact original registration-class spelling remains unknown.
// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringbaseascii/Common /Igame/Libraries/Source/WWVegas/WWLib

#include "AsciiString.h"

// Retail inlines ~AsciiString: temporaries are released by a direct call to
// StringBase<char>::releaseBuffer (0x00887940), not the ??1AsciiString stub.
inline AsciiString::~AsciiString() { ((StringBase<char> *)this)->releaseBuffer(); }

// Retail vtable 0x0107C7D0, pinned as _bfmeVftVE (targets/game/reverse/symbols.csv).
extern "C" int _bfmeVftVE[];
extern void j_0001579e();

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
            (BfmeParserCallback)j_0001579e, this);
    }
    ~BfmeParserRegistrationVE();

protected:
    void *m_vftable;
    DataChunkInput *m_table;
    UserParser *m_parser;
};

// Derived vtable 0x010E8580: no dir32_addresses.csv symbol names it.
extern void *g_010E8580[];

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
    self->m_vftable = g_010E8580;
    self->m_10 = localList;
}
