// cl: /O2 /MD

extern "C" void *memset(void *destination, int value, unsigned int size);

struct Rva000CE400Node
{
	virtual ~Rva000CE400Node();
	int m_4;
	int m_8;
	Rva000CE400Node *m_next;
};

struct Rva000CE400Stats { int m[6]; };

struct Rva000CE400Owner
{
	char m_pad[0x54];
	Rva000CE400Node *m_head;
	char m_pad2[0x74 - 0x58];
	Rva000CE400Stats m_statsA;
	Rva000CE400Stats m_statsB;
	void clearChainAndStats();
};

void Rva000CE400Owner::clearChainAndStats()
{
	while (m_head)
	{
		Rva000CE400Node *next = m_head->m_next;
		delete m_head;
		m_head = next;
	}
	memset(&m_statsA, 0, 0x18);
	memset(&m_statsB, 0, 0x18);
}
