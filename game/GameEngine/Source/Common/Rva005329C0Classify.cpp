// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

// Both wrappers call retail's ILT thunk 0x00047807, five bytes of
// `jmp 0x00532280`, with the receiver in ECX and (object, slot) on the stack.
// 0x00047807 is the call target the ledger pins these two wrappers to and the
// only symbol defined there is the generated zero-argument thunk
// ?j_00047807@@YAXXZ (game/gen_small/thunks_034.cpp); the address the thunk
// reaches is an int3 run the ledger holds as the anonymous dump
// ?d_00532280@@YAXXZ (game/gen_asm/d_004e8320.asm), whose dump name cannot be
// called with arguments. So the reference carries the thunk's name and the
// two-argument thiscall shape is recovered through the union pun the tree
// already uses for thunks reached with arguments (BfmeConv1850.cpp,
// game/GameEngine/Source/Common/INI/INIWindowTransition.cpp). The descriptive
// Rva005329Classify::classify spelling stays the name of the dispatch site; the
// definition it belongs to is the parent's to name.
extern void j_00047807();

class Rva005329C0Obj;

class Rva005329Classify
{
public:
	typedef void (Rva005329Classify::*Dispatch)(Rva005329C0Obj *, int);
};

class Rva005329C0
{
public:
	void wrap(Rva005329C0Obj *obj);
};

void Rva005329C0::wrap(Rva005329C0Obj *obj)
{
	union { void (*thunk)(); Rva005329Classify::Dispatch dispatch; } pun;
	pun.thunk = j_00047807;

	(reinterpret_cast<Rva005329Classify *>(this)->*pun.dispatch)(obj, 2);
}

class Rva005329E0
{
public:
	void wrap(Rva005329C0Obj *obj);
};

void Rva005329E0::wrap(Rva005329C0Obj *obj)
{
	union { void (*thunk)(); Rva005329Classify::Dispatch dispatch; } pun;
	pun.thunk = j_00047807;

	(reinterpret_cast<Rva005329Classify *>(this)->*pun.dispatch)(obj, 3);
}