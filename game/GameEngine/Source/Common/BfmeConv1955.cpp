class BfmeModERK;

class BfmeThingERK
{
public:
	BfmeModERK *bfmeFindERK(int key);
};

// NameKeyType is an enum, not a typedef of int: retail's mangled callee is
// ?nameToKey@NameKeyGenerator@@QAE?AW4NameKeyType@@PBD@Z (W4 = enum return).
enum NameKeyType
{
	NAMEKEY_INVALID = 0,
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *g_bfmeKeyGenERK;

void bfmeDoERK(BfmeThingERK *first, BfmeModERK *firstMod,
	BfmeThingERK *second, BfmeModERK *secondMod);

void bfmeApplyERK(BfmeThingERK *first, BfmeThingERK *second)
{
	static int s_bfmeKeyERK =
		g_bfmeKeyGenERK->nameToKey("CastleBehavior");

	BfmeModERK *firstMod = first->bfmeFindERK(s_bfmeKeyERK);
	BfmeModERK *secondMod = second->bfmeFindERK(s_bfmeKeyERK);

	bfmeDoERK(first, firstMod, second, secondMod);
}
