void **__stdcall bfmeMakeBFA(void *what);

void __stdcall bfmeGoBFA(void *one, void *two, void *three)
{
	void **got = bfmeMakeBFA(two);
	*got = three;
}
