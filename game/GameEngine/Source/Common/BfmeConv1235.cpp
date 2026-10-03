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

class Gen_008D2C80 { public: void bfmePush(void); };
class BfmeThingDXH { public: void bfmeGoDXH(void *a); };
class BfmeA1210 { public: void bfmePop1210(void); };
class BfmeThingXS { public: void bfmeApplyXS(void *what, void *sub); };
class Rva008A0F20Header { public: int isKind11(void) const; };

void BfmeN1235::bfmeDo1235(void *a, void *b)
{
	if ((m_bfme04 & 0x3f) == 0x13 && !((unsigned char)~(m_bfme04 >> 15) & 1))
		return;

	BfmeQ1235 *q = m_bfme50;

	((Gen_008D2C80 *)a)->bfmePush();
	((BfmeThingDXH *)a)->bfmeGoDXH((char *)this + 0x10);

	if ((m_bfme04 & 0x3f) == 0xd && !((unsigned char)~(m_bfme04 >> 15) & 1)) {
		((BfmeH1235 *)((char *)m_bfme50 + 0x24))->bfmeWalk1235(a, b);
		((BfmeA1210 *)a)->bfmePop1210();
		return;
	}
	if ((m_bfme04 & 0x3f) == 0x12 && !((unsigned char)~(m_bfme04 >> 15) & 1)) {
		((BfmeH1235 *)((char *)m_bfme50 + 0x24))->bfmeWalk1235(a, b);
		((BfmeA1210 *)a)->bfmePop1210();
		return;
	}
	if ((m_bfme04 & 0x3f) == 0xe && !((unsigned char)~(m_bfme04 >> 15) & 1)) {
		((BfmeH1235 *)((char *)m_bfme50 + 0x20))->bfmeWalk1235(a, b);
		((BfmeA1210 *)a)->bfmePop1210();
		return;
	}
	if ((m_bfme04 & 0x3f) == 0xf && !((unsigned char)~(m_bfme04 >> 15) & 1)) {
		((BfmeThingXS *)a)->bfmeApplyXS(b, (char *)m_bfme50 + 0x50);
		((BfmeA1210 *)a)->bfmePop1210();
		return;
	}

	if (!(unsigned char)((Rva008A0F20Header *)this)->isKind11()) {
		int *p = *(int **)((char *)q + 0xc);
		switch (*p) {
		case 1:
			((BfmeThingXS *)a)->bfmeApplyXS(b, (char *)p + 8);
			break;
		case 10:
			((BfmeThingXS *)a)->bfmeApplyXS(b, (char *)p + 8);
			break;
		}
	}
	((BfmeA1210 *)a)->bfmePop1210();
}
