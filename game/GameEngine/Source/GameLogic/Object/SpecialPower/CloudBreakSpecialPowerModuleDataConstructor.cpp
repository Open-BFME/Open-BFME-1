// cl: /DNDEBUG /MD /EHsc

// CloudBreakSpecialPowerModuleData's constructor, retail 0x002592A0.
//
// Same shape as TaintSpecialPowerModuleData at 0x0026B870: the shared
// SpecialPower module-data base running to +0x210, reached through the
// incremental-link thunk at 0x00015C44, then four fields of this class's own --
// 10.0f at +0x210, two zeros, and 100.0f at +0x21C.
//
// Retail writes the vftable pointer first, then +0x218 and +0x214 out of the
// zeroing register, then the two float constants ascending. MSVC 7.1 sinks a
// constructor's vptr store forward until a barrier stops it, and four plain
// scalar assignments give it none, so it ends up at the head of the
// immediate-store group beside the 10.0f. The barrier that puts it back at the
// top is a member sub-object: +0x218 is a small class whose inline default
// constructor zeroes it, and member sub-objects are constructed after the vptr
// is installed. Everything else is an ordinary body assignment, and the body's
// source order IS retail's write order -- +0x214, then +0x210, then +0x21C.
// The zero pair's order is not a canonicalisation, it is just which field the
// sub-object owns.
//
// This replaces an earlier __declspec(novtable) plus hand-written vftable plus
// volatile-lvalue spelling. Volatile turned out not to pin the vptr store at
// all; see the note on Taint's constructor.

class BfmeSpecialPowerModuleDataBase
{
public:
	BfmeSpecialPowerModuleDataBase();

	virtual void moduleDataAnchor();

private:
	unsigned char m_unmodelled_04[ 0x210 - 4 ];
};

// Width and zero initialiser are what the bytes show; the real type name is not
// recovered.  What IS recovered is that +0x218 is written by a sub-object
// constructor rather than by a statement in the body.
struct BfmeZeroedWord
{
	unsigned int m_value;

	BfmeZeroedWord() { m_value = 0; }
};

class CloudBreakSpecialPowerModuleData : public BfmeSpecialPowerModuleDataBase
{
public:
	CloudBreakSpecialPowerModuleData();

private:
	float m_unmodelled_210;						// +0x210
	unsigned int m_unmodelled_214;				// +0x214
	BfmeZeroedWord m_unmodelled_218;			// +0x218
	float m_unmodelled_21C;						// +0x21C
};

// ??0CloudBreakSpecialPowerModuleData@@QAE@XZ
CloudBreakSpecialPowerModuleData::CloudBreakSpecialPowerModuleData()
{
	m_unmodelled_214 = 0;
	m_unmodelled_210 = 10.0f;
	m_unmodelled_21C = 100.0f;
}
