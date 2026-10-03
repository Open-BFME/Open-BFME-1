class BfmeContainERE
{
public:
	virtual void bfmeSlot00ERE(void);
	virtual void bfmeSlot01ERE(void);
	virtual char bfmeIsGarrisonableERE(void);
	virtual void bfmeSlot03ERE(void);
	virtual void bfmeSlot04ERE(void);
	virtual void bfmeSlot05ERE(void);
	virtual void bfmeSlot06ERE(void);
	virtual void bfmeSlot07ERE(void);
	virtual void bfmeSlot08ERE(void);
	virtual void bfmeSlot09ERE(void);
	virtual void bfmeSlot10ERE(void);
	virtual void bfmeSlot11ERE(void);
	virtual void bfmeSlot12ERE(void);
	virtual void bfmeSlot13ERE(void);
	virtual void bfmeSlot14ERE(void);
	virtual void bfmeSlot15ERE(void);
	virtual void bfmeSlot16ERE(void);
	virtual void bfmeSlot17ERE(void);
	virtual void bfmeSlot18ERE(void);
	virtual void bfmeSlot19ERE(void);
	virtual void bfmeSlot20ERE(void);
	virtual void bfmeSlot21ERE(void);
	virtual void bfmeSlot22ERE(void);
	virtual void bfmeSlot23ERE(void);
	virtual void bfmeSlot24ERE(void);
	virtual void bfmeSlot25ERE(void);
	virtual void bfmeSlot26ERE(void);
	virtual void bfmeSlot27ERE(void);
	virtual void bfmeSlot28ERE(void);
	virtual void bfmeSlot29ERE(void);
	virtual void bfmeSlot30ERE(void);
	virtual void bfmeSlot31ERE(void);
	virtual void bfmeSlot32ERE(void);
	virtual void bfmeSlot33ERE(void);
	virtual void bfmeSlot34ERE(void);
	virtual void bfmeSlot35ERE(void);
	virtual void bfmeSlot36ERE(void);
	virtual void bfmeSlot37ERE(void);
	virtual void bfmeSlot38ERE(void);
	virtual void bfmeSlot39ERE(void);
	virtual void bfmeSlot40ERE(void);
	virtual void bfmeSlot41ERE(void);
	virtual void bfmeSlot42ERE(void);
	virtual void bfmeSlot43ERE(void);
	virtual void bfmeSlot44ERE(void);
	virtual void bfmeSlot45ERE(void);
	virtual void bfmeSlot46ERE(void);
	virtual void bfmeSlot47ERE(void);
	virtual void bfmeSlot48ERE(void);
	virtual void bfmeSlot49ERE(void);
	virtual void bfmeSlot50ERE(void);
	virtual void bfmeSlot51ERE(void);
	virtual void bfmeSlot52ERE(void);
	virtual void bfmeSlot53ERE(void);
	virtual void bfmeSlot54ERE(void);
	virtual void bfmeSlot55ERE(void);
	virtual void bfmeSlot56ERE(void);
	virtual void bfmeSlot57ERE(void);
	virtual void bfmeSlot58ERE(void);
	virtual void bfmeSlot59ERE(void);
	virtual void bfmeSlot60ERE(void);
	virtual void bfmeSlot61ERE(void);
	virtual void bfmeSlot62ERE(void);
	virtual void bfmeSlot63ERE(void);
	virtual int bfmeContainCountERE(int includeAll);
};

class BfmeObjectERE;

// Both predicates the filter calls are reached through the retail five-byte
// incremental-link thunks at 0x0004039A and 0x0003BD3B, so the only names
// defined at those addresses are the ?j_ thunk symbols (game/gen_small/
// thunks_030.cpp and thunks_028.cpp).  Reference those names; each call is
// typed through a __fastcall view of the thunk's thiscall shape, so the this
// pointer rides in ECX and no argument is stacked, exactly as retail does.
// The declarations stay __cdecl and undecorated: naming the symbol through
// __identifier and casting through the typedef keeps the reference the plain
// ?j_ name link.exe resolves.
extern "C" char __cdecl __identifier("?j_0004039a@@YAXXZ")();
extern "C" char __cdecl __identifier("?j_0003bd3b@@YAXXZ")();

typedef char (__fastcall *BfmeIsPredicateERE)(BfmeObjectERE *);

class BfmeObjectERE
{
public:
	unsigned char m_bfmeHeadERE[0x1fc];
	BfmeContainERE *m_bfmeContainERE;
};

class BfmeFilterERE
{
public:
	virtual char bfmeAllowERE(BfmeObjectERE *other);

	unsigned char m_bfmeHeadERE[4];
	char m_bfmeAllowNonBuildingsERE;
	char m_bfmeAllowInsignificantERE;
};

char BfmeFilterERE::bfmeAllowERE(BfmeObjectERE *other)
{
	if (((BfmeIsPredicateERE)__identifier("?j_0004039a@@YAXXZ"))(other))
	{
		if (((BfmeIsPredicateERE)__identifier("?j_0003bd3b@@YAXXZ"))(other)
			&& !m_bfmeAllowInsignificantERE)
		{
			BfmeContainERE *contain = other->m_bfmeContainERE;
			if (contain != 0)
			{
				if (!contain->bfmeIsGarrisonableERE() || contain->bfmeContainCountERE(0) == 0)
					return 0;
			}
		}
		return 1;
	}
	return m_bfmeAllowNonBuildingsERE != 0;
}
