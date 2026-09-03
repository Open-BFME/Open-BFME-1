// Open-BFME5 conversions.

class BfmeStrVSH
{
public:
	void bfmeSetVSH(const char *text, int length);
	void bfmeAssignVSH(const BfmeStrVSH &other);
	char *m_bfme00;
};

class BfmeSrcVSH
{
public:
	char m_bfmePad00[0x50];
	BfmeStrVSH m_bfme50;
};

class BfmeCfgVSH
{
public:
	void bfmeApplyVSH(BfmeSrcVSH *src);
	void bfmeStep1VSH(BfmeSrcVSH *src);
	void bfmeStep2VSH(BfmeSrcVSH *src);
	void bfmeStep3VSH(BfmeSrcVSH *src);
	void bfmeStep4VSH(BfmeSrcVSH *src);
	void bfmeStep5VSH(BfmeSrcVSH *src);
	BfmeStrVSH m_bfme00;
};

void BfmeCfgVSH::bfmeApplyVSH(BfmeSrcVSH *src)
{
	if (src != 0)
		m_bfme00.bfmeAssignVSH(src->m_bfme50);
	else
		m_bfme00.bfmeSetVSH("", 0);

	bfmeStep1VSH(src);
	bfmeStep2VSH(src);
	bfmeStep3VSH(src);
	bfmeStep4VSH(src);
	bfmeStep5VSH(src);
}
