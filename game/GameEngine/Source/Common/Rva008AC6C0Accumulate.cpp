struct BfmeQ1206
{
	int m_bfme00;
	int m_bfme04;
	int m_bfme08;
	int m_bfme0c;
	int m_bfme10;
	int m_bfme14;
};

extern "C" BfmeQ1206 g_bfmeD1206;

struct BfmeM1208
{
	float m_bfme00, m_bfme04, m_bfme08, m_bfme0c, m_bfme10, m_bfme14;
};

void bfmeMul1208(const BfmeM1208 *a, const BfmeM1208 *b, BfmeM1208 *out);

class BfmeNode1206
{
public:
	void bfmeAccumulate1206(int *out0, int *out1);

private:
	char m_pad00[0x10];
	char m_node10;
	char m_pad11[0x4C - 0x11];
	BfmeNode1206 *m_next;
};

void BfmeNode1206::bfmeAccumulate1206(int *out0, int *out1)
{
	int v00 = g_bfmeD1206.m_bfme00;
	int v08 = g_bfmeD1206.m_bfme08;
	BfmeNode1206 *node = this;
	int v04 = g_bfmeD1206.m_bfme04;
	BfmeQ1206 local;
	local.m_bfme00 = v00;
	int v0c = g_bfmeD1206.m_bfme0c;
	local.m_bfme04 = v04;
	int v10 = g_bfmeD1206.m_bfme10;
	local.m_bfme08 = v08;
	int v14 = g_bfmeD1206.m_bfme14;
	local.m_bfme0c = v0c;
	local.m_bfme10 = v10;
	local.m_bfme14 = v14;

	while (node)
	{
		bfmeMul1208((BfmeM1208 *)&local, (BfmeM1208 *)&node->m_node10, (BfmeM1208 *)&local);
		node = node->m_next;
	}

	if (out0)
		*out0 = local.m_bfme10;
	if (out1)
		*out1 = local.m_bfme14;
}
