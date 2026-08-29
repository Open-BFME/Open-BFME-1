// ?registerParser@DataChunkInput@@QAEXABVAsciiString@@0P6A_NAAV1@PAUDataChunkInfo@@PAX@Z3@Z
// partial score=0.84 date=2026-08-29
// cl: /DNDEBUG /MD /EHsc
// Open-BFME: DataChunkInput::registerParser, retail 0x00103840.
//
// BFME's UserParser keeps an intrusive previous-link alongside its next
// pointer.  The extra link is why this body allocates 0x1c bytes and why the
// insertion updates both the old head and the list head.

typedef bool Bool;

class DataChunkInput;
struct DataChunkInfo;
typedef Bool (*DataChunkParserPtr)(DataChunkInput &, DataChunkInfo *, void *);

class AsciiString
{
    void *m_data;

public:
    AsciiString(void) : m_data(0) {}
    void set(const AsciiString &stringSrc);
};

class UserParser
{
public:
    virtual void v(void);

    UserParser *next;
    UserParser *previousLink;
    DataChunkParserPtr parser;
    AsciiString label;
    AsciiString parentLabel;
    void *userData;
};

void UserParser::v(void)
{
}

class DataChunkInput
{
    char m_prefix[0x18];
    UserParser *m_parserList;

public:
    void registerParser(const AsciiString &label,
                        const AsciiString &parentLabel,
                        DataChunkParserPtr parser,
                        void *userData);
};

// ?registerParser@DataChunkInput@@QAEXABVAsciiString@@0P6A_NAAV1@PAUDataChunkInfo@@PAX@Z3@Z
void DataChunkInput::registerParser(const AsciiString &label,
                                    const AsciiString &parentLabel,
                                    DataChunkParserPtr parser,
                                    void *userData)
{
    UserParser *p = new UserParser;

    p->label.set(label);
    p->parentLabel.set(parentLabel);
    p->parser = parser;
    p->userData = userData;

    UserParser *next = m_parserList;
    p->next = next;
    if (next != 0)
        next->previousLink = (UserParser *)&p->next;
    p->previousLink = (UserParser *)&m_parserList;
    m_parserList = p;
}
