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
	void *end = m_end;
	void *result = bfmeFindInRange(m_begin, end, value, &value);
	return result == end ? 0 : result;
}
