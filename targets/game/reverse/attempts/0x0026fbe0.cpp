// ?rva0026fbe0@Rva0026FBE0Owner@@QAEXHH@Z
// partial score=0.4 date=2026-09-21
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// ?d_0026fbe0@@YAXXZ. A 6-way switch on `selector` maps to a "key" constant
// (0x30/0x2a/0x14/0x3b/0x3a) and a frame count (-1 default, -2 for the last
// two cases); selector 1 and anything past 5 are no-ops. The common path
// reads this->m_30 (a BfmeHostXZ-shaped host, see BfmeConv2082.cpp) and its
// m_58 slot pointer; if the slot's own +4 field already equals the key,
// nothing changes. Otherwise this->m_08 (a BfmeX920D) is queried, the
// result's vslot 70 (+0x118) is invoked with no args if non-null, the host's
// bfmeSnapshot (0x0016AD50, Bfme5TinyNineteen.cpp) and vslot 14 (+0x38,
// with the second argument) run unconditionally, and finally the host's
// setTemporaryState (0x0016AD90, BfmeConv2082.cpp's bfmeStartXZ thunk) is
// called with the chosen key/frames.

class BfmeRes920D;

class BfmeX920D
{
public:
	BfmeRes920D *bfmeGet920D(void);
};

class Rva0016AD50
{
public:
	void bfmeSnapshot(void);
};

enum StateID { };

class Rva0016AD90
{
public:
	void setTemporaryState(StateID state, int frames);
};

class Rva0026FBE0Owner
{
public:
	void rva0026fbe0(int selector, int param2);

private:
	char m_pad0[8];
	BfmeX920D *m_08;
	char m_pad30[0x30 - 0x08 - 4];
	void *m_30;
};

// Raw-vtable-slot call shims: a non-virtual pointer-to-member-function call
// is a plain thiscall (ecx=this) with no vtable indirection of its own, so
// reinterpreting a slot's function pointer as one reproduces retail's
// `call [reg+N]` exactly without modelling the whole vtable.
class RawCallShim { };
typedef void (RawCallShim::*RawVoidSlotFn)(void);
typedef void (RawCallShim::*RawIntSlotFn)(int);

// ?d_0026fbe0@@YAXXZ
void Rva0026FBE0Owner::rva0026fbe0(int selector, int param2)
{
	int key;
	int frames = -1;

	switch (selector)
	{
	case 0: key = 0x30; break;
	case 1: return;
	case 2: key = 0x2a; break;
	case 3: key = 0x14; break;
	case 4: key = 0x3b; frames = -2; break;
	case 5: key = 0x3a; frames = -2; break;
	default: return;
	}

	void *host = m_30;
	void *slot = *(void **)((char *)host + 0x58);
	int currentKey = slot ? *(int *)((char *)slot + 4) : 0xf423f;

	if (currentKey == key)
		return;

	BfmeX920D *owner = m_08;
	if (!owner)
		return;

	BfmeRes920D *res = owner->bfmeGet920D();
	if (res)
	{
		void **resVtbl = *(void ***)res;
		void *slotFn = resVtbl[70];
		RawVoidSlotFn pmf = *(RawVoidSlotFn *)&slotFn;
		(((RawCallShim *)res)->*pmf)();
	}

	((Rva0016AD50 *)host)->bfmeSnapshot();

	void **hostVtbl = *(void ***)host;
	void *hostSlotFn = hostVtbl[14];
	RawIntSlotFn hostPmf = *(RawIntSlotFn *)&hostSlotFn;
	(((RawCallShim *)host)->*hostPmf)(param2);

	((Rva0016AD90 *)host)->setTemporaryState((StateID)key, frames);
}
