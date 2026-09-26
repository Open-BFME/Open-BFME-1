// Retail 0x00194050: full 159-byte LibraryMaps parser constructor.
// Matched LibraryMapLists::readDataChunk at 0x00198700 names this constructor
// with four void-pointer arguments through ILT 0x0001ED26 -> 0x00194050.
// The 20-byte scoped parser holds lists at +0x0C and count at +0x10, clears
// *count after installing derived vptr0109C030, and returns with RET16.
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

class LibraryMapsParser : public BfmeParserRegistrationVE
{
public:
    LibraryMapsParser(void *lists, void *count, void *table,
        void *info);

private:
    void *m_lists;
    int *m_count;
};

LibraryMapsParser::LibraryMapsParser(
    void *lists, void *count, void *table, void *info)
    : BfmeParserRegistrationVE((DataChunkInput *)table,
        (AsciiString *)&AsciiString("LibraryMaps"),
        info ? (AsciiString *)info : &AsciiString::TheEmptyString)
{
    LibraryMapsParser *self = this;
    self->m_lists = lists;
    self->m_count = (int *)count;
    self->m_vftable = (void *)0x0109C030;
    *self->m_count = 0;
}
