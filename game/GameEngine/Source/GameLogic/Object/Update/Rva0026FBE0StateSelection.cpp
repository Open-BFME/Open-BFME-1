// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Opaque owner at 0x0026FBE0: map five selector values to state keys and
// durations. Read the host anew between dispatches: callbacks can mutate it.
class Rva001CF980Result;
#define OBJECT_TU_MEMBERS Rva001CF980Result *queryAt001CF980();
#include "../Object.h"
#undef OBJECT_TU_MEMBERS
class Rva0016AD50
{
public:
	void bfmeSnapshot();
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
	void selectState(int selector, int argument);
	char m_pad0[8];
	Object *m_08;
	char m_pad30[0x30 - 0x08 - 4];
	void *m_host;
};
class RawCallShim { };
typedef void (RawCallShim::*RawVoidSlotFn)(void);
typedef void (RawCallShim::*RawIntSlotFn)(int);

void Rva0026FBE0Owner::selectState(int selector, int argument)
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
	void *host = m_host;
	void *slot = *(void **)((char *)host + 0x58);
	int currentKey = slot ? *(int *)((char *)slot + 4) : 0xf423f;
	if (currentKey == key)
		return;
	Object *owner = m_08;
	if (!owner)
		return;
	Rva001CF980Result *result = owner->queryAt001CF980();
	if (result)
	{
		void **vtable = *(void ***)result;
		void *slotFunction = vtable[70];
		RawVoidSlotFn pmf = *(RawVoidSlotFn *)&slotFunction;
		(((RawCallShim *)result)->*pmf)();
	}
	((Rva0016AD50 *)m_host)->bfmeSnapshot();
	void **hostVtable = *(void ***)m_host;
	void *hostFunction = hostVtable[14];
	RawIntSlotFn hostPmf = *(RawIntSlotFn *)&hostFunction;
	(((RawCallShim *)m_host)->*hostPmf)(argument);
	((Rva0016AD90 *)m_host)->setTemporaryState((StateID)key, frames);
}
