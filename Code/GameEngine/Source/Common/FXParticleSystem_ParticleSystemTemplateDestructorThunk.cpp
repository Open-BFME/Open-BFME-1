// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: FXParticleSystem::ParticleSystemTemplate dtor.
// Early vtbl, Buffer @+0x98, MemberA @+0xa0, base dtor.

class Buffer
{
public:
	~Buffer();
private:
	unsigned char m_pad[4];
};

namespace FXParticleSystem
{

class ParticleSystemTemplateMemberA
{
public:
	~ParticleSystemTemplateMemberA();
private:
	unsigned char m_pad[4];
};

class ParticleSystemTemplateBase
{
public:
	virtual ~ParticleSystemTemplateBase();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ParticleSys.h
class ParticleSystemTemplate : public ParticleSystemTemplateBase
{
public:
	virtual ~ParticleSystemTemplate();
private:
	unsigned char m_gap[0x94];
	Buffer m_a; // +0x98
	unsigned char m_gap2[4];
	ParticleSystemTemplateMemberA m_b; // +0xa0
};

// ??1ParticleSystemTemplate@FXParticleSystem@@UAE@XZ
ParticleSystemTemplate::~ParticleSystemTemplate()
{
}

}
