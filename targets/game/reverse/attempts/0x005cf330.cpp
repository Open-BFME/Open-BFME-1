// ??0Particle@@QAE@ABVBfmeParticleSystemHandle@@PBVParticleInfo@@@Z
// partial score=0.55 date=2026-09-10
// ??0Particle@@QAE@ABVBfmeParticleSystemHandle@@PBVParticleInfo@@@Z
// New BFME reconstruction probe, retail RVA 0x005CF330 (1044 bytes).
// The direct caller is ParticleSystem::createParticle at 0x005D0040 via ILT
// 0x0001485D; Particle's vtable is 0x0110FE8C.  This TU uses the proven
// BFME handle, asset lookup, render-scene and debug-manager ownership views.
// stlport

#define _STLP_USE_STATIC_LIB
#define _STLP_NO_EXCEPTIONS 1
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>

typedef unsigned int UnsignedInt;
typedef unsigned char Byte;

class ParticleSystem;
class ParticleInfo;
class Particle;

struct Rva001408C0Target;
typedef Rva001408C0Target *Rva001408C0Key;
typedef _STL::set<Rva001408C0Key, _STL::less<Rva001408C0Key>,
	_STL::allocator<Rva001408C0Key> > Rva001408C0Set;

// Matched BFME asset lookup at retail 0x009EC0B0.
extern void *bfmeGoEMEb(void *name);
// This guarded forwarder is a matched body at retail 0x009EBAC0.
extern void Rva009EBAC0(int value);

template <typename T>
class StringBase
{
public:
	void removeLastChar();
	~StringBase();
	void *m_data;

	const char *str() const
	{
		return m_data ? reinterpret_cast<const char *>(m_data) + 8 :
			reinterpret_cast<const char *>(0x0107388B);
	}
};

class RenderObjClass;
class RTS3DScene
{
public:
	virtual void slot00();
	virtual void Add_Render_Object(RenderObjClass *object);
};

class W3DDisplay
{
public:
	static RTS3DScene *m_3DScene;
};

class BfmeDebugReport
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08();
	virtual void slot0C(); virtual void slot10(); virtual void slot14();
	virtual void slot18(); virtual void slot1C(); virtual void slot20();
	virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34(); virtual void addMessage(const char *);
	virtual void slot3C(); virtual void slot40(); virtual void slot44();
	virtual void slot48(); virtual void finish(UnsignedInt);
};

class Gen001336E5C
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08();
	virtual void slot0C(); virtual void slot10(); virtual void slot14();
	virtual void slot18(); virtual void slot1C(); virtual void slot20();
	virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34(); virtual void slot38();
	virtual void slot3C(); virtual void slot40(); virtual void slot44();
	virtual void slot48(); virtual void slot4C(); virtual void slot50();
	virtual void slot54(); virtual void slot58(); virtual void slot5C();
	virtual void beginReport(); virtual void slot64(); virtual void slot68();
	virtual BfmeDebugReport *startReport(void *, void *);
};

extern Gen001336E5C *TheGen001336E5C;

// VC7.1 reserves __thiscall in free-function-pointer typedefs; __fastcall
// gives the same ECX receiver for this vtable slot.
typedef void (__fastcall *RenderObjectSlot190)(RenderObjClass *, UnsignedInt);

static inline void call_render_slot_190(RenderObjClass *object)
{
	void **vtable = *reinterpret_cast<void ***>(object);
	((RenderObjectSlot190)vtable[0x190 / 4])(object, 1);
}

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

extern bool _bfme_debugReportingEnabled();
extern void _bfme_debugRecordCallsite(int kind);
extern RenderObjClass *Create_Render_Obj(const char *name);

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
	virtual UnsignedInt createRenderState();
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
	UnsignedInt id = particle_field<UnsignedInt>(system, 0x130);
	particle_field<UnsignedInt>(system, 0x130) = id + 1;
	particle_field<UnsignedInt>(particle, 0x58) = id;
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

	StringBase<char> asset_name;
	Rva001408C0Set asset_set;
	void *module_result = 0;
	UnsignedInt counter = 0;

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
		module->unknownQuerySlot(&asset_name);

		module_result = asset_name.m_data;
		if (module_result != 0 &&
			*reinterpret_cast<const unsigned short *>(
				reinterpret_cast<const Byte *>(module_result) + 4) != 0)
		{
			counter = 4;
			while (counter != 0)
			{
				asset_name.removeLastChar();
				--counter;
			}

			Rva001408C0Target *prototype =
				reinterpret_cast<Rva001408C0Target *>(
					bfmeGoEMEb(const_cast<char *>(asset_name.str())));
			if (asset_set.insert(prototype).second)
				Rva009EBAC0((int)&asset_name);

			RenderObjClass *render =
				reinterpret_cast<RenderObjClass *>(
					Create_Render_Obj(asset_name.str()));
			particle_field<void *>(this, 0x70) = render;
			particle_field<UnsignedInt>(this, 0x74) =
				module->createRenderState();

			if (render != 0)
			{
				call_render_slot_190(render);
				W3DDisplay::m_3DScene->Add_Render_Object(render);
			}
			else if (_bfme_debugReportingEnabled())
			{
				_bfme_debugRecordCallsite(1);
				TheGen001336E5C->beginReport();
				BfmeDebugReport *report =
					TheGen001336E5C->startReport(0, 0);
				report->addMessage(
					"Particle system: could not create render object named '");
				report->addMessage(asset_name.str());
				report->addMessage(
					"GameLODManager::getAudioLODIndex - Invalid LOD name '");
				report->finish(2);
			}
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
