// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: BfmeLivingWorldCampaignManager replenish-pair helper at retail
// 0x003B4510 (102B). ILT 0x00040F39. Caller Glo012F1024Item::j_0002d3e4.
// Looks up two GameLogic keys via bfmeFindFGE, then either LivingWorldArmy::
// replenish (flag clear) or findArmy(name)->bfmeApplyPair (flag set).

class AsciiString;

class LivingWorldPlayerArmy;

class LivingWorldArmy
{
public:
	void replenish(LivingWorldPlayerArmy *playerArmy);	// ILT 0x0002C66A
	void bfmeApplyPair(void *a, void *b);			// ILT 0x0001756C -> 0x00365630
};

class BfmeResFGE;

class BfmeGlobFGE
{
public:
	BfmeResFGE *bfmeFindFGE(void *key);			// ILT 0x0004AD0E
};

extern BfmeGlobFGE *g_bfmeGameLogic1294;			// 0x012F0898

class BfmeLivingWorldCampaignManager
{
public:
	void bfmeReplenishPair(void *keyA, void *keyB, void *nameRef, unsigned char useNamed);
	LivingWorldArmy *findArmy(const AsciiString &name);	// ILT 0x00010302
};

// ?bfmeReplenishPair@BfmeLivingWorldCampaignManager@@QAEXPAX00E@Z
void BfmeLivingWorldCampaignManager::bfmeReplenishPair(
	void *keyA, void *keyB, void *nameRef, unsigned char useNamed)
{
	LivingWorldArmy *left =
		(LivingWorldArmy *)g_bfmeGameLogic1294->bfmeFindFGE(keyA);
	LivingWorldPlayerArmy *right =
		(LivingWorldPlayerArmy *)g_bfmeGameLogic1294->bfmeFindFGE(keyB);
	if (!left || !right)
		return;
	if (!useNamed)
	{
		left->replenish(right);
		return;
	}
	LivingWorldArmy *army =
		findArmy(*(const AsciiString *)nameRef);
	if (army)
		army->bfmeApplyPair(left, right);
}
