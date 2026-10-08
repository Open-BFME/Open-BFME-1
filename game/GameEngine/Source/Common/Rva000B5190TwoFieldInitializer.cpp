// 0x010817AC is the BfmeBaseASCa vftable (pinned ??_7BfmeBaseASCa@@6B@ at RVA 0x00C817AC).
extern "C" const void *__identifier("??_7BfmeBaseASCa@@6B@")[];

struct Rva000B5190TwoFieldInitializer
{
	void *initialize( int unused );
};

void *Rva000B5190TwoFieldInitializer::initialize( int unused )
{
	(void)unused;
	*(unsigned *)this = (unsigned)__identifier("??_7BfmeBaseASCa@@6B@");
	*(unsigned *)((char *)this + 4) = 0;
	return this;
}
