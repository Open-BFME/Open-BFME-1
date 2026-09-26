// cl: /DNDEBUG /MD /GX- /O2 /Ob2

void __cdecl operator delete(void *block);
void __cdecl bfmeDeallocate(void *block, unsigned int bytes);

struct Rva006152A0Node;

struct Rva006152A0Owner
{
	char m_head[0x98];
	Rva006152A0Node *m_first;
	Rva006152A0Node *m_last;
};

struct Rva006152A0Node
{
	Rva006152A0Owner *m_owner;
	Rva006152A0Node *m_previous;
	Rva006152A0Node *m_next;
	unsigned int m_value;

	void unlink()
	{
		if (m_owner != 0) {
			if (m_previous != 0)
				m_previous->m_next = m_next;
			else
				m_owner->m_first = m_next;

			if (m_next != 0)
				m_next->m_previous = m_previous;
			else
				m_owner->m_last = m_previous;

			m_previous = 0;
			m_next = 0;
		}
	}
};

class Rva006152A0Vector
{
public:
	void destroy();

private:
	Rva006152A0Node *m_begin;
	Rva006152A0Node *m_end;
	Rva006152A0Node *m_capacity;
};

void Rva006152A0Vector::destroy()
{
	Rva006152A0Node *it = m_begin;
	Rva006152A0Node *last = m_end;

	while (it != last) {
		it->unlink();
		++it;
	}

	if (m_begin != 0) {
		unsigned int bytes = sizeof(Rva006152A0Node) * (m_capacity - m_begin);
		if (bytes > 0x80)
			operator delete(m_begin);
		else
			bfmeDeallocate(m_begin, bytes);
	}
}
