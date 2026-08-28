struct BfmeHolderBZB
{
	void *m_bfmePtr;
};

void bfmeOneBZB(void *what);
void bfmeTwoBZB(void *what);

void bfmeGoBZB(BfmeHolderBZB *holder)
{
	if (holder->m_bfmePtr != 0)
	{
		bfmeOneBZB(holder->m_bfmePtr);
		bfmeTwoBZB(holder->m_bfmePtr);
		holder->m_bfmePtr = 0;
	}
}
