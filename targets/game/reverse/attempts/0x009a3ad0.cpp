// ?refresh009A3AD0@Rva009A4620CollisionData@@QAEXXZ
// partial score=0.24 date=2026-09-28
// cl: /O2 /DNDEBUG /MD /EHsc
// Retail 0x009A3AD0 (1244 bytes, plain ret): the second of the three calls
// the collision data's update (0x009A4A30) brackets with its busy flag at
// +0xC06D. __thiscall on the owner (mov esi,ecx). Address-derived identity.
//
// What the bytes show. The owner keeps its nodes on a root list (+0x00, next
// at node+0x0C), counts them at +0x04, queues moved nodes on a dirty list
// (+0x08, next at node+0x14), and keeps one sorted endpoint list per axis at
// +0x0C (the count of sorted axes is at +0xC068, a force-rebuild flag at
// +0xC06C). Every node carries two endpoints per axis (0x14 bytes each:
// prev, next, node, max-bit, value) from +0x24. Moved nodes are re-inserted
// into each axis list in value order, reporting the nodes whose intervals
// they cross to 0x009A3960; when the summed movement score passes the node
// count, or the rebuild flag is set, the tables are recycled and every axis
// is swept again from scratch; otherwise each axis is insertion-sorted, with
// crossings reported to 0x009A3960 (max passes min) or 0x009A3540 (min
// passes max).

typedef float Real;

void __cdecl operator delete(void *block);

class Rva009A45A0CollisionData;

struct Rva009A3AD0Endpoint
{
	Rva009A3AD0Endpoint *m_prev;
	Rva009A3AD0Endpoint *m_next;
	Rva009A45A0CollisionData *m_node;
	bool m_isMax : 1;
	Real m_value;

	bool isMin() const { return !m_isMax; }
};

struct Rva009A3AD0Interval
{
	Rva009A3AD0Endpoint m_min;
	Rva009A3AD0Endpoint m_max;
};

// The node: its destructor is the matched 0x009A2390 body.
class Rva009A45A0CollisionData
{
public:
	~Rva009A45A0CollisionData();

	void *m_owner;
	void *m_source;
	void *m_rootPrev;
	Rva009A45A0CollisionData *m_rootNext;
	void *m_dirtyPrev;
	Rva009A45A0CollisionData *m_dirtyNext;
	Rva009A45A0CollisionData **m_openPrev;
	Rva009A45A0CollisionData *m_openNext;
	int m_rva009A3AD0_020;
	union
	{
		Rva009A3AD0Endpoint m_endpoints[6];
		Rva009A3AD0Interval m_intervals[3];
	};
};

class Rva009A2420CollisionNode
{
public:
	unsigned int getMovementScore(bool allowCache);
};

class BfmeLinkXX
{
public:
	void bfmeDropXX(void);
};

class Rva009A36F0Thing;

class Rva009A36F0Owner
{
public:
	void unlinkChain(Rva009A36F0Thing *thing);
};

struct Rva009A3540OpaqueOwner;

class Rva009A3540PairOwner
{
public:
	void removePair(Rva009A3540OpaqueOwner *first, Rva009A3540OpaqueOwner *second);
};

class Rva009A2A50Table
{
public:
	void recycleBuckets009A2A50();

private:
	unsigned char m_storage[0xae10 - 0x18];
};

class Rva009A2B80Owner
{
public:
	void clear();

private:
	unsigned char m_storage[0xc068 - 0xae10];
};

class Rva009A4620CollisionData
{
public:
	void refresh009A3AD0();
	void rva009A3960(Rva009A45A0CollisionData *first, Rva009A45A0CollisionData *second);
	void rva009A2750();
	void insertSorted009A3AD0(Rva009A45A0CollisionData *node, Rva009A3AD0Interval *axis, Rva009A3AD0Endpoint **head);
	void pushFront009A3AD0(Rva009A3AD0Interval *axis, Rva009A3AD0Endpoint **head);

	Rva009A45A0CollisionData *m_root;
	unsigned int m_nodeCount;
	Rva009A45A0CollisionData *m_dirty;
	Rva009A3AD0Endpoint *m_axisHeads[3];
	Rva009A2A50Table m_table;
	Rva009A2B80Owner m_owner;
	unsigned int m_axisCount;
	bool m_rebuild;
};

__forceinline void Rva009A4620CollisionData::insertSorted009A3AD0(Rva009A45A0CollisionData *node, Rva009A3AD0Interval *axis, Rva009A3AD0Endpoint **head)
{
	Rva009A3AD0Endpoint *cur = *head;
	Rva009A3AD0Endpoint *prev = 0;
	Rva009A45A0CollisionData *open = 0;
	Real value = axis->m_max.m_value;
	while (cur != 0 && !(cur->m_value > value))
	{
		if (cur->isMin())
		{
			cur->m_node->m_openPrev = &open;
			cur->m_node->m_openNext = open;
			if (cur->m_node->m_openNext != 0)
				cur->m_node->m_openNext->m_openPrev = &cur->m_node->m_openNext;
			open = cur->m_node;
		}
		else
		{
			if (cur->m_node->m_openNext != 0)
				cur->m_node->m_openNext->m_openPrev = cur->m_node->m_openPrev;
			*cur->m_node->m_openPrev = cur->m_node->m_openNext;
			cur->m_node->m_openPrev = 0;
		}
		prev = cur;
		cur = cur->m_next;
	}

	axis->m_max.m_prev = prev;
	axis->m_max.m_next = cur;
	if (prev != 0)
		prev->m_next = &axis->m_max;
	else
		*head = &axis->m_max;
	if (cur != 0)
		axis->m_max.m_next->m_prev = &axis->m_max;
	prev = &axis->m_max;

	if (cur != 0)
	{
		while (open != 0)
		{
			rva009A3960(open, node);
			Rva009A45A0CollisionData *closed = open;
			if (closed->m_openNext != 0)
				closed->m_openNext->m_openPrev = closed->m_openPrev;
			*closed->m_openPrev = closed->m_openNext;
			closed->m_openPrev = 0;
		}
		value = axis->m_min.m_value;
		do
		{
			if (!(cur->m_value < value))
				break;
			if (cur->isMin())
				rva009A3960(cur->m_node, node);
			prev = cur;
			cur = cur->m_next;
		}
		while (cur != 0);
	}

	axis->m_min.m_prev = prev;
	axis->m_min.m_next = cur;
	prev->m_next = &axis->m_min;
	if (cur != 0)
		axis->m_min.m_next->m_prev = &axis->m_min;
}

__forceinline void Rva009A4620CollisionData::pushFront009A3AD0(Rva009A3AD0Interval *axis, Rva009A3AD0Endpoint **head)
{
	axis->m_min.m_prev = 0;
	axis->m_min.m_next = *head;
	if (*head != 0)
		(*head)->m_prev = &axis->m_min;
	*head = &axis->m_min;
	axis->m_max.m_prev = 0;
	axis->m_max.m_next = *head;
	if (*head != 0)
		(*head)->m_prev = &axis->m_max;
	*head = &axis->m_max;
}

void Rva009A4620CollisionData::refresh009A3AD0()
{
	unsigned int totalScore = 0;
	Rva009A45A0CollisionData *node = m_dirty;
	while (node != 0)
	{
		unsigned int score = ((Rva009A2420CollisionNode *)node)->getMovementScore(true);
		if (score == 0)
		{
			node = node->m_dirtyNext;
			continue;
		}
		totalScore += score;
		((Rva009A36F0Owner *)this)->unlinkChain((Rva009A36F0Thing *)node);
		Rva009A45A0CollisionData *next = node->m_dirtyNext;
		if (node->m_source != 0)
		{
			if (node->m_endpoints[0].m_prev != 0)
			{
				unsigned int index = 0;
				do
				{
					Rva009A3AD0Endpoint *endpoint = &node->m_endpoints[index];
					if (endpoint->m_prev != 0)
						endpoint->m_prev->m_next = endpoint->m_next;
					else
						m_axisHeads[index >> 1] = endpoint->m_next;
					if (endpoint->m_next != 0)
						endpoint->m_next->m_prev = endpoint->m_prev;
					endpoint->m_prev = 0;
					endpoint->m_next = 0;
					++index;
				}
				while (index < 6);
			}

			unsigned int k = 0;
			do
			{
				if (k < m_axisCount && !m_rebuild)
					insertSorted009A3AD0(node, &node->m_intervals[k], &m_axisHeads[k]);
				else
					pushFront009A3AD0(&node->m_intervals[k], &m_axisHeads[k]);
				++k;
			}
			while (k < 3);

			((BfmeLinkXX *)node)->bfmeDropXX();
		}
		else
		{
			delete node;
		}
		node = next;
	}

	while (m_dirty != 0)
	{
		totalScore += ((Rva009A2420CollisionNode *)m_dirty)->getMovementScore(false);
		((BfmeLinkXX *)m_dirty)->bfmeDropXX();
	}

	if (m_root == 0)
		return;

	if (totalScore * 100 <= m_nodeCount * 100 && !m_rebuild)
	{
		for (unsigned int k = 0; k < m_axisCount; ++k)
		{
			Rva009A3AD0Endpoint **head = &m_axisHeads[k];
			Rva009A3AD0Endpoint *cur = (*head)->m_next;
			while (cur != 0)
			{
				if (cur->m_prev->m_value <= cur->m_value)
				{
					cur = cur->m_next;
					continue;
				}
				Rva009A3AD0Endpoint *pos = cur;
				if (cur->m_prev != 0)
				{
					do
					{
						Rva009A3AD0Endpoint *before = pos->m_prev;
						if (!(before->m_value > cur->m_value))
							break;
						if (before->m_isMax && cur->isMin())
							rva009A3960(before->m_node, cur->m_node);
						else if (before->isMin() && cur->m_isMax)
							((Rva009A3540PairOwner *)this)->removePair(
								(Rva009A3540OpaqueOwner *)before->m_node,
								(Rva009A3540OpaqueOwner *)cur->m_node);
						pos = pos->m_prev;
					}
					while (pos->m_prev != 0);
				}

				Rva009A3AD0Endpoint *next = cur->m_next;
				if (cur->m_prev != 0)
					cur->m_prev->m_next = cur->m_next;
				else
					*head = cur->m_next;
				if (cur->m_next != 0)
					cur->m_next->m_prev = cur->m_prev;
				cur->m_prev = 0;
				cur->m_next = 0;

				cur->m_prev = pos->m_prev;
				cur->m_next = pos;
				pos->m_prev = cur;
				if (cur->m_prev != 0)
					cur->m_prev->m_next = cur;
				else
					*head = cur;
				cur = next;
			}
		}
		return;
	}

	m_rebuild = false;
	m_table.recycleBuckets009A2A50();
	m_owner.clear();
	for (Rva009A45A0CollisionData *root = m_root; root != 0; root = root->m_rootNext)
		root->m_rva009A3AD0_020 = 0;
	rva009A2750();

	for (unsigned int k = 0; k < m_axisCount; ++k)
	{
		Rva009A45A0CollisionData *open = 0;
		for (Rva009A3AD0Endpoint *cur = m_axisHeads[k]; cur != 0; cur = cur->m_next)
		{
			if (cur->isMin())
			{
				for (Rva009A45A0CollisionData *other = open; other != 0; other = other->m_openNext)
					rva009A3960(other, cur->m_node);
				cur->m_node->m_openPrev = &open;
				cur->m_node->m_openNext = open;
				if (cur->m_node->m_openNext != 0)
					cur->m_node->m_openNext->m_openPrev = &cur->m_node->m_openNext;
				open = cur->m_node;
			}
			else
			{
				if (cur->m_node->m_openNext != 0)
					cur->m_node->m_openNext->m_openPrev = cur->m_node->m_openPrev;
				*cur->m_node->m_openPrev = cur->m_node->m_openNext;
				cur->m_node->m_openPrev = 0;
			}
		}
	}
}
