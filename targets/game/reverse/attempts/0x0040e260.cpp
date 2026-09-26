// ?bfmeTail923E@BfmeElem923E@@QAEXPAX0@Z
// partial score=0.55 date=2026-09-11
// Clean reconstruction of BfmeElem923E::bfmeTail923E at retail RVA 0x0040E260.
// The caller and the member declaration live in BfmeConv923.cpp; this isolated
// TU keeps the already-matched caller's code generation independent.

class BfmeTailObject923E
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39();
	virtual void slot40();
	virtual void slot41();
	virtual void slot42();
	virtual void slot43();
	virtual void slot44();
	virtual void slot45();
	virtual void slot46();
	virtual void slot47();
	virtual void slot48();
	virtual void slot49();
	virtual void slot50();
	virtual void slot51();
	virtual void slot52();
	virtual void slot53(void *, void *, void *, void *, void *, int, int);
	virtual void slot54();
	virtual void slot55();
};

class BfmeElem923E
{
public:
	__declspec(noinline) void bfmeTail923E(void *thing, void *record);

	void *m_bfme00;
	void *m_bfme04;
	void *m_bfme08;
	void *m_bfme0c;
	void *m_bfme10;
	void *m_bfme14;
};

struct BfmeTailParams923E
{
	void *m_first;
	void *m_second;
	void *m_third;
};

void BfmeElem923E::bfmeTail923E(void *thing, void *record)
{
	if (m_bfme00 == 0 || record != m_bfme14)
		return;
    BfmeTailObject923E *object = (BfmeTailObject923E *)thing;
    BfmeTailParams923E params;
	params.m_first = m_bfme0c;
	params.m_second = m_bfme08;
	params.m_third = m_bfme04;
    object->slot44();
    object->slot53(m_bfme00, params.m_third, params.m_second,
        params.m_first, m_bfme10, -1, 2);
	object->slot55();
}
