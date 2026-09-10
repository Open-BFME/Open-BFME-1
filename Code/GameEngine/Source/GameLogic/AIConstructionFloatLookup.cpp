// cl: /DNDEBUG /MD /GX- /O2 /Ob2
// The AI construction path looks up a float value in a small tree.

struct BfmeLookupNode
{
	char m_bfmePad[0x14];
	float m_bfmeValue;
};

struct BfmeLookupIterator
{
	BfmeLookupNode *m_bfmeNode;
};

class BfmeLookupTree
{
public:
	void bfmeFind(BfmeLookupIterator &out, const void *const &key);

	BfmeLookupNode *m_bfmeHeader;
	unsigned int m_bfmeSize;
};

class Gen_00141940
{
public:
	float *bfmeFindFloat(const void *key);

private:
	char m_bfmePad[0x34c];
	BfmeLookupTree m_bfmeTree;
};

float *Gen_00141940::bfmeFindFloat(const void *key)
{
	BfmeLookupIterator found;
	if (m_bfmeTree.m_bfmeSize == 0)
		return 0;
	else
	{
		m_bfmeTree.bfmeFind(found, key);
		if (found.m_bfmeNode == m_bfmeTree.m_bfmeHeader)
			return 0;
		return &found.m_bfmeNode->m_bfmeValue;
	}
}
