// ?aptPlay@@YAPAVAptValue@@PAURva008B5720Value@@@Z
// cl: /DNDEBUG /MD /EHsc
class AptValue;
extern AptValue* g_bfmeFallbackDB;
// Callback cell at VA 0x01337884, defined once as g_bfmeSlot19VB in
// BfmeOneHundredTwentyThree.cpp (data_rows.csv); cast to this call's shape.
extern void (__cdecl* g_bfmeSlot19VB)();
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
		((void (__cdecl*)(void*, int))g_bfmeSlot19VB)(v->m_clip, v->m_arg);
	return g_bfmeFallbackDB;
}
