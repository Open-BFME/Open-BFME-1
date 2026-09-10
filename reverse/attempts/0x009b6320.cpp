// ?Rva009B6320DecodeTree@@YAXPAURva009B6320Node@@HPAHPAEHH@Z
// partial score=0.75 date=2026-09-09

struct Rva009B6320Node
{
	unsigned m_first;
	unsigned m_second;
	unsigned m_unused;
};

void Rva009B6320DecodeTree(
	Rva009B6320Node *nodes, int node, int *codes, unsigned char *lengths,
	int code, int depth)
{
	register int currentDepth = depth;
	register int currentNode = node;
	register int currentCode = code;
	register Rva009B6320Node *currentNodes = nodes;

	for (;;) {
		unsigned value = currentNodes[currentNode].m_first;
		if (value & 1) {
			unsigned symbol = (value >> 1) & 0x7f;
			codes[symbol] = currentCode + currentCode;
			lengths[symbol] = (unsigned char)(currentDepth + 1);
			return;
		}

		Rva009B6320DecodeTree(
			currentNodes, (value >> 1) & 0x7f, codes, lengths,
			currentCode + currentCode, currentDepth + 1);

		value = currentNodes[currentNode].m_second;
		if (value & 1) {
			unsigned symbol = (value >> 1) & 0x7f;
			codes[symbol] = currentCode + currentCode + 1;
			lengths[symbol] = (unsigned char)(currentDepth + 1);
			return;
		}

		++currentDepth;
		currentCode = currentCode + currentCode + 1;
		currentNode = (value >> 1) & 0x7f;
	}
}
