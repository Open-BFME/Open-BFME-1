// ?validateParticleSystems@Rva005C5100Owner@@QAEXXZ
// partial score=0.95 date=2026-09-09
// cl: /DNDEBUG /MD /O2 /EHs-c-
// Open-BFME: convert d_005c5100, retail 0x005C5100 (329 bytes).
// The owning class remains address-derived. The two 16-byte records at +0x160
// and +0x170 hold a 12-byte particle-system handle followed by a saved ID.

#include <new>

struct BfmeFormattedText
{
	void *text;
	int tag;
};

extern "C" BfmeFormattedText *__cdecl bfmeFormatText(
	BfmeFormattedText *result, int tag, const char *format, ...);
__declspec(noreturn) void __stdcall _CxxThrowException(void *object, void *throwInfo);
extern int g_rva005c5100ThrowInfo;

enum ParticleSystemID { PARTICLE_SYSTEM_ID_NONE = 0 };

class ParticleSystem
{
public:
	unsigned char m_pad[0x1A8];
	unsigned char m_loaded;
};

extern "C" ParticleSystem *__cdecl Make00001B18();

class ParticleSystemHandle
{
public:
	ParticleSystemHandle &operator=(const ParticleSystemHandle &other);
	operator bool() const { return m_ptr != 0; }
	ParticleSystem *operator->() const
	{
		return m_ptr ? m_ptr : Make00001B18();
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
public:
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

		if (m_slotA.m_ptr == 0 || m_slotA->m_loaded != 1)
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

		if (m_slotB.m_ptr == 0 || m_slotB->m_loaded != 1)
		{
			BfmeFormattedText error;
			bfmeFormatText(&error, 5, 0);
			_CxxThrowException(&error, &g_rva005c5100ThrowInfo);
		}
	}
}
