// ?bfmeGetOrCreateDefault@Rva008A78D0Owner@@QAEPAXHPAPAX@Z
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Address-derived owner; constructor and sized-delete identities are pinned independently.

extern "C" void *(*WideAllocPtr)(unsigned int bytes);
extern void *Rva00897640(unsigned int bytes);

class Rva008A78D0VBase
{
public:
	virtual void bfmeNotify();
};

class Rva00897670HeaderedDelete
{
public:
	static void operator delete(void *memory, unsigned int bytes);
};

class Rva00899FC0 : public Rva00897670HeaderedDelete
{
public:
	static void *operator new(unsigned int bytes)
	{
		return Rva00897640(bytes);
	}

	__declspec(noinline) Rva00899FC0(int callback);

	void *m_bfmeVfptr;
	unsigned m_bfmeFlags;
	char m_bfmePad[0x18];
	int m_bfmeCallback;
};

extern "C" int __cdecl strcmp(const char *a, const char *b);
#pragma intrinsic(strcmp)

extern Rva00899FC0 *g_rva01337abc;

struct Rva00891B80Block
{
	unsigned short m_ref;
};

extern Rva00891B80Block g_default012D5298;

class BfmeStrVKK
{
public:
	void bfmeTruncVKK(unsigned n);
};

class Rva008A9B00
{
public:
	Rva008A9B00();

	void *operator new(unsigned int bytes)
	{
		return WideAllocPtr(bytes);
	}

	__forceinline void clearRegistered()
	{
		m_flags &= ~0x40000000;
	}

	void *m_vptr;
	unsigned m_flags;
	Rva00891B80Block *m_block;
	Rva008A9B00 *m_next;
};

struct Rva00899560Pool
{
	int m_capacity;
	int m_count;
	void **m_entries;

	__forceinline void addOrClear(Rva008A9B00 *obj)
	{
		int index = m_count;
		int *pcount = &m_count;
		int cap = m_capacity;
		if (index >= cap)
		{
			obj->clearRegistered();
			return;
		}

		m_entries[index] = obj;
		++*pcount;
	}
};

extern Rva00899560Pool *g_rva8CD130IdleHook;
extern Rva008A9B00 *Rva008C3B60Head;

class Rva008B2EA0Node
{
public:
	void append(void *node);
};

class Rva008A78D0Owner
{
public:
	void *bfmeGetOrCreateDefault(int unused, void **arg2);

	char m_pad0[0x20];
	void *m_slot20;
	void *m_slot24;
};

void *Rva008A78D0Owner::bfmeGetOrCreateDefault(int unused, void **arg2)
{
	if (strcmp((const char *)*arg2 + 8, "message") == 0)
	{
		Rva008A9B00 *obj = Rva008C3B60Head;

		if (obj != 0)
		{
			Rva008C3B60Head = obj->m_next;
			g_rva8CD130IdleHook->addOrClear(obj);

			if (obj->m_block != &g_default012D5298)
				((BfmeStrVKK *)&obj->m_block)->bfmeTruncVKK(0);
		}
		else
		{
			obj = new Rva008A9B00();
		}

		void *arg = (char *)m_slot20 + 8;
		((Rva008B2EA0Node *)obj)->append(arg);

		return obj;
	}

	if (strcmp((const char *)*arg2 + 8, "name") == 0)
	{
		Rva008A9B00 *obj = Rva008C3B60Head;

		if (obj != 0)
		{
			Rva008C3B60Head = obj->m_next;
			g_rva8CD130IdleHook->addOrClear(obj);

			if (obj->m_block != &g_default012D5298)
				((BfmeStrVKK *)&obj->m_block)->bfmeTruncVKK(0);
		}
		else
		{
			obj = new Rva008A9B00();
		}

		void *arg = (char *)m_slot24 + 8;
		((Rva008B2EA0Node *)obj)->append(arg);

		return obj;
	}

	if (strcmp((const char *)*arg2 + 8, "toString") == 0)
	{
		if (g_rva01337abc == 0)
		{
			g_rva01337abc = new Rva00899FC0(0xca62a0);
			g_rva01337abc->m_bfmeFlags = (g_rva01337abc->m_bfmeFlags & 0xffffc07f) | 0x40;
			((Rva008A78D0VBase *)g_rva01337abc)->bfmeNotify();
		}

		return g_rva01337abc;
	}

	return 0;
}
