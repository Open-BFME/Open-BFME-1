// cl: /Od
// Two one-slot records exchanged through a held copy, built without
// optimisation. The slot is assigned as a whole record, not as the pointer it
// holds: that is what reads the right-hand record before taking the address of
// the left-hand one.

struct BfmeSlot82D010
{
	void *m_value;
};

void bfmeSwap82D010(BfmeSlot82D010 *left, BfmeSlot82D010 *right)
{
	BfmeSlot82D010 held = *left;

	*left = *right;
	*right = held;
}
