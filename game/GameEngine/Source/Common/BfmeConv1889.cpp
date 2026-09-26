class BfmeHubZY
{
public:
	virtual void bfmeH00ZY();
	virtual void bfmeH01ZY();
	virtual void bfmeH02ZY();
	virtual void bfmeH03ZY();
	virtual void bfmeH04ZY();
	virtual void bfmeH05ZY();
	virtual void bfmeH06ZY();
	virtual void bfmeH07ZY();
	virtual void bfmeH08ZY();
	virtual void bfmeH09ZY();
	virtual void bfmeH10ZY();
	virtual void bfmeH11ZY();
	virtual void bfmeH12ZY();
	virtual void bfmeH13ZY();
	virtual void bfmeH14ZY();
	virtual void bfmeH15ZY();
	virtual void bfmeH16ZY();
	virtual void bfmeH17ZY();
	virtual void bfmeH18ZY();
	virtual void bfmeH19ZY();
	virtual void bfmeH20ZY();
	virtual void bfmeH21ZY();
	virtual void bfmeH22ZY();
	virtual void bfmeH23ZY();
	virtual void bfmeH24ZY();
	virtual void bfmeH25ZY();
	virtual void bfmeH26ZY();
	virtual void bfmeH27ZY();
	virtual void bfmeH28ZY();
	virtual void bfmeH29ZY();
	virtual void bfmeH30ZY();
	virtual void bfmeH31ZY();
	virtual void bfmeH32ZY();
	virtual void bfmeH33ZY();
	virtual void bfmeH34ZY();
	virtual void bfmeH35ZY();
	virtual void bfmeH36ZY();
	virtual void bfmeH37ZY();
	virtual void bfmeH38ZY();
	virtual void bfmeH39ZY();
	virtual void bfmeH40ZY();
	virtual void bfmeH41ZY();
	virtual void bfmeH42ZY();
	virtual void bfmeH43ZY();
	virtual void bfmeH44ZY();
	virtual void bfmeH45ZY();
	virtual void bfmeH46ZY();
	virtual void bfmeH47ZY();
	virtual void bfmeH48ZY();
	virtual void bfmeH49ZY();
	virtual void bfmeH50ZY();
	virtual void *bfmeKindZY();
};

class BfmeItemZY
{
public:
	unsigned char m_bfmeHeadZY[0x1fc];
	BfmeHubZY *m_bfmeHubZY;
};

struct BfmeNodeZY
{
	BfmeNodeZY *m_bfmeNextZY;
	unsigned char m_bfmePadZY[4];
	BfmeItemZY *m_bfmeItemZY;
};

class BfmeOwnerZY
{
public:
	char bfmeScanZY(void *want);

	char bfmeTryZY(BfmeItemZY *item);

	unsigned char m_bfmeStartZY[4];
	BfmeNodeZY *m_bfmeListZY;
};

char BfmeOwnerZY::bfmeScanZY(void *want)
{
	BfmeNodeZY *node = m_bfmeListZY->m_bfmeNextZY;

	while (node != m_bfmeListZY)
	{
		BfmeItemZY *item = node->m_bfmeItemZY;

		if (item != 0)
		{
			BfmeHubZY *hub = item->m_bfmeHubZY;

			if (hub != 0 && hub->bfmeKindZY() == want)
			{
				node = node->m_bfmeNextZY;
			}
			else
			{
				node = node->m_bfmeNextZY;

				if (bfmeTryZY(item) != 0)
					return 1;
			}
		}
	}

	return 0;
}
