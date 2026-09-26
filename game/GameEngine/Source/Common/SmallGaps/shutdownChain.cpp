// ?shutdownChain@@YAXXZ
struct Rva008C3B60Node {
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5();
	virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
	virtual void s12();
	virtual ~Rva008C3B60Node();
	virtual void s14();
	virtual void shutdown();
	int m_4; int m_8; Rva008C3B60Node* m_next;
};
extern Rva008C3B60Node* Rva008C3B60Head;
void shutdownChain()
{
	while (Rva008C3B60Head) {
		Rva008C3B60Node* next = Rva008C3B60Head->m_next;
		Rva008C3B60Head->shutdown();
		delete Rva008C3B60Head;
		Rva008C3B60Head = next;
	}
}
