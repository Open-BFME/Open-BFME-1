// Retail vtable 0x0107C7D0: BfmeParserBindingBaseVE's vftable, i.e.
// ??_7BfmeParserBindingBaseVE@@6B@ (targets/game/reverse/dir32_addresses.csv).
// The declaration carries no C++ name: __identifier spells the retail symbol
// exactly, so the store below references the defining name.
extern "C" int __identifier("??_7BfmeParserBindingBaseVE@@6B@")[];

class BfmeTargetCN
{
public:
	char bfmeStepCN(int flag);
};

class BfmeInnerCN
{
public:
	void bfmeCloseCN(void *value);

	int m_bfmeDataCN;
};

class BfmeScopeCO
{
public:
	BfmeScopeCO(void *owner, BfmeTargetCN *target, void *value);
	~BfmeScopeCO()
	{
		m_bfmeVfCO = __identifier("??_7BfmeParserBindingBaseVE@@6B@");

		m_bfmeInnerCO->bfmeCloseCN(m_bfmeArgCO);
	}

	int *m_bfmeVfCO;
	BfmeInnerCN *m_bfmeInnerCO;
	void *m_bfmeArgCO;
	int m_bfmePadCO[2];
};

class BfmeOwnCO
{
public:
	char bfmeGuardedCO(BfmeTargetCN *target, void *value);
};

char BfmeOwnCO::bfmeGuardedCO(BfmeTargetCN *target, void *value)
{
	BfmeScopeCO scope(this, target, value);

	return target->bfmeStepCN(0);
}
