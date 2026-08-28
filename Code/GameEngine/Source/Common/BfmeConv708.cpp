extern "C" unsigned char bfmeInfoDIE[];

class BfmeThingDIE
{
public:
	void bfmeOneDIE(void *p);
	void bfmeTwoDIE(void *info, int flag);
};

void *__stdcall bfmeAllocDIE(unsigned int size);

void bfmeGoDIE(void *spare, BfmeThingDIE *self)
{
	self->bfmeOneDIE(bfmeAllocDIE(8));
	self->bfmeTwoDIE(bfmeInfoDIE, 0);
}
