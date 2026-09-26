struct Rva0029CC20PostIncrement
{
	int increment();
};

int Rva0029CC20PostIncrement::increment()
{
	int old = *(int *)((char *)this + 0x10);
	*(int *)((char *)this + 0x10) = old + 1;
	return old;
}
