// Open-BFME5 conversions.

// The ledger pins bfmeSetVGR's second parameter as PAVBfmeTexVGR, so that
// element spelling stays.  The release it performs is the shared
// counted-texture base leaf ?Release_Ref@TextureBaseClass@@QAEXXZ
// (0x009EB7A0), which retail calls out of line.
class BfmeTexVGR
{
public:
	int m_bfme00;
	unsigned short m_bfmeRefs;
};

class TextureBaseClass
{
public:
	void Release_Ref();
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
		((TextureBaseClass *)*p)->Release_Ref();
	*p = *src;
}
