// cl: /DNDEBUG /MD

typedef unsigned char Bool;

// Retail calls the ILT thunk at 0x00049F3F, which gen_small/thunks_035.cpp owns
// as ?j_00049f3f@@YAXXZ; it forwards to 0x003DF580. The wrapper's own bytes set
// up eight stack arguments and never touch ecx, so the call is emitted through
// a member-call shape (which is the only one MSVC 7.1 gives callee-cleanup
// argument pushes without preloading the first two arguments into ecx/edx)
// while the referenced name stays the ledger's address-derived thunk.
void j_00049f3f(void);

class Inner39Query
{
public:
	Bool query(void *a1, void *a2, void *a3, void *a4, void *a5, void *a6,
		void **a7, int a8);
};
typedef Bool (Inner39Query::*Inner39QueryCall)(void *a1, void *a2, void *a3,
	void *a4, void *a5, void *a6, void **a7, int a8);

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Pathfinder
{
public:
	Bool bfmeWrapE6E90(void *a1, void *a2, void *a3, void *a4, void *a5,
		void *a6);
};

// ?bfmeWrapE6E90@Pathfinder@@QAEEPAX00000@Z
Bool Pathfinder::bfmeWrapE6E90(void *a1, void *a2, void *a3, void *a4, void *a5,
	void *a6)
{
	union
	{
		void (*raw)(void);
		Inner39QueryCall member;
	} call;
	call.raw = j_00049f3f;

	if (!(reinterpret_cast<Inner39Query *>(this)->*call.member)(
			a1, a2, a3, a4, a5, a6, &a6, 0))
		return 0;
	int result = 0;
	void *p = a6;
	return (Bool)(result + (p == 0));
}