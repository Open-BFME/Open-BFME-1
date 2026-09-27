// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/stringinline /Iinputs/reference/shims/sweep
#include "StringInline.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef int Bool;

class GameWindow
{
public:
	void *winGetUserData();
};

class WinInstanceData;

struct ComboBoxData
{
	char m_pad[0x28];
	GameWindow *editBox;
};

static GameWindow *comboBoxPlayer[8];

static GameWindow *GadgetComboBoxGetEditBox(GameWindow *window)
{
	ComboBoxData *data = (ComboBoxData *)window->winGetUserData();
	if (data && data->editBox)
		return data->editBox;
	return 0;
}

inline const unsigned short *UnicodeString::str() const
{
	return m_data ? m_data->m_text : (const unsigned short *)L"";
}

struct Rva0068D3E0Slot
{
	char m_body[0x68];
};

class Rva0068D3E0Arr;
typedef Rva0068D3E0Slot *(__fastcall *Rva0068D3E0AtThunk)(Rva0068D3E0Arr *);
extern void j_000234d4(void);

class Rva0068D3E0Arr
{
public:
	Rva0068D3E0Slot *at(Int index);
	Rva0068D3E0Slot *at() { return ((Rva0068D3E0AtThunk)&j_000234d4)(this); }
};

class LANPlayer
{
public:
	const UnicodeString &getName() const { return m_name; }
	const UnicodeString &getLogin() const { return m_login; }
	const UnicodeString &getHost() const { return m_host; }

	UnicodeString m_name;
	UnicodeString m_login;
	UnicodeString m_host;
};

class LANGameSlot : public Rva0068D3E0Slot
{
public:
	LANPlayer *getUser();
};

class LANGameInfo : public Rva0068D3E0Arr
{
public:
	LANGameSlot *getLANSlot() { return (LANGameSlot *)at(); }
};

class LANAPI;
extern LANAPI *TheLAN;

// The index remains on the stack for the proven ret-4 slot accessor.
class LANAPIStackView
{
public:
	virtual void slot00() = 0; virtual void slot04() = 0; virtual void slot08() = 0;
	virtual void slot0C() = 0; virtual void slot10() = 0; virtual void slot14() = 0;
	virtual void slot18() = 0; virtual void slot1C() = 0; virtual void slot20() = 0;
	virtual void slot24() = 0; virtual void slot28() = 0; virtual void slot2C() = 0;
	virtual void slot30() = 0; virtual void slot34() = 0; virtual void slot38() = 0;
	virtual void slot3C() = 0; virtual void slot40() = 0; virtual void slot44() = 0;
	virtual void slot48() = 0; virtual void slot4C() = 0; virtual void slot50() = 0;
	virtual void slot54() = 0; virtual void slot58() = 0; virtual void slot5C() = 0;
	virtual void slot60() = 0; virtual void slot64() = 0; virtual void slot68() = 0;
	virtual void slot6C() = 0; virtual void slot70() = 0; virtual void slot74() = 0;
	virtual void slot78() = 0; virtual void slot7C() = 0; virtual void slot80() = 0;
	virtual void slot84() = 0; virtual void slot88() = 0; virtual void slot8C() = 0;
	virtual void slot90() = 0; virtual void slot94() = 0; virtual void slot98() = 0;
	virtual void slot9C() = 0; virtual void slotA0() = 0; virtual void slotA4() = 0;
	virtual void slotA8() = 0; virtual void slotAC() = 0; virtual void slotB0() = 0;
	virtual void slotB4() = 0; virtual void slotB8() = 0; virtual void slotBC() = 0;
	virtual LANGameInfo *getMyGameWithStackIndex(Int) = 0;
};

static __forceinline LANGameInfo *getMyGameWithStackIndex(Int index)
{
	return ((LANAPIStackView *)TheLAN)->getMyGameWithStackIndex(index);
}

struct RGBColor;
class Mouse
{
public:
	void setCursorTooltip(UnicodeString text, Int width, const RGBColor *color, float scale);
};
extern Mouse *TheMouse;

class GameTextInterface
{
public:
	virtual ~GameTextInterface() {}
	virtual void init() = 0;
	virtual void postProcessLoad() = 0;
	virtual void reset() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual Bool bfme_gt_6(void *) = 0;
	virtual void bfme_gt_7() = 0;
	virtual void bfme_gt_8(void *) = 0;
	virtual void bfme_gt_9() = 0;
	virtual UnicodeString fetch(const char *label, Bool *exists = 0) = 0;
};
extern GameTextInterface *TheGameText;

#define DEBUG_ASSERTCRASH(condition, message) ((void)0)

void rva004CB220PlayerTooltip(GameWindow *window, WinInstanceData *, UnsignedInt)
{
	Int idx = -1;
	for (Int i = 0; i < 8; ++i)
	{
		if (window && window == GadgetComboBoxGetEditBox(comboBoxPlayer[i]))
		{
			idx = i;
			break;
		}
	}
	if (idx == -1)
		return;

	LANGameSlot *slot = getMyGameWithStackIndex(i)->getLANSlot();
	if (!slot)
		return;

	LANPlayer *player = slot->getUser();
	if (!player)
	{
		DEBUG_ASSERTCRASH(TheLAN->GetMyGame()->getIP(i) == 0, ("No player info in listbox!"));
		TheMouse->setCursorTooltip(UnicodeString::TheEmptyString, -1, 0, 1.0f);
		return;
	}

	UnicodeString tooltip;
	tooltip.format(TheGameText->fetch("TOOLTIP:LANPlayer"), player->getName().str(), player->getLogin().str(), player->getHost().str());
	TheMouse->setCursorTooltip(tooltip, -1, 0, 1.0f);
}
