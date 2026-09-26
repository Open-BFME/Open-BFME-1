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

class BfmeScopeCN
{
public:
	BfmeScopeCN(void *owner, BfmeTargetCN *target, void *value);
	~BfmeScopeCN()
	{
		m_bfmeVfCN = _bfmeVftVE;

		m_bfmeInnerCN->bfmeCloseCN(m_bfmeArgCN);
	}

	int *m_bfmeVfCN;
	BfmeInnerCN *m_bfmeInnerCN;
	void *m_bfmeArgCN;
	int m_bfmePadCN;
};

class BfmeOwnCN
{
public:
	char bfmeGuardedCN(BfmeTargetCN *target, void *value);

	unsigned char m_bfmeHeadCN[0xc];
	void *m_bfmeCtxCN;
};

char BfmeOwnCN::bfmeGuardedCN(BfmeTargetCN *target, void *value)
{
	BfmeScopeCN scope(m_bfmeCtxCN, target, value);

	return target->bfmeStepCN(0);
}
