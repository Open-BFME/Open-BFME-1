// ?validateParticleSystems@Rva005C5100Owner@@QAEXXZ
// Open-BFME: validate the two saved particle-system handles at retail
// 0x005C5100 (329 bytes). The owner identity remains address-derived.
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

class ParticleSystem
{
public:
	unsigned char m_pad[0x1A8];
	unsigned char m_isDestroyed;
};

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

class Rva005C5100Owner;

class ParticleSystemManager
{
	friend class Rva005C5100Owner;

	private:
	BfmeParticleSystemHandle findParticleSystemByID(ParticleSystemID id);
};

extern ParticleSystemManager *TheParticleSystemManager;

class Rva005C5100Owner
{
public:
	void validateParticleSystems();

private:
	unsigned char m_pad0[0x160];
	ParticleSystemHandle m_slotA;
	ParticleSystemID m_slotAId;
	ParticleSystemHandle m_slotB;
	ParticleSystemID m_slotBId;
};

void Rva005C5100Owner::validateParticleSystems()
{
	if (m_slotAId)
	{
		if (m_slotA.m_ptr != 0)
		{
			BfmeFormattedText error;
			bfmeFormatText(&error, 5, 0);
			_CxxThrowException(&error, &g_rva005c5100ThrowInfo);
		}

		m_slotA = TheParticleSystemManager->findParticleSystemByID(m_slotAId);

		if (m_slotA.m_ptr == 0 || m_slotA->m_isDestroyed == 1)
		{
			BfmeFormattedText error;
			bfmeFormatText(&error, 5, 0);
			_CxxThrowException(&error, &g_rva005c5100ThrowInfo);
		}
	}

	if (m_slotBId)
	{
		if (m_slotB.m_ptr != 0)
		{
			BfmeFormattedText error;
			bfmeFormatText(&error, 5, 0);
			_CxxThrowException(&error, &g_rva005c5100ThrowInfo);
		}

		m_slotB = TheParticleSystemManager->findParticleSystemByID(m_slotBId);

		if (m_slotB.m_ptr == 0 || m_slotB->m_isDestroyed == 1)
		{
			BfmeFormattedText error;
			bfmeFormatText(&error, 5, 0);
			_CxxThrowException(&error, &g_rva005c5100ThrowInfo);
		}
	}
}
