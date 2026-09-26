// cl: /O2 /Ob1

void __cdecl operator delete(void *);

struct Gen_001DB2C0
{
	void **m_begin;
	void **m_end;
	void **m_capacity;
	int m_key;
	Gen_001DB2C0 *m_next;

	~Gen_001DB2C0();
};

class Rva001DB370List
{
public:
	int eraseByKey(int key);

private:
	Gen_001DB2C0 *m_current;
	Gen_001DB2C0 *m_head;
};

int Rva001DB370List::eraseByKey(int key)
{
	Gen_001DB2C0 *node = m_head;
	Gen_001DB2C0 *previous = 0;
	m_current = node;

	while (node != 0) {
		if (node->m_key == key) {
			if (previous != 0) {
				previous->m_next = node->m_next;
			} else {
				m_head = node->m_next;
			}

			node->~Gen_001DB2C0();
			::operator delete(node);
			return 1;
		}

		previous = node;
		node = node->m_next;
	}

	return 0;
}
