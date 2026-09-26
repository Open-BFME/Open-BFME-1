// cl: /O2
// Open-BFME: ParticleInfo scalar-deleting destructor wrapper, retail
// 0x005CF020 (30 bytes). Its vtable at 0x0110FE78 routes slot 0 here
// through ILT 0x004446F2; slot 2 returns "FXParticleInfo".

class ParticleInfo
{
public:
    __declspec(noinline) virtual ~ParticleInfo();
};

ParticleInfo::~ParticleInfo()
{
}
