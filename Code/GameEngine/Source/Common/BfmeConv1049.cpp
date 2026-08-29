// Open-BFME5 conversions.

void __stdcall bfmeNote1049(int h, int n);
void bfmeFree1049(void *p);

class BfmeA1049
{
public:
	void bfmeGo1049A(int unused);
	void bfmeStepA1049(void);
	void bfmeStepB1049(void);

	char m_bfmePad[0x44];
	void *m_bfmeP;
	int m_bfmeH;
	char m_bfmePad2[0x58];
	int m_bfmeKind;
};

void BfmeA1049::bfmeGo1049A(int unused)
{
	if (m_bfmeKind == 3)
		bfmeNote1049(m_bfmeH, 3);

	bfmeStepA1049();
	bfmeFree1049(m_bfmeP);
	bfmeStepB1049();
}

