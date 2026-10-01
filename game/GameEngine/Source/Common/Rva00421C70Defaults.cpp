// Retail 0x00421C70, 134 bytes: independent address-derived storage view.
// ECX supplies the destination; EAX returns the same address; RET takes no
// stack arguments. No caller/vtable/native declaration establishes its owner
// or constructor identity, so this is an ordinary explicit initializer method.
// Fields and triple-word subobjects name only physical offsets. Float and int
// spellings reproduce the witnessed constant bits and copies, not native types.
// The view has no constructor, base, vptr, ownership or lifetime claim.
// Boundary: INT3 through 0x00421C6F; RET at 0x00421CF5; INT3 starts CF6.
// Source lever shared with exact 0x00421D30: keep +4C/+50/+54 stores after
// triple-word copies. The late 1.0f stores preserve EBX/ESI/EDI allocation.
// The independent +58/+5C word stores are witnessed here, not inferred from
// the nearby initializer. No shared owner between the two views is asserted.
class Rva00421C70Vec
{
public:
	float m_00;
	float m_04;
	float m_08;
};

class Rva00421C70
{
public:
	Rva00421C70 *rva00421C70();

	float m_00;
	float m_04;
	float m_08;
	float m_0C;
	float m_10;
	float m_14;
	float m_18;
	float m_1C;
	float m_20;
	float m_24;
	Rva00421C70Vec m_28;
	Rva00421C70Vec m_34;
	Rva00421C70Vec m_40;
	float m_4C;
	float m_50;
	float m_54;
	int m_58;
	int m_5C;
};

Rva00421C70 *Rva00421C70::rva00421C70()
{
	m_00 = 4.0f;
	m_04 = 0.7f;
	m_08 = 1.0f;
	m_0C = 1.0f;
	m_10 = 1.0f;
	m_14 = 1.0f;
	m_18 = 1.0f;
	m_1C = 1.0f;
	m_24 = 1.0f;
	m_20 = 1.0f;
	m_34.m_00 = 0.5f;
	m_34.m_04 = 0.5f;
	m_34.m_08 = 0.5f;
	m_40 = m_34;
	m_28 = m_34;
	m_4C = 1.0f;
	m_50 = 1.0f;
	m_54 = 5.0f;
	m_58 = 3;
	m_5C = 1;
	return this;
}
