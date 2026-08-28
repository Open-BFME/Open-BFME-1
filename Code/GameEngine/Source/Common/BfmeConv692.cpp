class BfmeThingDGF
{
public:
	BfmeThingDGF *bfmeInitDGF(void *a);
};

void *__cdecl bfmeAllocDGF(unsigned int size);

BfmeThingDGF *bfmeGoDGF(void *a)
{
	void *p = bfmeAllocDGF(0x30);
	if (p != 0)
		return ((BfmeThingDGF *)p)->bfmeInitDGF(a);
	return 0;
}
