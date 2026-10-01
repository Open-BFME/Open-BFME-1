struct Rva009B6420Context
{
	unsigned char m_pad00[0x18];
	int m_mode;
};

struct Rva009B6420Node
{
	unsigned int m_left;
	unsigned int m_right;
	unsigned char m_probability;
	unsigned char m_pad0A[3];
};

typedef char CheckRva009B6420NodeSize[(sizeof(Rva009B6420Node) == 12) ? 1 : -1];

struct Rva009AC4B0State;
struct Rva009AC2F0State;
extern void __cdecl Rva009AC4B0AddValue(Rva009AC4B0State *, int, int);
// Retail 0x009AC2F0 consumes three cdecl words and returns with RET.
extern void __cdecl Rva009AC2F0PackBits(Rva009AC2F0State *, int, int);

void __cdecl Rva009B6420(Rva009B6420Context *context,
	const Rva009B6420Node *nodes, int bits, int bitCount)
{
	unsigned int node = 0;
	int bitIndex = bitCount;
	--bitIndex;
	if (bitIndex < 0)
		return;
	do
	{
		int bit = (bits >> bitIndex) & 1;
		if (context->m_mode != 0)
			Rva009AC4B0AddValue((Rva009AC4B0State *)context, bit, nodes[node].m_probability);
		else
			Rva009AC2F0PackBits((Rva009AC2F0State *)context, bit, nodes[node].m_probability);

		if (bit)
			node = (nodes[node].m_right >> 1) & 0x7f;
		else
			node = (nodes[node].m_left >> 1) & 0x7f;
		--bitIndex;
	}
	while (bitIndex >= 0);
}
