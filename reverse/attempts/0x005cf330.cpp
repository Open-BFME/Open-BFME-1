// ??0Particle@@QAE@ABVBfmeParticleSystemHandle@@PBVParticleInfo@@@Z
// partial score=0.4 date=2026-09-10
// cl: /O2 /EHsc
// Open-BFME: Particle constructor, retail 0x005CF330 (1044 bytes).
//
// Identity is established independently of the generated placeholder: the
// named ParticleSystem::createParticle body at 0x005D0040 calls this through
// ILT 0x0001485D, and the constructor installs Particle's vtable
// 0x0110FE8C.  The handle ABI and the 0x4C handle member are shared with the
// matched Particle destructor and ParticleSystem handle list bodies.
//
// The retail BFME ParticleInfo layout is kept opaque here.  Its fields used by
// this constructor are documented offsets from the constructor's raw stores;
// this avoids importing the different Generals ParticleInfo declaration into a
// TU whose job is only this body.

typedef unsigned int UnsignedInt;
typedef unsigned char Byte;

class ParticleSystem;
class ParticleInfo;
class Particle;

template <typename T>
static inline T &particle_field(void *object, UnsignedInt offset)
{
	return *reinterpret_cast<T *>(reinterpret_cast<Byte *>(object) + offset);
}

template <typename T>
static inline const T &particle_field(const void *object, UnsignedInt offset)
{
	return *reinterpret_cast<const T *>(reinterpret_cast<const Byte *>(object) + offset);
}

class ParticleSystemHandle
{
public:
	ParticleSystemHandle &operator=(const ParticleSystemHandle &that) throw();

	ParticleSystem *m_system;
	ParticleSystemHandle *m_previous;
	ParticleSystemHandle *m_next;
};

class BfmeParticleSystemHandle : public ParticleSystemHandle
{
public:
	~BfmeParticleSystemHandle() throw();
};

class ParticleSystem
{
};

class ParticleSystemManager
{
};

class Rva005CE920
{
public:
	~Rva005CE920();
};

extern ParticleSystemManager *TheParticleSystemManager;
extern ParticleSystem *emptyParticleSystem();

// The constructor's frame read is through the global ClientRoot4120 vtable at
// slot +0x68.  The slot is known; its retail semantic name is not claimed here.
class ClientRoot4120
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot0A();
	virtual void slot0B();
	virtual void slot0C();
	virtual void slot0D();
	virtual void slot0E();
	virtual void slot0F();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual UnsignedInt unknownFrameSlot();
};

extern ClientRoot4120 *TheGameClient;

// The five ParticleInfo fields below are polymorphic random-value objects in
// the retail BFME ABI.  Only their slot +8 call is relied upon; no guessed
// concrete callee name is introduced.
class ParticleRandomValue
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual UnsignedInt unknownValueSlot(void *particle) const;
};

static inline UnsignedInt particle_random_value(const void *info,
	UnsignedInt info_offset, void *particle)
{
	ParticleRandomValue *value = particle_field<ParticleRandomValue *>(info, info_offset);
	return value ? value->unknownValueSlot(particle) : 0;
}

class ParticleSystemModule
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void unknownQuerySlot(void *result);
};

struct ParticleConstructorScratch
{
	void *module_result;
	UnsignedInt counter;
	Byte payload[0x1C];
};

static inline void add_to_system_list(ParticleSystem *system, void *particle)
{
	if (system == 0)
		return;

	if (particle_field<Byte>(particle, 0x79))
		return;

	void **head = reinterpret_cast<void **>(reinterpret_cast<Byte *>(system) + 0xA0);
	void *tail = particle_field<void *>(system, 0xA4);
	if (*head == 0)
		*head = particle;
	if (tail != 0)
	{
		particle_field<void *>(tail, 0x3C) = particle;
		particle_field<void *>(particle, 0x40) = tail;
	}
	else
	{
		particle_field<void *>(particle, 0x40) = 0;
	}

	particle_field<void *>(system, 0xA4) = particle;
	particle_field<void *>(particle, 0x3C) = 0;
	particle_field<Byte>(particle, 0x7A) = 1;
	++particle_field<UnsignedInt>(system, 0xA8);
}

static inline void add_to_overall_list(ParticleSystemManager *manager,
	ParticleSystem *system, void *particle)
{
	if (manager == 0 || system == 0 || particle_field<Byte>(particle, 0x7A))
		return;

	UnsignedInt priority = particle_field<UnsignedInt>(system, 0x7C);
	Byte *manager_bytes = reinterpret_cast<Byte *>(manager);
	void **head = reinterpret_cast<void **>(manager_bytes + 0x0C + priority * 4);
	void **tail = reinterpret_cast<void **>(manager_bytes + 0x44 + priority * 4);

	if (*head == 0)
		*head = particle;
	if (*tail != 0)
	{
		particle_field<void *>(*tail, 0x44) = particle;
		particle_field<void *>(particle, 0x48) = *tail;
	}
	else
	{
		particle_field<void *>(particle, 0x48) = 0;
	}
	*tail = particle;
	particle_field<void *>(particle, 0x44) = 0;
	particle_field<Byte>(particle, 0x7A) = 1;
	++particle_field<UnsignedInt>(manager, 0x84);
}

class Particle
{
public:
	Particle(const BfmeParticleSystemHandle &system, const ParticleInfo *info);

private:
	UnsignedInt m_vtable;
	Byte m_pad04[0x48];
	BfmeParticleSystemHandle m_system;
	Byte m_pad58[0x24];
	BfmeParticleSystemHandle m_destroySystem;
	UnsignedInt m_destroySystemID;
	Rva005CE920 m_tail;
};

Particle::Particle(const BfmeParticleSystemHandle &system, const ParticleInfo *info)
{
	UnsignedInt zero = 0;

	particle_field<UnsignedInt>(this, 0x00) = 0x0110FE8C;
	particle_field<UnsignedInt>(this, 0x04) = zero;
	particle_field<UnsignedInt>(this, 0x08) = zero;
	particle_field<UnsignedInt>(this, 0x0C) = zero;
	particle_field<UnsignedInt>(this, 0x28) = zero;
	particle_field<UnsignedInt>(this, 0x2C) = zero;
	particle_field<UnsignedInt>(this, 0x30) = zero;
	particle_field<UnsignedInt>(this, 0x1C) = zero;
	particle_field<UnsignedInt>(this, 0x20) = zero;
	particle_field<UnsignedInt>(this, 0x24) = zero;
	particle_field<UnsignedInt>(this, 0x10) = zero;
	particle_field<UnsignedInt>(this, 0x14) = zero;
	particle_field<UnsignedInt>(this, 0x18) = zero;
	particle_field<UnsignedInt>(this, 0x34) = zero;
	particle_field<Byte>(this, 0x38) = 0;

	m_system = system;

	particle_field<UnsignedInt>(this, 0x70) = zero;
	particle_field<UnsignedInt>(this, 0x74) = 1;
	particle_field<UnsignedInt>(this, 0x7C) = zero;
	particle_field<UnsignedInt>(this, 0x80) = zero;
	particle_field<UnsignedInt>(this, 0x84) = zero;
	particle_field<UnsignedInt>(this, 0x88) = zero;
	particle_field<UnsignedInt>(this, 0x8C) = zero;
	particle_field<UnsignedInt>(this, 0x90) = zero;
	particle_field<UnsignedInt>(this, 0x94) = zero;
	particle_field<UnsignedInt>(this, 0x98) = zero;
	particle_field<UnsignedInt>(this, 0xA4) = zero;
	particle_field<UnsignedInt>(this, 0xA8) = zero;
	particle_field<UnsignedInt>(this, 0xAC) = zero;
	particle_field<UnsignedInt>(this, 0xB0) = zero;

	particle_field<UnsignedInt>(this, 0x10) = particle_field<const UnsignedInt>(info, 0x10);
	particle_field<UnsignedInt>(this, 0x14) = particle_field<const UnsignedInt>(info, 0x14);
	particle_field<UnsignedInt>(this, 0x18) = particle_field<const UnsignedInt>(info, 0x18);
	particle_field<UnsignedInt>(this, 0x1C) = particle_field<const UnsignedInt>(info, 0x1C);
	particle_field<UnsignedInt>(this, 0x20) = particle_field<const UnsignedInt>(info, 0x20);
	particle_field<UnsignedInt>(this, 0x24) = particle_field<const UnsignedInt>(info, 0x24);
	particle_field<UnsignedInt>(this, 0x28) = particle_field<const UnsignedInt>(info, 0x28);
	particle_field<UnsignedInt>(this, 0x2C) = particle_field<const UnsignedInt>(info, 0x2C);
	particle_field<UnsignedInt>(this, 0x30) = particle_field<const UnsignedInt>(info, 0x30);
	particle_field<UnsignedInt>(this, 0x34) = particle_field<const UnsignedInt>(info, 0x34);
	particle_field<Byte>(this, 0x38) = particle_field<const Byte>(info, 0x38);

	particle_field<UnsignedInt>(this, 0x6C) =
		TheGameClient->unknownFrameSlot();
	particle_field<UnsignedInt>(this, 0x58) = zero;

	ParticleConstructorScratch scratch;
	scratch.module_result = 0;
	scratch.counter = 0;

	particle_field<Byte>(this, 0x7A) = 0;
	particle_field<Byte>(this, 0x79) = 0;
	particle_field<void *>(this, 0x44) = 0;
	particle_field<void *>(this, 0x48) = 0;
	particle_field<void *>(this, 0x3C) = 0;
	particle_field<void *>(this, 0x40) = 0;

	ParticleSystem *owner = system.m_system;
	if (owner == 0)
		owner = emptyParticleSystem();

	if (particle_field<UnsignedInt>(owner, 0x0C) == 2)
	{
		ParticleSystemModule *module = particle_field<ParticleSystemModule *>(owner, 0x1C8);
		if (module != 0)
			module->unknownQuerySlot(&scratch.module_result);

		if (scratch.module_result != 0 &&
			*reinterpret_cast<const unsigned short *>(
				reinterpret_cast<const Byte *>(scratch.module_result) + 4) != 0)
		{
			scratch.counter = 4;
			while (scratch.counter != 0)
				--scratch.counter;
		}
	}

	add_to_overall_list(TheParticleSystemManager, owner, this);
	add_to_system_list(owner, this);

	particle_field<UnsignedInt>(this, 0x8C) = particle_random_value(info, 0x3C, this);
	particle_field<UnsignedInt>(this, 0x90) = particle_random_value(info, 0x40, this);
	particle_field<UnsignedInt>(this, 0x94) = particle_random_value(info, 0x44, this);
	particle_field<UnsignedInt>(this, 0x98) = particle_random_value(info, 0x48, this);
	particle_field<UnsignedInt>(this, 0xA4) = particle_random_value(info, 0x54, this);
}
