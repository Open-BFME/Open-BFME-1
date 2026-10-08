// cl: /Igame/Libraries/Source/WWVegas/WWLib
// Open-BFME5 conversions.

class AsciiString;
class CommandButton;
class GameWindow;

// retail ILT 0x0003B59D -> 0x004A0310 is the matched ControlBar::findCommandButton
// row and ILT 0x0003BCCD -> 0x004C1B60 the matched ControlBar::rva004C1B60 row
class ControlBar
{
public:
	const CommandButton *findCommandButton(const AsciiString &name);
	void rva004C1B60(GameWindow *window, void *data);
};

class BfmeB977;

class BfmeMgr977 : public ControlBar
{
};

#define bfmeFind977B(b) findCommandButton(*(const AsciiString *)(b))
#define bfmeDo977B(a, x) rva004C1B60((GameWindow *)(a), (void *)(x))

extern ControlBar *TheControlBar;

class BfmeCampaignSwitch977
{
public:
	char m_bfmePad[0x1C];
	bool m_bfmeRingCampaign;
};

// The retail global at 0x012F1024 is EA's
// `LivingWorldCampaignManager *TheLivingWorldCampaignManager`, defined once in
// game/GameEngine/Source/GameLogic/LivingWorld/LivingWorldCampaignManager.cpp;
// BfmeCampaignSwitch977 above is this TU's view of the object, cast at the use.
class LivingWorldCampaignManager;

extern LivingWorldCampaignManager *TheLivingWorldCampaignManager;

static inline const BfmeCampaignSwitch977 *livingWorldCampaignManagerView977()
{
	return (const BfmeCampaignSwitch977 *)TheLivingWorldCampaignManager;
}

#include "ascii_string.h"

struct BfmeRec977
{
	char m_bfmePad[4];
	short m_bfmeKind;
};

class BfmeB977
{
public:
	void bfmeGo977B(int unused);

	BfmeRec977 *m_bfmeRec;
};

void BfmeB977::bfmeGo977B(int unused)
{
	BfmeRec977 *r = m_bfmeRec;

	if (r && r->m_bfmeKind != 0) {
		void *x = (void *)reinterpret_cast<BfmeMgr977 *>(TheControlBar)->bfmeFind977B(this);

		if (x)
			reinterpret_cast<BfmeMgr977 *>(TheControlBar)->bfmeDo977B(0, x);
	}
}

// ?bfmeUpdateMaxPowerCommand@@YGXPAX@Z
void __stdcall bfmeUpdateMaxPowerCommand(void *)
{
	void *command;
	{
		bool ringCampaign = livingWorldCampaignManagerView977()->m_bfmeRingCampaign;
		const char *name = ringCampaign
			? "NonCommand_MaxRingPower" : "NonCommand_MaxEvenstarPower";
		AsciiString label(name);
		command = (void *)reinterpret_cast<BfmeMgr977 *>(TheControlBar)->bfmeFind977B((BfmeB977 *)&label);
	}

	if (command)
		reinterpret_cast<BfmeMgr977 *>(TheControlBar)->bfmeDo977B(0, command);
}

class BfmeClock977
{
public:
	virtual void bfmeV0977();
	virtual void bfmeV1977();
	virtual void bfmeV2977();
	virtual void bfmeV3977();
	virtual void bfmeV4977();
	virtual void bfmeV5977();
	virtual void bfmeV6977();
	virtual void bfmeV7977();
	virtual void bfmeV8977();
	virtual void bfmeV9977();
	virtual void bfmeV10977();
	virtual void bfmeV11977();
	virtual void bfmeV12977();
	virtual void bfmeV13977();
	virtual void bfmeV14977();
	virtual void bfmeV15977();
	virtual void bfmeV16977();
	virtual void bfmeV17977();
	virtual void bfmeV18977();
	virtual void bfmeV19977();
	virtual void bfmeV20977();
	virtual void bfmeV21977();
	virtual void bfmeV22977();
	virtual void bfmeV23977();
	virtual void bfmeV24977();
	virtual void bfmeV25977();
	virtual void bfmeV26977();
	virtual void bfmeV27977();
	virtual void bfmeV28977();
	virtual void bfmeV29977();
	virtual void bfmeV30977();
	virtual void bfmeV31977();
	virtual void bfmeV32977();
	virtual void bfmeV33977();
	virtual void bfmeV34977();
	virtual void bfmeV35977();
	virtual void bfmeV36977();
	virtual void bfmeV37977();
	virtual void bfmeV38977();
	virtual void bfmeV39977();
	virtual void bfmeV40977();
	virtual void bfmeV41977();
	virtual void bfmeV42977();
	virtual int bfmeNow977C();
};

// The global read at 0x012F1B40 is EA's window-manager singleton, spelled in
// exactly one name everywhere in the link: `GameWindowManager *TheWindowManager'
// (?TheWindowManager@@3PAVGameWindowManager@@A), defined in
// game/GameEngine/Source/GameClient/GUI/GameWindowManager.cpp. The class above
// is this TU's local ABI view of the slots it calls, cast to at the use; the cast
// is a no-op, so the bytes are unchanged.
class GameWindowManager;
extern GameWindowManager *TheWindowManager;

// retail 0x00892210 is the matched bfmeIsSet row
int bfmeIsSet();
#define bfmeFallback977C() (char)bfmeIsSet()

class BfmeC977
{
public:
	char bfmeGo977C();

	char m_bfmePad[0x19c];
	int *m_bfmeBuf;
	char m_bfmePad2[0x10];
	int m_bfmeStamp;
};

char BfmeC977::bfmeGo977C()
{
	if (m_bfmeBuf[-1] != -1 && m_bfmeStamp != 0
			&& m_bfmeStamp == ((BfmeClock977 *)TheWindowManager)->bfmeNow977C())
		return 1;

	return bfmeFallback977C();
}
