class BfmeWinYH
{
public:
	virtual void bfmeW000YH();
	virtual void bfmeW001YH();
	virtual void bfmeW002YH();
	virtual void bfmeW003YH();
	virtual void bfmeW004YH();
	virtual void bfmeW005YH();
	virtual void bfmeW006YH();
	virtual void bfmeW007YH();
	virtual void bfmeW008YH();
	virtual void bfmeW009YH();
	virtual void bfmeW010YH();
	virtual void bfmeW011YH();
	virtual void bfmeW012YH();
	virtual void bfmeW013YH();
	virtual void bfmeW014YH();
	virtual void bfmeW015YH();
	virtual void bfmeW016YH();
	virtual void bfmeW017YH();
	virtual void bfmeW018YH();
	virtual void bfmeW019YH();
	virtual void bfmeW020YH();
	virtual void bfmeW021YH();
	virtual void bfmeW022YH();
	virtual void bfmeW023YH();
	virtual void bfmeW024YH();
	virtual void bfmeW025YH();
	virtual void bfmeW026YH();
	virtual void bfmeW027YH();
	virtual void bfmeW028YH();
	virtual void bfmeW029YH();
	virtual void bfmeW030YH();
	virtual void bfmeW031YH();
	virtual void bfmeW032YH();
	virtual void bfmeW033YH();
	virtual void bfmeW034YH();
	virtual void bfmeW035YH();
	virtual void bfmeW036YH();
	virtual void bfmeW037YH();
	virtual void bfmeW038YH();
	virtual void bfmeW039YH();
	virtual void bfmeW040YH();
	virtual void bfmeW041YH();
	virtual void bfmeW042YH();
	virtual void bfmeW043YH();
	virtual void bfmeW044YH();
	virtual void bfmeW045YH();
	virtual void bfmeW046YH();
	virtual void bfmeW047YH();
	virtual void bfmeW048YH();
	virtual void bfmeW049YH();
	virtual void bfmeW050YH();
	virtual void bfmeW051YH();
	virtual void bfmeW052YH();
	virtual void bfmeW053YH();
	virtual void bfmeW054YH();
	virtual void bfmeW055YH();
	virtual void bfmeW056YH();
	virtual void bfmeW057YH();
	virtual void bfmeW058YH();
	virtual void bfmeW059YH();
	virtual void bfmeW060YH();
	virtual void bfmeW061YH();
	virtual void bfmeW062YH();
	virtual void bfmeW063YH();
	virtual void bfmeW064YH();
	virtual void bfmeW065YH();
	virtual void bfmeW066YH();
	virtual void bfmeW067YH();
	virtual void bfmeW068YH();
	virtual void bfmeW069YH();
	virtual void bfmeW070YH();
	virtual void bfmeW071YH();
	virtual void bfmeW072YH();
	virtual void bfmeW073YH();
	virtual void bfmeW074YH();
	virtual void bfmeW075YH();
	virtual void bfmeW076YH();
	virtual void bfmeW077YH();
	virtual void bfmeW078YH();
	virtual void bfmeW079YH();
	virtual void bfmeW080YH();
	virtual void bfmeW081YH();
	virtual void bfmeW082YH();
	virtual void bfmeW083YH();
	virtual void bfmeW084YH();
	virtual void bfmeW085YH();
	virtual void bfmeW086YH();
	virtual void bfmeW087YH();
	virtual void bfmeW088YH();
	virtual void bfmeW089YH();
	virtual void bfmeW090YH();
	virtual void bfmeW091YH();
	virtual void bfmeW092YH();
	virtual void bfmeW093YH();
	virtual void bfmeW094YH();
	virtual void bfmeW095YH();
	virtual void bfmeW096YH();
	virtual void bfmeW097YH();
	virtual void bfmeW098YH();
	virtual void bfmeW099YH();
	virtual void bfmeW100YH();
	virtual void bfmeW101YH();
	virtual void bfmeW102YH();
	virtual void bfmeW103YH();
	virtual void bfmeW104YH();
	virtual void bfmeW105YH();
	virtual void bfmeW106YH();
	virtual void bfmeW107YH();
	virtual void bfmeW108YH();
	virtual void bfmeW109YH();
	virtual void bfmeW110YH();
	virtual void bfmeW111YH();
	virtual void bfmeW112YH();
	virtual void bfmeW113YH();
	virtual void bfmeW114YH();
	virtual void bfmeW115YH();
	virtual void bfmeW116YH();
	virtual void bfmeW117YH();
	virtual void bfmeW118YH();
	virtual void bfmeW119YH();
	virtual void bfmeW120YH();
	virtual void bfmeW121YH();
	virtual void bfmeW122YH();
	virtual void bfmeW123YH();
	virtual void bfmeW124YH();
	virtual void bfmeW125YH();
	virtual void bfmeW126YH();
	virtual void bfmeHideYH(int how);

	unsigned char m_bfmeHeadYH[0x332];
	char m_bfmeShownYH;
};

class BfmeItemYH
{
public:
	void bfmeNotifyYH();

	unsigned char m_bfmeHeadYH[0x118];
	union
	{
		int m_bfmeFlagsYH;
		unsigned char m_bfmeFlagBitsYH;
	};
	unsigned char m_bfmeMidYH[0xe8];
	BfmeWinYH *m_bfmeWinYH;
};

class BfmeHolderYH
{
public:
	unsigned char m_bfmeHeadYH[0x10];
	BfmeItemYH *m_bfmeItemYH;
};

class BfmeOwnerYH
{
public:
	void bfmeCloseYH(void *arg);

	void bfmeBaseYH(void *arg);

	unsigned char m_bfmeHeadYH[0x1c];
	BfmeHolderYH *m_bfmeHolderYH;
};

void BfmeOwnerYH::bfmeCloseYH(void *arg)
{
	bfmeBaseYH(arg);

	BfmeItemYH *item = m_bfmeHolderYH->m_bfmeItemYH;

	if (item == 0)
		return;

	if (item->m_bfmeFlagBitsYH & 1)
	{
		item->m_bfmeFlagsYH &= ~1;
		item->bfmeNotifyYH();
	}

	if (item->m_bfmeWinYH != 0)
	{
		item->m_bfmeWinYH->bfmeHideYH(0);
		item->m_bfmeWinYH->m_bfmeShownYH = 0;
	}
}
