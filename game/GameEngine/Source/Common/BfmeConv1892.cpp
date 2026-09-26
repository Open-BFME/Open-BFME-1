// Retail 0x00151960 scans an owner's linked items against a subject hub.
// The +0x0c subject link, +0x1fc hub link, +0x04 list head, +0x84 virtual
// slot and the 0x000441A2 remove callee fix the recovered generic layout.

typedef char Bool;

class BfmeItemZZ;

class BfmeHubZZ
{
public:
	virtual void bfmeH00ZZ();
	virtual void bfmeH01ZZ();
	virtual void bfmeH02ZZ();
	virtual void bfmeH03ZZ();
	virtual void bfmeH04ZZ();
	virtual void bfmeH05ZZ();
	virtual void bfmeH06ZZ();
	virtual void bfmeH07ZZ();
	virtual void bfmeH08ZZ();
	virtual void bfmeH09ZZ();
	virtual void bfmeH10ZZ();
	virtual void bfmeH11ZZ();
	virtual void bfmeH12ZZ();
	virtual void bfmeH13ZZ();
	virtual void bfmeH14ZZ();
	virtual void bfmeH15ZZ();
	virtual void bfmeH16ZZ();
	virtual void bfmeH17ZZ();
	virtual void bfmeH18ZZ();
	virtual void bfmeH19ZZ();
	virtual void bfmeH20ZZ();
	virtual void bfmeH21ZZ();
	virtual void bfmeH22ZZ();
	virtual void bfmeH23ZZ();
	virtual void bfmeH24ZZ();
	virtual void bfmeH25ZZ();
	virtual void bfmeH26ZZ();
	virtual void bfmeH27ZZ();
	virtual void bfmeH28ZZ();
	virtual void bfmeH29ZZ();
	virtual void bfmeH30ZZ();
	virtual void bfmeH31ZZ();
	virtual void bfmeH32ZZ();
	virtual Bool bfmeAcceptZZ(BfmeItemZZ *item, int flag);
};

class BfmeItemZZ
{
public:
	unsigned char m_bfmeHeadZZ[0x1fc];
	BfmeHubZZ *m_bfmeHubZZ;
};

class BfmeSubjectZZ
{
public:
	unsigned char m_bfmeHeadZZ[0xc];
	BfmeItemZZ *m_bfmeItemZZ;
};

struct BfmeNodeZZ
{
	BfmeNodeZZ *m_bfmeNextZZ;
	unsigned char m_bfmePadZZ[4];
	BfmeItemZZ *m_bfmeItemZZ;
};

class BfmeOwnerZZ
{
public:
	Bool bfmeScanZZ(BfmeSubjectZZ *subject);
	Bool bfmeTryZZ(BfmeItemZZ *item);

private:
	unsigned char m_bfmeStartZZ[4];
	BfmeNodeZZ *m_bfmeListZZ;
};

#pragma comment(linker, "/alternatename:?bfmeTryZZ@BfmeOwnerZZ@@QAEDPAVBfmeItemZZ@@@Z=?j_000441a2@@YAXXZ")

Bool BfmeOwnerZZ::bfmeScanZZ(BfmeSubjectZZ *subject)
{
	BfmeItemZZ *item = subject->m_bfmeItemZZ;
	if (item != 0)
	{
		BfmeHubZZ *hub = item->m_bfmeHubZZ;
		BfmeNodeZZ *node = m_bfmeListZZ->m_bfmeNextZZ;
		while (node != m_bfmeListZZ)
		{
			BfmeItemZZ *member = node->m_bfmeItemZZ;
			BfmeNodeZZ *next = node->m_bfmeNextZZ;
			if (!hub->bfmeAcceptZZ(member, 0) && bfmeTryZZ(member))
				return false;
			node = next;
		}
	}
	return true;
}
