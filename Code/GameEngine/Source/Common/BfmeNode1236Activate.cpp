// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Open-BFME5: retail 0x008D2810. Advance an active node of type 0x0d or 0x12
// and walk its child list; a type 0x0e node walks the alternate list.

class BfmeThingCBC
{
public:
	void bfmeStepCBC(int value);
};

class BfmeA1227
{
public:
	void bfmeDump1227(void *value, int index);
};

class BfmeNodeDX
{
public:
	void bfmeEmit1281(int mode, void *tail, int zero);
};

class BfmeFilterWalk1236
{
public:
	void bfmeFilterWalk1236();
	void *m_list;
};

class BfmeNode1236List
{
public:
	void bfmeProcess1236(void *walk, void *owner, int count);
	int m_count;
};

struct BfmeCountedList1236
{
	char m_padding00[8];
	BfmeNode1236List m_ops;
};

struct BfmeChild1236
{
	char m_padding00[0x0c];
	BfmeCountedList1236 *m_list;
	char m_padding10[8];
	int m_count;
	unsigned int m_flags;
	BfmeFilterWalk1236 m_walk20;
	BfmeFilterWalk1236 m_walk24;
	int m_pending;
	int m_limit;
};

class BfmeNode1236
{
public:
	void bfmeActivate1236();
	bool bfmeIsLive1236(unsigned int kind) const
	{
		return (m_flags & 0x3f) == kind && !((unsigned char)(~(m_flags >> 15)) & 1);
	}

private:
	void *m_vtable;
	unsigned int m_flags;
	char m_padding08[0x48];
	BfmeChild1236 *m_child;
};

extern unsigned char g_bfmeExtra1282Flags;
extern void *g_bfmeExtra1282;

void BfmeNode1236::bfmeActivate1236()
{
	unsigned int flags = m_flags;
	unsigned int type = flags & 0x3f;
	if (type == 0x0d && !((unsigned char)(~(flags >> 15)) & 1))
		goto activate;
	type = flags & 0x3f;
	if (type == 0x12 && !((unsigned char)(~(flags >> 15)) & 1))
		goto activate;
	goto other;
activate:
	BfmeChild1236 *child = m_child;
	child->m_pending = 0;
	if ((child->m_flags >> 25) & 1)
	{
		if (child->m_limit == 1)
			child->m_count = 0;
		else
			++child->m_count;
		int count = child->m_count;
		if (count == 1 && child->m_list->m_ops.m_count == 1)
		{
			child->m_count = 0;
			goto emit;
		}
		if (count == child->m_list->m_ops.m_count)
		{
			reinterpret_cast<BfmeThingCBC *>(this)->bfmeStepCBC(0);
			goto emit;
		}
	}
	if ((child->m_flags >> 25) & 1)
		child->m_list->m_ops.bfmeProcess1236(&child->m_walk24, this, child->m_count);
	if (child->m_flags & 0x02000000)
	{
		child->m_pending = -child->m_count;
		reinterpret_cast<BfmeA1227 *>(&child->m_list->m_ops)->bfmeDump1227(this, child->m_count);
		child->m_pending = child->m_count;
	}
emit:
	if (!((child->m_flags >> 24) & 1) || bfmeIsLive1236(0x12))
	{
		if (!(g_bfmeExtra1282Flags & 2))
			reinterpret_cast<BfmeNodeDX *>(this)->bfmeEmit1281(2, g_bfmeExtra1282, 1);
	}
	if ((child->m_flags >> 24) & 1)
	{
		reinterpret_cast<BfmeNodeDX *>(this)->bfmeEmit1281(1, g_bfmeExtra1282, 1);
		child->m_flags &= ~0x01000000;
	}
	child->m_walk24.bfmeFilterWalk1236();
	return;

other:
	type = flags & 0x3f;
	if (type == 0x0e && !((unsigned char)(~(flags >> 15)) & 1))
		m_child->m_walk20.bfmeFilterWalk1236();
}
