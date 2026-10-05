// ?calculate_009F4900@Gen009F5040@@QAEXPAUGen009F5040Node@@PAH11@Z
// partial score=0.6267 date=2026-10-05
struct Gen009F5040Item;

// Independently matched overlapping receiver views, both called without a
// receiver adjustment. These declarations do not assert inheritance.
class BfmeHostER
{
public:
	unsigned int bfmeIndexER(float value);
};
class BfmeHostES
{
public:
	unsigned int bfmeIndexES(float value);
};

struct Gen009F4900Value0
{
	char m_pad00[0x10];
	float m_value10;
};
struct Gen009F4900Value1
{
	float m_value00;
	float m_value04;
};

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

class Gen009F5040
{
public:
	void handle();
	__declspec(noinline) void calculate_009F4900(Gen009F5040Node *node,
		int *result28, int *result2c, int *result24);
	__declspec(noinline) void remove(Gen009F5040Node *node);
	void linkNode_009F4D80(Gen009F5040Node *node);

	Gen009F5040Bucket m_buckets[2];
	Gen009F5040Counter *m_rangeBegin;
	Gen009F5040Counter *m_rangeEnd;
	char m_pad20[0xcc];
	unsigned int m_mask;
	Gen009F5040Node *m_node;
};

// Retail preserves ECX for all four index calls and returns RET16. The
// first getter result remains live across the second virtual call.
void Gen009F5040::calculate_009F4900(Gen009F5040Node *node,
	int *result28, int *result2c, int *result24)
{
	Gen009F4900Value0 *value0 = (Gen009F4900Value0 *)node->m_item->getValue0();
	Gen009F4900Value1 *value1 = (Gen009F4900Value1 *)node->m_item->getValue1();
	float value10 = value0->m_value10;
	*result28 = ((BfmeHostER *)this)->bfmeIndexER(value1->m_value00 - value10);
	*result2c = ((BfmeHostES *)this)->bfmeIndexES(value1->m_value04 - value10);
	unsigned int difference = ((BfmeHostER *)this)->bfmeIndexER(value10 + value1->m_value00) ^ *result28;
	difference |= ((BfmeHostES *)this)->bfmeIndexES(value10 + value1->m_value04) ^ *result2c;
	*result24 = difference;
	if (difference != 0) {
		unsigned int v = difference;
		int r = 0;
		if (v & 0xffff0000) { v >>= 16; r = 16; }
		if (v & 0xff00) { v >>= 8; r |= 8; }
		if (v & 0xf0) { v >>= 4; r |= 4; }
		if (v & 0xc) { v >>= 2; r |= 2; }
		if (v & 2) r |= 1;
		unsigned int mask = ~(1u << r);
		*result28 &= mask;
		*result2c &= mask;
	}
}

void Gen009F5040::remove(Gen009F5040Node *node)
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

void Gen009F5040::handle()
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
			calculate_009F4900(node, &result28, &result2c, &result24);
			if (result28 != node->m_result28 || result2c != node->m_result2c ||
				result24 != node->m_result24)
				shouldProcess = true;
		}
		if (shouldProcess) {
			remove(node);
			linkNode_009F4D80(node);
		}

		node = m_node;
	}
}

// The retail call from handle() enters this body at 0x009F4D80.  Its two
// intrusive links are distinct: handle() unlinks the +0x18/+0x1C pair while
// this insertion uses the +0x10/+0x14 pair.
void Gen009F5040::linkNode_009F4D80(Gen009F5040Node *node)
{
	calculate_009F4900(node, &node->m_result28, &node->m_result2c, &node->m_result24);
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
