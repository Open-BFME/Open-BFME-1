// Retail 0x00088F50: 146-byte ObjectsList scoped parser constructor.
// The literal VA0107C7B8 identifies the chunk, not the derived class name.
// Context is the first of three arguments and occupies +0x0C; RET12.
// Base vptr0107C7D0 is replaced by derived vptr0107C810 after registration.
// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringbaseascii/Common /Igame/Libraries/Source/WWVegas/WWLib

#include "AsciiString.h"

// Retail inlines ~AsciiString: temporaries are released by a direct call to
// StringBase<char>::releaseBuffer (0x00887940), not the ??1AsciiString stub.
inline AsciiString::~AsciiString() { ((StringBase<char> *)this)->releaseBuffer(); }

// Retail vtable 0x0107C7D0, pinned as _bfmeVftVE (targets/game/reverse/symbols.csv).
extern "C" int _bfmeVftVE[];

class UserParser;
class DataChunkInput;
struct DataChunkInfo;
typedef bool (*BfmeParserCallback)(DataChunkInput &, DataChunkInfo *, void *);
void j_0001579e();

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

// Two retail dispatch cells; the next zero dword is outside this array.
extern void *g_0107C810[2];
void j_000309d6();
void j_000167e8();
extern "C" void *__identifier("?g_0107C810@@3PAPAXA")[2] =
{
    (void *)j_000309d6, (void *)j_000167e8
};

class Rva00088F50ParserRegistration : public BfmeParserRegistrationVE
{
public:
    Rva00088F50ParserRegistration(void *extra, DataChunkInput *table,
        AsciiString *labelOverride);

private:
    void *m_0c;
};

Rva00088F50ParserRegistration::Rva00088F50ParserRegistration(
    void *extra, DataChunkInput *table, AsciiString *labelOverride)
    : BfmeParserRegistrationVE(table,
        (AsciiString *)&AsciiString("ObjectsList"),
        labelOverride ? labelOverride : &AsciiString::TheEmptyString)
{
    Rva00088F50ParserRegistration *self = this;
    self->m_0c = extra;
    self->m_vftable = g_0107C810;
}
