// Four 25-byte bodies with one shape: read the word at +0xBC, hand it to a
// member of a global object, and tail-jump into a member of whatever came
// back.
//
//     mov eax, [ecx + 0xBC]
//     mov ecx, [global]
//     push eax
//     call <finder>
//     mov ecx, eax
//     jmp  <getter>
//
// All four go through the same finder, so the type it returns is the same in
// all four; only the getter differs, which is why one result class carries
// four differently named members rather than four classes carrying one each.
// The global's address rides a DIR32 relocation from retail.

// Each callee below is a 5-byte ILT thunk whose only definition in the link
// is the gen-thunk body at that address (game/gen_small/thunks_0*.cpp), so
// call each one under its defined name: the defined mangling takes no
// arguments, so the real shapes are reached through the established
// pointer-to-member cast idiom (see Rva00219C70Remove.cpp, which calls the
// very same thunk at 0x0002F52C). The views below carry the shapes; they add
// no vtable and no code.
extern void j_0002f52c();							// ?j_0002f52c@@YAXXZ, ILT 0x0002F52C
extern void j_00027746();							// ?j_00027746@@YAXXZ, ILT 0x00027746
extern void j_0002818c();							// ?j_0002818c@@YAXXZ, ILT 0x0002818C
extern void j_00036165();							// ?j_00036165@@YAXXZ, ILT 0x00036165
extern void j_000456e2();							// ?j_000456e2@@YAXXZ, ILT 0x000456E2

class BfmeChainCallView
{
public:
	void *bfmeFind(int key);						// thiscall finder, key passed on the stack
	void *bfmeGet_002197e0(void);					// ILT 0x00027746
	void *bfmeGet_00219890(void);					// ILT 0x0002818C
	void *bfmeGet_002198b0(void);					// ILT 0x00036165
	void *bfmeGet_002198d0(void);					// ILT 0x000456E2
};

typedef void *(BfmeChainCallView::*BfmeChainFind)(int key);
typedef void *(BfmeChainCallView::*BfmeChainGet)(void);

union BfmeChainFindTarget
{
	void (*freeFunction)();
	BfmeChainFind memberFunction;
};

union BfmeChainGetTarget
{
	void (*freeFunction)();
	BfmeChainGet memberFunction;
};

// The DIR32 at 0x012F086C is retail's `CaveSystem *TheCaveSystem`
// (?TheCaveSystem@@3PAVCaveSystem@@A). The class itself is declared by
// game/GameEngine/Source/Common/System/game_engine_subsystems.h, so it is only
// forward-declared here and this TU's own view of it, BfmeChainCallView, is
// reached through a cast -- no second CaveSystem is declared in this TU.
class CaveSystem;

extern CaveSystem *TheCaveSystem;					// 0x012F086C

class Gen_002197e0
{
public:
	void *bfmeLookup(void);

private:
	char m_bfmeHead[0xBC];
	int m_bfme00BC;							// +0xBC
};

class Gen_00219890
{
public:
	void *bfmeLookup(void);

private:
	char m_bfmeHead[0xBC];
	int m_bfme00BC;							// +0xBC
};

class Gen_002198b0
{
public:
	void *bfmeLookup(void);

private:
	char m_bfmeHead[0xBC];
	int m_bfme00BC;							// +0xBC
};

class Gen_002198d0
{
public:
	void *bfmeLookup(void);

private:
	char m_bfmeHead[0xBC];
	int m_bfme00BC;							// +0xBC
};

// ?bfmeLookup@Gen_002197e0@@QAEPAXXZ
void *Gen_002197e0::bfmeLookup(void)
{
	BfmeChainFindTarget findTarget = { &j_0002f52c };
	BfmeChainGetTarget getTarget = { &j_00027746 };
	void *result = (reinterpret_cast<BfmeChainCallView *>(TheCaveSystem)->*findTarget.memberFunction)(m_bfme00BC);
	return (reinterpret_cast<BfmeChainCallView *>(result)->*getTarget.memberFunction)();
}

// ?bfmeLookup@Gen_00219890@@QAEPAXXZ
void *Gen_00219890::bfmeLookup(void)
{
	BfmeChainFindTarget findTarget = { &j_0002f52c };
	BfmeChainGetTarget getTarget = { &j_0002818c };
	void *result = (reinterpret_cast<BfmeChainCallView *>(TheCaveSystem)->*findTarget.memberFunction)(m_bfme00BC);
	return (reinterpret_cast<BfmeChainCallView *>(result)->*getTarget.memberFunction)();
}

// ?bfmeLookup@Gen_002198b0@@QAEPAXXZ
void *Gen_002198b0::bfmeLookup(void)
{
	BfmeChainFindTarget findTarget = { &j_0002f52c };
	BfmeChainGetTarget getTarget = { &j_00036165 };
	void *result = (reinterpret_cast<BfmeChainCallView *>(TheCaveSystem)->*findTarget.memberFunction)(m_bfme00BC);
	return (reinterpret_cast<BfmeChainCallView *>(result)->*getTarget.memberFunction)();
}

// ?bfmeLookup@Gen_002198d0@@QAEPAXXZ
void *Gen_002198d0::bfmeLookup(void)
{
	BfmeChainFindTarget findTarget = { &j_0002f52c };
	BfmeChainGetTarget getTarget = { &j_000456e2 };
	void *result = (reinterpret_cast<BfmeChainCallView *>(TheCaveSystem)->*findTarget.memberFunction)(m_bfme00BC);
	return (reinterpret_cast<BfmeChainCallView *>(result)->*getTarget.memberFunction)();
}
