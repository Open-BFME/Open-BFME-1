// Five more tiny ones: two emptiness tests against an embedded sentinel, a
// size with a constant floor, a byte count built from a span and a stride, and
// a flag normalised to zero or one before it is stored.
//
// The size keeps its floor in a variable the second path overwrites: written
// as an early return of the constant, the constant moves into its own block
// and the return is duplicated.

class BfmeNodeBY
{
public:
	BfmeNodeBY *m_bfmeNext;					// +0x00
	BfmeNodeBY *m_bfmePrev;					// +0x04
};

class Gen_00892500
{
public:
	bool bfmeIsEmpty(void) const;

private:
	int m_bfmeHead[2];					// +0x00
	BfmeNodeBY *m_bfmeNode;					// +0x08
	BfmeNodeBY m_bfmeSentinel;				// +0x0C
};

class Gen_00892550
{
public:
	bool bfmeIsEmpty(void) const;

private:
	int m_bfmeHead[2];					// +0x00
	BfmeNodeBY *m_bfmeNode;					// +0x08
	BfmeNodeBY m_bfmeSentinel;				// +0x0C
};

class Gen_00977870
{
public:
	int bfmeBytes(void) const;

private:
	int m_bfmeHead[2];					// +0x00
	int m_bfmeStride;					// +0x08
	int m_bfmeGap[3];					// +0x0C
	int m_bfmeFirst;					// +0x18
	int m_bfmeLast;						// +0x1C
};

class BfmeTargetBY
{
public:
	char m_bfmeHead[0x38];					// +0x00
	int m_bfmeFlag;						// +0x38
};

class Gen_0090E810
{
public:
	void bfmeSetFlag(unsigned char value);

private:
	BfmeTargetBY *m_bfmeTarget;				// +0x00
};

// ?bfmeSetFlag@Gen_0090E810@@QAEXE@Z
void Gen_0090E810::bfmeSetFlag(unsigned char value)
{
	BfmeTargetBY *target = m_bfmeTarget;

	if (target)
		target->m_bfmeFlag = (value != 0);
}
