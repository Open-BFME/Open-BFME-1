// Pop N stack entries, releasing each unless it carries the mark.

class BfmeItemBB
{
public:
	virtual void retain(void);
	virtual void release(void);

	unsigned int m_bfmeFlags;				// +0x04
};

class BfmeStackBB
{
public:
	void bfmePopN(int count);

	int m_bfmeCount;					// +0x00
	int m_bfmeGap04;					// +0x04
	BfmeItemBB **m_bfmeArr;					// +0x08
};

// ?bfmePopN@BfmeStackBB@@QAEXH@Z
void BfmeStackBB::bfmePopN(int count)
{
	if (count <= 0)
		return;

	int index = 1;

	if (count >= index)
	{
		do
		{
			BfmeItemBB *item = m_bfmeArr[m_bfmeCount - index];
			unsigned char mark = (unsigned char)(item->m_bfmeFlags >> 30);

			if ((mark & 1) == 0)
				item->release();

			++index;
		} while (index <= count);
	}

	m_bfmeCount = m_bfmeCount - count;
}
