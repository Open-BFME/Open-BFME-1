// cl: /O2
// Open-BFME: ParticleInfo::loadPostProcess, retail 0x005BD3F0 (1 byte).
// ParticleInfo vtable 0x0110FE78 slot 1 routes here through ILT 0x0040614F;
// the original ParticleSys.cpp and reference header declare this empty override.

class ParticleInfo
{
protected:
    virtual void loadPostProcess();
};

void ParticleInfo::loadPostProcess()
{
}
