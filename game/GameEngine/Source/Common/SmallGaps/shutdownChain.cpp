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
// The cell at 0x01338478 is defined once, by its canonical spelling, in
// game/GameEngine/Source/Common/Data/Rva01338478.cpp.  This TU's view of
// Rva008C3B60Node is local, but MSVC mangles only the pointee class name, so
// the spelling below is the same symbol retail's references bind to.
extern Rva008C3B60Node* g_rva01338478NodeHead;
void shutdownChain()
{
	while (g_rva01338478NodeHead) {
		Rva008C3B60Node* next = g_rva01338478NodeHead->m_next;
		g_rva01338478NodeHead->shutdown();
		delete g_rva01338478NodeHead;
		g_rva01338478NodeHead = next;
	}
}
