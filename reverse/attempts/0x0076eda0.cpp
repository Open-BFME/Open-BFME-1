// ?method@BfmeRva76EDA0@@QAEXHPAUBfmeRva76EDA0Out@@0@Z
// partial score=0.2 date=2026-09-05
// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: address-derived body, retail 0x0076EDA0, 456 bytes. Neighbours
// (0x0076EFE0 Rva0076EFE0::go, 0x0076F610 ParticleSys list ctor) and the
// same-dump sibling at 0x00764290 place this in the W3DDevice GameClient
// Drawable family; the -0xC adjustor call to
// ?target@Rva0076CAF0ConditionalDispatch@@QAEXXZ (pinned) matches the same
// interface used by the sibling bodies at 0x00764290/0x007626F0. Owning
// class/method name unproven within budget; landed under an address-derived
// name per IDENTITY POLICY.
//
// Shape: thiscall, 3 stack args (index, Coord2D *outA, Coord2D *outB), "ret
// 0xc". A stale-stamp guard (g_Va012F8064 vs this+0x90) forwards through the
// conditional-dispatch interface, then an index 0..2 selects one of three
// 0x1c-byte array slots at `this + index*0x1c`; a parallel "type" dword 8
// slots further picks between three blend cases (1/3/5) and a default that
// zeroes both outputs.

class Rva0076CAF0ConditionalDispatch
{
public:
	void target();
};

class BfmeRva76EDA0GetterObj
{
public:
	virtual void *s0();
	virtual void *s1();
	virtual void *s2();
	virtual int s3(); // +0x10 -> declared 4th slot below is the real one used
	virtual int s4();
};

extern int g_Va012F8064;
extern float g_bfmeDefaultBU; // 0x01075334
extern float g_Va01123C58;    // 0x01123C58

struct BfmeRva76EDA0Slot
{
	char m_pad0[0xd0];
	BfmeRva76EDA0GetterObj *m_getter; // +0xd0
	float m_fd4;                      // +0xd4
	float m_fd8;                      // +0xd8
	char m_pad1[0xe4 - 0xdc];
	int m_e4;                         // +0xe4
	unsigned char m_e8;                // +0xe8
};

struct BfmeRva76EDA0Out
{
	int x;
	float y;
};

class BfmeRva76EDA0
{
public:
	void method(int index, BfmeRva76EDA0Out *out1, BfmeRva76EDA0Out *out2);

	char m_pad0[0x90];
	int m_stamp; // +0x90
};

// ?d_0076eda0@@YAXXZ
void BfmeRva76EDA0::method(int index, BfmeRva76EDA0Out *out1, BfmeRva76EDA0Out *out2)
{
	if (g_Va012F8064 != m_stamp)
	{
		((Rva0076CAF0ConditionalDispatch *)((char *)this - 0xc))->target();
	}

	if (index < 0 || index >= 3)
	{
		out1->x = 0; out1->y = 0.0f;
		out2->x = 0; out2->y = 0.0f;
		return;
	}

	BfmeRva76EDA0Slot *slot = (BfmeRva76EDA0Slot *)((char *)this + index * 0x1c);
	if (slot->m_getter == 0)
	{
		out1->x = 0; out1->y = 0.0f;
		out2->x = 0; out2->y = 0.0f;
		return;
	}
	if (!slot->m_e8)
	{
		out1->x = (int)slot->m_fd8;
		out1->y = 0.0f;
		out2->x = 0; out2->y = 0.0f;
		return;
	}

	int type = *(int *)((char *)this + (index + 8) * 0x1c);
	if (type == 1)
	{
		out1->x = slot->m_getter->s4();
		out1->y = 0.0f;
		out2->x = (int)slot->m_fd8;
		out2->y = slot->m_fd4;
	}
	else if (type == 3)
	{
		int c = slot->m_getter->s4();
		out2->x = 0;
		out2->y = (float)c - g_bfmeDefaultBU;
	}
	else if (type == 5)
	{
		int c = slot->m_getter->s4();
		out1->x = c;
		out1->y = (float)c - g_Va01123C58;
	}
	else
	{
		out1->x = (int)slot->m_fd8;
		out1->y = slot->m_fd4;
	}
}
