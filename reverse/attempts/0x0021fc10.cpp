// ?bfmeMode2@Gen_0021FC10@@QAEXPAX0H@Z
// partial score=0.76 date=2026-09-04
// cl: /DNDEBUG /MD /EHsc
// Open-BFME6: 0x0021FC10. If the third argument is 2, walk the override at
// *(this-0x24)+4, skip when kind-of bit 0x4000 is set, then two virtuals on
// this-0xC.

class Overridable
{
public:
	const Overridable *getFinalOverride() const;
	void *m_vtable;
	Overridable *m_nextOverride;
};

class BfmeKindOf
{
public:
	unsigned char m_pad[0xD0];
	unsigned int m_kindOf;
};

class BfmeVirtFC10
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual unsigned int virt6c(int);
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual unsigned int virt78(int);
	virtual void slot31() = 0;
	virtual void slot32() = 0;
	virtual void slot33() = 0;
	virtual void slot34() = 0;
	virtual void slot35() = 0;
	virtual void slot36() = 0;
	virtual void slot37() = 0;
	virtual void slot38() = 0;
	virtual void slot39() = 0;
	virtual void slot40() = 0;
	virtual void slot41() = 0;
	virtual void slot42() = 0;
	virtual void slot43() = 0;
	virtual void slot44() = 0;
	virtual void slot45() = 0;
	virtual void slot46() = 0;
	virtual void slot47() = 0;
	virtual void slot48() = 0;
	virtual void slot49() = 0;
	virtual void slot50() = 0;
	virtual void slot51() = 0;
	virtual void slot52() = 0;
	virtual void slot53() = 0;
	virtual void slot54() = 0;
	virtual void slot55() = 0;
	virtual void slot56() = 0;
	virtual void slot57() = 0;
	virtual void slot58() = 0;
	virtual void slot59() = 0;
	virtual void slot60() = 0;
	virtual void slot61() = 0;
	virtual void slot62() = 0;
	virtual void slot63() = 0;
	virtual unsigned int virt100(int);
};

class Gen_0021FC10
{
public:
	void bfmeMode2(void *a, void *b, int mode);
};

// ?bfmeMode2@Gen_0021FC10@@QAEXPAX0H@Z
void Gen_0021FC10::bfmeMode2(void *a, void *b, int mode)
{
	if (mode != 2)
		return;
	Overridable *ovr = *(Overridable **)(4 + (unsigned)*(void **)((char *)this - 0x24));
	if (ovr != 0 && ovr->m_nextOverride != 0)
		ovr = (Overridable *)ovr->m_nextOverride->getFinalOverride();
	if ((((BfmeKindOf *)ovr)->m_kindOf & 0x4000) != 0)
		return;
	BfmeVirtFC10 *v = (BfmeVirtFC10 *)((char *)this - 0xC);
	if (v->virt100(0) <= 0)
		return;
	v->virt78(2);
	v->virt6c(2);
}
