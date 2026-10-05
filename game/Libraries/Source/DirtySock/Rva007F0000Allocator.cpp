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

struct Rva007F00B0Allocator;
extern Rva007F00B0Allocator *g_Rva0130A5B0;
extern char g_bfmeName1019[];
void bfmeInit1019(char *n);

void *Rva007F0000Alloc(int a)
{
	if (g_Rva0130A5B0 == 0)
		bfmeInit1019(g_bfmeName1019);

	return ((BfmeS1019 *)g_Rva0130A5B0)->bfmeDoB1019(a, 0);
}
