class Gen007F0130
{
public:
	static void *operator new(unsigned int size);
};

class BfmeThingDGD : public Gen007F0130
{
public:
	BfmeThingDGD(void *a) throw();
	unsigned char m_bfmeBody[0x6e0];
};

BfmeThingDGD *bfmeGoDGD(void *a)
{
	return new BfmeThingDGD(a);
}
