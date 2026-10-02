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
		c->bfmeDoZD(value, 1, 0);
}
