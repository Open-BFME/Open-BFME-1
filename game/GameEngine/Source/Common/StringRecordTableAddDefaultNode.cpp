// cl: /O2 /Ob0 /Igame/Libraries/Source/WWVegas/WWLib
// Open-BFME7: retail 0x0035D2B0 (127 bytes) is the twin of Rva00359330StringRecordAddNode.cpp
// whose node is 0x44 bytes and default-constructed by a constructor that cannot throw (no
// unwind state around the new expression).

#include "ascii_string.h"

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

class Rva00354BC0
{
	public:
	Rva00354BC0 *m_link;
	void *m_vptr;
	int m_pair0;
	int m_pair1;
	char m_10;
	char m_11;
	char m_12;
	Rva00354BC0(const Rva003529B0 *other);
};

struct Rva00359330Record
{
	int m_previous;
	int m_next;
	AsciiString m_name;
	unsigned char m_released;
	unsigned char m_pad;
	unsigned short m_references;
	Rva00354BC0 *m_nodes;
};

class Rva00359330StringRecordTable
{
public:
	int addNode(AsciiString *name, const Rva003529B0 *node);
	void release(int index);

private:
	int findOrCreateIndex(AsciiString *name);

	int *m_nameIndexesBegin;
	int *m_nameIndexesEnd;
	int *m_nameIndexesCapacity;
	Rva00359330Record *m_records;
	int m_10;
	int m_14;
	int m_freeHead;
	int m_activeTail;
};

int Rva00359330StringRecordTable::addNode(AsciiString *name, const Rva003529B0 *node)
{
	int index = findOrCreateIndex(name);
	if (index != -1) {
		Rva00359330Record *records = m_records;
		try {
			Rva00359330Record *record = records + index;
			Rva00354BC0 *newNode = new Rva00354BC0(node);
			newNode->m_link = record->m_nodes;
			record->m_nodes = newNode;
		} catch (...) {
			release(index);
			throw;
		}
	}
	return index;
}
