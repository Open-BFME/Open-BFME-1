// ?bfmeSweepAX@BfmeOwnAX@@QAEXXZ (identity unknown)
// partial score=0.9 date=2026-09-06
// 43/45. Everything matches through the six-byte alignment nop, including the
// register assignment once the locals are declared count / index / slot in
// that order (declaring the slot pointer before the index swaps edi and esi).
// Residue: retail loads the slot into eax, tests eax, then copies it to ecx
// for the virtual call; MSVC loads straight into ecx and saves the two-byte
// `mov ecx,eax`. Tried the item as a loop-local, as a function-scope local,
// as a copy through a second local, and guarding on *slot with the local
// taken inside the if. All four give the identical body.
class BfmeItemAX
{
public:
	virtual void bfmeSlot00AX(void);
	virtual void bfmeNotifyAX(void);
};

class BfmeOwnAX
{
public:
	void bfmeSweepAX(void);

	int m_bfmeCountAX;
	BfmeItemAX *m_bfmeItemsAX[0x40];
};

void BfmeOwnAX::bfmeSweepAX(void)
{
	int remaining = m_bfmeCountAX;
	int index = 0;
	BfmeItemAX **slot = m_bfmeItemsAX;

	for (; index < 0x40; ++index, ++slot)
	{
		BfmeItemAX *item = *slot;

		if (item)
		{
			item->bfmeNotifyAX();

			if (--remaining == 0)
				break;
		}
	}
}
