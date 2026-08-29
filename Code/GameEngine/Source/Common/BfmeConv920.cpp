// Open-BFME5 conversions.

class BfmeRes920D
{
public:
	virtual void bfmeSlot920D00();
	virtual void bfmeSlot920D01();
	virtual void bfmeSlot920D02();
	virtual void bfmeSlot920D03();
	virtual void bfmeSlot920D04();
	virtual void bfmeSlot920D05();
	virtual void bfmeSlot920D06();
	virtual void bfmeSlot920D07();
	virtual void bfmeSlot920D08();
	virtual void bfmeSlot920D09();
	virtual void bfmeSlot920D10();
	virtual void bfmeSlot920D11();
	virtual void bfmeSlot920D12();
	virtual void bfmeSlot920D13();
	virtual void bfmeSlot920D14();
	virtual void bfmeSlot920D15();
	virtual void bfmeSlot920D16();
	virtual void bfmeSlot920D17();
	virtual void bfmeSlot920D18();
	virtual void bfmeSlot920D19();
	virtual void bfmeSlot920D20();
	virtual void bfmeSlot920D21();
	virtual void bfmeSlot920D22();
	virtual void bfmeSlot920D23();
	virtual void bfmeSlot920D24();
	virtual void bfmeSlot920D25();
	virtual void bfmeSlot920D26();
	virtual void bfmeSlot920D27();
	virtual void bfmeSlot920D28();
	virtual void bfmeSlot920D29();
	virtual void bfmeSlot920D30();
	virtual void bfmeSlot920D31();
	virtual void bfmeSlot920D32();
	virtual void bfmeSlot920D33();
	virtual void bfmeSlot920D34();
	virtual void bfmeSlot920D35();
	virtual void bfmeSlot920D36();
	virtual void bfmeSlot920D37();
	virtual void bfmeSlot920D38();
	virtual void bfmeSlot920D39();
	virtual void bfmeSlot920D40();
	virtual void bfmeSlot920D41();
	virtual void bfmeSlot920D42();
	virtual void bfmeSlot920D43();
	virtual void bfmeSlot920D44();
	virtual void bfmeSlot920D45();
	virtual void bfmeSlot920D46();
	virtual void bfmeSlot920D47();
	virtual void bfmeSlot920D48();
	virtual void bfmeSlot920D49();
	virtual void bfmeSlot920D50();
	virtual void bfmeSlot920D51();
	virtual void bfmeSlot920D52();
	virtual void bfmeSlot920D53();
	virtual void bfmeSlot920D54();
	virtual void bfmeSlot920D55();
	virtual void bfmeSlot920D56();
	virtual void bfmeSlot920D57();
	virtual void bfmeSlot920D58();
	virtual void bfmeSlot920D59();
	virtual void bfmeSlot920D60();
	virtual void bfmeSlot920D61();
	virtual void bfmeSlot920D62();
	virtual void bfmeSlot920D63();
	virtual void bfmeSlot920D64();
	virtual void bfmeSlot920D65();
	virtual void bfmeSlot920D66();
	virtual void bfmeSlot920D67();
	virtual void bfmeSlot920D68();
	virtual void bfmeSlot920D69();
	virtual void bfmeSlot920D70();
	virtual void bfmeSlot920D71();
	virtual void bfmeSlot920D72();
	virtual void bfmeSlot920D73();
	virtual void bfmeSlot920D74();
	virtual void bfmeSlot920D75();
	virtual void bfmeSlot920D76();
	virtual void bfmeSlot920D77();
	virtual void bfmeSlot920D78();
	virtual void bfmeSlot920D79();
	virtual void bfmeSlot920D80();
	virtual void bfmeSlot920D81();
	virtual void bfmeSlot920D82();
	virtual void bfmeSlot920D83();
	virtual void bfmeSlot920D84();
	virtual void bfmeSlot920D85();
	virtual void bfmeSlot920D86();
	virtual void bfmeSlot920D87();
	virtual void bfmeSlot920D88();
	virtual void bfmeSlot920D89();
	virtual void bfmeSlot920D90();
	virtual void bfmeSlot920D91();
	virtual void bfmeSlot920D92();
	virtual void bfmeSlot920D93();
	virtual void bfmeSlot920D94();
	virtual void bfmeVirt920D();
};

class BfmeX920D
{
public:
	BfmeRes920D *bfmeGet920D();
};

struct BfmeSub920D
{
	char m_bfmePad[0x10];
	BfmeX920D *m_bfmeX;
};

class BfmeThing920D
{
public:
	void bfmeGo920D(void *a);
	char m_bfmePad[0x1c];
	BfmeSub920D *m_bfmeSub;
};

void BfmeThing920D::bfmeGo920D(void *a)
{
	BfmeX920D *x = m_bfmeSub->m_bfmeX;
	if (!x)
		return;
	BfmeRes920D *r = x->bfmeGet920D();
	if (!r)
		return;
	r->bfmeVirt920D();
}

class LocomotorTemplate;

class LocomotorTemplateDeleteAccess
{
public:
	static void destroy(LocomotorTemplate *p);
};

class BfmeThing920F
{
public:
	void bfmeGo920F();
	void bfmeOne920F(void (*cb)(LocomotorTemplate *));
	void bfmeTwo920F(void (*cb)(LocomotorTemplate *));
};

void BfmeThing920F::bfmeGo920F()
{
	bfmeOne920F(LocomotorTemplateDeleteAccess::destroy);
	bfmeTwo920F(LocomotorTemplateDeleteAccess::destroy);
}
