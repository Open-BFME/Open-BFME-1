// ?bfmeCopyBE@@YAPAUBfmeElemBE@@PBU1@0PAU1@ABUBfmeFalseBE@@@Z
// partial score=0.8 date=2026-09-11
// cl: /O2 /Ob0 /G6

struct BfmeTailBE
{
	char *m_p;
	void copyFrom(const BfmeTailBE *src);
};

struct BfmeElemBE
{
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
	BfmeTailBE m_1C;
	char m_20;
	char m_pad[3];
};

struct BfmeFalseBE
{
};

BfmeElemBE *bfmeCopyBE(const BfmeElemBE *first, const BfmeElemBE *last,
	BfmeElemBE *result, const BfmeFalseBE &)
{
	BfmeElemBE *destination = result;
	if (first != last)
	{
		BfmeTailBE *destinationTail = &destination->m_1C;
		const BfmeTailBE *sourceTail = &first->m_1C;
		do
		{
			if (destination != 0)
			{
				destination->m_00 = first->m_00;
				destination->m_04 = first->m_04;
				destination->m_08 = first->m_08;
				destination->m_0C = first->m_0C;
				destination->m_10 = first->m_10;
				destination->m_14 = first->m_14;
				destination->m_18 = first->m_18;
				destinationTail->copyFrom(sourceTail);
				destination->m_20 = first->m_20;
			}
			++first;
			++destination;
			++sourceTail;
			++destinationTail;
		}
		while (first != last);
	}
	return destination;
}
