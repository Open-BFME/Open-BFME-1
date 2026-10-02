// Retail vtable 0x0107C7D0: BfmeParserBindingBaseVE's vftable, i.e.
// ??_7BfmeParserBindingBaseVE@@6B@ (targets/game/reverse/dir32_addresses.csv).
// The declaration carries no C++ name: __identifier spells the retail symbol
// exactly, so the store below references the defining name.
extern "C" unsigned char __identifier("??_7BfmeParserBindingBaseVE@@6B@")[];

void bfmeFreeVE(void *what);

class BfmeSubVE
{
public:
	void bfmeDropVE(void *what);
};

class BfmeThingVE
{
public:
	void *bfmeKillVE(int flags);
	void *m_bfmeVft;
	BfmeSubVE *m_bfmeSub;
	void *m_bfmeWhat;
};

void *BfmeThingVE::bfmeKillVE(int flags)
{
	void *what = m_bfmeWhat;
	BfmeSubVE *sub = m_bfmeSub;
	m_bfmeVft = __identifier("??_7BfmeParserBindingBaseVE@@6B@");
	sub->bfmeDropVE(what);
	if ((flags & 1) != 0)
		bfmeFreeVE(this);
	return this;
}
