void __stdcall bfmeDoBLB(void *one, char *two);

void *__stdcall bfmeGoBLB(void *one, char *two)
{
	bfmeDoBLB(one, two + 0x38);
	return one;
}
