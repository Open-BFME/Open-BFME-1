// ?rva0035bce0@BfmeThingFFF@@QAEXPAPAURva0035BCE0Entry@@PAU2@@Z
// partial score=0.76 date=2026-09-24
// The neighboring methods at 0x0035B3D0 and 0x0035BDE0 identify this receiver as BfmeThingFFF.
// Retail reads the version table at this+0x18 and calls this body through thunk 0x000196D7.
// No caller names this method, so the address-derived name keeps its identity open.

struct Rva0035BCE0Entry;

struct Rva00354A00Node
{
	~Rva00354A00Node();

	Rva00354A00Node *m_next;      // +0x0  version-chain link
	unsigned char m_unused4[4];   // +0x4
	Rva0035BCE0Entry *m_child;    // +0x8  first of a child entry chain
	Rva0035BCE0Entry *m_sibling;  // +0xC  head-of-list entry stepped via bfmeStepFFF
};

struct Rva0035BCE0Entry
{
	Rva0035BCE0Entry *m_next;   // +0x0
	int m_tableIndex;           // +0x4
	int m_targetVersion;        // +0x8
};

struct Rva0035BCE0TableRow
{
	unsigned char m_unused[0xE]; // +0x0
	short m_version;             // +0xE
	Rva00354A00Node *m_head;     // +0x10
};

struct BfmeSubFFF;

class Rva00359330StringRecordTable
{
public:
	void release(int index);
};

struct ScriptPoolObject
{
	void deleteInstance(int destroy);
};

class BfmeThingFFF
{
public:
	void bfmeStepFFF(BfmeSubFFF *list, void *entryPointer);
	void rva0035bce0(Rva0035BCE0Entry **listSlot, Rva0035BCE0Entry *entry);

private:
	unsigned char m_unused[0x18];
	Rva0035BCE0TableRow *m_table; // +0x18
};

void BfmeThingFFF::rva0035bce0(Rva0035BCE0Entry **listSlot, Rva0035BCE0Entry *entry)
{
	int tableIndex = entry->m_tableIndex;
	int targetVersion = entry->m_targetVersion;
	Rva0035BCE0TableRow *tableEntry = &m_table[tableIndex];
	int version = tableEntry->m_version;
	Rva00354A00Node *node;
	if (version > targetVersion)
	{
		int diff = version - targetVersion;
		node = tableEntry->m_head;
		do
		{
			node = node->m_next;
		} while (--diff);
	}
	else
	{
		node = tableEntry->m_head;
	}

	Rva0035BCE0Entry *child = node->m_child;
	if (child)
	{
		do
		{
			rva0035bce0(&node->m_child, child);
			child = node->m_child;
		} while (child);
	}

	Rva0035BCE0Entry *sibling = node->m_sibling;
	if (sibling)
	{
		do
		{
			bfmeStepFFF((BfmeSubFFF *)&node->m_child, sibling);
			sibling = node->m_sibling;
		} while (sibling);
	}

	Rva0035BCE0Entry **link = listSlot;
	while (*link != entry)
	{
		Rva0035BCE0Entry *previous = *link;
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

	Rva0035BCE0TableRow *poppedRow = &m_table[entry->m_tableIndex];
	Rva00354A00Node *headNode = poppedRow->m_head;
	poppedRow->m_head = headNode->m_next;
	delete headNode;

	((Rva00359330StringRecordTable *)((char *)this + 0xC))->release(entry->m_tableIndex);

	ScriptPoolObject *leftover = (ScriptPoolObject *)entry->m_next;
	if (leftover)
		leftover->deleteInstance(1);
	delete entry;
}
