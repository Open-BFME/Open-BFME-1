// Retail 0x00190E10: full 135-byte polygon-parser constructor.
// Calls the matched 16-byte 0x00190610 parser base with context VA012EF41C;
// adds two fields, installs vptr0109BFBC, and clears the global polygon list.
// The list head/counter/dirty sequence is also matched at 0x0018EE40.
// The exact original derived name is unknown; keep the address-labelled view.
// cl: /DNDEBUG /MD /EHsc
class DataChunkInput;
class AsciiString;
class Rva00190610ParserRegistration
{
public:
    Rva00190610ParserRegistration(void *, DataChunkInput *, AsciiString *);
    ~Rva00190610ParserRegistration();
protected:
    void *m_vptr;
    void *m_table;
    void *m_parser;
    void *m_context;
};

class PolygonTrigger
{
public:
    virtual ~PolygonTrigger();
};
struct BfmePolygonTriggerTable { PolygonTrigger *head; };
extern "C" BfmePolygonTriggerTable *g_bfmePolygonTriggerTable;
extern int g_bfmeBFAE;
extern unsigned int g_bfmeDirtyBG;

class Rva00190E10PolygonParser : public Rva00190610ParserRegistration
{
public:
    Rva00190E10PolygonParser(DataChunkInput *, AsciiString *);
private:
    void *m_10;
    int m_14;
};

Rva00190E10PolygonParser::Rva00190E10PolygonParser(
    DataChunkInput *table, AsciiString *label)
    : Rva00190610ParserRegistration((void *)0x012EF41C, table, label)
{
    m_vptr = (void *)0x0109BFBC;
    m_10 = (void *)0x012EF41C;
    m_14 = 0;
    PolygonTrigger *old = g_bfmePolygonTriggerTable->head;
    g_bfmePolygonTriggerTable->head = 0;
    g_bfmeBFAE = 1;
    delete old;
    g_bfmeDirtyBG |= 1;
}
