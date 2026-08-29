// Open-BFME5 conversions.

extern char g_bfme918VftA[];
extern char g_bfme918VftB[];
extern char g_bfme918VftC[];

class BfmeSub918P
{
public:
	void bfmeDtor918P();
};

class BfmeSub918Q
{
public:
	void bfmeDtor918Q();
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
extern char g_bfme918E[];

void bfmeGo918E(void)
{
	int d = *(int *)(*(char **)g_bfme918E + 4);
	*(char **)(g_bfme918E + d) = g_bfme918VftB;
	((BfmeSub918Q *)(g_bfme918E + 4))->bfmeDtor918Q();
}
extern char g_bfme918F[];

void bfmeGo918F(void)
{
	int d = *(int *)(*(char **)g_bfme918F + 4);
	*(char **)(g_bfme918F + d) = g_bfme918VftB;
	((BfmeSub918Q *)(g_bfme918F + 4))->bfmeDtor918Q();
}
extern char g_bfme918G[];

void bfmeGo918G(void)
{
	int d = *(int *)(*(char **)g_bfme918G + 4);
	*(char **)(g_bfme918G + d) = g_bfme918VftA;
	((BfmeSub918P *)(g_bfme918G + 4))->bfmeDtor918P();
}
extern char g_bfme918H[];

void bfmeGo918H(void)
{
	int d = *(int *)(*(char **)g_bfme918H + 4);
	*(char **)(g_bfme918H + d) = g_bfme918VftC;
	((BfmeSub918Q *)(g_bfme918H + 8))->bfmeDtor918Q();
}
extern char g_bfme918I[];

void bfmeGo918I(void)
{
	int d = *(int *)(*(char **)g_bfme918I + 4);
	*(char **)(g_bfme918I + d) = g_bfme918VftB;
	((BfmeSub918Q *)(g_bfme918I + 4))->bfmeDtor918Q();
}
