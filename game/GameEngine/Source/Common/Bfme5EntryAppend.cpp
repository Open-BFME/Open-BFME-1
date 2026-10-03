// An entry make-and-append body.
//
// It news a twenty-byte entry, initialises a sub-object inside it, stores the
// second argument, and hangs the entry off the end of the list its owner keeps
// far into the object.
//
// The entry's constructor is inlined behind the null test new does: one store
// of the owner pointer offset by 0x70, then the three zeroes of the
// sub-object's own default constructor. The two statements that follow -- the
// sub-object's init and the extra store -- are outside the test, because a
// member call and a member store do not null-check.
//
// The append is the usual twelve-byte node splice with placement new at +0x08
// and the predecessor cached before the four stores.

// The twelve-byte node comes from STLport's __new_alloc::allocate, whose
// 162-byte body retail keeps at 0x0082E540 (matched as
// ?allocate@__new_alloc@_STL@@SAPAXI@Z in
// game/Libraries/Source/WWVegas/WWLib/STL_new_alloc_allocateThunk.cpp and
// ICF-folded with _Rb_tree's __node_alloc::_M_allocate). Spelled under its
// real mangled name so the reference resolves to that definition.
namespace _STL
{
	class __new_alloc
	{
	public:
		static void *allocate(unsigned int bytes);
	};
}

inline void * __cdecl operator new(unsigned int, void *where) { return where; }

// The sub-object's initialiser is reached through retail's incremental-link
// thunk ?j_0000df49@@YAXXZ (0x0000DF49 -> 0x000D34C0), the matched ILT row in
// game/gen_small/thunks_006.cpp: the call site itself is what this body emits,
// so the reference must carry the ILT's niladic name. VC7.1 reserves
// __thiscall in a free-function-pointer typedef, so the established
// pointer-to-member cast idiom is used, exactly as RTS3DScene_Render_Thunk.cpp
// and ScoreScreenLeave.cpp do for the same class of call.
extern void j_0000df49();

class BfmeSub
{
public:
	BfmeSub(void) : m_bfmeA(0), m_bfmeB(0), m_bfmeC(0) {}

private:
	int m_bfmeA;						// +0x00
	int m_bfmeB;						// +0x04
	int m_bfmeC;						// +0x08
};

__forceinline void bfmeSubInit(BfmeSub *sub, void *value)
{
	typedef void (BfmeSub::*SubInit)(void *);
	union { void (*function)(); SubInit member; } thunk;

	thunk.function = j_0000df49;
	(sub->*thunk.member)(value);
}

class BfmeEntry
{
public:
	BfmeEntry(void *owner) : m_bfmeOwner((char *)owner + 0x70) {}

	void *m_bfmeOwner;					// +0x00
	BfmeSub m_bfmeSub;					// +0x04
	void *m_bfmeExtra;					// +0x10
};

struct BfmeEntryHead
{
	BfmeEntryHead *m_bfmeNext;				// +0x00
	BfmeEntryHead *m_bfmePrev;				// +0x04
};

struct BfmeEntryNode
{
	BfmeEntryNode *m_bfmeNext;				// +0x00
	BfmeEntryNode *m_bfmePrev;				// +0x04
	BfmeEntry *m_bfmeValue;					// +0x08
};

class Gen_000D5E90
{
public:
	void bfmeAdd(void *owner, void *extra);

private:
	char m_bfmePad[0x640];					// +0x00
	BfmeEntryHead *m_bfmeList;				// +0x640
};

// ?bfmeAdd@Gen_000D5E90@@QAEXPAX0@Z
void Gen_000D5E90::bfmeAdd(void *owner, void *extra)
{
	BfmeEntry *entry = new BfmeEntry(owner);

	bfmeSubInit(&entry->m_bfmeSub, (char *)owner + 0x74);
	entry->m_bfmeExtra = extra;

	BfmeEntryHead *head = m_bfmeList;
	BfmeEntryNode *node = (BfmeEntryNode *)_STL::__new_alloc::allocate(sizeof(BfmeEntryNode));

	new (&node->m_bfmeValue) BfmeEntry *(entry);

	BfmeEntryHead *previous = head->m_bfmePrev;
	node->m_bfmeNext = (BfmeEntryNode *)head;
	node->m_bfmePrev = (BfmeEntryNode *)previous;
	previous->m_bfmeNext = (BfmeEntryHead *)node;
	head->m_bfmePrev = (BfmeEntryHead *)node;
}
