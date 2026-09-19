// ?aptPooledIndex@@YAPAVAptValue@@PAURva008AEA80Value@@H@Z
// cl: /DNDEBUG /MD /EHsc
class AptValue;
class AptInteger { public: static AptValue* Create(int value); };
extern AptValue* g_bfmeFallbackDB;
struct Rva008AEA80Value {
	int m_0;
	union { unsigned int m_flags; struct { unsigned int m_type : 6; unsigned int m_bits : 9; unsigned int m_pooled : 1; }; };
	int m_index;
};
AptValue* aptPooledIndex(Rva008AEA80Value* v, int argc)
{
	int type = v->m_type;
	bool notPooled = !v->m_pooled;
	if (type >= 0xc && type <= 0x13 && !notPooled)
		return AptInteger::Create(v->m_index - 0x4000);
	return g_bfmeFallbackDB;
}
