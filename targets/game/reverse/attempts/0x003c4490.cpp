// ?DoXfer@LivingWorldLogic@@UAEXAAVXfer@@@Z
// partial score=0.9705 date=2026-11-02
// cl: /DNDEBUG /MD /EHsc /Igame
// LivingWorldLogic::DoXfer, retail 0x003C4490 (542 bytes, ret 4 at +0x21B).
//
// Identity: the LivingWorldLogic Snapshot vtable 0x010EDBC8 (second table,
// installed at +0x08 by the matched constructor 0x003C2FC0) has this body in
// slot 3 through ILT 0x0000FDBC, and ilt_oracle CONFIRMS
static inline int Rva003C4490Active(int mode)
{
	if (mode == 8 || mode == 4)
		return 0;
	return 1;
}

// ?DoXfer@LivingWorldLogic@@UAEXAAVXfer@@@Z there (the ZH ?xfer@...PAVXfer
// spellings are CONTRADICTED). The receiver is that Snapshot subobject, so
// the whole object is this-8.
//
// [BFME 2 donor] Open-BFME-2 45afcff3 LivingWorldLogic_xfer.cpp (BFME 2
// 0x002BC653) gave the overall shape: light gate, version, a stored enable
// flag that ends the transfer early, the campaign/manager snapshots and the
// GameLogic transfer. The BFME 1 body is version 3 and differs in detail;
// every field, call and branch below is read from the retail body. Member
// names are offset labels.
#include <stdlib.h>
#include "GameEngine/Source/Common/System/xfer.h"

class Rva3SlotSnapshotView
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void transfer(Xfer *xfer);
};

class Rva003C4490Item : public Rva3SlotSnapshotView
{
public:
	int active;
};

class Rva006092D0State
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void reset(int value);
};
class BfmeOneAQA { public: void bfmeStopAQA(); };
class LivingWorldCampaignManager;
class LivingWorldManager;
class GameLogic;
class BfmeItemEN;
class BfmeThingEN { public: void bfmeGoEN(BfmeItemEN *item); };
class Transfer003C3D90
{
public:
	void transfer(Xfer *xfer);
	int load003C4160(Xfer *xfer);
};
class Gen_003C0F70 { public: void bfmeClear(); };
class Gen_003C1190 { public: void bfmeClear(); };
void postLoadGameFadeSteps();

extern Rva006092D0State *g_rva012F7048LivingWorld;
extern LivingWorldCampaignManager *TheLivingWorldCampaignManager;
extern LivingWorldManager *TheLivingWorldManager;
extern GameLogic *TheGameLogic;

struct Rva003C4490GameLogicView
{
	char m_unmodelled000[0x10C];
	int m_mode;
};

class Rva003C4490Base
{
public:
	virtual ~Rva003C4490Base();
	int active;
};

class Rva003C4490Snapshot
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void DoXfer(Xfer &xfer) = 0;
};

class LivingWorldLogic : public Rva003C4490Base, public Rva003C4490Snapshot
{
public:
	virtual void DoXfer(Xfer &xfer);

private:
	char m_unmodelled0C[0x28 - 0x0C];
	Rva003C4490Item *m_item28;			// +0x28
	char m_unmodelled2C;
	bool m_flag2D;						// +0x2D
	char m_unmodelled2E[0x45 - 0x2E];
	bool m_enabled45;					// +0x45
	char m_unmodelled46[0xD4 - 0x46];
	void *m_buffer;						// +0xD4
	unsigned int m_bufferSize;			// +0xD8
};

// ?DoXfer@LivingWorldLogic@@UAEXAAVXfer@@@Z
void LivingWorldLogic::DoXfer(Xfer &xfer)
{
	if (xfer.IsLightCRC())
		return;

	Xfer::Version version;
	version.data[0] = 1;
	version.data[1] = 3;
	xfer == version;

	if (version.data[1] >= 3)
	{
		xfer == m_bufferSize;
		if (xfer.IsLoading())
		{
			free(m_buffer);
			m_buffer = malloc(m_bufferSize);
		}
		xfer.XferRawBytes(m_buffer, m_bufferSize);
	}

	if (xfer.IsLoading())
	{
		xfer == m_enabled45;
		if (!m_enabled45)
		{
			((BfmeOneAQA *)g_rva012F7048LivingWorld)->bfmeStopAQA();
			return;
		}
		((BfmeOneAQA *)g_rva012F7048LivingWorld)->bfmeStopAQA();
		((Transfer003C3D90 *)this)->load003C4160(&xfer);
	}
	else
	{
		m_enabled45 = m_item28->active != 0;
		xfer == m_enabled45;
		if (!m_enabled45)
			return;
		((Transfer003C3D90 *)this)->transfer(&xfer);
	}

	((Rva3SlotSnapshotView *)((char *)TheLivingWorldCampaignManager + 8))->transfer(&xfer);

	if (version.data[1] >= 2)
	{
		int mode = ((Rva003C4490GameLogicView *)TheGameLogic)->m_mode;
		bool active = !(mode == 8 || mode == 4);
		xfer == active;
		m_flag2D = !active;
		if (xfer.IsLoading())
		{
			if (m_flag2D)
				((Gen_003C1190 *)this)->bfmeClear();
			else
				((Gen_003C0F70 *)this)->bfmeClear();
		}
	}

	m_item28->transfer(&xfer);
	((BfmeThingEN *)TheGameLogic)->bfmeGoEN((BfmeItemEN *)&xfer);
	((Rva3SlotSnapshotView *)((char *)TheLivingWorldManager + 8))->transfer(&xfer);

	if (xfer.IsLoading())
	{
		int state;
		xfer == state;
		if (state == 0)
		{
			// retail passes the whole object in ECX to the matched free
			// function 0x003C0610, which ignores it
			union
			{
				void (*raw)();
				void (Transfer003C3D90::*member)();
			} fade = { postLoadGameFadeSteps };
			(((Transfer003C3D90 *)this)->*fade.member)();
			return;
		}
		g_rva012F7048LivingWorld->reset(0);
		m_flag2D = false;
	}
	else
	{
		unsigned char active;
		if (version.data[1] >= 2)
			active = Rva003C4490Active(((Rva003C4490GameLogicView *)TheGameLogic)->m_mode);
		else
			active = ((Rva003C4490GameLogicView *)TheGameLogic)->m_mode != 8;
		int state = active;
		xfer == state;
	}
}




// bank s532: 542/542 B, 16 non-reloc diffs: register tie at the save-tail join (+0x1F4..+0x214)
