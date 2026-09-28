// cl: /O2 /Ob0 /G6

struct BfmeShapeE15
{
	char m[0x24];
};

extern BfmeShapeE15 g_bfmeBadE15;

class BfmeObjE15
{
public:
	BfmeShapeE15 *bfmeAtE15(int i);
	char m_00[0x2C];
	BfmeShapeE15 *volatile m_start;
	BfmeShapeE15 *m_finish;
};

BfmeShapeE15 *BfmeObjE15::bfmeAtE15(int i)
{
	if (i >= 0)
	{
		if ((unsigned)i < (unsigned)(m_finish - m_start))
			return m_start + i;
	}
	return &g_bfmeBadE15;
}
