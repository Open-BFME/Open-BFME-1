// cl: /O2
// Open-BFME: FXParticleSystem::ParticleSystemInfo vector-deleting destructor,
// retail 0x0005F1A0 (87 bytes).  The class vtable at 0x01073878 routes
// through ILT 0x0043D140 to this wrapper.

void operator delete[](void *block);

namespace FXParticleSystem
{

class ParticleSystemInfo
{
public:
	__declspec(noinline) virtual ~ParticleSystemInfo();

private:
	unsigned char m_data[0x94];
};

ParticleSystemInfo::~ParticleSystemInfo()
{
}

// These helpers are not retail claims; they force MSVC 7.1 to materialize the
// compiler-generated vector-deleting destructor used by the retail vtable.
ParticleSystemInfo *MakeParticleSystemInfoArray(int count)
{
	return new ParticleSystemInfo[count];
}

void DeleteParticleSystemInfoArray(ParticleSystemInfo *array)
{
	delete[] array;
}

}
