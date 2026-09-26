// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: ParticleSysBoneInfo scalar-deleting destructor at retail RVA
// 0x000A7900 (30 bytes). Its exact default constructor and the recovered
// vector<ParticleSysBoneInfo> copy, insertion, erase, clear, and destruction
// paths establish the value type. This wrapper calls the element destructor
// through ILT 0x0004A462 before conditionally invoking operator delete.

class ParticleSysBoneInfo
{
public:
	~ParticleSysBoneInfo();
};

void forceParticleSysBoneInfoDelete(ParticleSysBoneInfo *info)
{
	delete info;
}
