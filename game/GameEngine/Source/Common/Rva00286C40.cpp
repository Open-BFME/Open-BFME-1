// ?Rva00286C40@Rva00286C40Self@@QAEXPAVBfmeSeedTarget@@@Z
// Retail 0x00286C40. The concrete owning update class is not proven, so the
// address-derived owner preserves that uncertainty while the seed/Xfer ABI is
// represented by the existing named callees.
// cl: /DNDEBUG /MD /EHs-c-

typedef bool Bool;
typedef unsigned int UnsignedInt;

class BfmeSeedTarget;
class Rva00286C40Self;

// The inherited accept this body calls is retail's shared flag-pair dispatcher
// `Gen002B2080::handle(FlagPairTarget *)` at ILT 0x000044C1, declared here under
// its real spelling so the reference resolves (the definition lives in
// game/GameEngine/Source/GameLogic/AI/Gen002B2080Handle.cpp).
class FlagPairTarget;

class Gen002B2080
{
public:
	void handle(FlagPairTarget *target);
};

class Gen_001ED0C0
{
public:
	friend class Rva00286C40Self;

private:
	unsigned char m_pad00[0x24];
};

struct Rva00286C40Pair
{
	unsigned char first;
	unsigned char second;
};

class BfmeSeedTarget
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual Bool slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void takeAt24(void *item, int size);
	virtual void seed(Rva00286C40Pair *pair);
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void takeAt6C(void *item);
	virtual void slot28();
	virtual void takeAt74(void *item);
	virtual void takeAt78(void *item);
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void takeAt8C(void *item);
};

class BfmeSubAccept_0002C41C
{
public:
	void bfmeAccept(BfmeSeedTarget *target);

	unsigned char m_pad00[0x70];
};

class Rva000D6CF0Field
{
public:
};

// Retail reaches the 0x000D6CF0 body through ILT 0x0003573D.
extern void j_0003573d();
class Route0003573D {};
static __forceinline void callRva000D6CF0(void *self, BfmeSeedTarget *target)
{
	typedef void (Route0003573D::*Fn)(BfmeSeedTarget *);
	union { void (*fn)(); Fn call; } route = { j_0003573d };
	(((Route0003573D *)self)->*route.call)(target);
}

class Xfer; class MidVirtualSlot90Receiver;		// 0x0010C3C0, defined in MidVirtualSlot90Forwarders.cpp
Xfer & Rva0010C3C0(MidVirtualSlot90Receiver *target, void *value);

class Rva00286C40Self : public Gen_001ED0C0
{
public:
	void Rva00286C40(BfmeSeedTarget *target);

	unsigned char m_field24[4];
	unsigned char m_field28[4];
	unsigned char m_field2C[4];
	unsigned char m_field30[4];
	unsigned char m_field34[8];
	unsigned char m_field3C[4];
	Rva000D6CF0Field *m_field40;
	BfmeSubAccept_0002C41C m_sub[4][4];
	int m_field744;
};

void Rva00286C40Self::Rva00286C40(BfmeSeedTarget *target)
{
	((Gen002B2080 *)this)->handle((FlagPairTarget *)target);
	if (target->slot04())
		return;

	Rva00286C40Pair pair = { 1, 1 };
	target->seed(&pair);
	target->takeAt24(m_field24, 4);
	target->takeAt24(m_field28, 4);
	target->takeAt24(m_field2C, 4);
	target->takeAt24(m_field30, 4);
	target->takeAt74(m_field34);
	target->takeAt8C(m_field3C);
	target->takeAt8C(m_field3C + 1);
	target->takeAt6C(m_field40);
	target->takeAt78((char *)m_field40 + 4);
	target->takeAt78((char *)m_field40 + 8);
	target->takeAt78((char *)m_field40 + 0xc);
	target->takeAt6C((char *)m_field40 + 0x10);
	callRva000D6CF0((char *)m_field40 + 0x14, target);
	callRva000D6CF0((char *)m_field40 + 0x2c, target);

	(void)&Rva0010C3C0((MidVirtualSlot90Receiver *)target, &m_field744);

	BfmeSubAccept_0002C41C *sub = &m_sub[0][0];
	for (int outer = 4; outer != 0; --outer)
	{
		for (int inner = 4; inner != 0; --inner)
		{
			sub->bfmeAccept(target);
			sub = (BfmeSubAccept_0002C41C *)((char *)sub + 0x70);
		}
	}
}
