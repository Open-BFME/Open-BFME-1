// Open-BFME5 conversions.

void *__cdecl operator new(unsigned int size);
void __cdecl operator delete(void *block);

class BfmeThingVTD
{
public:
	BfmeThingVTD();
	int m_bfme00;
};

BfmeThingVTD *bfmeCreateVTD()
{
	return new BfmeThingVTD;
}
