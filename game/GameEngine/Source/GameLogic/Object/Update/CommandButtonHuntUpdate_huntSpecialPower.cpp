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

enum CommandSourceType
{
	CMD_FROM_AI = 2
};

enum SpecialPowerType
{
	SPECIAL_POWER_INVALID = 0
};

class Object;
class SpecialAbilityUpdate;

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
	SpecialAbilityUpdate *findSpecialAbilityUpdate(SpecialPowerType type) const;
	void doCommandButtonAtObject(const CommandButton *commandButton, Object *object,
		CommandSourceType source, Bool playVoiceResponse);
};

class CommandButtonHuntUpdate : public UpdateModule
{
	protected:
	UpdateSleepTime huntSpecialPower(AIUpdateInterface *ai);

	Object *scanClosestTarget();

private:
	void *m_commandButtonName;
	const CommandButton *m_commandButton;
};

#pragma comment(linker, "/alternatename:?friend_getFinalOverride@Overridable@@QAEPAV1@XZ=?j_00048c61@@YAXXZ")
#pragma comment(linker, "/alternatename:?friend_getFinalOverride@Overridable@@QBEPBV1@XZ=?j_00048c61@@YAXXZ")
#pragma comment(linker, "/alternatename:?findSpecialAbilityUpdate@Object@@QBEPAVSpecialAbilityUpdate@@W4SpecialPowerType@@@Z=?j_0004b4fc@@YAXXZ")
#pragma comment(linker, "/alternatename:?scanClosestTarget@CommandButtonHuntUpdate@@IAEPAVObject@@XZ=?j_00047cbc@@YAXXZ")

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
		SpecialAbilityUpdate *spUpdate = obj->findSpecialAbilityUpdate(
			spTemplate->getSpecialPowerType());
		if (spUpdate == 0)
			return UPDATE_SLEEP_FOREVER;
		if (spUpdate->isActive())
			return (UpdateSleepTime)data->m_scanFrames;
	}

	Object *victim = scanClosestTarget();
	if (victim)
	{
		obj->doCommandButtonAtObject(m_commandButton, victim, CMD_FROM_AI, false);
	}
	return (UpdateSleepTime)data->m_scanFrames;
}
