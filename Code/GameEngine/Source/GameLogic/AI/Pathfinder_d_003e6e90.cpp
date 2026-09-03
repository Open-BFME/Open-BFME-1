// cl: /DNDEBUG /MD
//
// Retail 0x003E6E90: six-argument thiscall wrapper around 0x003DF580.  Forwards
// the six arguments plus &arg6 and a trailing 0, then returns whether arg6 is
// null when the inner call succeeded.

typedef unsigned char Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Pathfinder
{
public:
	Bool bfmeInnerE6E90(void *a1, void *a2, void *a3, void *a4, void *a5,
		void *a6, void **a7, int a8);
	Bool bfmeWrapE6E90(void *a1, void *a2, void *a3, void *a4, void *a5,
		void *a6);
};

// ?bfmeWrapE6E90@Pathfinder@@QAEEPAX00000@Z
Bool Pathfinder::bfmeWrapE6E90(void *a1, void *a2, void *a3, void *a4, void *a5,
	void *a6)
{
	if (!bfmeInnerE6E90(a1, a2, a3, a4, a5, a6, &a6, 0))
		return 0;
	int result = 0;
	void *p = a6;
	return (Bool)(result + (p == 0));
}
