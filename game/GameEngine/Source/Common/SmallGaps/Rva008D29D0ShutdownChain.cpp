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
// The chain head at 0x013387D0 is the defining Rva008D2A10 list (see
// Rva008D2A10Link.cpp); spell the reference with its defining type so it
// resolves to ?g_rva008D2A10@@3PAVRva008D2A10@@A.
class Rva008D2A10;
extern Rva008D2A10* g_rva008D2A10;
void shutdownChain008D29D0()
{
	while (g_rva008D2A10) {
		Rva008D29D0Node* next = ((Rva008D29D0Node*)g_rva008D2A10)->m_next;
		((Rva008D29D0Node*)g_rva008D2A10)->shutdown();
		delete (Rva008D29D0Node*)g_rva008D2A10;
		g_rva008D2A10 = (Rva008D2A10*)next;
	}
}
