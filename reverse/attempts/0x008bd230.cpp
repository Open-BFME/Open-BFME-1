// ?d_008bd230@@YAXXZ
// partial score=0.95 date=2026-09-04
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
