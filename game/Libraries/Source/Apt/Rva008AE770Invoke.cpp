// cl: /DNDEBUG /DWIN32 /MD /EHsc
class AptValue
{
public:
    int toInteger() const;
};
struct Rva008AE770Stack
{
    int m_count;
    int m_rva0133874C;
    AptValue **m_rva01338750;
    // ?At@Rva008AE770Stack@@QAEPAVAptValue@@H@Z absent-from-retail
    AptValue *At(int offset) { return m_rva01338750[m_count - offset - 1]; }
    void invoke(void *a, int b, void *c, AptValue *d, int e, AptValue *f);
};
extern Rva008AE770Stack Rva008AE770TheStack;
extern AptValue* g_bfmeFallbackDB;
// Open BFME 2 Code/GameEngine/Source/Common/Rva006EC670Cluster.cpp.
AptValue* aptInvokeThree(void* self, int argc)
{
	Rva008AE770Stack &stack = Rva008AE770TheStack;
	AptValue **arr = stack.m_rva01338750;
	int n = stack.m_count;
	AptValue* b = stack.At(0);
	AptValue* a = stack.At(1);
	AptValue* c = argc >= 3 ? stack.At(2) : 0;
	int size = a->toInteger() + 0x4000;
	Rva008AE770TheStack.invoke(self, 0, self, b, size, c);
	return g_bfmeFallbackDB;
}
