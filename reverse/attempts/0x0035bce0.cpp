// ?rva0035bce0@BfmeThingFFF@@QAEXPAPAURva0035BCE0Entry@@PAU2@@Z
// partial score=0.16 date=2026-09-20
// Address-derived reconstruction of retail 0x0035BCE0 (carved, 201 B).
// The three stack/register fields on the second argument (next-link at +0,
// table index at +4, target version at +8) match the ListNode shape proven
// by the matched sibling 0x0035B3D0 (BfmeThingFFF::bfmeStepFFF,
// BfmeThingFFFStep.cpp), which this body calls directly with the same
// two-pointer ABI.  The version-chain node reuses the exact destructor
// proven at 0x00354A00 (Rva00354A00Node, Rva00354A00NodeDestructor.cpp) --
// same four-field, next-link-prefixed shape -- so this body walks and frees
// nodes of that class.  The receiver's +0xC subobject is the StringRecordTable
// proven at 0x00359330 (Rva00359330StringRecordRelease.cpp); +0x18 is a
// pointer to a 20-byte-stride table of version-chain heads (index and short
// version proven by the field reads at table-entry +0xE/+0x10).  No caller
// resolves a name for this method or its receiver beyond the ABI above.

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
	Rva0035BCE0TableRow *tableEntry = &m_table[entry->m_tableIndex];
	Rva00354A00Node *node = tableEntry->m_head;
	short version = tableEntry->m_version;
	int targetVersion = entry->m_targetVersion;
	if (version > targetVersion)
	{
		int diff = version - targetVersion;
		do
		{
			node = node->m_next;
		} while (--diff);
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
