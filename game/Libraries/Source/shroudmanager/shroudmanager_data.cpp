// cl: /DNDEBUG /MD /EHs-c- /O2 /Ob2
// ?bfmeDtorCDE@BfmeThingCDE@@QAEXXZ
//
// The node at 0x008F7EC0 clears the same 0x10-byte entries that this
// destructor passes to the array-delete helper. Its body is matched as
// ?method@Rva008F7EC0@@QAEXXZ at 0x008F7EC0 (Rva008F7EC0Sweep.cpp), so the
// call uses that name.

class CDEVirtualBase
{
public:
	virtual void f0();
	virtual void f1();
	virtual void f2();
	virtual void f3(void *arg);
};

class CDELeading
{
public:
	virtual void f0();
	virtual void f1();
};

class CDEProvider : public CDELeading, public virtual CDEVirtualBase
{
public:
	virtual void f0();
};

class CDELinkNode
{
public:
	void *m_00;
	char m_pad04[8];
	void *m_0c;
	char m_pad10[4];
	void *m_14;
};

// retail 0x008F7EC0, defined in game/GameEngine/Source/Common/Rva008F7EC0Sweep.cpp
class Rva008F7EC0
{
public:
	void method();
};

class BfmeHostXO
{
public:
	void bfmeFlushXO();
};

class BfmeThingCDE
{
public:
	bool bfmeCheckABI();
	void bfmeDtorCDE();

	void *m_owner;
	CDEProvider *m_ptr4;
	CDEProvider *m_ptr8;
	CDELinkNode *m_link0;
	CDELinkNode *m_link1;
	CDELinkNode *m_prev;
	CDELinkNode *m_next;
	void *m_array;
	int m_count;
	int m_values[16];
	int m_slots[16];
	unsigned char m_status[16];
	int m_bfmeB4;
	int m_bfmeB8;
	int m_bfmeBC;
	int m_bfmeC0;
	int m_bfmeA[2];
	unsigned int m_bfmeC[2];
	unsigned int m_bfmeB[2];
	unsigned char m_bfmeDC;
};

// 0x009F6D76 is the MSVC 7.1 CRT's own array-destruction helper, published by
// libc.lib's ..\build\intel\st_obj\ehvecdtr.obj under the reserved front-end
// name ??_M@YGXPAXIHP6EX0@Z@Z (see
// targets/game/reverse/identity_evidence/009f6d76-eh-vector-destructor-iterator.md).
// That is a reserved front-end name, not the mangling of any C++ declaration
// this compiler can spell, so it is declared as an extern "C" __identifier and
// reached through a local __stdcall view -- the same shape used by
// game/GameEngine/Source/Common/BfmeConv723.cpp. The fourth argument is the
// real Element destructor address, likewise spelled by __identifier, so this
// file needs no linker alias.
extern "C" void __cdecl __identifier("??_M@YGXPAXIHP6EX0@Z@Z")();
extern "C" void __cdecl __identifier("??1Element@@QAE@XZ")();

typedef void (__stdcall *VectorDestructorIterator)(
	void *base, unsigned int size, unsigned int count, void (*dtor)());

extern void __cdecl operator delete[](void *);

bool BfmeThingCDE::bfmeCheckABI()
{
	reinterpret_cast<BfmeHostXO *>(this)->bfmeFlushXO();

	if (m_ptr8 == 0)
		return false;

	unsigned int i = 0;
	int *value = &m_values[1];

	for (; i < 16; i += 4, value += 4)
	{
		if (m_status[i] && value[-1] == 3)
			break;
		if (m_status[i + 1] && value[0] == 3)
		{
			++i;
			break;
		}
		if (m_status[i + 2] && value[1] == 3)
		{
			i += 2;
			break;
		}
		if (m_status[i + 3] && value[2] == 3)
		{
			i += 3;
			break;
		}
	}

	if (i == 16)
		return false;

	m_ptr4->f3(0);
	m_ptr4 = 0;
	((CDELeading *)m_ptr8)->f1();
	return true;
}

void BfmeThingCDE::bfmeDtorCDE()
{
	reinterpret_cast<BfmeHostXO *>(this)->bfmeFlushXO();
	if (m_ptr4 != 0)
		m_ptr4->f3(0);
	if (m_ptr8 != 0)
	{
		m_ptr8->f3(0);
		m_ptr8->f0();
		m_ptr8 = 0;
	}
	reinterpret_cast<Rva008F7EC0 *>(this)->method();
	if (m_array != 0)
	{
		void *cookie = (char *)m_array - 4;
		((VectorDestructorIterator)__identifier("??_M@YGXPAXIHP6EX0@Z@Z"))(
			m_array, 0x10, *(unsigned *)cookie,
			__identifier("??1Element@@QAE@XZ"));
		::operator delete[](cookie);
	}
	if (m_prev != 0)
	{
		m_prev->m_00 = m_next;
		if (m_next != 0)
			m_next->m_14 = m_prev;
		m_prev = 0;
	}
	if (m_link1 != 0)
		m_link1->m_0c = m_link0;
	m_link0->m_00 = m_link1;
}
