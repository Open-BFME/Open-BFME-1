// ?bfmeVisit1236@BfmeNode1236@@QAEXXZ
// partial score=0.72 date=2026-09-03
// Open-BFME5 conversion, recovered from reverse/attempts/0x008adb50.cpp.
// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class BfmeWalk1236
{
public:
	void bfmeWalk1236();
};

struct BfmeChild1236
{
	char m_padding00[0x20];
	void *m_value20;
	BfmeWalk1236 m_walk;
	char m_padding28[0x44];
	int m_value6c;
};

extern void (__cdecl *g_bfmeFn01337874)(void *value, int count);
extern char g_bfmeSentinel012D5598;

class BfmeNode1236
{
public:
	void bfmeVisit1236();

private:
	void *m_vtable;
	unsigned m_flags;
	char m_padding08[0x48];
	BfmeChild1236 *m_child;
};

void BfmeNode1236::bfmeVisit1236()
{
	BfmeNode1236 *self = this;
	unsigned flags = self->m_flags;
	unsigned kind = flags;
	kind &= 0x3f;

	if (kind == 0x0d)
		goto check_d;
	goto check_12;

check_d:
	{
		unsigned bit = flags;
		bit >>= 15;
		if ((((unsigned char)~bit) & 1) == 0)
			goto do_walk;
	}

check_12:
	if (kind != 0x12)
		goto check_f;
	{
		unsigned bit = flags;
		bit >>= 15;
		if ((((unsigned char)~bit) & 1) != 0)
			goto check_f;
	}

do_walk:
	self->m_child->m_walk.bfmeWalk1236();
	return;

check_f:
	if (kind != 0x0f)
		return;
	{
		unsigned bit = flags;
		bit >>= 15;
		if ((((unsigned char)~bit) & 1) != 0)
			return;
	}

	BfmeChild1236 *child = self->m_child;
	void *value = child->m_value20;
	if (value != 0 && value != &g_bfmeSentinel012D5598)
	{
		child->m_value6c = 6;
		g_bfmeFn01337874(value, 2);
	}
	child->m_value20 = 0;
}
