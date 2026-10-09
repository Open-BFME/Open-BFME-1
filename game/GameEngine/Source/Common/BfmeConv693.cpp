class BfmeThingDGG;

class Gen007F0130
{
public:
	static void *operator new(unsigned int size);
};

class Rva007FA990 : public Gen007F0130
{
public:
	Rva007FA990(void *a) throw();
	unsigned char m_bfmeBody[0xd8];
};

BfmeThingDGG *bfmeGoDGG(void *a)
{
	return reinterpret_cast<BfmeThingDGG *>(new Rva007FA990(a));
}
