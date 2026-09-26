class BfmeModERK;

class BfmeThingERK
{
public:
	BfmeModERK *bfmeFindERK(int key);
};

class BfmeKeyGenERK
{
public:
	int bfmeNameToKeyERK(const char *name);
};

extern BfmeKeyGenERK *g_bfmeKeyGenERK;

void bfmeDoERK(BfmeThingERK *first, BfmeModERK *firstMod,
	BfmeThingERK *second, BfmeModERK *secondMod);

void bfmeApplyERK(BfmeThingERK *first, BfmeThingERK *second)
{
	static int s_bfmeKeyERK =
		g_bfmeKeyGenERK->bfmeNameToKeyERK("CastleBehavior");

	BfmeModERK *firstMod = first->bfmeFindERK(s_bfmeKeyERK);
	BfmeModERK *secondMod = second->bfmeFindERK(s_bfmeKeyERK);

	bfmeDoERK(first, firstMod, second, secondMod);
}
