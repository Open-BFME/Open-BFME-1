// cl: /O2 /Ob0

// Retail stores 0x01073744 at +0, Snapshot's vftable, i.e.
// ??_7Snapshot@@6B@ (targets/game/reverse/dir32_addresses.csv; ??0Snapshot at
// 0x0006B180 installs it). The declaration carries no C++ name: __identifier
// spells the retail symbol exactly, so the store below references the defining
// name, as WorldHeightMapRva0074ACB0Load.cpp does for BfmeParserBindingBaseVE.
extern "C" const void *__identifier("??_7Snapshot@@6B@")[];

class Rva0045C1B0
{
	unsigned m_vt;
	int m_zero;

public:
	void apply();
};

void Rva0045C1B0::apply()
{
	m_zero = 0;
	m_vt = (unsigned)__identifier("??_7Snapshot@@6B@");
}
