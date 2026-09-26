void bfmeCallDIA(void **item, void *value, void *arg);

void bfmeGoDIA(void **begin, void **end, void *spare, void *arg)
{
	while (begin != end)
	{
		bfmeCallDIA(begin, *begin, arg);
		++begin;
	}
}
