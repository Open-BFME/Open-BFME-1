// Open-BFME5 conversions.

class BfmeTexVGR
{
public:
	void bfmeReleaseVGR();
	int m_bfme00;
	unsigned short m_bfmeRefs;
};

struct BfmeTexBufVGR
{
	char m_bfmePad[8];
	BfmeTexVGR **m_bfmeArray;
};

class BfmeMeshVGR
{
public:
	BfmeTexBufVGR *bfmeGetArrVGR(int pass, int stage, bool grow);
	void bfmeSetVGR(int index, BfmeTexVGR **src, int pass, int stage);
};

void BfmeMeshVGR::bfmeSetVGR(int index, BfmeTexVGR **src, int pass, int stage)
{
	BfmeTexVGR **p = &bfmeGetArrVGR(pass, stage, true)->m_bfmeArray[index];
	if (*src)
		(*src)->m_bfmeRefs++;
	if (*p)
		(*p)->bfmeReleaseVGR();
	*p = *src;
}
