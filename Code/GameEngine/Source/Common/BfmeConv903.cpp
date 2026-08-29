// Open-BFME5 conversions.

struct BfmeThingLB
{
	char m_bfmePad[0x18];
	char m_bfmeFlag;
};

class BfmeOwnerLB
{
public:
	bool bfmeTestLB(BfmeThingLB *b);
};

int bfmeGoLB(BfmeOwnerLB *a, BfmeThingLB *b)
{
	if (a->bfmeTestLB(b)) {
		b->m_bfmeFlag = 1;
		return 0;
	}
	return 1;
}

struct BfmeNodeLC;

struct BfmeNodeLC
{
	char m_bfmePad[0xc];
	unsigned int m_bfmeBits;
	char m_bfmePad2[4];
	BfmeNodeLC *m_bfmeLink;
};

class BfmeKeyLC
{
public:
	BfmeNodeLC *bfmeFindLC();
};

void bfmeGoLC(BfmeKeyLC *k, unsigned int mask)
{
	if (k) {
		BfmeNodeLC *o = k->bfmeFindLC();
		if (o) {
			unsigned int m = mask;
			o->m_bfmeBits = o->m_bfmeBits | m;
			BfmeNodeLC *p = o->m_bfmeLink;
			if (p)
				p->m_bfmeBits = o->m_bfmeBits;
		}
	}
}

void bfmeGoLD(BfmeKeyLC *k, unsigned int mask)
{
	if (k) {
		BfmeNodeLC *o = k->bfmeFindLC();
		if (o) {
			unsigned int m = ~mask;
			o->m_bfmeBits = o->m_bfmeBits & m;
			BfmeNodeLC *p = o->m_bfmeLink;
			if (p)
				p->m_bfmeBits = o->m_bfmeBits;
		}
	}
}

class BfmeGlobLE
{
public:
	virtual void bfmeSlotLE00();
	virtual void bfmeSlotLE01();
	virtual void bfmeSlotLE02();
	virtual void bfmeSlotLE03();
	virtual void bfmeSlotLE04();
	virtual void bfmeSlotLE05();
	virtual void bfmeSlotLE06();
	virtual void bfmeSlotLE07();
	virtual void bfmeSlotLE08();
	virtual void bfmeSlotLE09();
	virtual void bfmeSlotLE10();
	virtual void bfmeSlotLE11();
	virtual void bfmeSlotLE12();
	virtual void bfmeSlotLE13();
	virtual void bfmeSlotLE14();
	virtual void bfmeSlotLE15();
	virtual void bfmeSlotLE16();
	virtual void bfmeActLE(int f);
	virtual void bfmeSlotLE18();
	virtual void bfmeSlotLE19();
	virtual void bfmeSlotLE20();
	virtual void bfmeSlotLE21();
	virtual void bfmeSlotLE22();
	virtual void bfmeSlotLE23();
	virtual void bfmeSlotLE24();
	virtual void bfmeSlotLE25();
	virtual void bfmeSlotLE26();
	virtual void bfmeSlotLE27();
	virtual void bfmeSlotLE28();
	virtual void bfmeSlotLE29();
	virtual void bfmeSlotLE30();
	virtual void bfmeSlotLE31();
	virtual void bfmeSlotLE32();
	virtual void bfmeSlotLE33();
	virtual void bfmeSlotLE34();
	virtual void bfmeSlotLE35();
	virtual void bfmeSlotLE36();
	virtual void bfmeSlotLE37();
	virtual void bfmeSlotLE38();
	virtual void bfmeSlotLE39();
	virtual void bfmeSlotLE40();
	virtual void bfmeSlotLE41();
	virtual void bfmeSlotLE42();
	virtual void bfmeSlotLE43();
	virtual void bfmeSlotLE44();
	virtual void bfmeSlotLE45();
	virtual bool bfmeCheckLE();
};

extern BfmeGlobLE *g_bfmeGlobLE;

void bfmeGoLE(void)
{
	if (g_bfmeGlobLE && g_bfmeGlobLE->bfmeCheckLE())
		g_bfmeGlobLE->bfmeActLE(1);
}

class BfmeGlobLF
{
public:
	bool bfmeTwoLF();
};

extern BfmeGlobLF *g_bfmeGlobLF;

void bfmeOneLF(void);
void bfmeThreeLF(void);
void bfmeFourLF(void);

void bfmeGoLF(void)
{
	bfmeOneLF();
	if (g_bfmeGlobLF && !g_bfmeGlobLF->bfmeTwoLF())
		bfmeThreeLF();
	else
		bfmeFourLF();
}
