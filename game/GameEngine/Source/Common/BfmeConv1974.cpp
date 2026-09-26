struct BfmePairESF
{
	int m_bfmeAESF;
	int m_bfmeBESF;
};

class BfmeAESF;
class BfmeBESF;

class BfmeCESF
{
public:
	unsigned char m_bfmeHeadESF[0xc];
	int m_bfmeKindESF;
};

__forceinline int bfmeKindOkESF(BfmeCESF *c);

class BfmeHostESF
{
public:
	char bfmeTestESF(BfmeAESF *a, BfmeBESF *b);
	char bfmeCheckESF(BfmeAESF *a, BfmePairESF *out);
	BfmeCESF *bfmeFindESF(BfmeBESF *b, int first, int second);
};

char BfmeHostESF::bfmeTestESF(BfmeAESF *a, BfmeBESF *b)
{
	BfmePairESF pair;

	if (bfmeCheckESF(a, &pair))
		return 1;

	BfmeCESF *c = bfmeFindESF(b, pair.m_bfmeAESF, pair.m_bfmeBESF);

	if (c == 0)
		return 1;

	return (char)bfmeKindOkESF(c);
}

__forceinline int bfmeKindOkESF(BfmeCESF *c)
{
	int kind = c->m_bfmeKindESF & 7;

	if (kind == 5 || kind == 1 || kind == 2)
		return 0;

	return 1;
}
