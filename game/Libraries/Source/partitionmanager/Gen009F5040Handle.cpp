struct Gen009F5040Item;

struct Gen009F5040Node
{
	char m_pad00[4];
	Gen009F5040Item *m_item;
	char m_pad08[8];
	Gen009F5040Node **m_secondaryPreviousLink;
	Gen009F5040Node *m_secondaryNext;
	Gen009F5040Node **m_previousLink;
	Gen009F5040Node *m_next;
	volatile int m_index;
	int m_result24;
	int m_result28;
	int m_result2c;
};

struct Gen009F5040Item
{
	virtual void *getValue0();
	virtual void *getValue1();
	virtual void *getValue2();
	virtual void *getValue3();
	virtual void *getValue4();
	virtual void *getValue5();
	virtual void *getValue6();
	virtual int getIndex();
};

struct Gen009F5040Counter
{
	int m_value;
	Gen009F5040Node *m_head;
};

struct Gen009F5040Bucket
{
	Gen009F5040Counter *m_counter;
	int m_pad04;
	int m_pad08;
};

class PartitionManagerImpl
{
public:
	void Update();
	__declspec(noinline) void _RemoveObjectFromTree(Gen009F5040Node *node);
	void _InsertObjectIntoTree(Gen009F5040Node *node);

	Gen009F5040Bucket m_buckets[2];
	Gen009F5040Counter *m_rangeBegin;
	Gen009F5040Counter *m_rangeEnd;
	char m_pad20[0xcc];
	unsigned int m_mask;
	Gen009F5040Node *m_node;
};

// Retail passes ECX plus four stack arguments to 0x009F4900. That body
// retains ECX for nested calls and returns RET16. The generated
// zero-argument export below does not describe that native ABI.
extern void d_009f4900();

static __forceinline void calculate(PartitionManagerImpl *self, Gen009F5040Node *node,
	int *result28, int *result2c, int *result24)
{
	typedef void (PartitionManagerImpl::*Fn)(Gen009F5040Node *, int *, int *, int *);
	union { void (*fn)(); Fn call; } u = { d_009f4900 };
	(self->*u.call)(node, result28, result2c, result24);
}

void PartitionManagerImpl::_RemoveObjectFromTree(Gen009F5040Node *node)
{
	if (node->m_secondaryNext != 0)
		node->m_secondaryNext->m_secondaryPreviousLink = node->m_secondaryPreviousLink;
	*node->m_secondaryPreviousLink = node->m_secondaryNext;

	node->m_secondaryPreviousLink = 0;
	Gen009F5040Counter *counter = m_buckets[node->m_index + 2].m_counter;

	Gen009F5040Counter *rangeEnd = m_rangeEnd;
	Gen009F5040Counter *rangeBegin = m_rangeBegin;
	unsigned int mask = m_mask >> 1;
	unsigned int count = (unsigned int)(rangeEnd - rangeBegin) >> 2;
	while (count != 0) {
		if ((node->m_result24 & mask) != 0)
			return;
		--counter->m_value;
		int step = (node->m_result2c & mask) != 0 ? 2 : 0;
		step += ((node->m_result28 & mask) != 0);
		counter += step * count + 1;
		count >>= 2;
		mask >>= 1;
	}
}

void PartitionManagerImpl::Update()
{
	Gen009F5040Node *node = m_node;
	if (node == 0)
		return;

	while (node != 0) {
		if (node->m_next != 0)
			node->m_next->m_previousLink = node->m_previousLink;
		*node->m_previousLink = node->m_next;
		node->m_previousLink = 0;

		bool shouldProcess = node->m_index != node->m_item->getIndex() + 1;
		if (!shouldProcess) {
			int result28;
			int result2c;
			int result24;
			calculate(this, node, &result28, &result2c, &result24);
			if (result28 != node->m_result28 || result2c != node->m_result2c ||
				result24 != node->m_result24)
				shouldProcess = true;
		}
		if (shouldProcess) {
			_RemoveObjectFromTree(node);
			_InsertObjectIntoTree(node);
		}

		node = m_node;
	}
}

// The retail call from Update() enters this body at 0x009F4D80.  Its two
// intrusive links are distinct: Update() unlinks the +0x18/+0x1C pair while
// this insertion uses the +0x10/+0x14 pair.
void PartitionManagerImpl::_InsertObjectIntoTree(Gen009F5040Node *node)
{
	calculate(this, node, &node->m_result28, &node->m_result2c, &node->m_result24);
	int index = node->m_item->getIndex();
	if (index < -1 || index >= 16)
		index = -1;
	Gen009F5040Counter *counter = m_buckets[index + 3].m_counter;
	unsigned int mask = m_mask >> 1;
	unsigned int count = (unsigned int)(m_rangeEnd - m_rangeBegin) >> 2;
	while (count != 0) {
		if (node->m_result24 & mask)
			break;
		++counter->m_value;
		int step = ((node->m_result2c & mask) != 0 ? 2 : 0);
		step += ((node->m_result28 & mask) != 0);
		counter += step * count + 1;
		count >>= 2;
		mask >>= 1;
	}
	Gen009F5040Node **slot = &counter->m_head;
	node->m_secondaryPreviousLink = slot;
	node->m_secondaryNext = *slot;
	if (node->m_secondaryNext != 0)
		node->m_secondaryNext->m_secondaryPreviousLink = &node->m_secondaryNext;
	*slot = node;
	node->m_index = index + 1;
}
