// cl: /DNDEBUG /MD /EHsc
// readable body of ?isReady@SpecialPowerModule@@UBE_NXZ: Code/GameEngine/Source/GameLogic/Object/SpecialPower/SpecialPowerModule.cpp

// BFME SpecialPowerModule::isReady, 0x0026AA20.
//
// Secondary result for prereg29: the packet pins 0x0026AA1C, four bytes of int3
// padding ahead of this body. The real start is 0x0026AA20 and the real size
// 123 - the packet's 127 is this body plus that padding, so only its start was
// wrong.
//
// Entered on the special power interface subobject. m_obj sits at -0x1c and
// m_moduleData at -0x20, and with ObjectModule holding them at +0x08 and +0x04
// (named in 160d00ada) both readings put that subobject at object+0x24, which
// is what the padding below encodes. The module's own m_availableOnFrame and
// m_pausedCount then land at subobject +4 and +8, exactly where retail reads
// them.
//
// Two departures from Zero Hour's body, both read off the bytes: retail guards
// on the object alone (Zero Hour also tests the module data) and reuses that
// pointer for getControllingPlayer rather than calling getObject twice.

typedef unsigned int UnsignedInt;
typedef int Int;

class Player;
class Object;
class SpecialPowerTemplate;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	UnsignedInt getFrame(void) const { return m_frame; }

private:
	char m_pad[0x3c];
	UnsignedInt m_frame;					// +0x3c
};

extern GameLogic *TheGameLogic;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	virtual ~Overridable();

	// Recursive by design. Retail unrolls it twice at this call site and then
	// calls the out-of-line copy, which is what inline_depth(2) reproduces;
	// the default depth stops after one level and comes up seven bytes short.
	Overridable *friend_getFinalOverride(void)
	{
		if (m_nextOverride)
			return m_nextOverride->friend_getFinalOverride();
		return this;
	}

	Overridable *m_nextOverride;			// +0x04
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SpecialPower.h
class SpecialPowerTemplate : public Overridable
{
public:
	bool isSharedNSync(void) const { return getFO()->m_sharedNSync; }

private:
	const SpecialPowerTemplate *getFO(void) const
	{
		SpecialPowerTemplate *self = (SpecialPowerTemplate *)this;
		return (const SpecialPowerTemplate *)(self->m_nextOverride
			? self->m_nextOverride->friend_getFinalOverride()
			: (Overridable *)self);
	}

	char m_pad[0x115 - 0x08];
	bool m_sharedNSync;						// +0x115
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Player *getControllingPlayer(void) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	UnsignedInt getOrStartSpecialPowerReadyFrame(const SpecialPowerTemplate *tmpl);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialPowerModule.h
class SpecialPowerModuleData
{
public:
	char m_pad[8];
	SpecialPowerTemplate *m_specialPowerTemplate;	// +0x08
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ObjectModule
{
public:
	virtual ~ObjectModule();

	Object *getObject(void) const { return m_obj; }
	const SpecialPowerModuleData *getSpecialPowerModuleData(void) const
	{
		return (const SpecialPowerModuleData *)m_moduleData;
	}

protected:
	void *m_moduleData;						// +0x04
	Object *m_obj;							// +0x08
};

// Carries the primary chain out to 0x24 so the interface subobject lands there.
class SpecialPowerPrimary : public ObjectModule
{
protected:
	char m_pad[0x24 - 0x0c];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialPowerModule.h
class SpecialPowerModuleInterface
{
public:
	virtual bool isReady(void) const = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialPowerModule.h
class SpecialPowerModule : public SpecialPowerPrimary, public SpecialPowerModuleInterface
{
public:
	virtual bool isReady(void) const;

private:
	UnsignedInt m_availableOnFrame;			// subobject +0x04
	Int m_pausedCount;						// subobject +0x08
};

bool SpecialPowerModule::isReady(void) const
{
	const Object *obj = getObject();
	const SpecialPowerModuleData *modData = getSpecialPowerModuleData();

	if (obj)
	{
		Player *player = obj->getControllingPlayer();
		if (player)
		{
			if (modData->m_specialPowerTemplate->isSharedNSync())
				return (TheGameLogic->getFrame() >= player->getOrStartSpecialPowerReadyFrame(modData->m_specialPowerTemplate));
		}
	}

	return (m_pausedCount == 0) && (TheGameLogic->getFrame() >= m_availableOnFrame);
}
