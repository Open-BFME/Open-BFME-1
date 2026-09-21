// ?dispatch@Rva006D2130@@QAEXXZ
// partial score=0.2 date=2026-09-21
// cl: /DNDEBUG /MD
//
// ?d_006d2130@@YAXXZ (address-derived; no caller, vtable or string evidence
// proves the owning class -- callers_of.py and find_emitter.py both come up
// empty). Full 250B boundary decoded via dis_retail.py: a suppression-flag
// early-out, a call to the already-matched trivial Gen_006c87a0::m() (1B
// "ret", so its real effect is irrelevant here), a switch on a dispatch
// state field (+0x3178) with 4 cases, a "budget" local set by the switch,
// a flag-gated shortcut (+0x3104), and -- when neither shortcut applies --
// a nested loop over a 0xC4-byte-stride 2D array (base +0x30d8, dimensions
// +0x30e0 outer / +0x30e4 inner) that probes each element through a still-
// dump callee (thunk 0x00013DE5 -> 0x00729180) and, on a hit, decrements
// the budget and applies a second still-dump callee (thunk 0x0002DB41 ->
// 0x0072EAA0). Both element callees take no visible arguments beyond
// their own `this`; return type/arg count read off the call sites, not
// guessed at semantically -- keep the class and the two probe/apply names
// address-derived per docs/naming_evidence.md.

class Gen_006c87a0
{
public:
	void m();
};

class Rva006D2130Elem
{
public:
	bool probe();
	void apply();
};

extern bool g_aiTargetDispatchSuppressed;

class Rva006D2130
{
public:
	void dispatch();

private:
	unsigned char pad1[0x30d8];
	Rva006D2130Elem *m_arrayBase; // +0x30d8
	unsigned char pad1b[4];       // +0x30dc (untouched by this body)
	int m_outerCount;             // +0x30e0
	int m_innerCount;             // +0x30e4
	unsigned char pad2[0x3104 - 0x30e8];
	bool m_flagA;                 // +0x3104
	unsigned char pad3[0x3178 - 0x3105];
	int m_state;                  // +0x3178
};

void Rva006D2130::dispatch()
{
	if (g_aiTargetDispatchSuppressed)
		return;

	((Gen_006c87a0 *)this)->m();

	int budget = 0;
	switch (m_state)
	{
	case 0:
		m_state = 3;
		return;
	case 1:
		m_state = 3;
		budget = 1;
		break;
	case 2:
		budget = 2;
		break;
	case 3:
	default:
		break;
	}

	if (m_flagA)
	{
		budget = 0x63;
	}
	else if (budget <= 0)
	{
		goto tail;
	}

	for (int ob = 0; ob < m_outerCount; ++ob)
	{
		if (m_innerCount > 0)
		{
			int ib = 0;
			do
			{
				if (budget < 1)
					break;

				Rva006D2130Elem *elem = m_arrayBase + (m_outerCount * ib + ob);
				if (elem->probe())
				{
					--budget;
					elem->apply();
				}

				++ib;
			} while (ib < m_innerCount);
		}
	}

tail:
	if (budget >= 1)
		m_state = 0;
	m_flagA = false;
}
