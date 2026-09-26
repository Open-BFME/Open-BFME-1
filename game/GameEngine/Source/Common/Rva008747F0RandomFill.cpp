// ?fillRandom008747F0@@YAXPAH@Z

extern int d_008790b0(int reset);
extern int bfmeRandomPositive(int range);

void __cdecl fillRandom008747F0(int *arr)
{
	d_008790b0(13);
	for (int outer = 0x65; outer; --outer)
	{
		for (int inner = 0x65; inner; --inner)
		{
			*arr = bfmeRandomPositive(0x4c4b40);
			++arr;
		}
	}
}
