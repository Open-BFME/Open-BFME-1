// Open-BFME5 conversions.

class BfmeStrVSG
{
public:
	void bfmeSetVSG(const char *text, int length);
	char *m_bfme00;
};

class BfmeCreditsVSG
{
public:
	void bfmeInitVSG();
	void bfmeNextVSG();
	char m_bfmePad000[0x27c];
	BfmeStrVSG m_bfme27c;
};

void BfmeCreditsVSG::bfmeInitVSG()
{
	m_bfme27c.bfmeSetVSG("CreditsMenu", 11);
	bfmeNextVSG();
}
