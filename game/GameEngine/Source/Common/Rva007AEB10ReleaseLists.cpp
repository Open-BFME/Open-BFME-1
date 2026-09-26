// cl: /DNDEBUG /MD
// Retail 0x007AEB10: destroy two intrusive chains owned at +0x10 and +0x18.

class FirstChainNode
{
public:
	virtual ~FirstChainNode();
	char m_padding[0xD0];
	FirstChainNode *m_next;
};

class SecondChainNode
{
public:
	virtual ~SecondChainNode();
	char m_padding[0x60];
	SecondChainNode *m_next;
};

class Rva007AEB10Owner
{
private:
	char m_padding0[0x10];
	FirstChainNode *m_first;
	char m_padding1[4];
	SecondChainNode *m_second;

public:
	void releaseLists();
};

void Rva007AEB10Owner::releaseLists()
{
	FirstChainNode *first = m_first;
	while ( first != 0 )
	{
		FirstChainNode *next = first->m_next;
		first->m_next = 0;
		delete first;
		first = next;
	}
	m_first = 0;

	SecondChainNode *second = m_second;
	while ( second != 0 )
	{
		SecondChainNode *next = second->m_next;
		second->m_next = 0;
		delete second;
		second = next;
	}
	m_second = 0;
}
