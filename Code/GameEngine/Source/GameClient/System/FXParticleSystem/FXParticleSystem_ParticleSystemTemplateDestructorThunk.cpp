// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: FXParticleSystem::ParticleSystemTemplate dtor.
// Early vtbl, BFMERetailAsciiString @+0x98, MemberA @+0xa0, base dtor.

// Retail destroys this member with a direct call to
// StringBase<char>::releaseBuffer (0x00887940) -- the member is a retail
// AsciiString, not the WWLib Buffer whose own destructor is the 40-byte
// body at 0x009E1E30, so name it the way the other lifted ModuleData
// destructors already do.
class BFMERetailAsciiString
{
public:
	~BFMERetailAsciiString() { releaseBuffer(); }

private:
	void releaseBuffer();
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
	BFMERetailAsciiString m_a; // +0x98
	unsigned char m_gap2[4];
	ParticleSystemTemplateMemberA m_b; // +0xa0
};

// ??1ParticleSystemTemplate@FXParticleSystem@@UAE@XZ
ParticleSystemTemplate::~ParticleSystemTemplate()
{
}

}
