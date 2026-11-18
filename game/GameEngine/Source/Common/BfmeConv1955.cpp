class BfmeModERK;

class BfmeThingERK
{
public:
	BfmeModERK *bfmeFindERK(int key);
};

// NameKeyType is an enum, not a typedef of int: retail's mangled callee is
// ?nameToKey@NameKeyGenerator@@QAE?AW4NameKeyType@@PBD@Z (W4 = enum return).
#include "../../Include/Common/NameKeyType.h"




class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

void bfmeDoERK(BfmeThingERK *first, BfmeModERK *firstMod,
	BfmeThingERK *second, BfmeModERK *secondMod);

void bfmeApplyERK(BfmeThingERK *first, BfmeThingERK *second)
{
	static int s_bfmeKeyERK =
		TheNameKeyGenerator->nameToKey("CastleBehavior");

	BfmeModERK *firstMod = first->bfmeFindERK(s_bfmeKeyERK);
	BfmeModERK *secondMod = second->bfmeFindERK(s_bfmeKeyERK);

	bfmeDoERK(first, firstMod, second, secondMod);
}
