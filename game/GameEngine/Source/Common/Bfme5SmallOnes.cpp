// Three more small ones: a push at the head of a list, a two-value rejection
// test and a setter that falls back on zero.
//
// The test has to answer one first: written as two early zeroes MSVC folds the
// second comparison into a setne. The setter keeps its value in a variable so
// that the zero goes through a register, which is what lets the store be
// duplicated into both paths instead of becoming an immediate.

class BfmeNodeBJ
{
public:
	int m_bfmeHead[4];					// +0x00
	BfmeNodeBJ *m_bfmeNext;					// +0x10
};

class Gen_0014A040
{
public:
	void bfmePush(BfmeNodeBJ *node);

private:
	int m_bfmeHead[61];					// +0x000
	BfmeNodeBJ *m_bfmeList;					// +0x0F4
};

// ?bfmePush@Gen_0014A040@@QAEXPAVBfmeNodeBJ@@@Z
void Gen_0014A040::bfmePush(BfmeNodeBJ *node)
{
	node->m_bfmeNext = m_bfmeList;

	m_bfmeList = node;
}

class Gen_000652A0
{
public:
	int bfmeAccepts(void) const;

private:
	int m_bfmeHead[67];					// +0x000
	int m_bfmeMode;						// +0x10C
};

// ?bfmeAccepts@Gen_000652A0@@QBEHXZ
int Gen_000652A0::bfmeAccepts(void) const
{
	int mode = m_bfmeMode;

	if (mode != 8 && mode != 4)
		return 1;

	return 0;
}

class BfmeSourceBJ
{
public:
	int m_bfmeHead[29];					// +0x00
	int m_bfmeValue;					// +0x74
};

class Gen_0016A330
{
public:
	void bfmeTake(BfmeSourceBJ *source);

private:
	int m_bfmeHead[17];					// +0x00
	int m_bfmeValue;					// +0x44
};

// ?bfmeTake@Gen_0016A330@@QAEXPAVBfmeSourceBJ@@@Z
void Gen_0016A330::bfmeTake(BfmeSourceBJ *source)
{
	int value;

	if (source)
		value = source->m_bfmeValue;
	else
		value = 0;

	m_bfmeValue = value;
}
