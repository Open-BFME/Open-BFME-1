// ?triggerAbilityEffect@ToggleMountedSpecialAbilityUpdate@@MAEXXZ
// partial score=0.7488 date=2026-10-31
// cl: /DNDEBUG /MD /EHsc
//
// ToggleMountedSpecialAbilityUpdate::triggerAbilityEffect, retail
// 0x0026C9E0 (406 bytes).
// BFME 1 target evidence: the matched constructor 0x0026C730 installs vtable
// VA 0x010B88E8 at +0, whose slot 15 reaches this body, and ilt_oracle
// confirms ?triggerAbilityEffect@ToggleMountedSpecialAbilityUpdate@@MAEXXZ.
// The body first runs the base trigger (ILT 0x0003FA30), then, for an idle
// AI with the ability in state 1, toggles the mounted model-condition bit
// (word +0x128 bit 11) with its weapon/armor flag handlers and AI slot 127,
// optionally cancels a disguise (module data +0x259, condition word +0x130
// bit 11, "SpecialDisguiseUpdate" module), and dirties the control bar for a
// selected drawable. Condition, slot and helper names stay address-derived.
// Donor (open-bfme-2 20a0cb6173, Code/GameEngine/Source/GameLogic/Object/
// Update/ToggleMountedSpecialAbilityEffect.cpp, retail 0x004ADF0B there,
// 417 B) supplies the control flow; BFME 1 has no mounted-template branch.
// s504: reading the mount test through a `words` pointer local and setting the
// bit unconditionally in the else arm reproduce retail's reload of +0x128
// before `or eax,0x800` (shape 1.000, 407/406). Remaining: the static key
// reload after the guard join is `mov ecx,[key]; push ecx` here versus
// retail `mov eax,[key]; push eax` (+1 B). Inert for it: non-const static,
// int key, findUpdateModule inline wrapper, key copy local, Module* local,
// words[9]/test(299) spellings, rotation_sweep --pairs (76 toggles).

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class Module;

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

template<int N> class Rva0026C9E0Slots : public Rva0026C9E0Slots<N - 1>
{
public:
	virtual void slot(char (*)[N]);
};
template<> class Rva0026C9E0Slots<0>
{
};

class Rva0026C9E0AI : public Rva0026C9E0Slots<96>
{
public:
	virtual bool v180();				// slot 96
	virtual void v184(); virtual void v188(); virtual void v18C(); virtual void v190();
	virtual void v194(); virtual void v198(); virtual void v19C(); virtual void v1A0();
	virtual void v1A4(); virtual void v1A8(); virtual void v1AC(); virtual void v1B0();
	virtual void v1B4(); virtual void v1B8(); virtual void v1BC(); virtual void v1C0();
	virtual void v1C4(); virtual void v1C8(); virtual void v1CC(); virtual void v1D0();
	virtual void v1D4(); virtual void v1D8(); virtual void v1DC(); virtual void v1E0();
	virtual void v1E4(); virtual void v1E8(); virtual void v1EC(); virtual void v1F0();
	virtual void v1F4(); virtual void v1F8();
	virtual void v1FC(int value);			// slot 127
};

class Rva0026C9E0Contain : public Rva0026C9E0Slots<37>
{
public:
	virtual void v94(int value);			// slot 37
	virtual void v98(); virtual void v9C(); virtual void vA0(); virtual void vA4();
	virtual void vA8(); virtual void vAC(); virtual void vB0(); virtual void vB4();
	virtual void vB8(); virtual void vBC(); virtual void vC0(); virtual void vC4();
	virtual void vC8(); virtual void vCC(); virtual void vD0(); virtual void vD4();
	virtual void vD8(); virtual void vDC(); virtual void vE0(); virtual void vE4();
	virtual void vE8(); virtual void vEC(); virtual void vF0(); virtual void vF4();
	virtual void vF8(); virtual void vFC();
	virtual unsigned int v100(int value);		// slot 64
};

class Rva0026C9E0Drawable
{
public:
	unsigned char m_pad000[0x3ac];
	bool m_selected3AC;				// +0x3AC
};

class ControlBar
{
public:
	unsigned char m_pad00[0x24];
	bool m_dirty24;					// +0x24
};
extern ControlBar *TheControlBar;

// Matched handlers on the Object, ledgered under address-derived classes.
class Gen001C9AC0 { public: void handle(int value); };
class Gen001C9A10 { public: void handle(int value); };
class Rva001BEF00GuardedVCall { public: void forward(int value); };
class Rva001BEEE0GuardedVCall { public: void forward(int value); };
class Rva00267D00 { public: void m00267D00(char value); };

struct Rva0026C9E0Flags
{
	unsigned int words[19];
	__forceinline unsigned int test(unsigned int bit) const { return words[bit >> 5] & (1U << (bit & 31)); }
	__forceinline void clear(unsigned int bit) { words[bit >> 5] &= ~(1U << (bit & 31)); }
	__forceinline void set(unsigned int bit) { words[bit >> 5] |= (1U << (bit & 31)); }
};

class Object : public Rva0026C9E0Slots<10>
{
	friend class ToggleMountedSpecialAbilityUpdate;
public:
	virtual Rva0026C9E0Drawable *getDrawable() const;	// slot 10
	void notifyModelConditionChanged();
	__forceinline void clearCondition235() { if (m_conditions.words[7] & 0x800) { m_conditions.words[7] &= ~0x800; notifyModelConditionChanged(); } }
	__forceinline void setCondition235() { if (!(m_conditions.words[7] & 0x800)) { m_conditions.words[7] |= 0x800; notifyModelConditionChanged(); } }
	unsigned char m_pad004[0x10c - 4];
	Rva0026C9E0Flags m_conditions;			// +0x10C
	unsigned char m_pad158[0x1fc - 0x158];
	Rva0026C9E0Contain *m_contain;			// +0x1FC
	unsigned char m_pad200[4];
	Rva0026C9E0AI *m_ai;				// +0x204
protected:
	Module *findModule(NameKeyType key) const;
};

struct Rva0026C9E0ModuleData
{
	unsigned char m_pad000[0x259];
	bool m_flag259;					// +0x259
};

// The base trigger body behind ILT 0x0003FA30 is ledgered under a
// destructor name; call it through its ILT row.
extern void j_0003fa30();
class Rva0026C9E0Call
{
public:
	void method();
};

class ToggleMountedSpecialAbilityUpdate : public Rva0026C9E0Slots<15>
{
protected:
	virtual void triggerAbilityEffect();		// slot 15
	const Rva0026C9E0ModuleData *m_data;		// +0x04
	Object *m_object;				// +0x08
	unsigned char m_pad0c[0x24 - 0xc];
	int m_state;					// +0x24
};

void ToggleMountedSpecialAbilityUpdate::triggerAbilityEffect()
{
	{
		union { void (*raw)(); void (Rva0026C9E0Call::*fn)(); } base;
		base.raw = j_0003fa30;
		(((Rva0026C9E0Call *)this)->*base.fn)();
	}
	Object *obj = m_object;
	Rva0026C9E0AI *ai = obj->m_ai;
	if (!ai->v180())
		return;
	if (m_state != 1)
		return;
	unsigned int *words = obj->m_conditions.words;
	if (words[7] & 0x800)
	{
		Rva0026C9E0Contain *contain = obj->m_contain;
		if (contain && contain->v100(0) > 0)
			obj->m_contain->v94(0);
		obj->clearCondition235();
		obj->m_ai->v1FC(0);
		((Gen001C9AC0 *)obj)->handle(0x15);
		((Rva001BEF00GuardedVCall *)obj)->forward(6);
		if (m_data->m_flag259 && (obj->m_conditions.words[9] & 0x800))
		{
			static const NameKeyType key = TheNameKeyGenerator->nameToKey("SpecialDisguiseUpdate");
			Rva00267D00 *disguise = (Rva00267D00 *)obj->findModule(key);
			if (disguise)
				disguise->m00267D00(true);
		}
	}
	else
	{
		obj->m_conditions.words[7] |= 0x800;
		obj->notifyModelConditionChanged();
		obj->m_ai->v1FC(7);
		((Gen001C9A10 *)obj)->handle(0x15);
		((Rva001BEEE0GuardedVCall *)obj)->forward(6);
	}
	Rva0026C9E0Drawable *drawable = obj->getDrawable();
	if (drawable && drawable->m_selected3AC)
		TheControlBar->m_dirty24 = true;
}
