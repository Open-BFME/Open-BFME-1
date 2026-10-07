struct BfmeHolderBZB
{
	void *m_bfmePtr;
};

void bfmeOneBZB(void *what);
// Retail 0x009A5E60 reaches the matched bfmeGo930C (0x009A58E0) through
// 0x009A5980, the matched Rva009A5980 tail stub (BfmeReleaseSetBZB.cpp); this
// TU-local forwarder keeps the caller spelling and names the stub.
void Rva009A5980(void *what);
static inline void bfmeGo930C(void *what)
{
	Rva009A5980(what);
}

void bfmeGoBZB(BfmeHolderBZB *holder)
{
	if (holder->m_bfmePtr != 0)
	{
		bfmeOneBZB(holder->m_bfmePtr);
		bfmeGo930C(holder->m_bfmePtr);
		holder->m_bfmePtr = 0;
	}
}
