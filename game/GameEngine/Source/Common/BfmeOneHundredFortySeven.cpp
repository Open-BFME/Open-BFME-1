// Two small questions asked of a record. The first counts anything past the
// first two states as interesting; the second wants something present but not
// yet given a place.

class BfmeThingXT
{
public:
	int bfmeOddXT(void) const;

private:
	unsigned char m_bfmeHead[0x18];		// 0x00
	int m_bfmeState;			// 0x18
};

int BfmeThingXT::bfmeOddXT(void) const
{
	int state = m_bfmeState;

	if (state != 0 && state != 1)
		return 1;

	return 0;
}

class BfmeSlotXT
{
public:
	int bfmeLooseXT(void) const;

private:
	unsigned char m_bfmeHead[0x58];		// 0x00
	int m_bfmeHolder;			// 0x58
	int m_bfmePlace;			// 0x5c
};

int BfmeSlotXT::bfmeLooseXT(void) const
{
	if (m_bfmeHolder != 0 && m_bfmePlace == -1)
		return 1;

	return 0;
}
