// cl: /DNDEBUG /MD /EHsc

// TaintSpecialPowerModuleData's constructor, retail 0x0026B870.
//
// The base constructor is the shared SpecialPower module-data one that runs to
// +0x210, reached here through the incremental-link thunk at 0x00015C44, the
// same pin ScavengerSpecialPowerModuleData uses. Only the four fields from
// +0x210 to +0x21C belong to this class: three zeros and 10.0f at +0x214.
//
// WHERE THE VFTABLE STORE SITS IS NOT A SPELLING SWITCH, IT IS A BARRIER
// QUESTION. MSVC 7.1 sinks a constructor's vptr store forward until something
// stops it, and absent a barrier it sinks all the way to the head of the
// immediate-store group -- which is why every ordering of four plain scalar
// assignments, body or member-init list, chained or separate, ascending or
// descending, emits the vftable store next to the 10.0f store instead of at
// the top. Statement order does not reach it; nine such orderings were probed
// and all nine produced the same sunk shape.
//
// The two things that DO stop the sink are a store the compiler cannot prove
// stays inside the object (a global assignment -- what W3DTerrainVisual's
// constructor at 0x007304E0 uses) and the construction of a member sub-object.
// Retail has no spare global store here and no spare instruction to spend on
// one, so the barrier is the sub-object: the field at +0x210 is a small class
// with its own inline default constructor, and because member sub-objects are
// constructed AFTER the vptr is installed, the vftable store lands at the top
// exactly as retail has it. The remaining three fields are ordinary body
// assignments in retail's write order.
//
// This replaces an earlier spelling that used __declspec(novtable), an
// extern "C" vftable byte stored by hand, and volatile lvalues on every member.
// That reproduced the same bytes but for the wrong reason; volatile does not in
// fact pin the vptr store (it orders only the volatile accesses among
// themselves), so the whole construct only worked because novtable had removed
// the compiler's own vptr store from the problem. Nothing contrived is needed.

class BfmeSpecialPowerModuleDataBase
{
public:
	BfmeSpecialPowerModuleDataBase();

	virtual void moduleDataAnchor();

private:
	unsigned char m_unmodelled_04[ 0x210 - 4 ];
};

// The width and the zero initialiser are what the bytes show; the real type
// name is not recovered.  What IS recovered is that +0x210 is written by a
// sub-object constructor rather than by a statement in the body.
struct BfmeZeroedWord
{
	unsigned int m_value;

	BfmeZeroedWord() { m_value = 0; }
};

class TaintSpecialPowerModuleData : public BfmeSpecialPowerModuleDataBase
{
public:
	TaintSpecialPowerModuleData();

private:
	BfmeZeroedWord m_unmodelled_210;			// +0x210
	float m_unmodelled_214;						// +0x214
	unsigned int m_unmodelled_218;				// +0x218
	unsigned int m_unmodelled_21C;				// +0x21C
};

// ??0TaintSpecialPowerModuleData@@QAE@XZ
TaintSpecialPowerModuleData::TaintSpecialPowerModuleData()
{
	m_unmodelled_218 = 0;
	m_unmodelled_21C = 0;
	m_unmodelled_214 = 10.0f;
}
