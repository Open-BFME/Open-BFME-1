class BfmeSlotJV
{
public:
	char bfmeUsedJV(void);

	unsigned char m_bfmeRawJV[0x68];
};

class BfmeOwnerJV
{
public:
	BfmeSlotJV *bfmeAtJV(int index)
	{
		if (index < 0 || index >= 8)
			return 0;

		return &m_bfmeSlotsJV[index];
	}

	int bfmeFindJV(void);

	unsigned char m_bfmeHeadJV[0xc];
	char m_bfmeActiveJV;
	unsigned char m_bfmeGapJV[0x4b];
	BfmeSlotJV m_bfmeSlotsJV[8];
};

int BfmeOwnerJV::bfmeFindJV(void)
{
	int result = -1;
	int index;

	if (m_bfmeActiveJV)
	{
		for (index = 0; index < 8; index++)
		{
			if (bfmeAtJV(index)->bfmeUsedJV())
			{
				result = index;
				break;
			}
		}
	}

	return result;
}
