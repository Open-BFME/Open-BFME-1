void bfmeCallDIC(void **item, void *value, void *arg);

void bfmeGoDIC(void **begin, void **end, void *spare, void *arg)
{
	while (begin != end)
	{
		bfmeCallDIC(begin, *begin, arg);
		++begin;
	}
}
