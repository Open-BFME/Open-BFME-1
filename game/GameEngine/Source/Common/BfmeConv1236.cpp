// Open-BFME5 conversions.

struct BfmeVec4_1236
{
	float x;
	float y;
	float z;
	float w;
};

class BfmeB1236
{
public:
	void bfmeApply1236(void *a);
	void bfmeEmit1236(void *a, int b, void *c);
	unsigned m_bfme00;
	unsigned m_bfme04;
	char m_bfmePad08[0x10 - 0x08];
	int m_bfme10;
	int m_bfme14;
	int m_bfme18;
	int m_bfme1c;
	int m_bfme20;
	int m_bfme24;
	BfmeVec4_1236 m_bfme28;
	BfmeVec4_1236 m_bfme38;
	int m_bfme48;
	void *m_bfme4c;
};

// Retail calls Gen_008D2C80::bfmePush (0x008D2C80) from this sequence; the
// mark step was a stand-in spelling of that same body.
class Gen_008D2C80
{
public:
	void bfmePush(void);
};

class BfmeA1236
{
public:
	void bfmeBegin1236();
	void bfmePush1236(void *a);
	void bfmeSet1236(void *a);
	void bfmePop1236();
	void bfmeEnd1236();
};

void bfmeGo1236(BfmeA1236 *a, BfmeB1236 *b, void *c)
{
	a->bfmeBegin1236();
	a->bfmePush1236(&b->m_bfme28);
	((Gen_008D2C80 *)a)->bfmePush();
	if ((b->m_bfme04 & 0x3f) == 0xf && !((unsigned char)(~(b->m_bfme04 >> 15)) & 1))
		b->bfmeApply1236(b->m_bfme4c);
	a->bfmeSet1236(&b->m_bfme10);
	b->bfmeEmit1236(a, 0, c);
	a->bfmePop1236();
	a->bfmeEnd1236();
}

struct BfmeTransform1236
{
	int m_bfme00;
	int m_bfme04;
	int m_bfme08;
	int m_bfme0c;
	int m_bfme10;
	int m_bfme14;
	int m_bfme18;
	int m_bfme1c;
	int m_bfme20;
	int m_bfme24;
	float m_bfme28;
	int m_bfme2c;
	int m_bfme30;
	int m_bfme34;
	int m_bfme38;
	float m_bfme3c;
	BfmeVec4_1236 m_bfme40;
	BfmeVec4_1236 m_bfme50;
};

extern BfmeTransform1236 *g_bfmeArenaCursor;
void bfmeCombine1236(BfmeTransform1236 *result, BfmeTransform1236 *left, BfmeTransform1236 *right);

void bfmeTransform1236(void *context, BfmeB1236 *b, void *tail)
{
	if ((b->m_bfme04 & 0x3f) == 0xf && !((unsigned char)(~(b->m_bfme04 >> 15)) & 1))
		b->bfmeApply1236(b->m_bfme4c);

	BfmeTransform1236 *previous = g_bfmeArenaCursor;
	BfmeTransform1236 *current = ++g_bfmeArenaCursor;
	current->m_bfme00 = b->m_bfme10;
	current->m_bfme04 = b->m_bfme14;
	current->m_bfme08 = 0;
	current->m_bfme0c = 0;
	current->m_bfme10 = b->m_bfme18;
	current->m_bfme14 = b->m_bfme1c;
	current->m_bfme18 = 0;
	current->m_bfme1c = 0;
	current->m_bfme20 = 0;
	current->m_bfme24 = 0;
	current->m_bfme28 = 1.0f;
	current->m_bfme2c = 0;
	current->m_bfme30 = b->m_bfme20;
	current->m_bfme34 = b->m_bfme24;
	current->m_bfme38 = 0;
	current->m_bfme3c = 1.0f;
	current->m_bfme40 = b->m_bfme28;
	current->m_bfme50 = b->m_bfme38;

	bfmeCombine1236(current, previous, current);
	current->m_bfme40.x *= previous->m_bfme40.x;
	current->m_bfme40.y *= previous->m_bfme40.y;
	current->m_bfme40.z *= previous->m_bfme40.z;
	current->m_bfme40.w *= previous->m_bfme40.w;
	current->m_bfme50.x += previous->m_bfme50.x;
	current->m_bfme50.y += previous->m_bfme50.y;
	current->m_bfme50.z += previous->m_bfme50.z;
	current->m_bfme50.w += previous->m_bfme50.w;
	b->bfmeEmit1236(context, (int)current, tail);
	--g_bfmeArenaCursor;
}

class BfmeZero1236
{
public:
	BfmeZero1236();

private:
	int m_values[32];
	int m_extra;
};

BfmeZero1236::BfmeZero1236()
{
	m_extra = 0;
	for (int i = 0; i < 32; ++i)
		m_values[i] = 0;
}

class BfmeChild1236;

class BfmeNode1236
{
public:
	void bfmeVisit1236();

private:
	void *m_vtable;
	unsigned m_flags;
	char m_padding08[0x48];
	BfmeChild1236 *m_child;
	char m_padding54[4];

public:
	BfmeNode1236 *m_next;
};

struct BfmeList1236
{
	BfmeNode1236 *m_head;
};

class BfmeWalk1236
{
public:
	__declspec(noinline) void bfmeWalk1236();

private:
	BfmeList1236 *m_list;
};

void BfmeWalk1236::bfmeWalk1236()
{
	BfmeNode1236 *node = m_list->m_head->m_next;
	while (node) {
		node->bfmeVisit1236();
		node = node->m_next;
	}
}

struct BfmeChild1236
{
	char m_padding00[0x20];
	void *m_value20;
	BfmeWalk1236 m_walk;
	char m_padding28[0x44];
	int m_value6c;
};

extern void (__cdecl *g_bfmeFreePair1286)(void *storage, int count);
extern char g_bfmeSpecialBlock1286;

#define BIT15(x) (((unsigned char)~((x) >> 15)) & 1)

// Retail at 0x008ADB50 keeps `this` in the callee-saved ESI, the raw m_flags in
// EAX and the masked kind in EDX, and repeats an unmerged
// `mov ecx,eax; shr ecx,0xf; not cl; test cl,1` in both walk cases.  Hoisting the
// mask into a named `kind` local lets MSVC 7.1 fold the tail of the 0x0d and
// 0x12 blocks into the function's return and re-use the flags register for the
// shift, which drops both copies and moves the child load to ECX.  Spelling
// `flags & 0x3f` out at each compare keeps the three compares as independent
// blocks and reproduces the register assignment.
void BfmeNode1236::bfmeVisit1236()
{
	unsigned flags = this->m_flags;

	if ((flags & 0x3f) == 0x0d)
	{
		if (!BIT15(flags))
			goto do_walk;
	}
	if ((flags & 0x3f) == 0x12)
	{
		if (!BIT15(flags))
			goto do_walk;
	}
	if ((flags & 0x3f) == 0x0f)
	{
		if (BIT15(flags))
			return;
		BfmeChild1236 *child = this->m_child;
		void *value = child->m_value20;
		if (value != 0 && value != &g_bfmeSpecialBlock1286)
		{
			child->m_value6c = 6;
			g_bfmeFreePair1286(value, 2);
		}
		child->m_value20 = 0;
	}
	return;

do_walk:
	this->m_child->m_walk.bfmeWalk1236();
}
