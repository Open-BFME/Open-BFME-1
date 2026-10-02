// ?aptConsumeResolved008ACEA0@@YAPAVAptValue@@PAX@Z
// cl: /DNDEBUG /MD /EHsc
class AptValue;
// 0x008CCCE0 is the matched Apt value resolver (ledger:
// ?rva8CCCE0ResolveValue@@YAXPAX0PAVRva8CCCE0Value@@PAPAV1@@Z in
// Rva8CCCE0ResolveValue.cpp); it takes and returns its own value view.
class Rva8CCCE0Value;
void __cdecl rva8CCCE0ResolveValue(void* a, void* b, Rva8CCCE0Value* c, Rva8CCCE0Value** out);
class Rva8CD490Target { public: void consume(Rva8CCCE0Value* v); };
extern AptValue* g_bfmeFallbackDB;
struct Rva008ACEA0Holder { char m_pad[0x50]; char* m_owner; };
struct Rva008ACEA0Value {
	int m_0;
	union { unsigned int m_flags; struct { unsigned int m_type : 6; unsigned int m_bits : 9; unsigned int m_pooled : 1; }; };
	char m_pad[0x4c - 8];
	Rva008ACEA0Holder* m_holder;
};
AptValue* aptConsumeResolved008ACEA0(void* self)
{
	Rva8CCCE0Value* resolved = 0;
	rva8CCCE0ResolveValue(self, 0, (Rva8CCCE0Value*)self, &resolved);
	Rva008ACEA0Value* v = (Rva008ACEA0Value*)resolved;
	if (v) {
		int type = v->m_type;
		bool notPooled = !v->m_pooled;
		if (type >= 0xc && type <= 0x13 && !notPooled)
			((Rva8CD490Target*)(v->m_holder->m_owner + 0x24))->consume((Rva8CCCE0Value*)v);
	}
	return g_bfmeFallbackDB;
}
