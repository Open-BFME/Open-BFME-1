struct BfmeBlockTQ
{
	int m_bfmeATQ;
	int m_bfmeBTQ;
	int m_bfmeCTQ;
	int m_bfmeDTQ;
};

void __cdecl bfmeSendTQ(void *first, BfmeBlockTQ *second, BfmeBlockTQ *third, BfmeBlockTQ block, void *fifth, int sixth);

void __cdecl bfmeCallTQ(void *first, BfmeBlockTQ *second, void *third)
{
	BfmeBlockTQ *adjusted = (BfmeBlockTQ *)((char *)second - 0x10);

	bfmeSendTQ(first, adjusted, adjusted, *adjusted, third, 0);
}
