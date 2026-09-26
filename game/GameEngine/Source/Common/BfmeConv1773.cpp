extern "C" int _bfmeVftVE[];

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
		m_bfmeVfCO = _bfmeVftVE;

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
