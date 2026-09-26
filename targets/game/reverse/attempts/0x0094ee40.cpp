// ?firstValue@Rva0094EE40Owner@@QBEHXZ
// partial score=0.85 date=2026-09-06
struct Rva0094EE40Link { Rva0094EE40Link* m_prev; Rva0094EE40Link* m_next; };
struct Rva0094EE40Inner { char m_pad[0x34]; int m_value; };
struct Rva0094EE40Node : Rva0094EE40Link { int m_8; Rva0094EE40Inner* m_inner; };
struct Rva0094EE40Owner {
	char m_pad[0xa8];
	Rva0094EE40Link m_head;
	Rva0094EE40Node* getFirst() const { return m_head.m_next == &m_head ? 0 : (Rva0094EE40Node*)m_head.m_next; }
	int firstValue() const;
};
int Rva0094EE40Owner::firstValue() const
{
	if (!getFirst())
		return 0;
	return getFirst()->m_inner->m_value;
}
