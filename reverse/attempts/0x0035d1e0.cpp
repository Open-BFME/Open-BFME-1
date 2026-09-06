// ?addNode@Rva0035D1E0StringRecordTable@@QAEHPAVAsciiString@@PBV?$list@PAVFXNugget@@V?$allocator@PAVFXNugget@@@_STL@@@_STL@@@Z
// partial score=0.5 date=2026-09-06
// cl: /O2 /Ob0
// Fuzzy twin (ratio 0.896) of Rva00359330StringRecordTable::addNode (0x0035CC50,
// Rva00359330StringRecordAddNode.cpp): same findOrCreateIndex/operator-new/link-insert
// shape and the SAME table+record layout, but the allocated node is a different type:
// a 0x44-byte node whose only non-trivial member is a 4-byte STLport
// list<FXNugget*, allocator<FXNugget*>> at +0x04, copy-constructed from the "node"
// argument directly (see S3RefCountedListCopies.cpp for the same list recipe).

namespace _STL
{

template <class T> class allocator
{
};

template <class T, class A> class list
{
public:
	list(const list &other);					// retail 0x00887B60 / pinned 0x0002F333 thunk

	void *m_bfmeNode;
};

}

class FXNugget;

typedef _STL::list<FXNugget *, _STL::allocator<FXNugget *> > BfmeNuggetList;

class AsciiString
{
};

struct Rva0035D1E0Record
{
	int m_previous;
	int m_next;
	AsciiString m_name;
	unsigned char m_released;
	unsigned char m_pad;
	unsigned short m_references;
	void *m_nodes;
};

class Rva0035D1E0Node
{
public:
	Rva0035D1E0Node *m_link;					// +0x00
	BfmeNuggetList m_particles;					// +0x04
	char m_pad[0x44 - 0x08];					// pad node to 0x44 bytes

	Rva0035D1E0Node(const BfmeNuggetList *nuggets);
};

Rva0035D1E0Node::Rva0035D1E0Node(const BfmeNuggetList *nuggets)
	: m_particles(*nuggets)
{
}

class Rva0035D1E0StringRecordTable
{
public:
	int addNode(AsciiString *name, const BfmeNuggetList *nuggets);
	void release(int index);

private:
	int findOrCreateIndex(AsciiString *name);

	int *m_nameIndexesBegin;
	int *m_nameIndexesEnd;
	int *m_nameIndexesCapacity;
	Rva0035D1E0Record *m_records;
	int m_10;
	int m_14;
	int m_freeHead;
	int m_activeTail;
};

int Rva0035D1E0StringRecordTable::addNode(AsciiString *name, const BfmeNuggetList *nuggets)
{
	int index = findOrCreateIndex(name);
	if (index != -1) {
		Rva0035D1E0Record *records = m_records;
		try {
			Rva0035D1E0Record *record = records + index;
			Rva0035D1E0Node *newNode = new Rva0035D1E0Node(nuggets);
			newNode->m_link = (Rva0035D1E0Node *)record->m_nodes;
			record->m_nodes = newNode;
		} catch (...) {
			release(index);
			throw;
		}
	}
	return index;
}
