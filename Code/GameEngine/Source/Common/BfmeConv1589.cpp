// Open-BFME5 conversions.

class BfmeStrVSO
{
public:
	BfmeStrVSO(const BfmeStrVSO &other);
	~BfmeStrVSO();
	void bfmeAssignVSO(const BfmeStrVSO &other);
	char *m_bfme00;
};

class BfmeSrcVSO
{
public:
	BfmeStrVSO bfmeMakeVSO();
};

void bfmeApplyVSO(BfmeSrcVSO *src, int unused, BfmeStrVSO *out)
{
	out->bfmeAssignVSO(src->bfmeMakeVSO());
}
