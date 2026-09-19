// ?aptPlay@@YAPAVAptValue@@PAURva008B5720Value@@@Z
// cl: /DNDEBUG /MD /EHsc
class AptValue;
extern AptValue* g_bfmeFallbackDB;
extern void (__cdecl* g_bfmePlay1282)(void* clip, int arg);
struct Rva008B5720Value {
	int m_0;
	union { unsigned int m_flags; struct { unsigned int m_type : 6; unsigned int m_bits : 9; unsigned int m_pooled : 1; }; };
	char m_pad[0x24 - 8];
	void* m_clip;
	int m_arg;
};
AptValue* aptPlay(Rva008B5720Value* v)
{
	bool notPooled = !v->m_pooled;
	if (v->m_type == 0x15 && !notPooled && v->m_clip)
		g_bfmePlay1282(v->m_clip, v->m_arg);
	return g_bfmeFallbackDB;
}
