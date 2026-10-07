// Open-BFME5 conversions.

void *__cdecl operator new(unsigned int size);
void __cdecl operator delete(void *block);

class BfmeThingVTD
{
public:
	int m_bfme00;
};

// The object is built by the matched 9-byte vfptr ctor ??0Rva009C85B0@@QAE@XZ
// (0x009C85B0, TinyVfptrCtors.cpp), which the pin for this call names.
class Rva009C85B0
{
public:
	Rva009C85B0();
	int m_bfme00;
};

BfmeThingVTD *bfmeCreateVTD()
{
	return reinterpret_cast<BfmeThingVTD *>(new Rva009C85B0);
}
