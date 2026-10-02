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
// The chain head at 0x013387D4 is retail's global ?g_rva008D2A80@@3PAVRva008D2A80@@A,
// defined by Rva008D2A80Link.cpp; only the pointer value crosses here.
class Rva008D2A80;
extern Rva008D2A80* g_rva008D2A80;
void shutdownChain008D2A40()
{
	while (g_rva008D2A80) {
		Rva008D2A40Node* next = ((Rva008D2A40Node*)g_rva008D2A80)->m_next;
		((Rva008D2A40Node*)g_rva008D2A80)->shutdown();
		delete (Rva008D2A40Node*)g_rva008D2A80;
		g_rva008D2A80 = (Rva008D2A80*)next;
	}
}
