// cl: /EHsc /Igame/Libraries/Source/WWVegas/WWLib 
// Retail 0x004B2330, 252 bytes: the TooltipText rank-cap helper.  It walks
// the object's experience-level iterator to the end of the run and returns
// that node's rank, clamped down to the object's rank limit when the limit
// query answers true.  Identity stays address-derived: the helper is only
// reached from the TooltipText builder at 0x004B25D0 and no owning class name
// survives.
// The level queries are reached through ILT 0x0000EDC7, 0x0000DFC1,
// 0x00041295, 0x000012A8 and 0x00031471, so each call site is bound with the
// matched retail body's own name (rva0037F190 / rva0037F220 on
// ExperienceLevelSystem, bfmeMpSkirmishFlagGate at 0x0037E810, bfmeGoEGAa at
// 0x0037D810, Gen_001b2030::m at 0x001B2030) through the
// function-pointer/member-pointer union idiom CommandXlatVoice.cpp uses.

class Object;

struct Rva0037F190Result;

struct Rva0037F220Iterator
{
	void *a;
	void *b;
	Rva0037F220Iterator() {}
	Rva0037F220Iterator(const Rva0037F220Iterator &other) : a(other.a), b(other.b) {}
};

class ExperienceLevelSystem
{
public:
	void rva0037F190(Rva0037F190Result *result, Object *object);
	bool at0037E810(Rva0037F220Iterator value);
	Rva0037F220Iterator rva0037F220(Rva0037F220Iterator value);
	int at0037D810(Rva0037F220Iterator value);
};

extern ExperienceLevelSystem *TheExperienceLevelSystem;

struct BfmeFlagHolder;
class BfmeFlagCandidate;
struct BfmeThingEGA;
bool __stdcall bfmeMpSkirmishFlagGate(BfmeFlagHolder *, BfmeFlagCandidate *);
void *__stdcall bfmeGoEGAa(void *, BfmeThingEGA *);

class Gen_001b2030
{
public:
	bool m(int value);
};

typedef bool (ExperienceLevelSystem::*MpSkirmishFlagGateCall)(Rva0037F220Iterator);
__forceinline MpSkirmishFlagGateCall Rva0037E810Binding()
{
	union { bool (__stdcall *raw)(BfmeFlagHolder *, BfmeFlagCandidate *); MpSkirmishFlagGateCall member; } fn;
	fn.raw = bfmeMpSkirmishFlagGate;
	return fn.member;
}

typedef int (ExperienceLevelSystem::*GoEGAaCall)(Rva0037F220Iterator);
__forceinline GoEGAaCall Rva0037D810Binding()
{
	union { void *(__stdcall *raw)(void *, BfmeThingEGA *); GoEGAaCall member; } fn;
	fn.raw = bfmeGoEGAa;
	return fn.member;
}

template<class T> inline T &field004B2330(void *p, unsigned n) { return *(T *)((char *)p + n); }

// ?Rva004B2330@@YAHPAVObject@@@Z
static __declspec(noinline) int Rva004B2330(Object *object)
{
	Rva0037F220Iterator it;
	TheExperienceLevelSystem->rva0037F190((Rva0037F190Result *)&it, object);
	if (!(TheExperienceLevelSystem->*Rva0037E810Binding())(it))
		return 0;
	Rva0037F220Iterator next = TheExperienceLevelSystem->rva0037F220(it);
	while ((TheExperienceLevelSystem->*Rva0037E810Binding())(next))
	{
		it = next;
		next = TheExperienceLevelSystem->rva0037F220(it);
	}
	int rank = (TheExperienceLevelSystem->*Rva0037D810Binding())(it);
	int cap;
	if (field004B2330<Gen_001b2030 *>(object, 0x210)->m((int)&cap) && cap < rank)
		rank = cap;
	return rank;
}

// This caller exists only to make the compiler emit the helper's private
// convention, as retail's TooltipText builder does.
// ?Rva004B2330Caller@@YAHPAVObject@@@Z absent-from-retail
int Rva004B2330Caller(Object *object)
{
	return Rva004B2330(object);
}
