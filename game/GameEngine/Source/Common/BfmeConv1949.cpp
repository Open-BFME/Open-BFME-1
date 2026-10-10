#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

namespace FXParticleSystem
{
// Retail's allocation is 0xD0; initialization belongs to the native ctor.
class ParticleSystemTemplate
{
public:
	ParticleSystemTemplate(const ParticleSystemTemplate &);
private:
	unsigned char m_bfmeBodyERD[0xd0];
};
}

class ParticleSystemTemplate;
class BfmeSysERD;
class ParticleSystemManager
{
public:
	ParticleSystemTemplate *findTemplate(const AsciiString &) const;
};

extern ParticleSystemManager *TheParticleSystemManager;

BfmeSysERD * __stdcall bfmeMakeERD(const char *name)
{
	ParticleSystemTemplate *tmpl;
	{
		const AsciiString &text = AsciiString(name);
		tmpl = TheParticleSystemManager->findTemplate(text);
	}
	if (tmpl == 0)
		return 0;
	return reinterpret_cast<BfmeSysERD *>(
		new FXParticleSystem::ParticleSystemTemplate(
			*reinterpret_cast<const FXParticleSystem::ParticleSystemTemplate *>(tmpl)));
}
