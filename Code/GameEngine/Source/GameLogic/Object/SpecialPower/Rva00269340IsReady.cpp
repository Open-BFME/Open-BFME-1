// cl: /DNDEBUG /MD /EHsc
// Candidate for retail 0x00269340 (121B). Entered on the interface subobject at
// primary+0x10 (same shape as getPercentReady @0x00268A90): moduleData at -0xC,
// Object at -8, available/paused at +4/+8, BFME flag at +0x14.

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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SpecialPower.h
class SpecialPowerTemplate
{
public:
	bool isShortcutPower(void) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Player *getControllingPlayer(void) const;

	char m_pad[0x98];
	unsigned int m_statusBits;				// +0x98
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
class Rva00269340Primary
{
public:
	virtual ~Rva00269340Primary();

	void *m_moduleData;						// +0x04
	Object *m_obj;							// +0x08
	char m_pad0C[4];						// +0x0C; interface at +0x10
};

class Rva00269340Interface
{
public:
	virtual bool isReady(void) const = 0;
};

class Rva00269340Owner : public Rva00269340Primary, public Rva00269340Interface
{
public:
	virtual bool isReady(void) const;

private:
	UnsignedInt m_availableOnFrame;			// iface +0x04
	Int m_pausedCount;						// iface +0x08
	char m_pad0C[8];						// +0x0C..+0x13
	unsigned char m_flag14;					// iface +0x14
};

// ?isReady@Rva00269340Owner@@UBE_NXZ
bool Rva00269340Owner::isReady(void) const
{
	if (m_flag14)
		return false;

	Object *obj = m_obj;
	if (obj->m_statusBits & 0x20)
		return false;

	SpecialPowerModuleData *modData = (SpecialPowerModuleData *)m_moduleData;
	if (modData)
	{
		Player *player = obj->getControllingPlayer();
		if (player)
		{
			SpecialPowerTemplate *tmpl = modData->m_specialPowerTemplate;
			if (tmpl->isShortcutPower())
				return (TheGameLogic->getFrame() >= player->getOrStartSpecialPowerReadyFrame(tmpl));
		}
	}

	return (m_pausedCount == 0) && (TheGameLogic->getFrame() >= m_availableOnFrame);
}
