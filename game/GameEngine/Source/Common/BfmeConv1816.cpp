extern float g_bfmeDefaultBU;

class BfmeItemVM
{
public:
	unsigned char m_bfmeHeadVM[0x10];
	int m_bfmeStateVM;
	unsigned char m_bfmeGapVM[8];
	float m_bfmeValueVM;
};

class BfmeOwnerVM
{
public:
	virtual void bfmeV0VM(void);
	virtual void bfmeV1VM(void);
	virtual void bfmeV2VM(void);
	virtual void bfmeV3VM(void);
	virtual float bfmeComputeVM(void);

	void bfmeClampVM(BfmeItemVM *item);
	void bfmeNotifyVM(BfmeItemVM *item);
};

void BfmeOwnerVM::bfmeClampVM(BfmeItemVM *item)
{
	if (item->m_bfmeStateVM != 8)
	{
		float limit = bfmeComputeVM() - g_bfmeDefaultBU;

		const float &chosen = item->m_bfmeValueVM < limit ? item->m_bfmeValueVM : limit;

		item->m_bfmeValueVM = chosen;
	}

	bfmeNotifyVM(item);
}
