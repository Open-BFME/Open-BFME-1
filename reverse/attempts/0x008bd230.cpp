// ?d_008bd230@@YAXXZ
// partial score=0.95 date=2026-08-30
class BfmeNode1279;

class BfmeQuery1279
{
public:
	void bfmeQuery1279(void *value, int zero, void **other, void **result);
	BfmeNode1279 *bfmeInsert1279(void *value, BfmeNode1279 *node);
};

class BfmeNode1279
{
public:
	virtual void bfmeLinked1279() = 0;
	char m_padding04[0x08 - 0x04];
	void *m_value;
	char m_padding0c[0x54 - 0x0c];
	BfmeNode1279 *m_previous;
	BfmeNode1279 *m_next;
};

struct BfmeInput1279
{
	void *m_value;
};

class BfmeWrapper1279
{
public:
	void bfmeProcess1279(void *value);
	void bfmeForward1279(BfmeInput1279 *input);

private:
	BfmeQuery1279 *m_query;
};

void BfmeWrapper1279::bfmeForward1279(BfmeInput1279 *input)
{
	void *other;
	m_query->bfmeQuery1279(input->m_value, 0, &other, (void **)&input);
	bfmeProcess1279(input);
}

BfmeNode1279 *BfmeQuery1279::bfmeInsert1279(void *value, BfmeNode1279 *node)
{
	void *const originalValue = value;
	void *other;
	bfmeQuery1279(value, 0, &value, &other);
	BfmeNode1279 *previous = (BfmeNode1279 *)value;
	node->m_next = previous->m_next;
	node->m_previous = previous;
	node->bfmeLinked1279();
	if (node->m_next)
		node->m_next->m_previous = node;
	node->m_previous->m_next = node;
	node->m_value = originalValue;
	return node;
}
