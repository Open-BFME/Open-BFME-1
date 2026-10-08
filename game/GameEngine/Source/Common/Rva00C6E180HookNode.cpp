// cl: /O2 /MD
// Insert the static node into the list head: preserve the previous link first.
//
// The node at VA 0x012D7764 is a 12-byte .data record: the list link
// (0 until this initializer runs), the keyword "LoadSubsystem" (VA
// 0x01141630) and the matched parseSubsystemLegendDefinition callback
// (0x009A16A0). VA 0x012D7770 starts the next recorded datum.
struct BlockParse;
class INI;
extern BlockParse *theBlockParseList;
void parseSubsystemLegendDefinition(INI *ini);

struct Rva012D7764BlockParseNode
{
    void *m_next;
    const char *m_token;
    void (*m_parse)(INI *ini);
};

Rva012D7764BlockParseNode g_bfmeRva012D7764Node = { 0, "LoadSubsystem", parseSubsystemLegendDefinition };

void bfmeRva00C6E180InsertStaticNode()
{
    g_bfmeRva012D7764Node.m_next = theBlockParseList;
    theBlockParseList = reinterpret_cast<BlockParse *>(&g_bfmeRva012D7764Node);
}
