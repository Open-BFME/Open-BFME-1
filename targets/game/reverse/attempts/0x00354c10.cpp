// ??0Rva0035D2B0Node@@QAE@XZ
// partial score=0.99 date=2026-09-10
// cl: /O2 /Ob0
// Open-BFME7: retail 0x0035D2B0 (127 bytes) is the twin of Rva00359330StringRecordAddNode.cpp
// whose node is 0x44 bytes and default-constructed by a constructor that cannot throw (no
// unwind state around the new expression).

class AsciiString
{
};

class Rva003529B0
{
};

class Rva0035D2B0Node
{
	public:
	Rva0035D2B0Node *m_link;
	void *m_vptr;
	int m_zero08;
	int m_zero0c;
	int m_zero10;
	int m_zero14;
	bool m_one18;
	bool m_one19;
	bool m_one1a;
	bool m_zero1b;
	bool m_one1c;
	bool m_one1d;
	bool m_one1e;
	unsigned char m_pad1f;
	int m_zero20;
	int m_zero24;
	int m_zero28;
	int m_zero2c;
	bool m_zero30;
	unsigned char m_pad31[3];
	int m_zero34;
	int m_zero38;
	int m_zero3c;
	int m_zero40;
	Rva0035D2B0Node() throw();
};

// ??0Rva0035D2B0Node@@QAE@XZ
Rva0035D2B0Node::Rva0035D2B0Node() throw()
{
	m_link = 0;
	m_vptr = (void *)0x010E858C;
	m_zero08 = 0;
	m_zero0c = 0;
	m_zero10 = 0;
	m_zero14 = 0;
	m_one18 = true;
	m_one19 = true;
	m_one1a = true;
	m_zero1b = false;
	m_one1c = true;
	m_one1d = true;
	m_one1e = true;
	m_zero20 = 0;
	m_zero24 = 0;
	m_zero28 = 0;
	m_zero2c = 0;
	m_zero30 = false;
	m_zero34 = 0;
	m_zero38 = 0;
	m_zero3c = 0;
	m_zero40 = 0;
}

struct Rva0035D2B0Record
{
	int m_previous;
	int m_next;
	AsciiString m_name;
	unsigned char m_released;
	unsigned char m_pad;
	unsigned short m_references;
	Rva0035D2B0Node *m_nodes;
};

class Rva0035D2B0StringRecordTable
{
public:
	int addNode(AsciiString *name);
	void release(int index);

private:
	int findOrCreateIndex(AsciiString *name);

	int *m_nameIndexesBegin;
	int *m_nameIndexesEnd;
	int *m_nameIndexesCapacity;
	Rva0035D2B0Record *m_records;
	int m_10;
	int m_14;
	int m_freeHead;
	int m_activeTail;
};

int Rva0035D2B0StringRecordTable::addNode(AsciiString *name)
{
	int index = findOrCreateIndex(name);
	if (index != -1) {
		Rva0035D2B0Record *records = m_records;
		try {
			Rva0035D2B0Record *record = records + index;
			Rva0035D2B0Node *newNode = new Rva0035D2B0Node();
			newNode->m_link = record->m_nodes;
			record->m_nodes = newNode;
		} catch (...) {
			release(index);
			throw;
		}
	}
	return index;
}
