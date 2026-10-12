// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /I.
// Retail 0x004B24F0, 90 bytes: the TooltipText rank helper. It reads an
// object's experience-level iterator through TheExperienceLevelSystem and
// returns that node's rank, or 0 when no node matches.
// The two level queries are reached through ILT 0x0000DFC1 and 0x000012A8, so
// each call site is bound with the matched retail body's own name
// (bfmeMpSkirmishFlagGate at 0x0037E810, bfmeGoEGAa at 0x0037D810) through the
// function-pointer/member-pointer union idiom CommandXlatVoice.cpp uses.
// Identity stays address-derived: the helper is only reached from the
// TooltipText builder at 0x004B25D0 and no owning class name survives.

class Object;

struct Iterator004B25D0
{
	void *a;
	void *b;
	Iterator004B25D0() {}
	Iterator004B25D0(const Iterator004B25D0 &other) : a(other.a), b(other.b) {}
};

// The ABI view of the list lookup, whose matched ledger row names this type.
struct Rva0037F190Result;

class ExperienceLevelSystem
{
public:
	void rva0037F190(Rva0037F190Result *, Object *);
	bool at0037E810(Iterator004B25D0);
	int at0037D810(Iterator004B25D0);
};

extern ExperienceLevelSystem *TheExperienceLevelSystem;

struct BfmeFlagHolder;
class BfmeFlagCandidate;
struct BfmeThingEGA;
bool __stdcall bfmeMpSkirmishFlagGate(BfmeFlagHolder *, BfmeFlagCandidate *);
void *__stdcall bfmeGoEGAa(void *, BfmeThingEGA *);

typedef bool (ExperienceLevelSystem::*MpSkirmishFlagGateCall)(Iterator004B25D0);
__forceinline MpSkirmishFlagGateCall Rva0037E810Binding()
{
	union { bool (__stdcall *raw)(BfmeFlagHolder *, BfmeFlagCandidate *); MpSkirmishFlagGateCall member; } fn;
	fn.raw = bfmeMpSkirmishFlagGate;
	return fn.member;
}

typedef int (ExperienceLevelSystem::*GoEGAaCall)(Iterator004B25D0);
__forceinline GoEGAaCall Rva0037D810Binding()
{
	union { void *(__stdcall *raw)(void *, BfmeThingEGA *); GoEGAaCall member; } fn;
	fn.raw = bfmeGoEGAa;
	return fn.member;
}

// ?rank004B24F0@@YAHPAVObject@@@Z
static __declspec(noinline) int rank004B24F0(Object *object)
{
	Iterator004B25D0 node;
	TheExperienceLevelSystem->rva0037F190((Rva0037F190Result *)&node, object);
	if (!(TheExperienceLevelSystem->*Rva0037E810Binding())(node))
		return 0;
	return (TheExperienceLevelSystem->*Rva0037D810Binding())(node);
}

// This caller exists only to make the compiler emit the helper's private
// convention, as retail's TooltipText builder does.
// ?rank004B24F0Caller@@YAHPAVObject@@@Z absent-from-retail
int rank004B24F0Caller(Object *object)
{
	return rank004B24F0(object);
}
