// ?shutdownChain2@@YAXXZ
struct Rva008D2960Node {
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5();
	virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
	virtual void s12();
	virtual ~Rva008D2960Node();
	virtual void s14();
	virtual void shutdown();
	int m_4; Rva008D2960Node* m_next;
};
// The chain head at 0x013387CC is the global this TU spells Rva008D2960Head;
// Rva008D29A0Link.cpp defines it as ?g_rva008D29A0, a Rva008D29A0*. Only the
// pointer value moves here, so the defining name is referenced by its own class
// name (forward declared, never defined in this TU).
class Rva008D29A0;
extern Rva008D29A0* g_rva008D29A0;
void shutdownChain2()
{
	while (g_rva008D29A0) {
		Rva008D2960Node* next = ((Rva008D2960Node*)g_rva008D29A0)->m_next;
		((Rva008D2960Node*)g_rva008D29A0)->shutdown();
		delete (Rva008D2960Node*)g_rva008D29A0;
		g_rva008D29A0 = (Rva008D29A0*)next;
	}
}
