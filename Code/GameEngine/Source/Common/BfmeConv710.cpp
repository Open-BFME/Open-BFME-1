extern "C" unsigned char bfmeInfoDIG[];

class BfmeThingDIG
{
public:
	void bfmeOneDIG(void *p);
	void bfmeTwoDIG(void *info, int flag);
};

void *__stdcall bfmeAllocDIG(unsigned int size);

void bfmeGoDIG(void *spare, BfmeThingDIG *self)
{
	self->bfmeOneDIG(bfmeAllocDIG(8));
	self->bfmeTwoDIG(bfmeInfoDIG, 0);
}
