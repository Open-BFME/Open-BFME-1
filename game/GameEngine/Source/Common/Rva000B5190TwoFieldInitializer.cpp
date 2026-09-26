struct Rva000B5190TwoFieldInitializer
{
	void *initialize( int unused );
};

void *Rva000B5190TwoFieldInitializer::initialize( int unused )
{
	(void)unused;
	*(unsigned *)this = 0x010817AC;
	*(unsigned *)((char *)this + 4) = 0;
	return this;
}
