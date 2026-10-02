// Open-BFME5 conversions.

class BfmeMgrVNR;

// Retail's per-cell shroud update body lives on the shroud manager element:
// game/GameEngine/Source/Common/RTS/ShroudManagerImpl008FBA40.cpp
class ShroudManagerImpl008FBA40;

class ShroudManagerImpl008FBA40Element
{
public:
	void updatePlayerCells008FC300(ShroudManagerImpl008FBA40 *manager, int idx);
};

class BfmeCellVNR
{
public:
	char m_bfmePad00[0x68];
};

class BfmeMgrVNR
{
public:
	void bfmeUpdateVNR(int idx);
	char m_bfmePad00[0x24];
	int m_bfme24;
	int m_bfme28;
	BfmeCellVNR *m_bfme2c;
};

void BfmeMgrVNR::bfmeUpdateVNR(int idx)
{
	if (idx >= 0 && idx < 0x10)
	{
		int n = m_bfme28 * m_bfme24;
		BfmeCellVNR *e = m_bfme2c + n;
		BfmeCellVNR *p = m_bfme2c;

		while (p != e)
		{
			reinterpret_cast<ShroudManagerImpl008FBA40Element *>(p)
				->updatePlayerCells008FC300(
					reinterpret_cast<ShroudManagerImpl008FBA40 *>(this), idx);
			++p;
		}
	}
}
