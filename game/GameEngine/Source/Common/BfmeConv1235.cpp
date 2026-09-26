// Open-BFME5 conversions.

class BfmeQ1235
{
public:
	int m_bfme00;
	int m_bfme04;
};

class BfmeN1235
{
public:
	void bfmeDo1235(void *a, void *b);
	unsigned m_bfme00;
	unsigned m_bfme04;
	char m_bfmePad08[0x50 - 0x08];
	BfmeQ1235 *m_bfme50;
	char m_bfmePad54[4];
	BfmeN1235 *m_bfme58;
};

class BfmeR1235
{
public:
	BfmeN1235 *m_bfme00;
	char m_bfmePad04[0x58 - 0x04];
	BfmeN1235 *m_bfme58;
};

class BfmeH1235
{
public:
	void bfmeWalk1235(void *a, void *b);
	BfmeR1235 **m_bfme00;
};

void BfmeH1235::bfmeWalk1235(void *a, void *b)
{
	BfmeN1235 *p;

	for (p = (*m_bfme00)->m_bfme58; p; p = p->m_bfme58) {
		if (!((unsigned char)(~(p->m_bfme04 >> 15)) & 1) && (p->m_bfme04 & 0x3f) != 0x13
			&& p->m_bfme50->m_bfme04 < 0)
			p->bfmeDo1235(a, b);
	}
}
