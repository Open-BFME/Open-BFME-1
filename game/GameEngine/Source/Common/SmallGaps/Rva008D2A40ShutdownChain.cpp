// ?shutdownChain008D2A40@@YAXXZ
struct Rva008D2A40Node {
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5();
	virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
	virtual void s12();
	virtual ~Rva008D2A40Node();
	virtual void s14();
	virtual void shutdown();
	int m_4; Rva008D2A40Node* m_next;
};
extern Rva008D2A40Node* Rva008D2A40Head;
void shutdownChain008D2A40()
{
	while (Rva008D2A40Head) {
		Rva008D2A40Node* next = Rva008D2A40Head->m_next;
		Rva008D2A40Head->shutdown();
		delete Rva008D2A40Head;
		Rva008D2A40Head = next;
	}
}
