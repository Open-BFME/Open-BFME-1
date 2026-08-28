// cl: /DNDEBUG /MD /EHsc
// readable body of ?getNATPortAllocationScheme@FirewallHelperClass@@AAEHHPAG0AA_N1@Z: Code/GameEngine/Source/GameNetwork/FirewallHelper.cpp
// Open-BFME: FirewallHelperClass::getNATPortAllocationScheme, retail
// 0x0066E870, 242 bytes. The body carried no ledger row; its name sat on a
// 5-byte thunk.
//
// The reference's body minus two things BFME dropped: the bubble sort over the
// two port arrays and the sequential/semi-sequential special cases. What is
// left is the ladder of difference tests -- the three absolute delta cases,
// then the same three again after subtracting the original ports, which is
// what makes the result relative -- and the compiler merges the shared tails,
// which is why the first comparison lands on two exits.

typedef int Int;
typedef unsigned short UnsignedShort;
typedef bool Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/FirewallHelper.h
class FirewallHelperClass
{
private:
	Int getNATPortAllocationScheme(Int numPorts, UnsignedShort *originalPorts, UnsignedShort *mangledPorts, Bool &relativeDelta, Bool &looksGood);
};

Int FirewallHelperClass::getNATPortAllocationScheme(Int numPorts, UnsignedShort *originalPorts, UnsignedShort *mangledPorts, Bool &relativeDelta, Bool &looksGood)
{
	Int diff1 = mangledPorts[1] - mangledPorts[0];
	Int diff2 = mangledPorts[2] - mangledPorts[1];
	Int diff3 = mangledPorts[3] - mangledPorts[2];

	if (diff1 == diff2 && diff2 == diff3) {
		relativeDelta = false;
		looksGood = true;
		return(diff1);
	}

	if (diff1 == diff2) {
		relativeDelta = false;
		looksGood = false;
		return(diff1);
	}

	if (diff2 == diff3) {
		relativeDelta = false;
		looksGood = false;
		return(diff2);
	}

	for (Int i=0 ; i<numPorts ; i++) {
		mangledPorts[i] -= originalPorts[i];
	}

	diff1 = mangledPorts[1] - mangledPorts[0];
	diff2 = mangledPorts[2] - mangledPorts[1];
	diff3 = mangledPorts[3] - mangledPorts[2];

	if (diff1 == diff2 && diff2 == diff3) {
		relativeDelta = true;
		looksGood = true;
		return(diff1);
	}

	if (diff1 == diff2 || diff1 == diff3) {
		relativeDelta = true;
		looksGood = false;
		return(diff1);
	}

	if (diff2 == diff3) {
		relativeDelta = true;
		looksGood = false;
		return(diff2);
	}

	looksGood = false;
	relativeDelta = false;
	return(0);
}
