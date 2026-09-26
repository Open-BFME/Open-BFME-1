// ?loadPostProcess@ParticleSystem@@MAEXXZ
// ParticleSystem::loadPostProcess, retail 0x005C5100 (329 bytes): slot 1 of
// ParticleSystem's vftable 0x0110FE48, BFME's Snapshot loadPostProcess slot.
// Zero Hour's body: reconnect the slave, then the master, system from their
// saved IDs, throwing if a pointer is already set or the lookup fails.
// cl: /DNDEBUG /MD /O2 /EHs-c-

struct BfmeFormattedText
{
	void *text;
	int tag;
};

extern "C" BfmeFormattedText *__cdecl bfmeFormatText(
	BfmeFormattedText *result, int tag, const char *format, ...);
__declspec(noreturn) void __stdcall _CxxThrowException(
	void *object, void *throwInfo);
extern int g_rva005c5100ThrowInfo;

enum ParticleSystemID
{
	PARTICLE_SYSTEM_ID_NONE = 0
};

class ParticleSystem;

ParticleSystem *Make00001B18();

class ParticleSystemHandle
{
public:
	ParticleSystemHandle &operator=(const ParticleSystemHandle &other);
	operator bool() const { return m_ptr != 0; }
	ParticleSystem *operator->() const
	{
		if (m_ptr == 0)
			return Make00001B18();
		return m_ptr;
	}

	ParticleSystem *m_ptr;
	unsigned char m_pad[0x08];
};

class BfmeParticleSystemHandle : public ParticleSystemHandle
{
public:
	~BfmeParticleSystemHandle();
};

class ParticleSystemManager
{
	friend class ParticleSystem;

	private:
	BfmeParticleSystemHandle findParticleSystemByID(ParticleSystemID id);
};

extern ParticleSystemManager *TheParticleSystemManager;

class ParticleSystem
{
protected:
	virtual void loadPostProcess(void);

private:
	unsigned char m_pad4[0x160 - 0x04];
	ParticleSystemHandle m_slaveSystem;
	ParticleSystemID m_slaveSystemID;
	ParticleSystemHandle m_masterSystem;
	ParticleSystemID m_masterSystemID;
	unsigned char m_pad180[0x1A8 - 0x180];

public:
	unsigned char m_isDestroyed;
};

// ?loadPostProcess@ParticleSystem@@MAEXXZ
void ParticleSystem::loadPostProcess(void)
{
	if (m_slaveSystemID)
	{
		if (m_slaveSystem.m_ptr != 0)
		{
			BfmeFormattedText error;
			bfmeFormatText(&error, 5, 0);
			_CxxThrowException(&error, &g_rva005c5100ThrowInfo);
		}

		m_slaveSystem = TheParticleSystemManager->findParticleSystemByID(m_slaveSystemID);

		if (m_slaveSystem.m_ptr == 0 || m_slaveSystem->m_isDestroyed == 1)
		{
			BfmeFormattedText error;
			bfmeFormatText(&error, 5, 0);
			_CxxThrowException(&error, &g_rva005c5100ThrowInfo);
		}
	}

	if (m_masterSystemID)
	{
		if (m_masterSystem.m_ptr != 0)
		{
			BfmeFormattedText error;
			bfmeFormatText(&error, 5, 0);
			_CxxThrowException(&error, &g_rva005c5100ThrowInfo);
		}

		m_masterSystem = TheParticleSystemManager->findParticleSystemByID(m_masterSystemID);

		if (m_masterSystem.m_ptr == 0 || m_masterSystem->m_isDestroyed == 1)
		{
			BfmeFormattedText error;
			bfmeFormatText(&error, 5, 0);
			_CxxThrowException(&error, &g_rva005c5100ThrowInfo);
		}
	}
}
