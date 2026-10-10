#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

// Retail allocates 0xD0 bytes before calling the recorded copy constructor.
// This TU uses only the complete allocation extent; the native constructor
// owns all subobject initialization.
namespace FXParticleSystem
{
class ParticleSystemTemplate
{
public:
	ParticleSystemTemplate(const ParticleSystemTemplate &);
private:
	unsigned char m_bfmeBodyEAU[0xd0];
};
}

class BfmeStrEAU;
class BfmeThingEAU;

class ParticleSystemManager
{
public:
	void bfmeRegisterEAU(BfmeStrEAU *text, BfmeThingEAU *thing);
};

extern ParticleSystemManager *TheParticleSystemManager;

class BfmeHostEAU
{
public:
	virtual void bfmeSlot00EAU();
	virtual void bfmeSlot01EAU();
	virtual void bfmeSlot02EAU();
	virtual void bfmeSlot03EAU();
	virtual void bfmeSlot04EAU();
	virtual void bfmeSlot05EAU();
	virtual void bfmeSlot06EAU();
	virtual void bfmeResetEAU();

	void bfmeSpawnEAU(const char *name, void *param);
};

void BfmeHostEAU::bfmeSpawnEAU(const char *name, void *param)
{
	bfmeResetEAU();

	FXParticleSystem::ParticleSystemTemplate *thing =
		new FXParticleSystem::ParticleSystemTemplate(
			*reinterpret_cast<const FXParticleSystem::ParticleSystemTemplate *>(param));

	{
		AsciiString text(name);

		TheParticleSystemManager->bfmeRegisterEAU(reinterpret_cast<BfmeStrEAU *>(&text),
			reinterpret_cast<BfmeThingEAU *>(thing));
	}
}
