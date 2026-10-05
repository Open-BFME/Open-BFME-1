// cl: /O2 /DNDEBUG /MD

extern int g_rva00891FA0Ready;
extern int g_rva00891FA0Value;
extern void (__cdecl *g_bfmeJ1017Fn)(void *, int);

class BfmeJ1017
{
public:
	void bfmeInsert(unsigned int packed);

private:
	char m_pad0[0x1238];
	int m_count;
	unsigned int *m_array;
	char m_pad1[0x68];
	int m_cap;
};

void BfmeJ1017::bfmeInsert(unsigned int packed)
{
	struct Tmp
	{
		int a;
		unsigned int b;
	} tmp;

	int count = m_count;
	if (count >= m_cap)
		return;
	if (count > 0)
	{
		if (m_array[count - 1] == packed)
			return;
	}
	m_array[count] = packed;
	m_count++;
	if (g_rva00891FA0Ready)
	{
		tmp.a = g_rva00891FA0Value;
		tmp.b = packed;
		g_bfmeJ1017Fn(&tmp, 8);
	}
}
