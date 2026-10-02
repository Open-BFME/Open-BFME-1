struct BfmeHolderBZB
{
	void *m_bfmePtr;
};

void bfmeOneBZB(void *what);
void bfmeGo930C(void *what);

void bfmeGoBZB(BfmeHolderBZB *holder)
{
	if (holder->m_bfmePtr != 0)
	{
		bfmeOneBZB(holder->m_bfmePtr);
		bfmeGo930C(holder->m_bfmePtr);
		holder->m_bfmePtr = 0;
	}
}
