// Retail 0x00352810: full 153-byte PlayerScriptsList registration ctor.
// Four arguments and RET16; context/list at +0x0C/+0x10. Base vptr0107C7D0
// becomes derived vptr010E8538 after the string temporary is released.
// Literal VA010E8544 identifies the chunk, not the original class name.
// This is not the no-argument SidesList preparation method of the old dump.
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

class Rva00352810ParserRegistration : public BfmeParserRegistrationVE
{
public:
    Rva00352810ParserRegistration(void *dataContext, void *localList,
        DataChunkInput *table, AsciiString *labelOverride);

private:
    void *m_0c;
    void *m_10;
};

Rva00352810ParserRegistration::Rva00352810ParserRegistration(
    void *dataContext, void *localList, DataChunkInput *table,
    AsciiString *labelOverride)
    : BfmeParserRegistrationVE(table,
        (AsciiString *)&AsciiString("PlayerScriptsList"),
        labelOverride ? labelOverride : &AsciiString::TheEmptyString)
{
    Rva00352810ParserRegistration *self = this;
    self->m_0c = dataContext;
    self->m_vftable = (void *)0x010E8538;
    self->m_10 = localList;
}
