class BfmeKeyZP
{
public:
	unsigned char m_bfmeHeadZP[4];
	int m_bfmeIdZP;
};

// Retail calls 0x00801EC0 directly, matched as Rva00801EC0Owner::rva00801ec0
// (Rva00801EC0FeslFill.cpp).
class Rva007FBEF0GameRecord;
class Rva00801EC0Owner
{
public:
	void rva00801ec0(Rva007FBEF0GameRecord *record);
};

class BfmeSlotZP
{
public:
	unsigned char m_bfmeHeadZP[8];
	int m_bfmeIdZP;
	unsigned char m_bfmeTailZP[0x74];
};

class BfmeOwnerZP
{
public:
	void bfmeFindZP(BfmeKeyZP *key);

	unsigned char m_bfmeHeadZP[0x1c];
	BfmeSlotZP *m_bfmeSlotsZP;
	int m_bfmeCountZP;
};

void BfmeOwnerZP::bfmeFindZP(BfmeKeyZP *key)
{
	BfmeSlotZP *p = m_bfmeSlotsZP;
	BfmeSlotZP *end = m_bfmeSlotsZP + m_bfmeCountZP;
	int want = key->m_bfmeIdZP;

	while (p < end)
	{
		if (p->m_bfmeIdZP == want)
		{
			reinterpret_cast<Rva00801EC0Owner *>(p)->rva00801ec0(
				reinterpret_cast<Rva007FBEF0GameRecord *>(key));
			return;
		}

		p++;
	}
}
