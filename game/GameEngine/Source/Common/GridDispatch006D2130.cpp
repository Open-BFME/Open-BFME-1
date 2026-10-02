// cl: /DNDEBUG /MD
// RVA 0x006D2130: 250-byte budgeted grid dispatch; owner identity remains opaque.
// Retail table at VA 0x00AD222C: case 0 returns; case 1 sets state 3 and
// returns; case 2 sets budget 1 then state 3; case 3 sets budget 2.
// Element stride 0xC4 and both dimensions are witnessed by the loop arithmetic.
// The first element call decrements the budget on AL=true; the second is unconditional.
// Both calls load ECX=element with no stack args; their bodies return with C3.
// All 250 executable bytes plus alignment and four jump-table entries verified.

class Gen_006c87a0
{
public:
	void m();
};

void j_00013de5();
void j_0002db41();

class Rva006D2130Elem
{
public:
	void rva0072EAA0();

	__forceinline bool rva00729180()
    {
        union { void (*thunk)(); bool (Rva006D2130Elem::*method)(); } call;
        call.thunk = &j_00013de5;
        return (this->*call.method)();
    }
	unsigned char extent[0xc4];
	__forceinline void callRva0072EAA0()
    {
        union { void (*thunk)(); void (Rva006D2130Elem::*method)(); } call;
        call.thunk = &j_0002db41;
        (this->*call.method)();
    }
};

void Rva006D2130Elem::rva0072EAA0()
{
	__asm
	{
		push -1
		push 0104D340h
		mov eax, fs:[0]
		push eax
		mov fs:[0], esp
		mov ecx, [esp]
		mov fs:[0], ecx
		add esp, 0Ch
	}
}

bool g_aiTargetDispatchSuppressed = false;

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
		return;
	case 1:
		m_state = 3;
		return;
	case 2:
		budget = 1;
		m_state = 3;
		break;
	case 3:
		budget = 2;
		break;
	default:
		break;
	}

	if (m_flagA)
	{
		budget = 0x63;
	}
	else if (budget <= 0)
	{
		goto clearFlag;
	}

	for (int ob = 0; ob < m_outerCount; ++ob)
	{
		int ib = 0;
		if (m_innerCount > 0)
		{
			do
			{
				if (budget < 1)
					break;

				Rva006D2130Elem *elem = m_arrayBase + (m_outerCount * ib + ob);
				if (elem->rva00729180())
				{
					--budget;
				}
				elem->callRva0072EAA0();

				++ib;
			} while (ib < m_innerCount);
		}
	}

	if (budget >= 1)
		m_state = 0;
clearFlag:
	m_flagA = false;
}
