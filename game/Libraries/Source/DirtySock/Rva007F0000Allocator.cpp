// DirtySock FESL allocator wrapper at retail RVA 0x007F0000.
// The allocation slot returns its pointer in EAX.
class BfmeS1019
{
public:
	virtual void bfmeVS01019();
	virtual void bfmeVS11019();
	virtual void *bfmeDoB1019(int a, int b);
	virtual void bfmeDoC1019(int a, int b);
};

extern BfmeS1019 *g_bfmeS1019;
extern char g_bfmeName1019[];
void bfmeInit1019(char *n);

void *Rva007F0000Alloc(int a)
{
	if (g_bfmeS1019 == 0)
		bfmeInit1019(g_bfmeName1019);

	return g_bfmeS1019->bfmeDoB1019(a, 0);
}
