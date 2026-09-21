// ?refreshPlayerTeamControl@SkirmishScreenState@@QAEXH@Z
// partial score=0.45 date=2026-09-18
// ?refreshPlayerTeamControl@SkirmishScreenState@@QAEXH@Z
// cl: /O2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ivendor/stlport /ICode/Libraries/Source/WWVegas/WWLib /Ireference/shims/stringbaseascii /Ireference/shims/stringbaseunicode
// stlport
//
// Retail 0x005294F0.  The matched refreshAllPlayerControls and
// handlePlayerSelection callers prove the SkirmishScreenState method name.
// The map/start-position helper is called through its retail ILT; its
// address-derived Gen005293E0 layout is the only layout claim made here.

#define _STLP_USE_NEWALLOC 1

#include <set>
#include "ascii_string.h"
#include "unicode_string.h"

typedef int Int;
typedef bool Bool;

class GameWindow
{
};

class GameInfo;
class GameSlot;

class SkirmishScreenOwner
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual Bool contains(GameInfo *game) = 0;
};

class GameInfo
{
public:
	GameSlot *getSlot(Int index);
};

class GameSlot
{
public:
	Bool isAI() const;
};

struct StartPositionInfo
{
	unsigned char m_data[20];
};

class Gen_00525EE0
{
public:
	const StartPositionInfo *bfmeGetStartPositionInfo(Int index);
};

class MultiplayerColorDefinition
{
public:
	Int getColor() const
	{
		return *(const Int *)((const char *)this + 0x10);
	}
};

class MultiplayerSettings
{
public:
	MultiplayerColorDefinition *getColor(Int index);
};

class GameTextInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual UnicodeString fetch(const char *label, Bool *exists = 0) = 0;
	virtual UnicodeString fetch(AsciiString label, Bool *exists = 0) = 0;
};

class PopulateRemoteIPComboBoxEntry : public UnicodeString
{
public:
	PopulateRemoteIPComboBoxEntry(const UnicodeString &source)
		: UnicodeString(source) {}
};

class PlayerTemplate
{
public:
	const AsciiString &getSide() const
	{
		return m_side;
	}

	Bool isPlayableSide() const
	{
		return m_playableSide;
	}

	Bool isObserver() const
	{
		return m_observer;
	}

private:
	unsigned char m_beforeSide[0x08];
	AsciiString m_side;
	unsigned char m_beforeObserver[0xbc - 0x0c];
	Bool m_observer;
	Bool m_playableSide;
	unsigned char m_afterPlayableSide[0x124 - 0xbe];
};

class PlayerTemplateStore
{
public:
	const PlayerTemplate *getNthPlayerTemplate(Int index) const;

	Int getPlayerTemplateCount() const
	{
		return (Int)(m_end - m_begin);
	}

private:
	unsigned char m_beforeTemplates[0x08];
	PlayerTemplate *m_begin;
	PlayerTemplate *m_end;
};

class SkirmishScreenState
{
public:
	void refreshPlayerTeamControl(Int index);

private:
	unsigned char m_vtable[4];
	SkirmishScreenOwner *m_owner;
	GameInfo *m_game;
	GameInfo *m_secondaryGame;
	unsigned char m_flags10[0x08];
	unsigned char m_visible[0x01];
	unsigned char m_padding19[0x03];
	Int m_value1c;
	Int m_value20;
	Int m_value24;
	unsigned char m_member28[0x40];
	GameWindow *m_first[8];
	GameWindow *m_elements[8];
	GameWindow *m_second[8];
	GameWindow *m_third[8];
	GameWindow *m_fourth[8];
	unsigned char m_member10c[0x20];
	Int m_field128;
};

extern GameTextInterface *TheGameText;
extern MultiplayerSettings *TheMultiplayerSettings;
extern PlayerTemplateStore *ThePlayerTemplateStore;

extern void GadgetComboBoxGetSelectedPos(GameWindow *window, Int *selected);
extern void *GadgetComboBoxGetItemData(GameWindow *window, Int selected);
extern void GadgetComboBoxReset(GameWindow *window);
extern void GadgetComboBoxSetItemData(GameWindow *window, Int item, void *data);
extern void GadgetComboBoxSetSelectedPos(GameWindow *window, Int selected,
	Bool dontHide);
extern void GadgetComboBoxSetMaxDisplay(GameWindow *window, Int count);

extern void j_00003071();
extern void j_00007004();
extern void j_0001d01b();
extern void j_0001ec18();
extern void j_00021ec2();
extern void j_00028f6f();
extern void j_0002f338();
extern void j_00037bd2();
extern void j_0003aa67();
extern void j_0003b75a();
extern void j_0003b971();
extern void j_000422df();
extern void j_000439c3();
extern void j_00044080();

static __forceinline const char *rva005294f0AsciiText(
	const AsciiString &value)
{
	const void *data = *(const void *const *)&value;
	return data ? (const char *)data + 8 : (const char *)0x0107388b;
}

static __forceinline GameSlot *rva005294f0GetSlot(GameInfo *game, Int index)
{
	union
	{
		void (*raw)(void);
		GameSlot *(GameInfo::*member)(Int);
	} call;
	call.raw = j_0001ec18;
	return (game->*call.member)(index);
}

static __forceinline Bool rva005294f0IsAI(GameSlot *slot)
{
	union
	{
		void (*raw)(void);
		Bool (GameSlot::*member)() const;
	} call;
	call.raw = j_000422df;
	return (slot->*call.member)();
}

static __forceinline const StartPositionInfo *rva005294f0StartInfo(
	SkirmishScreenState *state, Int index)
{
	union
	{
		void (*raw)(void);
		const StartPositionInfo *(Gen_00525EE0::*member)(Int);
	} call;
	call.raw = j_0003aa67;
	return (((Gen_00525EE0 *)state)->*call.member)(index);
}

static __forceinline void rva005294f0GetSelectedPos(GameWindow *window, Int *selected)
{
	union
	{
		void (*raw)(void);
		void (*function)(GameWindow *, Int *);
	} call;
	call.raw = j_0003b75a;
	call.function(window, selected);
}

static __forceinline void *rva005294f0GetItemData(GameWindow *window, Int selected)
{
	union
	{
		void (*raw)(void);
		void *(*function)(GameWindow *, Int);
	} call;
	call.raw = j_0003b971;
	return call.function(window, selected);
}

static __forceinline void rva005294f0Reset(GameWindow *window)
{
	union
	{
		void (*raw)(void);
		void (*function)(GameWindow *);
	} call;
	call.raw = j_00007004;
	call.function(window);
}

static __forceinline MultiplayerColorDefinition *rva005294f0GetColor(
	MultiplayerSettings *settings, Int index)
{
	union
	{
		void (*raw)(void);
		MultiplayerColorDefinition *(MultiplayerSettings::*member)(Int);
	} call;
	call.raw = j_00021ec2;
	return (settings->*call.member)(index);
}

static __forceinline Int rva005294f0AddEntry(GameWindow *window,
	PopulateRemoteIPComboBoxEntry text,
	Int color)
{
	union
	{
		void (*raw)(void);
		Int (*function)(GameWindow *, PopulateRemoteIPComboBoxEntry, Int);
	} call;
	call.raw = j_0002f338;
	return call.function(window, text, color);
}

static __forceinline void rva005294f0SetItemData(GameWindow *window, Int item, void *data)
{
	union
	{
		void (*raw)(void);
		void (*function)(GameWindow *, Int, void *);
	} call;
	call.raw = j_0001d01b;
	call.function(window, item, data);
}

static __forceinline Bool rva005294f0MapKeyExists(StartPositionInfo *start,
	AsciiString *side)
{
	union
	{
		void (*raw)(void);
		Bool (*function)(void *, void *);
	} call;
	call.raw = j_00028f6f;
	return call.function((void *)start, (void *)side);
}

static __forceinline const PlayerTemplate *rva005294f0GetTemplate(Int index)
{
	union
	{
		void (*raw)(void);
		const PlayerTemplate *(PlayerTemplateStore::*member)(Int) const;
	} call;
	call.raw = j_00037bd2;
	return (ThePlayerTemplateStore->*call.member)(index);
}

static __forceinline void rva005294f0SetSelectedPos(GameWindow *window, Int selected,
	Bool dontHide)
{
	union
	{
		void (*raw)(void);
		void (*function)(GameWindow *, Int, Bool);
	} call;
	call.raw = j_000439c3;
	call.function(window, selected, dontHide);
}

static __forceinline void rva005294f0SetMaxDisplay(GameWindow *window, Int count)
{
	union
	{
		void (*raw)(void);
		void (*function)(GameWindow *, Int);
	} call;
	call.raw = j_00044080;
	call.function(window, count);
}

// ?refreshPlayerTeamControl@SkirmishScreenState@@QAEXH@Z
void SkirmishScreenState::refreshPlayerTeamControl(Int index)
{
	if (m_game && !m_owner->contains(m_game))
		m_game = 0;

	if (m_secondaryGame
		&& !m_owner->contains(m_secondaryGame))
		m_secondaryGame = 0;

	if (!m_game)
		return;

	GameSlot *slot = m_game->getSlot(index);
	if (!slot)
		return;

	Bool addObserver;
	if (!slot->isAI())
	{
		addObserver = true;
		if (*(const unsigned char *)((const char *)this + 0x120) & 4)
			addObserver = false;
	}
	else
		addObserver = false;

	const StartPositionInfo *start =
		((Gen_00525EE0 *)this)->bfmeGetStartPositionInfo(index);
	GameWindow *combo = m_third[index];
	Int selected = 0;
	GadgetComboBoxGetSelectedPos(combo, &selected);
	Int oldData = -1;
	if (selected >= 0)
		oldData = (Int)GadgetComboBoxGetItemData(combo, selected);

	Int numPlayerTemplates = ThePlayerTemplateStore->getPlayerTemplateCount();
	(void)oldData;
	GadgetComboBoxReset(combo);
	MultiplayerColorDefinition *def =
		TheMultiplayerSettings->getColor(-1);

	const unsigned char forceRandom =
		*(const unsigned char *)((const char *)this + 0x124);
	if ((!forceRandom && (!start || *(const Int *)((const char *)start + 0x0c) != 1))
		|| (forceRandom && start
			&& *(const Int *)((const char *)start + 0x0c) != 1))
	{
		Int newIndex = rva005294f0AddEntry(
			combo, TheGameText->fetch((const char *)0x010eb894, 0),
			def->getColor());
		GadgetComboBoxSetItemData(combo, newIndex, (void *)-1);
	}

	std::set<AsciiString> seenSides;
	if (*(const unsigned char *)((const char *)this + 0x124)
		&& start && numPlayerTemplates > 0)
	{
		Int c = 0;
		while (c < numPlayerTemplates)
		{
			const PlayerTemplate *playerTemplate =
				ThePlayerTemplateStore->getNthPlayerTemplate(c);
			if (playerTemplate && playerTemplate->isPlayableSide()
				&& !playerTemplate->isObserver())
			{
				AsciiString side;
				side.format(AsciiString("SIDE:%s"),
					rva005294f0AsciiText(playerTemplate->getSide()));
				if (seenSides.find(side) == seenSides.end())
				{
					seenSides.insert(side);
					Bool accepted;
					{
						AsciiString mapSide(
							rva005294f0AsciiText(playerTemplate->getSide()));
						accepted = rva005294f0MapKeyExists(
							(StartPositionInfo *)start, &mapSide);
					}
					if (accepted)
					{
						Bool exists = false;
						TheGameText->fetch(side, &exists);
						if (exists)
						{
							UnicodeString text = TheGameText->fetch(side);
							Int newIndex = rva005294f0AddEntry(
								combo, text, def->getColor());
							GadgetComboBoxSetItemData(
								combo, newIndex, (void *)c);
						}
					}
				}
			}
			++c;
		}
	}

	if (!start && addObserver)
	{
		MultiplayerColorDefinition *observer =
			TheMultiplayerSettings->getColor(-2);
		Int newIndex = rva005294f0AddEntry(
			combo, TheGameText->fetch((const char *)0x010eb884, 0),
			observer->getColor());
		GadgetComboBoxSetItemData(combo, newIndex, (void *)-2);
		if (newIndex == -2)
		{
			GadgetComboBoxSetSelectedPos(combo, selected, false);
			GadgetComboBoxSetMaxDisplay(combo, 10);
		}
	}
}
