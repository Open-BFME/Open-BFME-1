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
	int m_pair0;
	int m_pair1;
	char m_10;
	char m_11;
	char m_12;
	char m_pad13[0x44 - 0x13];
	Rva0035D2B0Node() throw();
};

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
