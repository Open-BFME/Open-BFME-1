// Open-BFME5 conversions: three-hop member chain predicates and a span helper.

class Bfme5Sub
{
public:
	virtual void bfmeSV0();
	virtual void bfmeSV1();
	virtual void bfmeSV2();
	virtual void bfmeSV3();
	virtual void bfmeSV4();
	virtual void bfmeSV5();
	virtual void bfmeSV6();
	virtual void bfmeSV7();
	virtual void bfmeSV8();
	virtual void bfmeSV9();
	virtual void bfmeSV10();
	virtual void bfmeSV11();
	virtual char bfmeIsA();
	virtual void bfmeSV13();
	virtual char bfmeIsB();
};

class Bfme5Ctx
{
public:
	virtual void bfmeCV0();
	virtual void bfmeCV1();
	virtual void bfmeCV2();
	virtual void bfmeCV3();
	virtual void bfmeCV4();
	virtual void bfmeCV5();
	virtual void bfmeCV6();
	virtual void bfmeCV7();
	virtual void bfmeCV8();
	virtual void bfmeCV9();
	virtual void bfmeCV10();
	virtual void bfmeCV11();
	virtual void bfmeCV12();
	virtual void bfmeCV13();
	virtual void bfmeCV14();
	virtual void bfmeCV15();
	virtual void bfmeCV16();
	virtual void bfmeCV17();
	virtual void bfmeCV18();
	virtual void bfmeCV19();
	virtual void bfmeCV20();
	virtual void bfmeCV21();
	virtual void bfmeCV22();
	virtual void bfmeCV23();
	virtual void bfmeCV24();
	virtual void bfmeCV25();
	virtual void bfmeCV26();
	virtual void bfmeCV27();
	virtual void bfmeCV28();
	virtual void bfmeCV29();
	virtual void bfmeCV30();
	virtual void bfmeCV31();
	virtual void bfmeCV32();
	virtual void bfmeCV33();
	virtual void bfmeCV34();
	virtual void bfmeCV35();
	virtual void bfmeCV36();
	virtual void bfmeCV37();
	virtual void bfmeCV38();
	virtual void bfmeCV39();
	virtual void bfmeCV40();
	virtual void bfmeCV41();
	virtual void bfmeCV42();
	virtual void bfmeCV43();
	virtual void bfmeCV44();
	virtual void bfmeCV45();
	virtual void bfmeCV46();
	virtual void bfmeCV47();
	virtual void bfmeCV48();
	virtual void bfmeCV49();
	virtual void bfmeCV50();
	virtual void bfmeCV51();
	virtual void bfmeCV52();
	virtual void bfmeCV53();
	virtual void bfmeCV54();
	virtual void bfmeCV55();
	virtual void bfmeCV56();
	virtual void bfmeCV57();
	virtual void bfmeCV58();
	virtual void bfmeCV59();
	virtual void bfmeCV60();
	virtual void bfmeCV61();
	virtual void bfmeCV62();
	virtual void bfmeCV63();
	virtual void bfmeCV64();
	virtual void bfmeCV65();
	virtual void bfmeCV66();
	virtual void bfmeCV67();
	virtual void bfmeCV68();
	virtual void bfmeCV69();
	virtual void bfmeCV70();
	virtual void bfmeCV71();
	virtual void bfmeCV72();
	virtual void bfmeCV73();
	virtual void bfmeCV74();
	virtual void bfmeCV75();
	virtual void bfmeCV76();
	virtual void bfmeCV77();
	virtual void bfmeCV78();
	virtual void bfmeCV79();
	virtual void bfmeCV80();
	virtual class Bfme5Sub *bfmeGet();
};

class Bfme5Level { public: char m_bfmePad[0x204]; Bfme5Ctx *m_bfmeCtx; };
class Bfme5Slot { public: char m_bfmePad[0x10]; Bfme5Level *m_bfmeLevel; };
class Bfme5Owner { public: char m_bfmePad[0x1c]; Bfme5Slot *m_bfmeSlot; };

char __cdecl bfme5OwnerIsA(Bfme5Owner *o)
{
	Bfme5Ctx *c = o->m_bfmeSlot->m_bfmeLevel->m_bfmeCtx;
	Bfme5Sub *s;

	if (!c)
		return 0;

	s = c->bfmeGet();

	if (!s)
		return 0;

	if (s->bfmeIsA())
		return 1;

	return 0;
}

char __cdecl bfme5OwnerIsB(Bfme5Owner *o)
{
	Bfme5Ctx *c = o->m_bfmeSlot->m_bfmeLevel->m_bfmeCtx;
	Bfme5Sub *s;

	if (!c)
		return 0;

	s = c->bfmeGet();

	if (!s)
		return 0;

	if (s->bfmeIsB())
		return 1;

	return 0;
}

class Bfme5Span
{
public:
	virtual void bfmeDV0();
	virtual void bfmeDV1();
	virtual void bfmeDV2();
	virtual void bfmeDV3();
	virtual void bfmeDV4();
	virtual void bfmeDV5();
	virtual void bfmeDV6();
	virtual void bfmeDV7();
	virtual void bfmeDV8();
	virtual void bfmeDV9();
	virtual void bfmeDV10();
	virtual void bfmeDV11();
	virtual void bfmeDV12();
	virtual void bfmeDV13();
	virtual void bfmeDV14();
	virtual void bfmeDV15();
	virtual void bfmeDV16();
	virtual void bfmeDV17();
	virtual void bfmeDV18();
	virtual void bfmeDV19();
	virtual void bfmeDV20();
	virtual void bfmeDV21();
	virtual void bfmeDV22();
	virtual void bfmeDV23();
	virtual void bfmeDV24();
	virtual void bfmeDV25();
	virtual void bfmeDV26();
	virtual void bfmeDV27();
	virtual void bfmeDV28();
	virtual void bfmeDV29();
	virtual void bfmeDV30();
	virtual void bfmeDV31();
	virtual void bfmeDV32();
	virtual void bfmeDV33();
	virtual void bfmeDV34();
	virtual void bfmeDV35();
	virtual void bfmeDV36();
	virtual void bfmeDV37();
	virtual void bfmeDV38();
	virtual void bfmeDV39();
	virtual void bfmeDV40();
	virtual void bfmeDV41();
	virtual void bfmeDV42();
	virtual void bfmeDV43();
	virtual void bfmeDV44();
	virtual void bfmeDV45();
	virtual void bfmeDV46();
	virtual void bfmeDV47();
	virtual void bfmeDV48();
	virtual void bfmeDV49();
	virtual void bfmeDV50();
	virtual void bfmeDV51();
	virtual void bfmeDV52();
	virtual void bfmeDV53();
	virtual void bfmeDV54();
	virtual void bfmeDV55();
	virtual void bfmeDV56();
	virtual void bfmeDV57();
	virtual void bfmeDV58();
	virtual void bfmeDV59();
	virtual void bfmeDV60();
	virtual void bfmeDV61();
	virtual void bfmeDV62();
	virtual void bfmeDV63();
	virtual void bfmeDV64();
	virtual void bfmeDV65();
	virtual void bfmeDV66();
	virtual void bfmeDV67();
	virtual void bfmeDV68();
	virtual void bfmeDV69();
	virtual void bfmeDV70();
	virtual void bfmeDV71();
	virtual void bfmeDV72();
	virtual void bfmeDV73();
	virtual void bfmeDV74();
	virtual void bfmeDV75();
	virtual void bfmeDV76();
	virtual void bfmeDV77();
	virtual void bfmeDV78();
	virtual void bfmeDV79();
	virtual void bfmeDV80();
	virtual void bfmeDV81();
	virtual void bfmeDV82();
	virtual void bfmeDV83();
	virtual int bfmeHead(int a);
	virtual int bfmeTail();

	int bfmeLength(void);
};

int Bfme5Span::bfmeLength(void)
{
	return bfmeHead(0) - bfmeTail();
}

