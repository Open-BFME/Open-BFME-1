// Retail 0x00253D50, split by the ledger across its two return arms.
//
// The four pushes name the callee exactly: 0.0f, 1.0f, a file path and a
// decimal line number are GetGameLogicRandomValueReal's arguments, and the
// path still in the image is
//
//     F:\bfme\Code\gameengine\Source\GameLogic\Object\Die\CreateCrateDie.cpp
//
// with 0x70 for the line, so this body was compiled from line 112 of that
// file. The two float bounds are pushed as immediates, so they are literals
// rather than the named constants a memory compare would need.
//
// The value it is compared against is read out of the argument BEFORE the call
// and parked in the argument's own stack slot, which is free because the
// pointer is already in a register. That only happens if the source holds it
// in a local first -- comparing the member directly makes MSVC reload the
// pointer after the call instead, and the body loses eight bytes. fcomp's C0 says the random draw is the
// smaller one, and test ah,5 with jp branches away when it is not -- so the
// true case is a strict less-than, the usual shape of a percentage roll.

typedef float Real;

Real GetGameLogicRandomValueReal(Real low, Real high, char *file, int line);

class Gen_00253d50Arg
{
public:
	char m_bfmeHead[0x10];
	Real m_bfmeChance;						// +0x10
};

// ?Gen_00253d50@@YGHPBVGen_00253d50Arg@@@Z
int __stdcall Gen_00253d50(const Gen_00253d50Arg *info)
{
	Real chance = info->m_bfmeChance;

	if (GetGameLogicRandomValueReal(0.0f, 1.0f,
			"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Die\\CreateCrateDie.cpp",
			112) < chance)
		return 1;

	return 0;
}
