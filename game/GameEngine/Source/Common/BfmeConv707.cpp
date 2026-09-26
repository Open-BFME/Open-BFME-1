void bfmeCallDID(void **item, void *value, void *arg);

void bfmeGoDID(void **begin, void **end, void *arg)
{
	while (begin != end)
	{
		bfmeCallDID(begin, *begin, arg);
		++begin;
	}
}
