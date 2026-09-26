class BfmeThingDGG
{
public:
	BfmeThingDGG *bfmeInitDGG(void *a);
};

void *__cdecl bfmeAllocDGG(unsigned int size);

BfmeThingDGG *bfmeGoDGG(void *a)
{
	void *p = bfmeAllocDGG(0xd8);
	if (p != 0)
		return ((BfmeThingDGG *)p)->bfmeInitDGG(a);
	return 0;
}
