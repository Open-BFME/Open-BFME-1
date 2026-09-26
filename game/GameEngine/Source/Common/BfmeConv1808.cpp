struct BfmeBlockTP
{
	int m_bfmeATP;
	int m_bfmeBTP;
	int m_bfmeCTP;
	int m_bfmeDTP;
};

void __cdecl bfmeSendTP(void *first, BfmeBlockTP *second, BfmeBlockTP *third, BfmeBlockTP block, void *fifth, int sixth);

void __cdecl bfmeCallTP(void *first, BfmeBlockTP *second, void *third, void *fourth)
{
	BfmeBlockTP *adjusted = (BfmeBlockTP *)((char *)second - 0x10);

	bfmeSendTP(first, adjusted, adjusted, *adjusted, fourth, 0);
}
