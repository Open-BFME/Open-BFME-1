// DynamicPortalBehaviour::removeUpgrade at retail 0x001F8DD0: slot 7 of the UpgradeMux table 0x010A3868, reached
// only through ILT 0x00025A09 (its VA appears once in the image). DynamicPortalBehaviour's registered
// constructor 0x001F8B80 stores that table. Slot 7 is
// EA's removeUpgrade (BFME2/RotWK WorldBuilder labels, matching slot), which undoes
// slot 9 (upgradeImplementation). Evidence:
// targets/game/reverse/identity_evidence/upgrademux-slot7-removeupgrade.md and
// targets/game/reverse/identity_evidence/upgrademux-slot7-owner-names.md

class BfmeTargetZJ
{
public:
	virtual void bfmeT0ZJ();
	virtual void bfmeT1ZJ();
	virtual void bfmeDoneZJ(int how);
};

class BfmeHostZJ
{
public:
	BfmeTargetZJ *bfmeTopZJ();

	unsigned char m_bfmeHeadZJ[0x204];
	void *m_bfmeThingZJ;
};

class BfmeBaseZJ
{
public:
	void bfmeStopZJ();
	void bfmeClearZJ();

	unsigned char m_bfmeHeadZJ[8];
	BfmeHostZJ *m_bfmeHostZJ;
};

class DynamicPortalBehaviour
{
public:
	virtual void bfmeV0ZJ();
	virtual void bfmeV1ZJ();
	virtual void bfmeV2ZJ();
	virtual void bfmeV3ZJ();
	virtual void bfmeV4ZJ();
	virtual void bfmeV5ZJ();
	virtual void bfmeV6ZJ();
	virtual void bfmeV7ZJ();
	virtual void bfmeHideZJ(int how);

public:
	virtual void removeUpgrade();
};

void DynamicPortalBehaviour::removeUpgrade()
{
	bfmeHideZJ(0);

	((BfmeBaseZJ *)((char *)this - 0x10))->bfmeStopZJ();
	((BfmeBaseZJ *)((char *)this - 0x10))->bfmeClearZJ();

	BfmeHostZJ *host = ((BfmeBaseZJ *)((char *)this - 0x10))->m_bfmeHostZJ;

	if (host->m_bfmeThingZJ != 0)
	{
		BfmeTargetZJ *target = host->bfmeTopZJ();

		if (target != 0)
			target->bfmeDoneZJ(0);
	}
}
