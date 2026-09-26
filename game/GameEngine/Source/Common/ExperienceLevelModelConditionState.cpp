// The INI `ExperienceLevel` block's `ModelConditionState = ` field callback.
// The block is parsed by 0x00382460 and its 22-entry FieldParse table at
// 0x010EAB48 points that key here, at 0x0037D1A0 (docs/ini_schema.md, read out
// of the exe). The body is the null-guarded forward every INIFieldParseProc of
// this shape uses: the instance owns the sub-parser, and a null instance is
// skipped rather than faulted.
//
// The instance layout is not recovered, so the sub-object it forwards to keeps
// its address-family name.

struct BfmeSubBKC
{
	void bfmeDoBKC(void *what, int flag);
	unsigned char m_bfmeHead[4];
};

struct BfmeThingBKC
{
	unsigned char m_bfmeHead[0x50];
	BfmeSubBKC m_bfmeSub;
};

void parseExperienceLevelModelConditionState(void *one, BfmeThingBKC *two)
{
	if (two != 0)
		two->m_bfmeSub.bfmeDoBKC(one, 0);
}
