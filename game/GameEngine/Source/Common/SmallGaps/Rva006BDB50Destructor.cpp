// ??1Rva006BDB50@@UAE@XZ
// cl: /DNDEBUG /MD /EHsc
struct Rva006BDB50Node { virtual ~Rva006BDB50Node(); char m_pad[0x10c]; Rva006BDB50Node* m_next; };
struct Rva006BDB50Base {
	virtual ~Rva006BDB50Base();
	int m_4;
	int m_8;
};
struct Rva006BDB50 : Rva006BDB50Base {
	Rva006BDB50Node* m_head;
	void reset();
	virtual ~Rva006BDB50();
};
Rva006BDB50::~Rva006BDB50()
{
	reset();
	Rva006BDB50Node* n = m_head;
	while (n) {
		Rva006BDB50Node* next = n->m_next;
		delete n;
		n = next;
	}
}
