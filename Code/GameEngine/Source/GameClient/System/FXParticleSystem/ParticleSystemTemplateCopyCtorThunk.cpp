// cl: /DNDEBUG /MD /EHsc

class AsciiString;

class AsciiStringCopyCtorShim
{
public:
	void construct(const AsciiString *other);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString(const AsciiString &other)
	{
		const AsciiString *source = &other;
		((AsciiStringCopyCtorShim *)this)->construct(source);
	}
	~AsciiString();

private:
	char *m_data;
};

namespace FXParticleSystem
{

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ParticleSys.h
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ParticleSys.h
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
