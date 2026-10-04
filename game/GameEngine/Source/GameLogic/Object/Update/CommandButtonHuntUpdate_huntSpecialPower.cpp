// cl: /DNDEBUG /MD /EHsc

// CommandButtonHuntUpdate::huntSpecialPower, retail 0x0028B490, 133 bytes.
// The module stores its data pointer at +0x04, its owner at +0x08, and its
// command button at +0x24. The three calls below use the retail thunks for the
// override walk, special-ability lookup, and target scan.

typedef bool Bool;
typedef unsigned int UnsignedInt;

enum UpdateSleepTime
{
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

#include "../../command_source_type.h"

enum SpecialPowerType
{
	SPECIAL_POWER_INVALID = 0
};

class Object;
class SpecialAbilityUpdate;

// Route class for the member-pointer call below: it only names a signature,
// the call itself goes to the retail ILT thunk.
class Route00047CBC {};

// Retail ILT thunks the calls below are routed through.
extern void j_0004b4fc();
extern void j_00047cbc();

class PB_DeepBase
{
public:
	virtual ~PB_DeepBase();

protected:
	void *m_moduleData;
	Object *m_object;
};

class PB_Iface1
{
public:
	virtual void slot();
};

class PB_Iface2
{
public:
	UpdateSleepTime rva0028b540Update();
	virtual void slot();
};

class UpdateModule : public PB_DeepBase, public PB_Iface1, public PB_Iface2
{
protected:
	Object *getObject() const
	{
		return m_object;
	}

private:
	UnsignedInt m_f14;
	int m_f18;
	int m_f1c;
};

class CommandButtonHuntUpdateModuleData
{
public:
	unsigned char m_unmodelled[8];
	UnsignedInt m_scanFrames;
};

template <int N>
class BfmeVirtualSlots : public BfmeVirtualSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};

template <>
class BfmeVirtualSlots<0>
{
};

class AIUpdateInterface : public BfmeVirtualSlots<96>
{
public:
	virtual Bool isIdle() const = 0;
};

class Overridable
{
public:
	virtual ~Overridable();
	Overridable *friend_getFinalOverride()
	{
		if (m_nextOverride)
			return m_nextOverride->friend_getFinalOverride();
		return this;
	}
	const Overridable *friend_getFinalOverride() const
	{
		if (m_nextOverride)
			return m_nextOverride->friend_getFinalOverride();
		return this;
	}

	Overridable *m_nextOverride;
};

class SpecialPowerTemplate : public Overridable
{
public:
	const SpecialPowerTemplate *getFO() const
	{
		return (const SpecialPowerTemplate *)friend_getFinalOverride();
	}

	SpecialPowerType getSpecialPowerType() const
	{
		return getFO()->m_specialPowerType;
	}

	private:
	unsigned char m_unmodelled[0x14 - 8];
	SpecialPowerType m_specialPowerType;
};

class CommandButton
{
public:
	const SpecialPowerTemplate *getSpecialPowerTemplate() const
	{
		return m_specialPowerTemplate;
	}

private:
	unsigned char m_unmodelled[0x34];
	const SpecialPowerTemplate *m_specialPowerTemplate;
};

class SpecialAbilityUpdateInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual Bool isActive() const = 0;
};

class SpecialAbilityUpdateBase
{
public:
	virtual void slot() = 0;

protected:
	unsigned char m_unmodelled[0x1c];
};

class SpecialAbilityUpdate : public SpecialAbilityUpdateBase,
	public SpecialAbilityUpdateInterface
{
};

class Object
{
public:
	// Only ever taken by address into a union below: retail calls this through
	// the ILT thunk j_0004b4fc, never through a definition in this TU.
	SpecialAbilityUpdate *findSpecialAbilityUpdate(SpecialPowerType type) const;
	void doCommandButtonAtObject(const CommandButton *commandButton, Object *object,
		CommandSourceType source, Bool playVoiceResponse);
};

class CommandButtonHuntUpdate : public UpdateModule
{
	friend class PB_Iface2;
	protected:
	UpdateSleepTime huntSpecialPower(AIUpdateInterface *ai);

	// Only ever taken by address into a union below: retail calls this through
	// the ILT thunk j_00047cbc, never through a definition in this TU.
	Object *scanClosestTarget();

private:
	void *m_commandButtonName;
	const CommandButton *m_commandButton;
};

UpdateSleepTime CommandButtonHuntUpdate::huntSpecialPower(AIUpdateInterface *ai)
{
	Object *obj = getObject();
	const CommandButtonHuntUpdateModuleData *data =
		(const CommandButtonHuntUpdateModuleData *)m_moduleData;
	if (!ai->isIdle())
	{
		return (UpdateSleepTime)data->m_scanFrames;
	}

	const SpecialPowerTemplate *spTemplate = m_commandButton->getSpecialPowerTemplate();
	if (spTemplate)
	{
		typedef SpecialAbilityUpdate *(Object::*FindUpdate)(SpecialPowerType) const;
		union { void (*fn)(); FindUpdate call; } findUpdate = { j_0004b4fc };
		SpecialAbilityUpdate *spUpdate = (obj->*findUpdate.call)(
			spTemplate->getSpecialPowerType());
		if (spUpdate == 0)
			return UPDATE_SLEEP_FOREVER;
		if (spUpdate->isActive())
			return (UpdateSleepTime)data->m_scanFrames;
	}

	typedef Object *(Route00047CBC::*ScanClosestTarget)();
	union { void (*fn)(); ScanClosestTarget call; } scanClosestTarget = { j_00047cbc };
	Object *victim = (((Route00047CBC *)this)->*scanClosestTarget.call)();
	if (victim)
	{
		obj->doCommandButtonAtObject(m_commandButton, victim, CMD_FROM_AI, false);
	}
	return (UpdateSleepTime)data->m_scanFrames;
}

class BFMERetailAsciiString
{
public:
	void clear() { releaseBuffer(); }
private:
	void releaseBuffer();
};

class Rva0028B540AIView : public BfmeVirtualSlots<128>
{
public:
	virtual int status();
};

class BfmeTarget;
class Gen_0028B440
{
public:
	int bfmeApply(BfmeTarget *target);
};

UpdateSleepTime PB_Iface2::rva0028b540Update()
{
	register PB_Iface2 *self = this;
	Object *object = *(Object **)((char *)self - 8);
	Rva0028B540AIView *ai = *(Rva0028B540AIView **)((char *)object + 0x204);
	if (ai && *(const CommandButton **)((char *)self + 0x14))
	{
		if (ai->status() != 2)
		{
			*(const CommandButton **)((char *)self + 0x14) = 0;
			((BFMERetailAsciiString *)((char *)self + 0x10))->clear();
			return UPDATE_SLEEP_FOREVER;
		}
		const CommandButton *button = *(const CommandButton **)((char *)self + 0x14);
		const int command = *(const int *)((const char *)button + 0x10);
		switch (command)
		{
		case 23: case 36:
			return ((CommandButtonHuntUpdate *)((char *)self - 0x10))->huntSpecialPower((AIUpdateInterface *)ai);
		case 22: case 26:
			return (UpdateSleepTime)((Gen_0028B440 *)((char *)self - 0x10))->bfmeApply((BfmeTarget *)ai);
		}
	}
	return UPDATE_SLEEP_FOREVER;
}
