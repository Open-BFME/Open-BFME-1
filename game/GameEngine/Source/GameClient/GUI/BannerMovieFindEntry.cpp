// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD

void *bfmeFindInRange(void *begin, void *end, int value, const int *key);

class BfmeRangeOwner
{
public:
	void *find(int value);

private:
	unsigned char m_pad00[0x30];
	void *m_begin;
	void *m_end;
};

// ?find@BfmeRangeOwner@@QAEPAXH@Z
void *BfmeRangeOwner::find(int value)
{
	void *rangeEnd = m_end;
	void *foundEntry = bfmeFindInRange(m_begin, rangeEnd, value, &value);
	return foundEntry == rangeEnd ? 0 : foundEntry;
}
