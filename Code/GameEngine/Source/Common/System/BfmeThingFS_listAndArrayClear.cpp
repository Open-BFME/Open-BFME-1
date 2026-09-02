// cl: /DNDEBUG /MD /EHsc
// stlport
// Open-BFME: two-pass list clear plus cookie-array teardown, retail 0x000FD0B0.
//
// A circular list of 0xC-byte nodes at this+0x10 is walked twice: first the
// owned pointer at +8 is destroyed, then each node is returned to the small
// allocator.  The sentinel is then reset to self-links and the cookie-prefixed
// 0xC-element array at this+8 is torn down with the EH vector destructor.

void __cdecl bfmeDeallocate(void *block, unsigned int bytes);

class BfmeOwnedPtr
{
public:
	virtual ~BfmeOwnedPtr(void);
};

struct BfmeListNode
{
	BfmeListNode *next;
	BfmeListNode *prev;
	BfmeOwnedPtr *value;
};

class BfmeArrayElem
{
public:
	~BfmeArrayElem(void);
	char m_bytes[0xC];
};

class BfmeListAndArray
{
	char m_prefix[8];
	BfmeArrayElem *m_array;
	int m_arrayTail;
	BfmeListNode *m_list;

public:
	void bfmeClear(void);
};

// ?bfmeClear@BfmeListAndArray@@QAEXXZ
void BfmeListAndArray::bfmeClear(void)
{
	BfmeListNode *sentinel = m_list;
	BfmeListNode *node = sentinel->next;

	while (node != sentinel)
	{
		delete node->value;
		node = node->next;
		sentinel = m_list;
	}

	sentinel = m_list;
	node = sentinel->next;
	while (node != sentinel)
	{
		BfmeListNode *current = node;
		node = node->next;
		bfmeDeallocate(current, sizeof(BfmeListNode));
		sentinel = m_list;
	}

	m_list->next = m_list;
	m_list->prev = m_list;

	if (m_array != 0)
	{
		delete[] m_array;
		m_array = 0;
		m_arrayTail = 0;
	}
}
