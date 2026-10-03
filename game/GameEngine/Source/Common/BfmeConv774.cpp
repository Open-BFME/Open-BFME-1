class Object;

class UpgradeMuxData
{
public:
	void performUpgradeFX(Object *what) const;
	void muxDataProcessUpgradeRemoval(Object *what) const;
};

struct BfmeOwnerDSN
{
	unsigned char m_bfmeHead[0x5c];
	UpgradeMuxData m_bfmeSub;
};

struct BfmeThingDSN
{
	void bfmeGoDSN();
	void bfmeGoDSO();
};

void BfmeThingDSN::bfmeGoDSN()
{
	void *what = *(void **)((char *)this - 0xd8);
	BfmeOwnerDSN *owner = *(BfmeOwnerDSN **)((char *)this - 0xdc);
	owner->m_bfmeSub.performUpgradeFX((Object *)what);
}

void BfmeThingDSN::bfmeGoDSO()
{
	void *what = *(void **)((char *)this - 0xd8);
	BfmeOwnerDSN *owner = *(BfmeOwnerDSN **)((char *)this - 0xdc);
	owner->m_bfmeSub.muxDataProcessUpgradeRemoval((Object *)what);
}
