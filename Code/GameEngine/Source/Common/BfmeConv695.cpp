class BfmeThingDGD
{
public:
	BfmeThingDGD *bfmeInitDGD(void *a);
};

void *__cdecl bfmeAllocDGD(unsigned int size);

BfmeThingDGD *bfmeGoDGD(void *a)
{
	void *p = bfmeAllocDGD(0x6e0);
	if (p != 0)
		return ((BfmeThingDGD *)p)->bfmeInitDGD(a);
	return 0;
}
