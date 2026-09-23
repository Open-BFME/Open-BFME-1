// ?aptMarkOwner@@YAXPAXPAURva008C6DC0Holder@@@Z
// cl: /DNDEBUG /MD /EHsc
struct Rva008C6DC0Owner { char m_pad[0x1c]; unsigned int m_flags; };
struct Rva008C6DC0Value {
	int m_0;
	union { unsigned int m_flags; struct { unsigned int m_type : 6; unsigned int m_bits : 9; unsigned int m_pooled : 1; }; };
	char m_pad[0x50 - 8];
	Rva008C6DC0Owner* m_owner;
};
struct Rva008C6DC0Holder { int m_0; Rva008C6DC0Value* m_value; };
void aptMarkOwner(void* self, Rva008C6DC0Holder* holder)
{
	Rva008C6DC0Value* v = holder->m_value;
	bool notPooled = !v->m_pooled;
	if (!notPooled && v->m_type != 0x13)
		v->m_owner->m_flags |= 0x2000000;
}

// RVA 0x008C6DF0: adjacent action-table entry VA 0x012D5A84.
// The matching setter is entry VA 0x012D5A80 -> RVA 0x008C6DC0.
// Identical pooled/type guard and owner layout; this body clears bit 25.
void aptClearOwnerFlag_008C6DF0(void* self, Rva008C6DC0Holder* holder)
{
	Rva008C6DC0Value* v = holder->m_value;
	bool notPooled = !v->m_pooled;
	if (!notPooled && v->m_type != 0x13)
		v->m_owner->m_flags &= ~0x2000000u;
}
