// ?bfmeAccept@Gen_00287130@@QAE_NPAURvaC4390Second@@@Z
// partial score=0.78 date=2026-09-22
// Retail 0x00287130 (147 B).
//
// Sibling of the matched Rva002871F0Update.cpp: same RvaC4390Second::resolve
// / RvaC4390First::getInterface / Object::getControllingPlayer callee triple,
// and the same "this"-relative NEGATIVE offset pair (this-0x1c, this-0x18)
// for two pointer fields that sit just before this method's vtable-adjusted
// this pointer -- confirmed directly from dis_retail.py: mov ebp,[ebx-0x1c]
// at +0x10 and mov ebx,[ebx-0x18] at +0x4e. filterOwner (this-0x1c) plus 8
// is the BfmeRvaA760ProbeInterface::accepts() receiver, exactly matching the
// sibling's "probe = filterOwner + 8" shape. The guard vtable (slot 0x180/4
// = index 96) and the RvaC4390Interface slots 0x18/0x1c (index 6/7, state
// and value) are unchanged from the prior stash and already verified by the
// disassembly's call[eax+0x180], call[edx+0x1c], call[edx+0x18].
// cl: /DNDEBUG /MD /EHsc

#define BFME_TEN_VIRTUALS(PREFIX) \
	virtual void PREFIX##0(void); virtual void PREFIX##1(void); \
	virtual void PREFIX##2(void); virtual void PREFIX##3(void); \
	virtual void PREFIX##4(void); virtual void PREFIX##5(void); \
	virtual void PREFIX##6(void); virtual void PREFIX##7(void); \
	virtual void PREFIX##8(void); virtual void PREFIX##9(void)

class Player {};

class Object
{
public:
	Player *getControllingPlayer();

	unsigned char m_bfmeFields[0x74];
	unsigned int m_id;
};

class BfmeGuard96
{
public:
	BFME_TEN_VIRTUALS(v00);
	BFME_TEN_VIRTUALS(v10);
	BFME_TEN_VIRTUALS(v20);
	BFME_TEN_VIRTUALS(v30);
	BFME_TEN_VIRTUALS(v40);
	BFME_TEN_VIRTUALS(v50);
	BFME_TEN_VIRTUALS(v60);
	BFME_TEN_VIRTUALS(v70);
	BFME_TEN_VIRTUALS(v80);
	virtual void v90(void);
	virtual void v91(void);
	virtual void v92(void);
	virtual void v93(void);
	virtual void v94(void);
	virtual void v95(void);
	virtual bool bfmeAllows(void);
};

struct RvaC4390Interface
{
	virtual void v0(void);
	virtual void v1(void);
	virtual void v2(void);
	virtual void v3(void);
	virtual void v4(void);
	virtual void v5(void);
	virtual int bfmeState(void);
	virtual int bfmeValue(void);
};

struct RvaC4390First
{
	RvaC4390Interface *getInterface(void);

	char m_bfmeFields[0x204];
	BfmeGuard96 *m_bfmeGuard;
};

struct RvaC4390Second
{
	RvaC4390First *resolve(int mode);
};

class Rva2225E0Filter
{
public:
	bool accepts(RvaC4390First *object, Player *player);
};

struct BfmeFilterHolder
{
	char m_bfmeFields[8];
	Rva2225E0Filter m_bfmeFilter;
};

class Gen_00287130
{
public:
	bool bfmeAccept(RvaC4390Second *source);
};

// ?bfmeAccept@Gen_00287130@@QAE_NPAVRvaC4390Second@@@Z
bool Gen_00287130::bfmeAccept(RvaC4390Second *source)
{
	RvaC4390First *first = source->resolve(0);
	BfmeFilterHolder *filterOwner = *(BfmeFilterHolder **)((char *)this - 0x1c);

	if (first == 0)
		return false;

	BfmeGuard96 *guard = first->m_bfmeGuard;
	if (guard != 0)
	{
		if (!guard->bfmeAllows())
			return false;
	}

	RvaC4390Interface *interfaceValue = first->getInterface();
	if (interfaceValue == 0)
		return false;

	Object *owner = *(Object **)((char *)this - 0x18);
	Player *player = owner->getControllingPlayer();
	Rva2225E0Filter *probe = (Rva2225E0Filter *)((char *)filterOwner + 8);
	if (!probe->accepts(first, player))
		return false;

	int value = interfaceValue->bfmeValue();
	unsigned int ownerValue;
	if (value == 0 || ((ownerValue = owner->m_id), interfaceValue->bfmeValue() == (int)ownerValue))
	{
		bool stateIsZero = (interfaceValue->bfmeState() == 0);
		return stateIsZero;
	}

	return false;
}

#undef BFME_TEN_VIRTUALS
