void bfmeCallDIB(void **item, void *value, void *arg);

void bfmeGoDIB(void **begin, void **end, void *arg)
{
	while (begin != end)
	{
		bfmeCallDIB(begin, *begin, arg);
		++begin;
	}
}
