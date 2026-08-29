// ?d_002b6390@@YAXXZ
// partial score=0.96 date=2026-08-29
// cl: /DNDEBUG /MD /EHsc
//
// A guarded chain walk followed by three virtual dispatches, retail 0x002B6390.
//
// this->+0x1c -> +0x10 -> +0x204, and if that last pointer is null the function
// returns -2 without touching anything else.  Otherwise it calls slot 0x13c on
// it, hands the result the value at this+0x24 through slot 0x28, then calls
// slot 0x18 on the object at this+0x28 and returns 0.
//
// The parked note recorded this as a register-allocation tie-break: retail keeps
// reusing eax down the chain (mov eax,[eax+0x10]) where the earlier
// reconstruction switched to ecx one load earlier, and explicit intermediate
// locals did not move it.  Locals are the wrong tool -- they are what makes the
// compiler materialise a value and then keep it somewhere of its own choosing.
// Routing the middle hop through an IN-CLASS ACCESSOR instead is what reproduced
// retail's chain in ControlBar::onPlayerRankChanged, and it is what is tried here.

class Open2ChainResult2B6390
{
public:
	virtual void slot000();
	virtual void slot004();
	virtual void slot008();
	virtual void slot00c();
	virtual void slot010();
	virtual void slot014();
	virtual void slot018();
	virtual void slot01c();
	virtual void slot020();
	virtual void slot024();
	virtual void takeValue(void *value);			///< vtable +0x28
};

class Open2ChainOwner2B6390
{
public:
	virtual void slot000();
	virtual void slot004();
	virtual void slot008();
	virtual void slot00c();
	virtual void slot010();
	virtual void slot014();
	virtual void slot018();
	virtual void slot01c();
	virtual void slot020();
	virtual void slot024();
	virtual void slot028();
	virtual void slot02c();
	virtual void slot030();
	virtual void slot034();
	virtual void slot038();
	virtual void slot03c();
	virtual void slot040();
	virtual void slot044();
	virtual void slot048();
	virtual void slot04c();
	virtual void slot050();
	virtual void slot054();
	virtual void slot058();
	virtual void slot05c();
	virtual void slot060();
	virtual void slot064();
	virtual void slot068();
	virtual void slot06c();
	virtual void slot070();
	virtual void slot074();
	virtual void slot078();
	virtual void slot07c();
	virtual void slot080();
	virtual void slot084();
	virtual void slot088();
	virtual void slot08c();
	virtual void slot090();
	virtual void slot094();
	virtual void slot098();
	virtual void slot09c();
	virtual void slot0a0();
	virtual void slot0a4();
	virtual void slot0a8();
	virtual void slot0ac();
	virtual void slot0b0();
	virtual void slot0b4();
	virtual void slot0b8();
	virtual void slot0bc();
	virtual void slot0c0();
	virtual void slot0c4();
	virtual void slot0c8();
	virtual void slot0cc();
	virtual void slot0d0();
	virtual void slot0d4();
	virtual void slot0d8();
	virtual void slot0dc();
	virtual void slot0e0();
	virtual void slot0e4();
	virtual void slot0e8();
	virtual void slot0ec();
	virtual void slot0f0();
	virtual void slot0f4();
	virtual void slot0f8();
	virtual void slot0fc();
	virtual void slot100();
	virtual void slot104();
	virtual void slot108();
	virtual void slot10c();
	virtual void slot110();
	virtual void slot114();
	virtual void slot118();
	virtual void slot11c();
	virtual void slot120();
	virtual void slot124();
	virtual void slot128();
	virtual void slot12c();
	virtual void slot130();
	virtual void slot134();
	virtual void slot138();
	virtual Open2ChainResult2B6390 *resolve();		///< vtable +0x13c
};

class Open2ChainNotify2B6390
{
public:
	virtual void slot000();
	virtual void slot004();
	virtual void slot008();
	virtual void slot00c();
	virtual void slot010();
	virtual void slot014();
	virtual void notify();					///< vtable +0x18
};

class Open2ChainMid2B6390
{
public:
	unsigned char m_beforeOwner[0x204];
	Open2ChainOwner2B6390 *m_owner;				///< retail this+0x204

	Open2ChainOwner2B6390 *getOwner() const { return m_owner; }
};

class Open2ChainHead2B6390
{
public:
	unsigned char m_beforeMid[0x10];
	Open2ChainMid2B6390 *m_mid;				///< retail this+0x10

	// The accessor, not a local: this is the hop retail keeps in eax.
	Open2ChainMid2B6390 *getMid() const { return m_mid; }
};

class Open2Chain2B6390
{
public:
	unsigned char m_beforeHead[0x1c];
	Open2ChainHead2B6390 *m_head;				///< retail this+0x1c
	unsigned char m_beforeValue[0x24 - 0x20];
	void *m_value;						///< retail this+0x24
	Open2ChainNotify2B6390 *m_notify;			///< retail this+0x28

	int run();
};

// @?run@Open2Chain2B6390@@QAEHXZ 0x002B6390
int Open2Chain2B6390::run()
{
	Open2ChainMid2B6390 &mid = *m_head->getMid();
	Open2ChainOwner2B6390 *owner = mid.getOwner();
	if (!owner)
		return -2;

	owner->resolve()->takeValue(m_value);
	m_notify->notify();
	return 0;
}
