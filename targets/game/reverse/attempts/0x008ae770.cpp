// ?aptInvokeThree@@YAPAVAptValue@@PAXH@Z
// partial score=0.85 date=2026-09-06
// 75/75 B, 17 diff bytes: retail loads arr[n-1] between the argc compare and its branch and keeps it in edi with the optional third arg in esi; ours swaps the two callee-saved registers (a,c,b order) or loads before the compare (a,b,c order).
// cl: /DNDEBUG /MD /EHsc
class AptValue { public: int toInteger() const; };
struct Rva008AE770Stack { void invoke(void* a, int b, void* c, AptValue* d, int e, void* f); };
extern Rva008AE770Stack Rva008AE770TheStack;
extern AptValue** g_bfmeArr1233;
extern AptValue* g_bfmeFallbackDB;
AptValue* aptInvokeThree(void* self, int argc)
{
	AptValue** arr = g_bfmeArr1233;
	int n = *(int*)&Rva008AE770TheStack;
	AptValue* a = arr[n - 2];
	AptValue* c = argc >= 3 ? arr[n - 3] : 0;
	AptValue* b = arr[n - 1];
	Rva008AE770TheStack.invoke(self, 0, self, b, a->toInteger() + 0x4000, c);
	return g_bfmeFallbackDB;
}
