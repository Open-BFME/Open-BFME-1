// Address-derived reconstruction of retail 0x0035B3D0.  The matched caller at
// 0x0035BDE0 proves the receiver, list-head subobject, and two-pointer ABI.  The
// removed record node routes through 0x00354A60 to the Script destructor at
// 0x00352C20 (vtable 0x010E858C).  The concrete list-node class is not known.

// Retail call +0x43 routes through ILT 0x00028EC0 to the existing
// Rva00354A60::invoke provider (add ecx,4; tail jump). Call +0x54 routes
// through ILT 0x0003E85B to Rva00359530StringRecordTable::release, which
// receives the table in ECX and one integer stack argument (ret 4).
class Rva00354A60
{
public:
	void invoke();
};

class Rva00359530StringRecordTable
{
public:
	void release(int index);
};

class Rva0035B3D0RecordNode
{
public:
	Rva0035B3D0RecordNode *m_next;
};

struct Rva0035B3D0Record
{
	char m_unused[0x10];
	Rva0035B3D0RecordNode *m_head;
};

class Rva0035B3D0TableView
{
public:
	char m_unused[0x0C];
	Rva0035B3D0Record *m_records;
};

class Rva0035B3D0ListNode
{
public:
	void *bfmeDelete350E30(unsigned int flags);
	~Rva0035B3D0ListNode()
	{
		if (m_next)
			m_next->bfmeDelete350E30(1);
	}

	Rva0035B3D0ListNode *m_next;
	int m_recordIndex;
};

struct BfmeSubFFF
{
	char m_unused[4];
	Rva0035B3D0ListNode *m_first;
};

class BfmeThingFFF
{
public:
	void bfmeStepFFF(BfmeSubFFF *list, void *entryPointer);

private:
	char m_unused[0x2C];
	Rva0035B3D0TableView m_recordsAt2C;
};

void BfmeThingFFF::bfmeStepFFF(BfmeSubFFF *list, void *entryPointer)
{
	Rva0035B3D0ListNode *entry = (Rva0035B3D0ListNode *)entryPointer;
	Rva0035B3D0ListNode **link = &list->m_first;

	while (*link != entry)
	{
		Rva0035B3D0ListNode *previous = *link;
		if (previous == 0)
		{
			link = 0;
			break;
		}
		link = &previous->m_next;
	}

	if (link != 0)
	{
		*link = entry->m_next;
		entry->m_next = 0;
	}

	int index = entry->m_recordIndex;
	Rva0035B3D0TableView *records = &m_recordsAt2C;
	Rva0035B3D0Record *record = &records->m_records[index];
	Rva0035B3D0RecordNode *node = record->m_head;
	record->m_head = node->m_next;
	((Rva00354A60 *)node)->invoke();
	delete node;
	((Rva00359530StringRecordTable *)records)->release(index);

	delete entry;
}

// Retail 0x0035AD00, 143B. Like 0x0035AB70, released records lose their
// head and table index; retained records keep only the head node.
class Rva0035AD00OwnedNode : public Rva0035B3D0RecordNode
{
public:
	~Rva0035AD00OwnedNode() { ((Rva00354A60 *)this)->invoke(); }
};

struct Rva0035AD00Record
{
	int previous, next;
	void *name;
	unsigned char released, pad;
	unsigned short references;
	Rva0035B3D0RecordNode *nodes;
};

class Rva0035AD00Table
{
public:
	void cleanup();
	int *begin, *end, *capacity;
	Rva0035AD00Record *records;
	int unknown10, unknown14, freeHead, activeTail;
};

void Rva0035AD00Table::cleanup()
{
	Rva0035AD00Table *owner = this;
	int index = owner->activeTail;
	while (index != -1)
	{
		Rva0035AD00Record *record = owner->records + index;
		int previous = record->previous;
		if (record->released)
		{
			Rva0035B3D0RecordNode *node = record->nodes;
			record->nodes = record->nodes->m_next;
			((Rva00354A60 *)node)->invoke();
			delete node;
			((Rva00359530StringRecordTable *)owner)->release(index);
		}
		else
		{
			Rva0035B3D0RecordNode *first = record->nodes;
			while (first->m_next)
			{
				Rva0035B3D0RecordNode *node = first->m_next;
				Rva0035B3D0RecordNode *next = first->m_next->m_next;
				delete ((Rva0035AD00OwnedNode *)node);
				first->m_next = next;
			}
			record->references = 1;
		}
		index = previous;
	}
}
