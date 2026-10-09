class BfmeThingDGF;
class Rva007EAServiceList;

class Gen007F0130
{
public:
	static void *operator new(unsigned int size);
};

class BfmeThingTWA : public Gen007F0130
{
public:
	BfmeThingTWA(Rva007EAServiceList *a) throw();
	unsigned char m_bfmeBody[0x30];
};

BfmeThingDGF *bfmeGoDGF(void *a)
{
	return reinterpret_cast<BfmeThingDGF *>(new BfmeThingTWA(static_cast<Rva007EAServiceList *>(a)));
}
