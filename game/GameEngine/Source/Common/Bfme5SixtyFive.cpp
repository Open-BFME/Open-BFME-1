// Two more: another bit test taken from the argument and a clamp between two
// bounds.

class BfmeThingEL
{
public:
	int m_bfmeHead[8];					// +0x00
	unsigned int m_bfmeIndex;				// +0x20
};

class Gen_000D5930
{
public:
	bool bfmeHasBit(const BfmeThingEL *thing) const;

private:
	int m_bfmeHead[35];					// +0x00
	unsigned int m_bfmeWords[8];				// +0x8C
};

// ?bfmeHasBit@Gen_000D5930@@QBE_NPBVBfmeThingEL@@@Z
bool Gen_000D5930::bfmeHasBit(const BfmeThingEL *thing) const
{
	if (thing == 0)
		return false;

	unsigned int index = thing->m_bfmeIndex;

	return (m_bfmeWords[index >> 5] & (1 << (index & 31))) != 0;
}

class Gen_000B2860
{
public:
	void bfmeClamp(float low, float high);

private:
	int m_bfmeHead[21];					// +0x00
	float m_bfmeValue;					// +0x54
};

// ?bfmeClamp@Gen_000B2860@@QAEXMM@Z
void Gen_000B2860::bfmeClamp(float low, float high)
{
	float value = m_bfmeValue;

	m_bfmeValue = value < low ? low : (value > high ? high : value);
}
