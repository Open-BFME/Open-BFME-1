// ??0ParticleSystem@@QAE@PBVParticleSystemTemplate@@W4ParticleSystemID@@_N@Z
// partial score=0.32 date=2026-09-10
// Candidate reconstruction for ??0ParticleSystem@@QAE@PBVParticleSystemTemplate@@W4ParticleSystemID@@_N@Z.
// The retail body is 1426 bytes at 0x005CF850.  This TU deliberately keeps the
// BFME layout local: the global Generals ParticleSystemInfo declaration has a
// different base and caused the first reference-shaped experiment to drift.

typedef unsigned int UnsignedInt;
enum ParticleSystemID
{
	INVALID_PARTICLE_SYSTEM_ID = 0
};

namespace FXParticleSystem
{
class ParticleSystemInfo
{
public:
	ParticleSystemInfo();
	virtual ~ParticleSystemInfo();
	unsigned char m_tail[0x94];
};
}

template <typename T>
static inline T &particle_field(void *object, unsigned int offset)
{
	return *reinterpret_cast<T *>(reinterpret_cast<unsigned char *>(object) + offset);
}

template <typename T>
static inline const T &particle_field(const void *object, unsigned int offset)
{
	return *reinterpret_cast<const T *>(reinterpret_cast<const unsigned char *>(object) + offset);
}

template <typename T>
static inline void particle_copy(void *destination, unsigned int destinationOffset,
	const void *source, unsigned int sourceOffset)
{
	particle_field<T>(destination, destinationOffset) = particle_field<const T>(source, sourceOffset);
}

template <typename T>
class StringBase
{
public:
	void set(const StringBase<T> &that);
};

typedef StringBase<char> AsciiString;

class GameClientRandomVariable
{
public:
	float getValue() const;
};

class ParticleSystem;

// The +0xA0 object in the retail template is dispatched through its second
// virtual slot.  Its concrete BFME class is not proven in this TU, so keep the
// slot explicitly unnamed rather than assigning it a guessed callee name.
class ParticleTemplateSlotView
{
public:
	virtual void unusedSlot();
	virtual ParticleSystem *unknownSlot2(bool) const;
};

class ParticleSystemTemplate
{
public:
	virtual ~ParticleSystemTemplate();
	unsigned char m_fields[0xA0];
};

class ParticleSystemHandle
{
public:
	ParticleSystemHandle &operator=(const ParticleSystemHandle &that);
};

class GameClient
{
public:
	virtual UnsignedInt getFrame();
};

extern GameClient *TheGameClient;

class ParticleSystem : public FXParticleSystem::ParticleSystemInfo
{
public:
	ParticleSystem(const ParticleSystemTemplate *systemTemplate,
		ParticleSystemID id, bool createSlaves);
	virtual ~ParticleSystem();
	unsigned char m_fields[0x1E0 - 0x98];
};

ParticleSystem::ParticleSystem(const ParticleSystemTemplate *systemTemplate,
	ParticleSystemID id, bool createSlaves)
{
	unsigned int zero = 0;
	const unsigned int one = 1;
	const unsigned int unit = 0x3F800000;

	particle_field<void *>(this, 0x98) = 0;
	particle_field<void *>(this, 0x9C) = 0;
	particle_field<UnsignedInt>(this, 0xBC) = zero;
	particle_field<UnsignedInt>(this, 0x160) = zero;
	particle_field<UnsignedInt>(this, 0x164) = zero;
	particle_field<UnsignedInt>(this, 0x168) = zero;
	particle_field<UnsignedInt>(this, 0x170) = zero;
	particle_field<UnsignedInt>(this, 0x174) = zero;
	particle_field<UnsignedInt>(this, 0x178) = zero;
	particle_field<UnsignedInt>(this, 0x1B0) = zero;
	particle_field<UnsignedInt>(this, 0x1B4) = zero;
	particle_field<UnsignedInt>(this, 0x1B8) = zero;
	particle_field<UnsignedInt>(this, 0x1BC) = zero;
	particle_field<UnsignedInt>(this, 0x1C0) = zero;
	particle_field<UnsignedInt>(this, 0x1C4) = zero;
	particle_field<UnsignedInt>(this, 0x1C8) = zero;
	particle_field<UnsignedInt>(this, 0x1CC) = zero;
	particle_field<UnsignedInt>(this, 0x1D0) = zero;
	particle_field<UnsignedInt>(this, 0x1D4) = zero;
	particle_field<UnsignedInt>(this, 0x1D8) = zero;

	particle_field<UnsignedInt>(this, 0xAC) = static_cast<UnsignedInt>(id);
	particle_field<UnsignedInt>(this, 0xA4) = zero;
	particle_field<UnsignedInt>(this, 0xA0) = zero;
	particle_field<unsigned char>(this, 0x1A9) = 1;
	particle_field<UnsignedInt>(this, 0x19C) = reinterpret_cast<UnsignedInt>(systemTemplate);
	particle_field<UnsignedInt>(this, 0x154) = zero;
	particle_field<UnsignedInt>(this, 0x158) = zero;
	particle_field<UnsignedInt>(this, 0x15C) = zero;
	particle_field<UnsignedInt>(this, 0x148) = zero;
	particle_field<UnsignedInt>(this, 0x14C) = zero;
	particle_field<UnsignedInt>(this, 0x150) = zero;
	particle_field<UnsignedInt>(this, 0x134) = zero;
	particle_field<UnsignedInt>(this, 0x138) = zero;
	particle_field<UnsignedInt>(this, 0x13C) = zero;
	particle_field<UnsignedInt>(this, 0xB4) = zero;
	particle_field<UnsignedInt>(this, 0xB8) = zero;

	particle_field<unsigned char>(this, 0x1A4) = 1;
	particle_field<UnsignedInt>(this, 0xC4) = zero;
	particle_field<UnsignedInt>(this, 0xC8) = zero;
	particle_field<UnsignedInt>(this, 0xCC) = zero;
	particle_field<UnsignedInt>(this, 0xC0) = unit;
	particle_field<UnsignedInt>(this, 0xD0) = zero;
	particle_field<UnsignedInt>(this, 0xD4) = unit;
	particle_field<UnsignedInt>(this, 0xD8) = zero;
	particle_field<UnsignedInt>(this, 0xDC) = zero;
	particle_field<UnsignedInt>(this, 0xE0) = zero;
	particle_field<UnsignedInt>(this, 0xE4) = zero;
	particle_field<UnsignedInt>(this, 0xE8) = unit;
	particle_field<UnsignedInt>(this, 0xEC) = zero;
	particle_field<unsigned char>(this, 0x1A5) = 1;
	particle_field<UnsignedInt>(this, 0xF0) = unit;
	particle_field<UnsignedInt>(this, 0xF4) = zero;
	particle_field<UnsignedInt>(this, 0xF8) = zero;
	particle_field<UnsignedInt>(this, 0xFC) = zero;
	particle_field<UnsignedInt>(this, 0x100) = zero;
	particle_field<UnsignedInt>(this, 0x104) = unit;
	particle_field<UnsignedInt>(this, 0x108) = zero;
	particle_field<UnsignedInt>(this, 0x10C) = zero;
	particle_field<UnsignedInt>(this, 0x110) = 4;
	particle_field<UnsignedInt>(this, 0x114) = zero;
	particle_field<UnsignedInt>(this, 0x118) = unit;
	particle_field<UnsignedInt>(this, 0x11C) = zero;
	particle_field<unsigned char>(this, 0x1A7) = 0;
	particle_field<unsigned char>(this, 0x1A8) = 0;
	particle_field<unsigned char>(this, 0x1AA) = 1;
	particle_field<unsigned char>(this, 0x1AB) = 0;

	particle_copy<unsigned int>(this, 0x6C, systemTemplate, 0x6C);
	particle_field<UnsignedInt>(this, 0x134) = unit;
	particle_field<UnsignedInt>(this, 0x138) = unit;
	particle_field<UnsignedInt>(this, 0x13C) = unit;
	particle_field<UnsignedInt>(this, 0x140) = unit;
	particle_field<UnsignedInt>(this, 0x144) = unit;
	particle_field<UnsignedInt>(this, 0x180) = unit;
	particle_field<UnsignedInt>(this, 0x188) = unit;
	particle_field<UnsignedInt>(this, 0x40) = zero;
	particle_field<UnsignedInt>(this, 0x18C) = zero;
	particle_field<UnsignedInt>(this, 0x190) = zero;
	particle_field<UnsignedInt>(this, 0x194) = zero;
	particle_field<UnsignedInt>(this, 0x198) = zero;

	particle_copy<unsigned int>(this, 0x14, systemTemplate, 0x14);
	particle_copy<unsigned int>(this, 0x28, systemTemplate, 0x28);
	particle_copy<unsigned int>(this, 0x34, systemTemplate, 0x34);
	particle_copy<unsigned int>(this, 0x44, systemTemplate, 0x44);
	particle_field<UnsignedInt>(this, 0x120) = zero;
	particle_copy<unsigned int>(this, 0x50, systemTemplate, 0x50);
	particle_field<unsigned char>(this, 0x1A6) =
		particle_field<const unsigned char>(systemTemplate, 0x20) == 0;
	particle_copy<unsigned int>(this, 0x24, systemTemplate, 0x24);
	particle_field<UnsignedInt>(this, 0x184) = zero;
	particle_copy<unsigned int>(this, 0x7C, systemTemplate, 0x7C);
	particle_copy<unsigned int>(this, 0x80, systemTemplate, 0x80);
	particle_copy<unsigned int>(this, 0x84, systemTemplate, 0x84);
	particle_copy<unsigned int>(this, 0x88, systemTemplate, 0x88);
	particle_copy<unsigned int>(this, 0x8C, systemTemplate, 0x8C);
	particle_copy<unsigned int>(this, 0x90, systemTemplate, 0x90);
	particle_copy<unsigned int>(this, 0x94, systemTemplate, 0x94);
	particle_field<unsigned char>(this, 0x04) = particle_field<const unsigned char>(systemTemplate, 0x04);

	particle_field<UnsignedInt>(this, 0x124) = static_cast<UnsignedInt>(
		particle_field<const GameClientRandomVariable>(systemTemplate, 0x5C).getValue());
	particle_field<UnsignedInt>(this, 0x128) = TheGameClient->getFrame();
	particle_copy<unsigned int>(this, 0x12C, systemTemplate, 0x20);
	particle_copy<unsigned int>(this, 0x24, systemTemplate, 0x24);
	particle_field<UnsignedInt>(this, 0x1A0) = zero;
	particle_field<unsigned char>(this, 0x1AC) = 0;

	if (createSlaves)
	{
		ParticleSystem *slave = reinterpret_cast<ParticleTemplateSlotView *>(
			particle_field<void *>(systemTemplate, 0xA0))->unknownSlot2(true);
		particle_field<ParticleSystemHandle>(this, 0x160) =
			particle_field<const ParticleSystemHandle>(slave, 0x160);
		particle_field<UnsignedInt>(this, 0x16C) = slave
			? particle_field<const UnsignedInt>(slave, 0xAC) : 0;
	}

	particle_field<UnsignedInt>(this, 0xA8) = zero;
	particle_field<UnsignedInt>(this, 0xB0) = zero;
	particle_field<UnsignedInt>(this, 0x130) = zero;
	particle_field<UnsignedInt>(this, 0x1A0) = zero;
	particle_field<unsigned char>(this, 0x1AC) = 0;
	particle_copy<unsigned int>(this, 0x78, systemTemplate, 0x78);
	particle_copy<unsigned int>(this, 0x84, systemTemplate, 0x84);
	particle_field<ParticleSystemHandle>(this, 0x9C) =
		particle_field<const ParticleSystemHandle>(this, 0x9C);
	particle_field<UnsignedInt>(this, 0x1B0) = 0;
	particle_field<UnsignedInt>(this, 0x1B4) = 0;
	particle_field<UnsignedInt>(this, 0x1B8) = 0;
	particle_field<UnsignedInt>(this, 0x1BC) = 0;
	particle_field<UnsignedInt>(this, 0x1C0) = 0;
	particle_field<UnsignedInt>(this, 0x1C4) = 0;
	particle_field<UnsignedInt>(this, 0x1C8) = 0;
	particle_field<UnsignedInt>(this, 0x1CC) = 0;
	particle_field<UnsignedInt>(this, 0x1D0) = 0;
	particle_field<UnsignedInt>(this, 0x1D4) = 0;
	particle_field<UnsignedInt>(this, 0x1D8) = 0;
}
