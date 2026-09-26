// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

class AsciiString;

class AsciiStringCopyCtorShim
{
public:
	void construct(const AsciiString *other);
};

#include "ascii_string.h"

namespace FXParticleSystem
{

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ParticleSys.h
class ParticleSystemInfo
{
public:
	ParticleSystemInfo(const ParticleSystemInfo &other);
	virtual ~ParticleSystemInfo();

private:
	unsigned char m_pad[0x94];
};

class ParticleSystemTemplateTail
{
public:
	ParticleSystemTemplateTail(const ParticleSystemTemplateTail &other);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ParticleSys.h
class ParticleSystemTemplate : public ParticleSystemInfo
{
public:
	ParticleSystemTemplate(const ParticleSystemTemplate &other);

private:
	AsciiString m_name;
	int m_slaveTemplate;
	ParticleSystemTemplateTail m_tail;
};

ParticleSystemTemplate::ParticleSystemTemplate(const ParticleSystemTemplate &other) :
	ParticleSystemInfo(other),
	m_name(other.m_name),
	m_slaveTemplate(0),
	m_tail(other.m_tail)
{
}

}
