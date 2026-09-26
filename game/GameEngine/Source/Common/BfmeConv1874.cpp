struct BfmeSmallZG
{
	int bfmeGoZG(void *a, void *b, int n);

	int m_bfmeSlotZG;
};

int __cdecl bfmeClampZG(void *first, int value, void *third, int limit, BfmeSmallZG obj)
{
	int n = value < limit ? value : limit;
	int r = obj.bfmeGoZG(first, third, n);

	if (r != 0)
		return r;

	return value - limit;
}
