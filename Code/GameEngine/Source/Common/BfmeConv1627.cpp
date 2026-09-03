// Open-BFME5 conversions.

class BfmeStrVTY
{
public:
	BfmeStrVTY() { m_bfme00 = 0; }
	~BfmeStrVTY() { bfmeClearVTY(); }
	void bfmeAssignVTY(const BfmeStrVTY &other);
	void bfmeClearVTY();
	unsigned short *m_bfme00;
};

class BfmeOwnVTY
{
public:
	BfmeOwnVTY(BfmeStrVTY *first, const BfmeStrVTY &second);
	virtual void bfmeSlot0VTY();
	BfmeStrVTY m_bfme04;
	BfmeStrVTY *m_bfme08;
};

BfmeOwnVTY::BfmeOwnVTY(BfmeStrVTY *first, const BfmeStrVTY &second)
	: m_bfme08(first)
{
	m_bfme04.bfmeAssignVTY(*first);
	first->bfmeAssignVTY(second);
}
