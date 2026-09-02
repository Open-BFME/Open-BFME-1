// ?find@Gen_008951B0@@QBEXPAPAVBfmeNodeFD@@PAX@Z
// partial score=0.88 date=2026-09-02
class BfmeNodeFD
{
public:
	void *m_item;
	BfmeNodeFD *m_next;
};

class BfmeKeyedFD
{
public:
	char m_pad[8];
	void *m_key;
};

class Gen_008951B0
{
public:
	void find(BfmeNodeFD **out, void *key) const;

private:
	BfmeNodeFD *m_head;
};

void Gen_008951B0::find(BfmeNodeFD **out, void *key) const
{
	BfmeNodeFD *node = m_head;
	if (node)
	{
		void *k = key;
		do
		{
			if (((BfmeKeyedFD *)node->m_item)->m_key == k)
			{
				*out = node;
				return;
			}
			node = node->m_next;
		}
		while (node);
	}
	*out = 0;
}
