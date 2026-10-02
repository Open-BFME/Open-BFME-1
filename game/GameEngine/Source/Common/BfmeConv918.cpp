// Open-BFME5 conversions.

extern char g_bfme918VftA[];

class BfmeSub918P
{
public:
	void bfmeDtor918P();
};


extern char g_bfme918C[];

void bfmeGo918C(void)
{
	int d = *(int *)(*(char **)g_bfme918C + 4);
	*(char **)(g_bfme918C + d) = g_bfme918VftA;
	((BfmeSub918P *)(g_bfme918C + 4))->bfmeDtor918P();
}
extern char g_bfme918D[];

void bfmeGo918D(void)
{
	int d = *(int *)(*(char **)g_bfme918D + 4);
	*(char **)(g_bfme918D + d) = g_bfme918VftA;
	((BfmeSub918P *)(g_bfme918D + 4))->bfmeDtor918P();
}
