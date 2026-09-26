// Retail 0x00465E00: hide every active APT window, then refresh the manager.
// The slot records begin at +0xA8 and are 0x14 bytes wide.  The existing
// BfmeW1183 hide helper is the pinned ILT at 0x0003F3E1.

struct BfmeWindowManagerAptSlot
{
	char m_pad00[0x10];
	unsigned char m_flags;
	char m_pad11[3];
};

class BfmeW1183
{
public:
	void bfmeHide1183(unsigned int index);
	virtual void slot0() = 0;
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual void slot4() = 0;
	virtual void slot5() = 0;

	void hideAllAptWindows();

private:
	char m_pad00[0xa4];
	BfmeWindowManagerAptSlot m_aptWindows[12];
	char m_pad198[0x15];
	unsigned char m_aptWindowsDirty;
};

// ?hideAllAptWindows@BfmeW1183@@QAEXXZ
void BfmeW1183::hideAllAptWindows()
{
	for (int index = 0; index < 12; ++index)
	{
		if (m_aptWindows[index].m_flags & 2)
		{
			bfmeHide1183(index);
			m_aptWindows[index].m_flags |= 1;
		}
	}

	m_aptWindowsDirty = 1;
	slot5();
}
