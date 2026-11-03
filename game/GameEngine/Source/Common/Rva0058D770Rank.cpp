// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib 
// Retail 0x0058D770, 90 bytes: byte-for-byte the shape of the matched rank
// helper 0x004B24F0 (Rva004B24F0.cpp). It reads an object's experience-level
// node through TheExperienceLevelSystem (ILT 0x0000EDC7) and returns that
// node's rank through ILT 0x000012A8, or 0 when the ILT 0x0000DFC1 gate fails.
// The object arrives in EAX: its only caller, the 0x00594FD0 dump, loads EAX
// and calls directly, so the helper is static and a stub caller makes the
// compiler emit that private convention. Identity stays address-derived.

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

// ?rank0058D770@@YAHPAVObject@@@Z
static __declspec(noinline) int rank0058D770(Object *object)
{
	Iterator004B25D0 node;
	TheExperienceLevelSystem->rva0037F190((Rva0037F190Result *)&node, object);
	MpSkirmishFlagGateCall check = Rva0037E810Binding();
	if (!(TheExperienceLevelSystem->*check)(node))
		return 0;
	GoEGAaCall rank = Rva0037D810Binding();
	return (TheExperienceLevelSystem->*rank)(node);
}

// This caller exists only to make the compiler emit the helper's private
// convention, as retail's 0x00594FD0 caller does.
// ?rank0058D770Caller@@YAHPAVObject@@@Z absent-from-retail
int rank0058D770Caller(Object *object)
{
	return rank0058D770(object);
}
