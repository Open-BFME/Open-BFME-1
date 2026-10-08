// Retail vtable 0x0107C7D0: BfmeParserBindingBaseVE's vftable, i.e.
// ??_7BfmeParserBindingBaseVE@@6B@ (targets/game/reverse/dir32_addresses.csv).
// The declaration carries no C++ name: __identifier spells the retail symbol
// exactly, so the store below references the defining name.
extern "C" unsigned char __identifier("??_7BfmeParserBindingBaseVE@@6B@")[];

// retail ILT 0x0000871A -> 0x00102610 is the matched
// Q1Forwardee0000871A::handle row; 0x00881EB0 is operator delete
class Q1Forwardee0000871A
{
public:
	void handle(int value);
};

class BfmeSubVE;

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
	((Q1Forwardee0000871A *)sub)->handle((int)what);
	if ((flags & 1) != 0)
		operator delete(this);
	return this;
}
