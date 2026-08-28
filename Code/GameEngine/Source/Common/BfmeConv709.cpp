extern "C" unsigned char bfmeInfoDIF[];

class BfmeThingDIF
{
public:
	void bfmeOneDIF(void *p);
	void bfmeTwoDIF(void *info, int flag);
};

void *__stdcall bfmeAllocDIF(unsigned int size);

void bfmeGoDIF(void *spare, BfmeThingDIF *self)
{
	self->bfmeOneDIF(bfmeAllocDIF(8));
	self->bfmeTwoDIF(bfmeInfoDIF, 0);
}
