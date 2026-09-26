// ?j_0001bc70@BfmeThingCDA@@QAEXXZ
// partial score=0.21 date=2026-09-18
// cl: /MD /EHsc
//
// Retail 0x00597130 (1085 bytes): the BfmeThingCDA state refresh reached by
// the 0x0001BC70 ILT from Rva005976B0StateUpdate.cpp.  The caller and ILT
// prove the owner name; the fields below are only the offsets witnessed by
// this body and its already-matched CDA sibling.

typedef bool Bool;
typedef int Int;

template <typename T> class StringBase
{
public:
	StringBase() : m_data(0) {}
	StringBase(const T *text);
	StringBase(const StringBase &other);
	~StringBase();

	void *m_data;
};

class BFMERetailAsciiString : private StringBase<char>
{
public:
	BFMERetailAsciiString() : StringBase<char>() {}
	BFMERetailAsciiString(const char *text) : StringBase<char>(text) {}
	BFMERetailAsciiString(const BFMERetailAsciiString &other) : StringBase<char>(other) {}
	~BFMERetailAsciiString() { releaseBuffer(); }
	void releaseBuffer();
};

struct CdaEntry
{
	void *m_control;
	void *m_module;
	void *m_portrait;
	Int m_state;
	float m_scale;
	void *m_value;
	void *m_name;
	unsigned char m_active;
	unsigned char m_hasValue;
	unsigned char m_pad1e[2];
};

class BfmeThingCDA
{
public:
	void j_0001bc70();

	unsigned char m_flag;
	unsigned char m_ready;
	unsigned char m_pad02[2];
	void *m_value;
	unsigned char m_pad08[0x20];
	void *m_portrait;
	CdaEntry m_entries[6];
};

class CdaGameLogicCall
{
};

class CdaObjectCall
{
};

class CdaWindowManagerCall
{
};

class CdaNameKeyGeneratorCall
{
};

class CdaControlBarCall
{
};

class CdaPlayerCall
{
};

class CdaSubobjectCall
{
};

class CdaCleanupCall
{
};

extern void j_0003144e();
extern void j_0001f253();
extern void j_0001f3b6();
extern void j_0001681a();
extern void j_00047b31();
extern void j_0003add7();
extern void j_0002ae23();
extern void j_000361dd();
extern void j_00010e88();
extern void j_00012ac1();
extern void j_0003d942();
extern void j_000129d1();
extern void j_0001ff91();
extern void j_000179bd();
extern void j_0003a5b7();
extern void j_00023dda();
extern void j_000052b3();
extern void j_00016045();
extern void j_0001ed1c();
extern void j_00007eeb();
extern void j_0000ec5a();
extern void j_00047cc1();
extern void j_0001c341();
extern void j_00011400();
extern void j_0000aa2e();
extern void j_000474bf();

#define TheBfmeGameLogic (*(CdaGameLogicCall **)0x012F0898)
#define TheWindowManager (*(CdaWindowManagerCall **)0x012F19E8)
#define TheNameKeyGenerator (*(CdaNameKeyGeneratorCall **)0x012ED600)
#define TheControlBar (*(CdaControlBarCall **)0x012F33F8)
#define ThePlayers (*(CdaPlayerCall **)0x012ED748)
#define CdaNameKeyReadyByte (*(volatile unsigned char *)0x012F4C34)
#define CdaNameKeyReadyFlags (*(volatile Int *)0x012F4C34)
#define CdaAutoAbilityKey (*(Int *)0x012F4C30)
#define CdaFrameScale (*(const float *)0x01076C24)

static __forceinline void cdaInitialize(BfmeThingCDA *self)
{
	(void)self;
	j_0003144e();
}

static __forceinline CdaObjectCall *cdaFindObject(CdaGameLogicCall *logic, Int id)
{
	typedef void *(CdaGameLogicCall::*Call)(Int);
	union { void (*raw)(void); Call member; } fn;
	fn.raw = j_0001f253;
	return reinterpret_cast<CdaObjectCall *>((logic->*fn.member)(id));
}

static __forceinline void *cdaFindPortrait(BfmeThingCDA *self, CdaObjectCall *object)
{
	typedef void *(BfmeThingCDA::*Call)(CdaObjectCall *);
	union { void (*raw)(void); Call member; } fn;
	fn.raw = j_0001f3b6;
	return (self->*fn.member)(object);
}

static __forceinline void cdaInstallPortrait(CdaWindowManagerCall *manager,
	BFMERetailAsciiString &name, void *portrait)
{
	typedef void (CdaWindowManagerCall::*Call)(BFMERetailAsciiString &, void *);
	union { void (*raw)(void); Call member; } fn;
	fn.raw = j_0001681a;
	(manager->*fn.member)(name, portrait);
}

static __forceinline void cdaRemovePortrait(CdaWindowManagerCall *manager,
	BFMERetailAsciiString &name)
{
	typedef void (CdaWindowManagerCall::*Call)(BFMERetailAsciiString &);
	union { void (*raw)(void); Call member; } fn;
	fn.raw = j_00047b31;
	(manager->*fn.member)(name);
}

static __forceinline Int cdaNameToKey(CdaNameKeyGeneratorCall *generator,
	const char *name)
{
	typedef Int (CdaNameKeyGeneratorCall::*Call)(const char *);
	union { void (*raw)(void); Call member; } fn;
	fn.raw = j_0003add7;
	return (generator->*fn.member)(name);
}

static __forceinline void *cdaFindModule(CdaObjectCall *object, Int key)
{
	typedef void *(CdaObjectCall::*Call)(Int);
	union { void (*raw)(void); Call member; } fn;
	fn.raw = j_0002ae23;
	return (object->*fn.member)(key);
}

static __forceinline void cdaResetEntry(BfmeThingCDA *self, Int index)
{
	typedef void (BfmeThingCDA::*Call)(Int);
	union { void (*raw)(void); Call member; } fn;
	fn.raw = j_000361dd;
	(self->*fn.member)(index);
}

static __forceinline void *cdaFindControl(CdaControlBarCall *bar, void *control)
{
	typedef void *(CdaControlBarCall::*Call)(void *);
	union { void (*raw)(void); Call member; } fn;
	fn.raw = j_00010e88;
	return (bar->*fn.member)(control);
}

static __forceinline Bool cdaObjectActive(CdaObjectCall *object)
{
	typedef Bool (CdaObjectCall::*Call)();
	union { void (*raw)(void); Call member; } fn;
	fn.raw = j_0001ff91;
	return (object->*fn.member)();
}

static __forceinline Bool cdaPlayerActive(CdaPlayerCall *player)
{
	typedef Bool (CdaPlayerCall::*Call)();
	union { void (*raw)(void); Call member; } fn;
	fn.raw = j_000179bd;
	return (player->*fn.member)();
}

static __forceinline Bool cdaIsReady(BfmeThingCDA *self)
{
	typedef Bool (BfmeThingCDA::*Call)();
	union { void (*raw)(void); Call member; } fn;
	fn.raw = j_0003a5b7;
	return (self->*fn.member)();
}

static __forceinline Int cdaState(BfmeThingCDA *self)
{
	typedef Int (BfmeThingCDA::*Call)();
	union { void (*raw)(void); Call member; } fn;
	fn.raw = j_00023dda;
	return (self->*fn.member)();
}

static __forceinline Int cdaValue(BfmeThingCDA *self)
{
	return ((Int (__cdecl *)(void *))j_000052b3)(self);
}

static __forceinline void *cdaValueObject(BfmeThingCDA *self)
{
	return ((void * (__cdecl *)(void *))j_00016045)(self);
}

static __forceinline void cdaStateChanged(Int index, Int state)
{
	((void (__cdecl *)(Int, Int))j_0001ed1c)(index, state);
}

static __forceinline Bool cdaModuleReady(void *module)
{
	return ((Bool (__cdecl *)(void *))j_00007eeb)(module);
}

static __forceinline void cdaSetActive(Int index)
{
	((void (__cdecl *)(Int))j_0000ec5a)(index);
}

static __forceinline void cdaClearActive(Int index)
{
	((void (__cdecl *)(Int))j_00047cc1)(index);
}

static __forceinline void cdaSetModuleState(Int index, Bool state)
{
	((void (__cdecl *)(Int, Bool))j_0001c341)(index, state);
}

static __forceinline void *cdaGetValue(BfmeThingCDA *self)
{
	return ((void * (__cdecl *)(void *))j_00011400)(self);
}

static __forceinline void cdaUpdateName(Int index, BFMERetailAsciiString &name)
{
	((void (__cdecl *)(Int, BFMERetailAsciiString *))j_000129d1)(index, &name);
}

static __forceinline void cdaRefreshEntry(Int index, void *value)
{
	((void (__cdecl *)(Int, void *))j_00012ac1)(index, value);
}

static __forceinline void cdaInspect(void *control)
{
	((void (__cdecl *)(void *))j_0003d942)(control);
}

static __forceinline void cdaDestroyTail(BfmeThingCDA *self, void *value)
{
	typedef void (CdaSubobjectCall::*Call)(void *);
	union { void (*raw)(void); Call member; } fn;
	fn.raw = j_0000aa2e;
	(reinterpret_cast<CdaSubobjectCall *>((char *)self + 8)->*fn.member)(value);
}

static __forceinline void cdaDestroyAux(BfmeThingCDA *self, void *value)
{
	typedef void (CdaCleanupCall::*Call)(void *);
	union { void (*raw)(void); Call member; } fn;
	fn.raw = j_000474bf;
	(reinterpret_cast<CdaCleanupCall *>((char *)self + 0x1c)->*fn.member)(value);
}

// ?j_0001bc70@BfmeThingCDA@@QAEXXZ
void BfmeThingCDA::j_0001bc70()
{
	BfmeThingCDA *self = this;
	if (self->m_flag != 0)
	{
		if (self->m_ready == 0)
		{
			cdaInitialize(self);
			self->m_ready = 1;
		}
		if (self->m_ready != 0)
		{
			Int index = 0;
			CdaObjectCall *object = 0;
			if (self->m_value != 0)
			{
				object = cdaFindObject(TheBfmeGameLogic,
					(Int)(unsigned int)self->m_value);
			}

			if (self->m_value != 0)
			{
				void *portrait = cdaFindPortrait(self, object);
				if (portrait != self->m_portrait)
				{
					if (portrait != 0)
					{
						BFMERetailAsciiString name("CommandUI/Portrait");
						cdaInstallPortrait(TheWindowManager, name, portrait);
					}
					else if (self->m_portrait != 0)
					{
						BFMERetailAsciiString name("CommandUI/Portrait");
						cdaRemovePortrait(TheWindowManager, name);
					}
					self->m_portrait = portrait;
				}
			}

			void *objectModule = 0;
			if (object != 0)
			{
				if ((CdaNameKeyReadyByte & 1) == 0)
				{
					CdaNameKeyReadyFlags |= 1;
					CdaAutoAbilityKey = cdaNameToKey(TheNameKeyGenerator,
						"AutoAbilityBehavior");
				}
				objectModule = cdaFindModule((CdaObjectCall *)object,
					CdaAutoAbilityKey);
			}

			register Int controlOffset = 0x100;
			CdaEntry *entry = &self->m_entries[0];
			do
			{
				void *control = *(void **)((char *)TheControlBar + controlOffset);
				if (control == 0)
				{
					if (entry->m_control != 0)
						cdaResetEntry(self, index);
				}
				else if (entry->m_control == 0)
				{
					void *module = cdaFindControl(TheControlBar, control);
					if (module != 0 && *(unsigned char *)((char *)module + 0x14e) != 0)
					{
						entry->m_module = module;
						entry->m_control = control;
						cdaRefreshEntry(index, entry->m_name);
					}
				}

				if (entry->m_control != 0)
				{
					void *control = entry->m_control;
					cdaInspect(control);
					void *portrait = *(void **)((char *)control + 0x48);
					void *entryModule = entry->m_module;
					if (portrait != entry->m_portrait)
					{
						BFMERetailAsciiString name;
						cdaUpdateName(index, name);
						if (portrait != 0)
							cdaInstallPortrait(TheWindowManager, name, portrait);
						else
							cdaRemovePortrait(TheWindowManager, name);
						entry->m_portrait = portrait;
					}

					unsigned char playerReady = 0;
					if (object != 0 &&
						!cdaObjectActive((CdaObjectCall *)object))
					{
						CdaPlayerCall *player =
							*(CdaPlayerCall **)((char *)ThePlayers + 0x0c);
						playerReady = cdaPlayerActive(player);
					}

					float scale = 1.0f;
					Int state = 0;
					if (!cdaIsReady(self))
					{
						Int flags = cdaState(self);
						if (flags & 0x00400000)
							state = 4;
						else if (flags & 8)
							state = objectModule != 0 &&
								(*(Int *)((char *)entryModule + 0x18) &
									0x10000000)
								? 3 : 5;
						else
						{
							flags = cdaState(self);
							if (flags & 0x40000000)
								state = 6;
							else
								state = (flags & 0x01000000) ? 2 : 1;
						}
					}

					if (playerReady == 0)
					{
						Int frameValue = cdaValue(self);
						scale = (float)frameValue * CdaFrameScale;
						entry->m_value = cdaValueObject(self);
					}

					if (state != entry->m_state)
					{
						cdaStateChanged(index, state);
						entry->m_state = state;
					}
					entry->m_scale = scale;

					if (playerReady == 0 && entryModule != 0 &&
						objectModule != 0 && cdaModuleReady(entryModule))
					{
						if (entry->m_active == 0)
						{
							cdaSetActive(index);
							entry->m_active = 1;
						}
						else
						{
							cdaClearActive(index);
							entry->m_active = 0;
						}

						Bool hasValue =
							*(Int *)((char *)entryModule + 0x144) > 0;
						if (hasValue != (entry->m_hasValue != 0))
						{
							cdaSetModuleState(index, hasValue);
							entry->m_hasValue = hasValue;
						}
					}

					void *nameValue = cdaGetValue(self);
					if (nameValue != entry->m_name)
					{
						cdaRefreshEntry(index, nameValue);
						entry->m_name = nameValue;
					}
				}
				++index;
				++entry;
				controlOffset += 4;
			} while (controlOffset < 0x118);

			cdaDestroyTail(self, object);
			if (object != 0)
				cdaDestroyAux(self, object);
		}
		return;
	}

	for (Int index = 0; index < 6; ++index)
	{
		if (self->m_entries[index].m_active != 0)
		{
			cdaClearActive(index);
			self->m_entries[index].m_active = 0;
		}
	}
}
