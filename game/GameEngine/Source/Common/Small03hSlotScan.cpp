// cl: /DNDEBUG /MD /G6 /EHsc
//
// Retail 0x0092F5C0 is a linear slot scan over the pointer table at
// this+0x34: it keys on the handle word, walks at most m_count entries and
// returns the matching index, or -1. Neighbours: matinfo.cpp
// Peek/Find_Vertex_Material, meshmdl.cpp. IDENTITY IS NOT RECOVERED: the
// owner keeps its address token. The do/while shared-tail spelling is what
// emits retail's push-esi-second + jl-loop form.
class Rva0092F5C0Box
{
public:
	int findSlot(void *handle);
	int m_pad[13];
	void **m_table;
	int m_pad2[2];
	int m_count;
};
int Rva0092F5C0Box::findSlot(void *handle)
{
	int n = m_count;
	int i = 0;
	void *key;
	void **table;
	if (n > 0)
	{
		key = *(void **)handle;
		table = m_table;
		do
		{
			if (*table == key)
				return i;
			++i;
			++table;
		} while (i < n);
	}
	return -1;
}
