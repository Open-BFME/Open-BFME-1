class BfmeTargetYV
{
public:
	virtual void bfmeT00YV();
	virtual void bfmeT01YV();
	virtual void bfmeT02YV();
	virtual void bfmeT03YV();
	virtual void bfmeT04YV();
	virtual void bfmeT05YV();
	virtual void bfmeT06YV();
	virtual void bfmeT07YV();
	virtual void bfmeT08YV();
	virtual void bfmeT09YV();
	virtual void bfmeT10YV();
	virtual void bfmeT11YV();
	virtual void bfmeT12YV();
	virtual void bfmeT13YV();
	virtual void bfmeT14YV();
	virtual void bfmeT15YV();
	virtual void bfmeT16YV();
	virtual void bfmeT17YV();
	virtual void bfmeT18YV();
	virtual void bfmeT19YV();
	virtual void bfmeT20YV();
	virtual void bfmeT21YV();
	virtual void bfmeT22YV();
	virtual void bfmeT23YV();
	virtual void bfmeT24YV();
	virtual void bfmeT25YV();
	virtual void bfmeT26YV();
	virtual void bfmeT27YV();
	virtual void bfmeT28YV();
	virtual void bfmeT29YV();
	virtual void bfmeT30YV();
	virtual void bfmeT31YV();
	virtual void bfmeT32YV();
	virtual void bfmeT33YV();
	virtual void bfmeT34YV();
	virtual void bfmeT35YV();
	virtual void bfmeT36YV();
	virtual void bfmeT37YV();
	virtual void bfmeT38YV();
	virtual void bfmeT39YV();
	virtual void bfmeT40YV();
	virtual void bfmeT41YV();
	virtual void bfmeT42YV();
	virtual void bfmeT43YV();
	virtual void bfmeT44YV();
	virtual void bfmeT45YV();
	virtual void bfmeBeginYV();
	virtual void bfmeEndYV();
};

class BfmeHubYV
{
public:
	virtual void bfmeH00YV();
	virtual void bfmeH01YV();
	virtual void bfmeH02YV();
	virtual void bfmeH03YV();
	virtual void bfmeH04YV();
	virtual void bfmeH05YV();
	virtual void bfmeH06YV();
	virtual void bfmeH07YV();
	virtual void bfmeH08YV();
	virtual void bfmeH09YV();
	virtual void bfmeH10YV();
	virtual void bfmeH11YV();
	virtual void bfmeH12YV();
	virtual void bfmeH13YV();
	virtual void bfmeH14YV();
	virtual void bfmeH15YV();
	virtual void bfmeH16YV();
	virtual void bfmeH17YV();
	virtual void bfmeH18YV();
	virtual void bfmeH19YV();
	virtual void bfmeH20YV();
	virtual void bfmeH21YV();
	virtual void bfmeH22YV();
	virtual void bfmeH23YV();
	virtual void bfmeH24YV();
	virtual void bfmeH25YV();
	virtual BfmeTargetYV *bfmeTopYV();
};

class BfmeThingYV
{
public:
	unsigned char m_bfmeHeadYV[0x1fc];
	BfmeHubYV *m_bfmeHubYV;
};

class BfmeOwnerYV
{
public:
	void bfmeRunYV(void *arg);

	void bfmeApplyYV(void *arg);

	unsigned char m_bfmeStartYV[8];
	BfmeThingYV *m_bfmeThingYV;
};

void BfmeOwnerYV::bfmeRunYV(void *arg)
{
	BfmeHubYV *hub = m_bfmeThingYV->m_bfmeHubYV;

	if (hub == 0)
		return;

	BfmeTargetYV *target = hub->bfmeTopYV();

	if (target == 0)
		return;

	target->bfmeBeginYV();
	bfmeApplyYV(arg);
	target->bfmeEndYV();
}
