// cl: /DNDEBUG /MD /EHsc

struct Coord3D;

class BfmeClear4D0
{
public:
	bool bfmeClear4D0(int);
};

class BfmeRva491F0Object
{
public:
	void activate();
};

class BfmeThingPositionSetter
{
public:
	void setPosition(const Coord3D *);
};

class BfmeXCQE
{
public:
	void bfmeRunCQE(int);
};

class BfmeV28NoArg
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0; virtual void slot02() = 0;
	virtual void slot03() = 0; virtual void slot04() = 0; virtual void slot05() = 0;
	virtual void slot06() = 0; virtual void slot07() = 0; virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual BfmeXCQE *slot28();
};

class BfmeV28Arg
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0; virtual void slot02() = 0;
	virtual void slot03() = 0; virtual void slot04() = 0; virtual void slot05() = 0;
	virtual void slot06() = 0; virtual void slot07() = 0; virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual BfmeXCQE *slot28();
};

class BfmeSubBIA
{
public:
	void *m_vtable;
	BfmeSubBIA *m_nextOverride;
	int ask();
};

class GameLogic
{
public:
	char m_pad[0x3C];
	volatile int m_frame;
};

extern volatile GameLogic * volatile TheGameLogic;
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class BfmeOwner4D0
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0; virtual void slot02() = 0;
	virtual void slot03() = 0; virtual void slot04() = 0; virtual void slot05() = 0;
	virtual void slot06() = 0; virtual void slot07() = 0; virtual void slot08() = 0;
	virtual void slot09() = 0; virtual void slot10() = 0; virtual void slot11() = 0;
	virtual void slot12() = 0; virtual void slot13() = 0; virtual void slot14() = 0;
	virtual void slot15() = 0; virtual void slot16() = 0; virtual void slot17() = 0;
	virtual void slot18() = 0; virtual void slot19() = 0; virtual void slot20() = 0;
	virtual void finish();
};

class BfmeObject4D0
{
public:
	void *m_vtable;
	BfmeSubBIA *m_override;
	char m_pad[0x330 - 8];
	int m_stamp;
	char m_pad2[0x424 - 0x334];
	int m_delay;
};

class Gen_0022F4D0
{
public:
	void bfmeInit4D0(void *);
	void bfmeGo4D0(void *);
};

// ?bfmeGo4D0@Gen_0022F4D0@@QAEXPAX@Z
void Gen_0022F4D0::bfmeGo4D0(void *payload)
{
	BfmeObject4D0 *object = (BfmeObject4D0 *)payload;
	bfmeInit4D0(payload);
	((BfmeClear4D0 *)object)->bfmeClear4D0(3);
	((BfmeRva491F0Object *)object)->activate();
	((BfmeThingPositionSetter *)object)->setPosition((const Coord3D *)((char *)*(void **)((char *)this - 0x18) + 0x38));

	BfmeV28NoArg *first = (BfmeV28NoArg *)object;
	if (first->slot28() != 0)
	{
		int frame = TheGameLogic->m_frame;
		_ReadWriteBarrier();
		BfmeSubBIA *over = object->m_override;
		if (over != 0 && over->m_nextOverride != 0)
			over = (BfmeSubBIA *)over->m_nextOverride->ask();
		object->m_stamp = ((BfmeObject4D0 *)over)->m_delay + frame;

		BfmeV28Arg *second = (BfmeV28Arg *)object;
		second->slot28()->bfmeRunCQE(0);
	}
	((BfmeOwner4D0 *)((char *)this - 0x20))->finish();
}
