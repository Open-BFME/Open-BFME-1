// cl: /EHsc

// ~DamageInfo() destroys its two data members in reverse declaration order
// (out, then in), then falls into the inherited Snapshot destructor on
// `this` itself. All three calls land on the same address because
// DamageInfoInput and DamageInfoOutput add no members of their own, so their
// implicit destructors are nothing but a direct call to Snapshot's.
//
// Snapshot is NOT polymorphic here: the retail bytes contain no vtable-
// pointer store anywhere in this function, which a virtual member would
// force at the top of ~DamageInfo(). Snapshot instead carries one real
// 4-byte data member of its own (the vendored ZH header does not show it --
// BFME's Snapshot keeps something ZH's commented out, or the header simply
// omits it). That one member is what gives `in` and `out` their exact +4
// and +8 spacing without any vtable involved, and it is why Snapshot's own
// destructor has to be a real out-of-line, non-inline call instead of
// folding away entirely.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Snapshot.h
class Snapshot
{
public:
	~Snapshot();

private:
	unsigned long m_snapshotData;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Damage.h
class DamageInfoInput : public Snapshot
{
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Damage.h
class DamageInfoOutput : public Snapshot
{
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Damage.h
class DamageInfo : public Snapshot
{
public:
	~DamageInfo();

private:
	DamageInfoInput in;
	DamageInfoOutput out;
};

// ??1DamageInfo@@QAE@XZ
DamageInfo::~DamageInfo()
{
}
