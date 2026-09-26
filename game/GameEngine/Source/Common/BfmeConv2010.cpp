class BfmeStrEAU
{
public:
	BfmeStrEAU(const char *text);
	~BfmeStrEAU();

	void *m_bfmeDataEAU;
};

class BfmeThingEAU
{
public:
	BfmeThingEAU(void *param);

	unsigned char m_bfmeBodyEAU[0xd0];
};

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

	BfmeThingEAU *thing = new BfmeThingEAU(param);

	{
		BfmeStrEAU text(name);

		TheParticleSystemManager->bfmeRegisterEAU(&text, thing);
	}
}
