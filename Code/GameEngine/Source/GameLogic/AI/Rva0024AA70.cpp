// cl: /DNDEBUG /MD /EHsc
// Open-BFME: Horde transport admission and linked-member update, retail 0x0024AA70.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	char m_head[4];
	Object *m_next;
	char m_gap[0x120];
	unsigned int m_flags;
	unsigned int m_status;
};

class BfmeRvaAA70Candidate
{
public:
	char m_head[4];
	BfmeRvaAA70Candidate *m_next;
	char m_gap[0xc4];
	unsigned int m_flags;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
};

class Rva2225E0Filter
{
public:
	bool accepts(Object *object, Player *count);
};

class BfmeRvaBA90Member
{
public:
	int getCount(void);
};

class Rva0025FA10Object
{
public:
	bool hasCondition(int value);
};

class BfmeRvaAA70MemberAction
{
public:
	void set(int value);
	void notify(void);
};

class BfmeRvaAA70Owner
{
public:
	void finish(Object *object);
};

class BfmeSubBIA
{
public:
	int ask(void);
};

struct BfmeRvaAA70Node
{
	BfmeRvaAA70Node *m_next;
	BfmeRvaAA70Node *m_previous;
	Object *m_object;
};

struct BfmeRvaAA70Probe
{
	char m_head[0x224];
	Rva2225E0Filter m_filter;
	int m_capacity;
};

extern BfmeRvaAA70Probe *g_bfmeRvaAA70Probe;

class Rva0024AA70
{
public:
	void update(Object *object);

	char m_head[0xcc];
	BfmeRvaAA70Node *m_sentinel;
	int m_count;
	unsigned char m_done;
};

void Rva0024AA70::update(Object *object)
{
	BfmeRvaBA90Member *counter =
		*(BfmeRvaBA90Member **)((char *)this - 0x18);
	BfmeRvaAA70Probe *probe =
		*(BfmeRvaAA70Probe **)((char *)this - 0x1c);
	int count = counter->getCount();
	if (probe->m_filter.accepts(object, (Player *)count) &&
		probe->m_capacity > 0)
	{
		BfmeRvaAA70Node *sentinel = m_sentinel;
		BfmeRvaAA70Node *node =
			(BfmeRvaAA70Node *)operator new(12);
		Object **slot = &node->m_object;
		if (slot != 0)
			*slot = object;
		BfmeRvaAA70Node *previous = sentinel->m_previous;
		node->m_next = sentinel;
		node->m_previous = previous;
		previous->m_next = node;
		sentinel->m_previous = node;
		m_count++;

		if (!((Rva0025FA10Object *)object)->hasCondition(0x14))
			return;
		((BfmeRvaAA70MemberAction *)object)->set(0x14);
		unsigned char status = (unsigned char)object->m_status;
		unsigned int mask = 0x80;
		if ((status & mask) == 0)
		{
			object->m_status |= mask;
			((BfmeRvaAA70MemberAction *)object)->notify();
		}
		return;
	}

	unsigned char flags = (unsigned char)object->m_flags;
	unsigned int mask = 0x40;
	if ((flags & mask) == 0)
	{
		object->m_flags |= mask;
		((BfmeRvaAA70MemberAction *)object)->notify();
	}
	((BfmeRvaAA70Owner *)this)->finish(object);
	object = object->m_next;
	Object *candidate;
	if (object == 0)
		candidate = 0;
	else if (object->m_next != 0)
		candidate = (Object *)((BfmeSubBIA *)object->m_next)->ask();
	else
		candidate = object;
	if (((BfmeRvaAA70Candidate *)candidate)->m_flags & 0x400000)
		m_done = 1;
}
