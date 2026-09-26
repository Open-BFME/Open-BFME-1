void __cdecl bfmeRunBL(void *first, int flags, void *last);

void __cdecl bfmeSendBL(void *first, char second, char third, void *last)
{
	int flags = (second == 0) + 1;

	if (third)
		flags |= 8;
	else
		flags |= 4;

	bfmeRunBL(first, flags | 0x40, last);
}
