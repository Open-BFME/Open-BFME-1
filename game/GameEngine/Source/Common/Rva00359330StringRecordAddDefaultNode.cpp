// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

#include "ascii_string.h"

class Rva00354BC0
{
	public:
	Rva00354BC0 *m_link;
	private:
	void *m_vptr;
	int m_pair0;
	int m_pair1;
	char m_10;
	char m_11;
	char m_12;

public:
	Rva00354BC0()
		: m_link(0), m_pair0(0), m_pair1(0)
	{
		m_vptr = (void *)0x010E855C;
		m_10 = 1;
		m_11 = 0;
		m_12 = 0;
	}
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
	int addNode(AsciiString *name);
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

int Rva00359330StringRecordTable::addNode(AsciiString *name)
{
	int index = findOrCreateIndex(name);
	if (index != -1)
	{
		Rva00359330Record *records = m_records;
		try
		{
			Rva00359330Record *record = records + index;
			Rva00354BC0 *newNode = new Rva00354BC0();
			newNode->m_link = record->m_nodes;
			record->m_nodes = newNode;
		}
		catch (...)
		{
			release(index);
			throw;
		}
	}
	return index;
}
