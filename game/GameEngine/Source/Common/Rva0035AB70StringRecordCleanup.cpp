// Retail RVA0x0035AB70,143B. release(int) at359330 and node dtor354A00
// independently prove the paired string-record-table operations.
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

#include "ascii_string.h"

void __cdecl operator delete(void *);

class Rva00354A00Node
{
public:
	~Rva00354A00Node();
	Rva00354A00Node *m_next;
};

struct Rva0035AB70Record
{
	int m_previous;
	int m_next;
	AsciiString m_name;
	unsigned char m_released;
	unsigned char m_pad;
	unsigned short m_references;
	Rva00354A00Node *m_nodes;
};

class Rva00359330StringRecordTable
{
public:
	void release(int index);
	void cleanup();
	int *m_nameIndexesBegin;
	int *m_nameIndexesEnd;
	int *m_nameIndexesCapacity;
	Rva0035AB70Record *m_records;
	int m_10;
	int m_14;
	int m_freeHead;
	int m_activeTail;
};

// Retains an unreleased head node and drains all of its successors. A released
// record removes its first node before releasing the record index.
void Rva00359330StringRecordTable::cleanup()
{
	Rva00359330StringRecordTable *owner = this;
	int index = owner->m_activeTail;
	while (index != -1)
	{
		Rva0035AB70Record *record = owner->m_records + index;
		int previous = record->m_previous;
		if (record->m_released)
		{
			Rva00354A00Node *node = record->m_nodes;
			record->m_nodes = record->m_nodes->m_next;
			node->~Rva00354A00Node();
			operator delete(node);
			owner->release(index);
		}
		else
		{
			Rva00354A00Node *first = record->m_nodes;
			while (first->m_next)
			{
				Rva00354A00Node *node = first->m_next;
				Rva00354A00Node *next = first->m_next->m_next;
				delete node;
				first->m_next = next;
			}
			record->m_references = 1;
		}
		index = previous;
	}
}
