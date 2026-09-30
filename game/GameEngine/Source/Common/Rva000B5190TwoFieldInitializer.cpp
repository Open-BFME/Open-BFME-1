extern "C" unsigned char bfmeVftASCa[];

struct Rva000B5190TwoFieldInitializer
{
	void *initialize( int unused );
};

void *Rva000B5190TwoFieldInitializer::initialize( int unused )
{
	(void)unused;
	*(unsigned *)this = (unsigned)bfmeVftASCa;
	*(unsigned *)((char *)this + 4) = 0;
	return this;
}
