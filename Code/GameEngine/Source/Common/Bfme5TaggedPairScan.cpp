struct BfmeTaggedRecord
{
	int m_bfmeValue;
	unsigned int m_bfmeTag;
	char m_bfmeFields[0x14];
};

struct BfmeTaggedPair
{
	BfmeTaggedPair(const BfmeTaggedPair &other)
	{
		m_bfmeRecords[0] = other.m_bfmeRecords[0];
		m_bfmeRecords[1] = other.m_bfmeRecords[1];
	}

	BfmeTaggedRecord *m_bfmeRecords[2];
};

// ?bfmeScanTaggedPair@@YA?AUBfmeTaggedPair@@PAUBfmeTaggedRecord@@0U1@@Z
BfmeTaggedPair bfmeScanTaggedPair(
	BfmeTaggedRecord *first,
	BfmeTaggedRecord *last,
	BfmeTaggedPair found)
{
	while (first != last)
	{
		if (first->m_bfmeTag < 2 && found.m_bfmeRecords[first->m_bfmeTag] == 0)
			found.m_bfmeRecords[first->m_bfmeTag] = first;

		++first;
	}

	return found;
}
