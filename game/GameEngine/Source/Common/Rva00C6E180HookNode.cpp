// cl: /O2 /MD
// Insert the static node into the list head: preserve the previous link first.
extern void *g_bfmeRva0130CE50Head;
extern void *g_bfmeRva012D7764Node;

void bfmeRva00C6E180InsertStaticNode()
{
    g_bfmeRva012D7764Node = g_bfmeRva0130CE50Head;
    g_bfmeRva0130CE50Head = &g_bfmeRva012D7764Node;
}
