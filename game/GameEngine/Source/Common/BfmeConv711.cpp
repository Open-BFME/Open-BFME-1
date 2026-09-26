extern "C" unsigned char bfmeInfoDIH[];

class BfmeThingDIH
{
public:
	void bfmeOneDIH(void *p);
	void bfmeTwoDIH(void *info, int flag);
};

void *__stdcall bfmeAllocDIH(unsigned int size);

void bfmeGoDIH(void *spare, BfmeThingDIH *self)
{
	self->bfmeOneDIH(bfmeAllocDIH(8));
	self->bfmeTwoDIH(bfmeInfoDIH, 0);
}
