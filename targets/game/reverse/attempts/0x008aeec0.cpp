// ?d_008aeec0@@YAXXZ
// partial score=0.984 date=2026-09-28
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class AptValue
{
public:
	float toNumber();
	int toInteger() const;

	void *m_vtable;
	unsigned int m_flags;
};

class AptInteger
{
public:
	static AptInteger *Create(int value);
};

class BfmeQ1235
{
public:
	int m_bfme00;
	int m_bfme04;
};

class BfmeN1235
{
public:
	void bfmeDo1235(void *a, void *b);
	unsigned m_bfme00;
	unsigned m_bfme04;
	char m_bfmePad08[0x50 - 0x08];
	BfmeQ1235 *m_bfme50;
	char m_bfmePad54[4];
	BfmeN1235 *m_bfme58;
};

struct Rva008AE770Stack
{
	int m_count;
};

extern Rva008AE770Stack Rva008AE770TheStack;
extern AptValue **g_bfmeArr1233;
extern int g_bfmeB1038;
extern int (__cdecl *Rva013378B0Callback)(float first, float second, void *owner);

void __cdecl Rva008AEEC0(BfmeN1235 *owner, int count)
{
	float first;
	float second;
	float bounds[8];

	if (count == 1)
	{
		AptValue *value = g_bfmeArr1233[Rva008AE770TheStack.m_count - 1];
		int type = value->m_flags & 0x3f;
		if (type < 0xc || type > 0x13)
			goto create_false;

		bounds[4] = 1.0e9f;
		bounds[6] = -1.0e9f;
		bounds[7] = -1.0e9f;
		bounds[5] = 1.0e9f;
		owner->bfmeDo1235((void *)g_bfmeB1038, &bounds[4]);
		bounds[0] = 1.0e9f;
		bounds[2] = -1.0e9f;
		bounds[3] = -1.0e9f;
		bounds[1] = 1.0e9f;
		((BfmeN1235 *)value)->bfmeDo1235((void *)g_bfmeB1038, bounds);
		if (!(bounds[0] <= bounds[6]) || !(bounds[2] >= bounds[4])
			|| !(bounds[3] >= bounds[5]))
			goto create_false;

		second = bounds[1];
	}
	else
	{
		if (count <= 1)
			goto create_false;

		first = g_bfmeArr1233[Rva008AE770TheStack.m_count - 1]->toNumber();
		second = g_bfmeArr1233[Rva008AE770TheStack.m_count - 2]->toNumber();
		if (count > 2 && g_bfmeArr1233[Rva008AE770TheStack.m_count - 3]->toInteger() != 0)
		{
			AptInteger::Create(Rva013378B0Callback(first, second, owner));
			return;
		}

		bounds[4] = 1.0e9f;
		bounds[6] = -1.0e9f;
		bounds[7] = -1.0e9f;
		bounds[5] = 1.0e9f;
		owner->bfmeDo1235((void *)g_bfmeB1038, &bounds[4]);
		if (!(first >= bounds[4]))
			goto create_false;
		if (!(first <= bounds[6]))
			goto create_false;
		if (!(second >= bounds[5]))
			goto create_false;
	}

	if (second <= bounds[7])
	{
		AptInteger::Create(1);
		return;
	}

create_false:
	AptInteger::Create(0);
}
