// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

struct Rva000EC470Node
{
	unsigned char m_padding[0x10];
	Rva000EC470Node *volatile m_next;
	Rva000EC470Node *volatile m_previous;
};

class Rva000EC470List
{
public:
	void insert(Rva000EC470Node *node);

private:
	unsigned char m_padding[0x274];
	Rva000EC470Node *volatile m_head;
};

void Rva000EC470List::insert(Rva000EC470Node *node)
{
	if (m_head == node) {
		return;
	}
	if (node->m_next != 0) {
		return;
	}
	if (node->m_previous != 0) {
		return;
	}
	node->m_previous = m_head;
	Rva000EC470Node *head = m_head;
	if (head != 0) {
		head->m_next = node;
	}
	m_head = node;
}
