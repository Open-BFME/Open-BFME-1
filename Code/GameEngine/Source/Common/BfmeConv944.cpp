// Open-BFME5 conversions.

class BfmeRes944A
{
public:
	virtual void bfmeSlot944R00();
	virtual void bfmeSlot944R01();
	virtual void bfmeSlot944R02();
	virtual void bfmeSlot944R03();
	virtual void bfmeSlot944R04();
	virtual void bfmeSlot944R05();
	virtual void bfmeSlot944R06();
	virtual void bfmeSlot944R07();
	virtual int bfmeVirtA944A();
	virtual int bfmeVirtB944A();
};

class BfmeC944A
{
public:
	virtual void bfmeSlot944C00();
	virtual void bfmeSlot944C01();
	virtual void bfmeSlot944C02();
	virtual void bfmeSlot944C03();
	virtual void bfmeSlot944C04();
	virtual void bfmeSlot944C05();
	virtual void bfmeSlot944C06();
	virtual void bfmeSlot944C07();
	virtual void bfmeSlot944C08();
	virtual void bfmeSlot944C09();
	virtual void bfmeSlot944C10();
	virtual void bfmeSlot944C11();
	virtual void bfmeSlot944C12();
	virtual void bfmeSlot944C13();
	virtual void bfmeSlot944C14();
	virtual void bfmeSlot944C15();
	virtual void bfmeSlot944C16();
	virtual void bfmeSlot944C17();
	virtual void bfmeSlot944C18();
	virtual void bfmeSlot944C19();
	virtual void bfmeSlot944C20();
	virtual void bfmeSlot944C21();
	virtual void bfmeSlot944C22();
	virtual void bfmeSlot944C23();
	virtual void bfmeSlot944C24();
	virtual void bfmeSlot944C25();
	virtual void bfmeSlot944C26();
	virtual void bfmeSlot944C27();
	virtual void bfmeSlot944C28();
	virtual void bfmeSlot944C29();
	virtual void bfmeSlot944C30();
	virtual void bfmeSlot944C31();
	virtual void bfmeSlot944C32();
	virtual void bfmeSlot944C33();
	virtual void bfmeSlot944C34();
	virtual void bfmeSlot944C35();
	virtual void bfmeSlot944C36();
	virtual void bfmeSlot944C37();
	virtual void bfmeSlot944C38();
	virtual void bfmeSlot944C39();
	virtual void bfmeSlot944C40();
	virtual void bfmeSlot944C41();
	virtual void bfmeSlot944C42();
	virtual void bfmeSlot944C43();
	virtual void bfmeSlot944C44();
	virtual void bfmeSlot944C45();
	virtual void bfmeSlot944C46();
	virtual void bfmeSlot944C47();
	virtual void bfmeSlot944C48();
	virtual void bfmeSlot944C49();
	virtual void bfmeSlot944C50();
	virtual void bfmeSlot944C51();
	virtual void bfmeSlot944C52();
	virtual void bfmeSlot944C53();
	virtual void bfmeSlot944C54();
	virtual void bfmeSlot944C55();
	virtual void bfmeSlot944C56();
	virtual void bfmeSlot944C57();
	virtual void bfmeSlot944C58();
	virtual void bfmeSlot944C59();
	virtual void bfmeSlot944C60();
	virtual void bfmeSlot944C61();
	virtual void bfmeSlot944C62();
	virtual void bfmeSlot944C63();
	virtual void bfmeSlot944C64();
	virtual void bfmeSlot944C65();
	virtual void bfmeSlot944C66();
	virtual void bfmeSlot944C67();
	virtual void bfmeSlot944C68();
	virtual void bfmeSlot944C69();
	virtual void bfmeSlot944C70();
	virtual void bfmeSlot944C71();
	virtual void bfmeSlot944C72();
	virtual void bfmeSlot944C73();
	virtual void bfmeSlot944C74();
	virtual void bfmeSlot944C75();
	virtual void bfmeSlot944C76();
	virtual void bfmeSlot944C77();
	virtual void bfmeSlot944C78();
	virtual void bfmeSlot944C79();
	virtual void bfmeSlot944C80();
	virtual BfmeRes944A *bfmeFind944A();
};

struct BfmeB944A
{
	char m_bfmePad[0x204];
	BfmeC944A *m_bfmeC;
};

struct BfmeA944A
{
	char m_bfmePad[0x10];
	BfmeB944A *m_bfmeB;
};

struct BfmeGlob944A
{
	char m_bfmePad[0x3c];
	int m_bfmeBase;
};

extern BfmeGlob944A *g_bfme944Glob;

class BfmeThing944A
{
public:
	int bfmeGo944A();
	char m_bfmePad[0x1c];
	BfmeA944A *m_bfmeA;
	char m_bfmePad2[4];
	int m_bfmeOut;
};

int BfmeThing944A::bfmeGo944A()
{
	BfmeRes944A *r = m_bfmeA->m_bfmeB->m_bfmeC->bfmeFind944A();
	if (!r)
		return -2;
	int base = g_bfme944Glob->m_bfmeBase;
	m_bfmeOut = base + r->bfmeVirtA944A();
	return 0;
}

class BfmeThing944B
{
public:
	int bfmeGo944B();
	char m_bfmePad[0x1c];
	BfmeA944A *m_bfmeA;
	char m_bfmePad2[4];
	int m_bfmeOut;
};

int BfmeThing944B::bfmeGo944B()
{
	BfmeRes944A *r = m_bfmeA->m_bfmeB->m_bfmeC->bfmeFind944A();
	if (!r)
		return -2;
	int base = g_bfme944Glob->m_bfmeBase;
	m_bfmeOut = base + r->bfmeVirtB944A();
	return 0;
}
