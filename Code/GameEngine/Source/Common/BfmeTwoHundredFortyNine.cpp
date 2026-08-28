// cl: /Od
// Which of four groups a kind belongs to. The kind is read afresh for every
// comparison, so this one was built without optimisation.

struct BfmeThingOL
{
	unsigned char m_bfmeHead[0xcc];		// 0x000
	int m_bfmeKind;				// 0x0cc
};

int bfmeGroupOL(const BfmeThingOL *what)
{
	if (what->m_bfmeKind == 2 || what->m_bfmeKind == 3)
		return 2;

	if (what->m_bfmeKind == 1 || what->m_bfmeKind == 7)
		return 1;

	if (what->m_bfmeKind == 4 || what->m_bfmeKind == 5)
		return 3;

	return 4;
}
