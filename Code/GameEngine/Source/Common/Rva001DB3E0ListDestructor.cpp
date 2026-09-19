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

class Rva001DB3E0List
{
public:
	~Rva001DB3E0List();

private:
	Gen_001DB2C0 *m_current;
	Gen_001DB2C0 *m_head;
};

Rva001DB3E0List::~Rva001DB3E0List()
{
	while (m_head != 0)
	{
		Gen_001DB2C0 *current = m_head;
		m_current = current;
		m_head = current->m_next;
		current->~Gen_001DB2C0();
		::operator delete(current);
	}
}
