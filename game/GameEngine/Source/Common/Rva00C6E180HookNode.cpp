// cl: /O2 /MD
// Insert the static node into the list head: preserve the previous link first.
struct BlockParse;
extern BlockParse *theBlockParseList;
extern void *g_bfmeRva012D7764Node;

void bfmeRva00C6E180InsertStaticNode()
{
    g_bfmeRva012D7764Node = theBlockParseList;
    theBlockParseList = reinterpret_cast<BlockParse *>(&g_bfmeRva012D7764Node);
}
