// ?apply@Gen00587600@@QAEXHH@Z
// partial score=0.93 date=2026-09-03
struct BfmeApplyNode;

struct BfmeApplyFalseType
{
};

struct BfmeApplyIterator
{
	BfmeApplyIterator(const BfmeApplyIterator &other) : m_bfmeNode(other.m_bfmeNode) {}

	BfmeApplyNode *m_bfmeNode;
};

class BfmeApplyVector
{
public:
	void bfmeOverflow(int *position, const int &first,
		const BfmeApplyFalseType &, int firstCount, bool secondCount);

	void bfmeAppend(const int &value)
	{
		if (m_bfmeFinish != m_bfmeEnd)
		{
			if (m_bfmeFinish != 0)
				*m_bfmeFinish = value;
			++m_bfmeFinish;
		}
		else
		{
			bfmeOverflow(m_bfmeFinish, value,
				reinterpret_cast<const BfmeApplyFalseType &>(value), 1, true);
		}
	}

	int *m_bfmeStart;
	int *m_bfmeFinish;
	int *m_bfmeEnd;
};

struct BfmeApplyNode
{
	char m_bfmeFields[0x24];
	BfmeApplyVector m_bfmeValues;
};

class BfmeApplyTree
{
public:
	BfmeApplyIterator bfmeFind(const int &key);

	BfmeApplyNode *m_bfmeHead;
};

class Gen00587600
{
public:
	void apply(int value, int which);

private:
	char m_bfmeFields[0x24];
	BfmeApplyTree m_bfmeTree;
};

// ?apply@Gen00587600@@QAEXHH@Z
void Gen00587600::apply(int value, int which)
{
	BfmeApplyIterator found = m_bfmeTree.bfmeFind(value);

	if (found.m_bfmeNode != m_bfmeTree.m_bfmeHead)
		found.m_bfmeNode->m_bfmeValues.bfmeAppend(which);
}
