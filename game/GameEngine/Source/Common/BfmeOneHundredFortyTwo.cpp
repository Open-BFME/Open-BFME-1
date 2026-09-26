// Two tables of slots, each holding a pointer that may be empty. Handing three
// numbers to a slot writes them straight through; an empty slot swallows them.

class BfmeSlotXM
{
public:
	unsigned char m_bfmeHead[0xe4];		// 0x00
	int m_bfmeAcross;			// 0xe4
	int m_bfmeUp;				// 0xe8
	int m_bfmeAlong;			// 0xec
};

class BfmeBoardXM
{
public:
	void bfmeSetNearXM(int index, int across, int up, int along);
	void bfmeSetFarXM(int index, int across, int up, int along);

private:
	unsigned char m_bfmeGap[0x144];		// 0x000
	BfmeSlotXM *m_bfmeNear[4];		// 0x144
	BfmeSlotXM *m_bfmeFar[4];		// 0x154
};

void BfmeBoardXM::bfmeSetNearXM(int index, int across, int up, int along)
{
	BfmeSlotXM *slot = m_bfmeNear[index];

	if (slot != 0)
	{
		slot->m_bfmeAcross = across;
		slot->m_bfmeUp = up;
		slot->m_bfmeAlong = along;
	}
}

void BfmeBoardXM::bfmeSetFarXM(int index, int across, int up, int along)
{
	BfmeSlotXM *slot = m_bfmeFar[index];

	if (slot != 0)
	{
		slot->m_bfmeAcross = across;
		slot->m_bfmeUp = up;
		slot->m_bfmeAlong = along;
	}
}
