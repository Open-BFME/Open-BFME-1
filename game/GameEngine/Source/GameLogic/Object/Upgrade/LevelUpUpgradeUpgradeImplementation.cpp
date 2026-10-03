// LevelUpUpgrade::upgradeImplementation at retail 0x002D6050: slot 9 of the UpgradeMux table
// 0x010CCE50, reached only through ILT 0x00030C9C. LevelUpUpgrade's registered
// constructor 0x002D5F10 stores that table. Evidence:
// targets/game/reverse/identity_evidence/upgrademux-slot9-upgradeimplementation.md
class BfmeCZD
{
public:
	void bfmeDoZD(int value, int flag, int spare);

	unsigned char m_bfmeHeadZD[0x28];
	int m_bfmeBaseZD;
};

// RVA 0x0004A12E is retail's five-byte ILT thunk into the body at 0x005B2A10
// that this call reaches; `?j_0004a12e@@YAXXZ` is the only definition of that
// address in the ledger. Naming the thunk keeps the reference resolvable at
// link time and reproduces retail's call rel32.
extern void j_0004a12e();

static __forceinline void bfmeDoZD(BfmeCZD *c, int value, int flag, int spare)
{
	union
	{
		void (*raw)();
		void (BfmeCZD::*member)(int, int, int);
	} call;

	call.raw = j_0004a12e;
	(c->*call.member)(value, flag, spare);
}

class BfmeBZD
{
public:
	unsigned char m_bfmeHeadZD[0x210];
	BfmeCZD *m_bfmeCZD;
};

class BfmeAZD
{
public:
	unsigned char m_bfmeHeadZD[0x70];
	int m_bfmeFirstZD;
	int m_bfmeSecondZD;
};

class LevelUpUpgrade
{
protected:
	virtual void upgradeImplementation();
};

void LevelUpUpgrade::upgradeImplementation()
{
	BfmeAZD *a = *(BfmeAZD **)((char *)this - 0xc);
	BfmeBZD *b = *(BfmeBZD **)((char *)this - 8);
	BfmeCZD *c = b->m_bfmeCZD;

	int first = a->m_bfmeFirstZD;
	int second = a->m_bfmeSecondZD - c->m_bfmeBaseZD;
	const int &value = first < second ? first : second;

	if (value >= 1)
		bfmeDoZD(c, value, 1, 0);
}
