// ?bfmeFindFloat@Gen_001418F0@@QAEMPBX@Z
// partial score=0.9 date=2026-09-02
// cl: /DNDEBUG /MD /GX- /O2 /Ob2
// Small map-value lookup wrappers used by the AI construction path.

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

class Gen_001418F0
{
public:
	float bfmeFindFloat(const void *key);

private:
	char m_bfmePad[0x340];
	BfmeLookupTree m_bfmeTree;
};

class Gen_00141940
{
public:
	float *bfmeFindFloat(const void *key);

private:
	char m_bfmePad[0x34c];
	BfmeLookupTree m_bfmeTree;
};

extern float g_bfmeMissingFloat;

float Gen_001418F0::bfmeFindFloat(const void *key)
{
	BfmeLookupIterator found;
	if (m_bfmeTree.m_bfmeSize == 0)
		return g_bfmeMissingFloat;
	m_bfmeTree.bfmeFind(found, key);
	if (found.m_bfmeNode == m_bfmeTree.m_bfmeHeader)
		return g_bfmeMissingFloat;
	return found.m_bfmeNode->m_bfmeValue;
}

float *Gen_00141940::bfmeFindFloat(const void *key)
{
	BfmeLookupIterator found;
	if (m_bfmeTree.m_bfmeSize != 0)
		goto present;
missing:
	return 0;
present:
	m_bfmeTree.bfmeFind(found, key);
	if (found.m_bfmeNode == m_bfmeTree.m_bfmeHeader)
		goto missing;
	return &found.m_bfmeNode->m_bfmeValue;
}
