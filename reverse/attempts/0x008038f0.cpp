// ?submit@BfmeSinkSKA@@AAEXPAVBfmeC994@@@Z
// partial score=0.88 date=2026-09-04
// cl: /DNDEBUG /MD /GX-
// FESL submit / bfmeSendVJH @ 0x008038F0 (123B).
// Combined 36-byte frame keeps param at [esp+8] / guard at [esp+0x1c]
// (two locals invert by size on MSVC 13.10). Zero+open in Frame ctor gets
// push esi into the right place. Residual: 15B prologue scheduling — retail
// does mov esi,ecx / lea guard / then all five param zeros; MSVC emits one
// zero, then mov esi,ecx, then three zeros, then lea, then the m_00 zero.
// Same instruction multiset after +0x26. No flag or declaration-order lever
// moved the lea above the zeros while keeping this in esi.

extern char g_bfmeVftSubmit1250[];

class BfmeGuard1250
{
public:
	void open();
	void close();

	char *m_vft;
	int m_04;
	int m_08;
	int m_0c;
};

struct BfmeParam1250
{
	volatile int m_00;
	volatile int m_04;
	volatile int m_08;
	volatile int m_0c;
	volatile char m_10;
	char m_pad[3];
};

struct BfmeFrame1250
{
	__forceinline BfmeFrame1250()
	{
		int z = 0;
		param.m_00 = z;
		param.m_04 = z;
		param.m_08 = z;
		param.m_0c = z;
		param.m_10 = (char)z;
		guard.open();
	}

	BfmeParam1250 param;
	BfmeGuard1250 guard;
};

class BfmeMsg1250
{
public:
	char m_pad00[0x10];
	int m_10;
	int m_14;
	char m_pad18[4];
	int m_1c;
	int m_20;
};

class BfmeApply1250
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void apply(BfmeParam1250 *param);
};

class BfmeSink1250
{
public:
	int m_00;
	BfmeApply1250 m_apply;
};

class BfmeThing1250
{
public:
	void submit(BfmeMsg1250 *message);

	char m_pad[0x10];
	BfmeSink1250 *m_10;
};

void BfmeThing1250::submit(BfmeMsg1250 *message)
{
	BfmeThing1250 *self = this;
	int z = 0;
	BfmeFrame1250 frame;

	frame.param.m_00 = message->m_1c;
	frame.param.m_04 = message->m_20;
	frame.param.m_08 = message->m_10;
	frame.param.m_0c = message->m_14;

	frame.guard.m_vft = g_bfmeVftSubmit1250;
	frame.guard.m_08 = z;
	frame.guard.m_0c = z;
	frame.guard.m_04 = z;

	self->m_10->m_apply.apply(&frame.param);
	frame.guard.close();
}
