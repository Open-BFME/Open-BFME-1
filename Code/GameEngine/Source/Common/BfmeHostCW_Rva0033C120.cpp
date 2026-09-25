// ?rva0033C120@BfmeHostCW@@QAEXPBD@Z
// Retail 0x0033C120 sits between BfmeHostCW::bfmeSpawnCW (0x0033C080) and the
// 0x0033C290 lookup. Same this as the 0x0033AFF0 clear it calls first (id +4
// and active flag +8): it looks the named particle template up through
// TheParticleSystemManager then creates a system and places it at (500 500)
// on the terrain height plus 50.

class BfmeStrERD
{
public:
	BfmeStrERD(const char *text);

	~BfmeStrERD() { releaseBuffer(); }

	void *m_bfmeDataERD;

private:
	void releaseBuffer();
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

class ParticleSystem
{
public:
	void setPosition(const Coord3D *pos);

	unsigned char m_pad00[0xac];
	unsigned int m_systemID;
	unsigned char m_padB0[0x1a6 - 0xb0];
	unsigned char m_flag1A6;
};

ParticleSystem *emptyParticleSystem();

class ParticleSystemTemplate;

class BfmeParticleSystemHandle
{
public:
	~BfmeParticleSystemHandle() throw();

	ParticleSystem *m_system;
	unsigned char m_tail[8];
};

class BfmeTmplERD;

class ParticleSystemManager
{
public:
	BfmeParticleSystemHandle createParticleSystem(const ParticleSystemTemplate *tmpl, bool createSlaves);
};

class BfmeMgrERD
{
public:
	BfmeTmplERD *bfmeFindERD(const BfmeStrERD &name);
};

extern ParticleSystemManager *TheParticleSystemManager;
extern BfmeMgrERD *g_bfmeMgrERD;

class BFMERetailTerrainHeightView
{
public:
	virtual void slot0() = 0;
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual void slot4() = 0;
	virtual void slot5() = 0;
	virtual float getGroundHeight(float x, float y, Coord3D *normal = 0) = 0;
};

struct Rva003FD060TerrainLogic;
extern Rva003FD060TerrainLogic *TheTerrainLogic;

class BfmeHostCW
{
public:
	void bfmeStartCW();
	void rva0033C120(const char *name);

	unsigned char m_pad00[4];
	unsigned int m_systemID;
	unsigned char m_active;
};

void BfmeHostCW::rva0033C120(const char *name)
{
	bfmeStartCW();

	const ParticleSystemTemplate *tmpl;

	{
		const BfmeStrERD &text = BfmeStrERD(name);

		tmpl = (const ParticleSystemTemplate *)g_bfmeMgrERD->bfmeFindERD(text);
	}

	if (tmpl != 0)
	{
		BfmeParticleSystemHandle handle = TheParticleSystemManager->createParticleSystem(tmpl, true);

		if (handle.m_system != 0)
		{
			m_systemID = handle.m_system->m_systemID;
			m_active = handle.m_system->m_flag1A6;

			Coord3D pos;
			pos.y = 500.0f;
			pos.x = 500.0f;
			pos.z = ((BFMERetailTerrainHeightView *)TheTerrainLogic)->getGroundHeight(500.0f, 500.0f) + 50.0f;

			ParticleSystem *system = handle.m_system;

			if (system == 0)
				system = emptyParticleSystem();

			system->setPosition(&pos);
		}
	}
}
