// ?visitAll@Rva00124C70Owner@@QAEXPAURva00124C70Visitor@@@Z
struct Rva00124C70Flags { bool m_a; bool m_b; };
struct Rva00124C70Visitor {
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
	virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
	virtual void begin(Rva00124C70Flags* flags);
	virtual void s11();
	virtual void visit(void* item);
};
struct Rva00124C70Owner {
	char m_pad[0x10];
	void** m_begin;
	void** m_end;
	void visitAll(Rva00124C70Visitor* visitor);
};
void Rva00124C70Owner::visitAll(Rva00124C70Visitor* visitor)
{
	Rva00124C70Flags flags;
	flags.m_a = true;
	flags.m_b = true;
	visitor->begin(&flags);
	for (void** it = m_begin; it != m_end; ++it)
		visitor->visit(*it);
}
