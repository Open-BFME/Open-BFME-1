extern "C" unsigned char bfmeVftTL[];

class BfmeLocaleShim
{
public:
	static void bfmeLocaleCtor(void);
};

struct BfmeListNodeTL
{
	void *m_next;
	void *m_previous;
	void *m_value;
};

struct BfmeListTL
{
	BfmeListNodeTL m_head;
	unsigned char m_padding[0x14];
};

class BfmeThingTL
{
public:
	BfmeThingTL *bfmeBaseTL(void *what, int flag);
	BfmeThingTL *bfmeInitTL(void *what);
	void *m_bfmeVft;
	void * volatile m_bfmeBaseWhat;
	void * volatile m_bfmeBaseFlag;
	BfmeListTL m_bfmeList0;
	BfmeListTL m_bfmeList1;
	unsigned char m_bfmeLocale[4];
	volatile unsigned int m_bfmeZero;
	void *m_bfmeWhat;
};

// ?bfmeBaseTL@BfmeThingTL@@QAEPAV1@PAXH@Z		97 bytes
// The retail compiler schedules this LEA before the volatile field store;
// MSVC 7.1 does not reproduce that order from clean C++ alone.
__declspec(noinline) BfmeThingTL *BfmeThingTL::bfmeBaseTL(void *what, int flag)
{
	void *baseWhat = what;
	void *baseFlag = reinterpret_cast<void *>(static_cast<unsigned int>(flag));
	m_bfmeVft = reinterpret_cast<void *>(0x0112ebd4);
	m_bfmeBaseWhat = baseWhat != 0 ? baseWhat : &m_bfmeList0.m_head;
	void *resolvedBaseFlag = baseFlag != 0 ? baseFlag : &m_bfmeList1.m_head;
	__asm { lea ecx, [esi+0x4c] }
	m_bfmeBaseFlag = resolvedBaseFlag;
	BfmeLocaleShim::bfmeLocaleCtor();
	BfmeListNodeTL *baseWhatNode =
		(m_bfmeZero = 0, m_bfmeZero = 0,
		 static_cast<BfmeListNodeTL *>(m_bfmeBaseWhat));
	if (baseWhatNode == &m_bfmeList0.m_head)
	{
		baseWhatNode->m_value = 0;
		baseWhatNode->m_next = 0;
		baseWhatNode->m_previous = 0;
	}
	BfmeListNodeTL *baseFlagHead = &m_bfmeList1.m_head;
	BfmeListNodeTL *baseFlagNode = static_cast<BfmeListNodeTL *>(m_bfmeBaseFlag);
	if (baseFlagNode == baseFlagHead)
	{
		baseFlagNode->m_value = 0;
		baseFlagNode->m_next = 0;
		baseFlagNode->m_previous = 0;
	}
	return this;
}

BfmeThingTL *BfmeThingTL::bfmeInitTL(void *what)
{
	bfmeBaseTL(what, 0);
	m_bfmeWhat = what;
	m_bfmeVft = bfmeVftTL;
	return this;
}
