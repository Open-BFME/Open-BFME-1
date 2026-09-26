// ?shutdownChain008D29D0@@YAXXZ
struct Rva008D29D0Node {
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5();
	virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
	virtual void s12();
	virtual ~Rva008D29D0Node();
	virtual void s14();
	virtual void shutdown();
	int m_4; Rva008D29D0Node* m_next;
};
extern Rva008D29D0Node* Rva008D29D0Head;
void shutdownChain008D29D0()
{
	while (Rva008D29D0Head) {
		Rva008D29D0Node* next = Rva008D29D0Head->m_next;
		Rva008D29D0Head->shutdown();
		delete Rva008D29D0Head;
		Rva008D29D0Head = next;
	}
}
