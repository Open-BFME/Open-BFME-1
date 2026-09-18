// ?refreshPlayerSlot@SkirmishScreenState@@QAEXH@Z
// partial score=0.33 date=2026-09-17
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC
// stlport
//
// Retail 0x005284F0 is the body reached by the refreshPlayerSlot ILT.  The
// matched apply caller proves the owner and method identity.  The routine is
// the BFME color-entry refresh: it computes the colors available to one slot,
// compares them with the current list data, and rebuilds the image entries
// only when that bit vector changed.

#include <list>
#include <set>
#include <vector>

typedef bool Bool;
typedef int Int;

class GameInfo;
class GameSlot;
class GameWindow;
class Image;
class ImageCollection;
class MultiplayerSettings;
class MultiplayerColorDefinition;

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
	virtual Bool contains(GameInfo *) = 0;
};

class GameSlot
{
};

class GameInfo
{
};

class GameWindow
{
};

class Image
{
};

class ImageCollection
{
};

class MultiplayerSettings
{
};

class MultiplayerColorDefinition
{
};

// The two temporary strings use the BFME 8-byte string header.  Their inline
// wrapper destructor is the releaseBuffer callee seen twice in the retail
// body.
class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString(const char *text);
	~BFMERetailAsciiString()
	{
		releaseBuffer();
	}
	void releaseBuffer();

	void *m_data;
};

struct Rva005284F0Combo
{
	GameWindow *m_window;
};

extern void j_00009084();
extern void j_00010857();
extern void j_00013115();
extern void j_0001b90f();
extern void j_0001d606();
extern void j_0001ec18();
extern void j_00021ec2();
extern void j_00026be8();
extern void j_00029460();
extern void j_00035b02();
extern void j_00036f34();
extern void j_0003b1a1();
extern void j_0003eb53();
extern void j_000436da();
extern void j_00046a01();
extern void j_00046dbc();
extern void j_00046538();
extern void j_000477df();
extern void j_00047e2e();
extern void j_00082e5f0();
extern void j_000881eb0();
extern void j_000887940();
extern void j_000888bc0();

static GameSlot *rva005284f0SlotAt(GameInfo *game, Int index)
{
	union
	{
		void (*raw)(void);
		GameSlot *(GameInfo::*member)(Int);
	} call;
	call.raw = j_0001ec18;
	return (game->*call.member)(index);
}

static GameSlot *rva005284f0ConstSlotAt(GameInfo *game, Int index)
{
	union
	{
		void (*raw)(void);
		GameSlot *(GameInfo::*member)(Int);
	} call;
	call.raw = j_00029460;
	return (game->*call.member)(index);
}

static void *rva005284f0UserData(GameWindow *window)
{
	union
	{
		void (*raw)(void);
		void *(GameWindow::*member)();
	} call;
	call.raw = j_00046538;
	return (window->*call.member)();
}

static void rva005284f0CopyCombo(Rva005284F0Combo *combo,
	GameWindow *window)
{
	union
	{
		void (*raw)(void);
		void *(Rva005284F0Combo::*member)(void *);
	} call;
	call.raw = j_0001b90f;
	(combo->*call.member)(window);
}

static Int rva005284f0ListLength(Rva005284F0Combo *combo)
{
	union
	{
		void (*raw)(void);
		Int (Rva005284F0Combo::*member)();
	} call;
	call.raw = j_000436da;
	return (combo->*call.member)();
}

static void *rva005284f0ListItemData(GameWindow *listbox, Int row,
	Int column)
{
	union
	{
		void (*raw)(void);
		void *(*function)(GameWindow *, Int, Int);
	} call;
	call.raw = j_00009084;
	return call.function(listbox, row, column);
}

static Int rva005284f0ListEntryCount(GameWindow *listbox)
{
	union
	{
		void (*raw)(void);
		Int (*function)(GameWindow *);
	} call;
	call.raw = j_00010857;
	return call.function(listbox);
}

static MultiplayerColorDefinition *rva005284f0Color(
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

static const Image *rva005284f0Image(ImageCollection *images,
	const BFMERetailAsciiString &name)
{
	union
	{
		void (*raw)(void);
		const Image *(ImageCollection::*member)(const BFMERetailAsciiString &);
	} call;
	call.raw = j_0001d606;
	return (images->*call.member)(name);
}

static Int rva005284f0AddImage(Rva005284F0Combo *combo,
	const Image *image, Int width, Int height, Int color)
{
	union
	{
		void (*raw)(void);
		Int (Rva005284F0Combo::*member)(const Image *, Int, Int, Int);
	} call;
	call.raw = j_00026be8;
	return (combo->*call.member)(image, width, height, color);
}

static void rva005284f0SetItemData(Rva005284F0Combo *combo,
	Int item, void *data)
{
	union
	{
		void (*raw)(void);
		void (Rva005284F0Combo::*member)(Int, void *);
	} call;
	call.raw = j_00035b02;
	(combo->*call.member)(item, data);
}

static void rva005284f0SetSelection(Rva005284F0Combo *combo, void *data)
{
	union
	{
		void (*raw)(void);
		void (Rva005284F0Combo::*member)(void *);
	} call;
	call.raw = j_00046dbc;
	(combo->*call.member)(data);
}

static void rva005284f0ResetCombo(Rva005284F0Combo *combo)
{
	union
	{
		void (*raw)(void);
		void (Rva005284F0Combo::*member)();
	} call;
	call.raw = j_00046a01;
	(combo->*call.member)();
}

static void rva005284f0SetExtent(Rva005284F0Combo *combo, Int extent)
{
	union
	{
		void (*raw)(void);
		void (Rva005284F0Combo::*member)(Int);
	} call;
	call.raw = j_00036f34;
	(combo->*call.member)(extent);
}

static Bool rva005284f0SameBits(const _STL::vector<bool> &first,
	const _STL::vector<bool> &second)
{
	union
	{
		void (*raw)(void);
		Bool (*function)(const _STL::vector<bool> &,
			const _STL::vector<bool> &);
	} call;
	call.raw = j_000477df;
	return call.function(first, second);
}

static void rva005284f0FinishCombo(Rva005284F0Combo *combo)
{
	union
	{
		void (*raw)(void);
		void (Rva005284F0Combo::*member)();
	} call;
	call.raw = j_0003eb53;
	(combo->*call.member)();
}

class SkirmishScreenState
{
public:
	void refreshPlayerSlot(Int index);

	public:
	unsigned char m_vtable[4];
	SkirmishScreenOwner *m_owner;
	GameInfo *m_game;
	GameInfo *m_secondaryGame;
	unsigned char m_unmodelled10[0x78];
	GameWindow *m_playerSlotCombos[8];
};

typedef char SkirmishScreenState_player_slot_combo_offset
	[(offsetof(SkirmishScreenState, m_playerSlotCombos) == 0x88) ? 1 : -1];

// ?refreshPlayerSlot@SkirmishScreenState@@QAEXH@Z
void SkirmishScreenState::refreshPlayerSlot(Int index)
{
	if (m_game && !m_owner->contains(m_game))
		m_game = 0;

	if (m_secondaryGame && !m_owner->contains(m_secondaryGame))
		m_secondaryGame = 0;

	if (!m_game)
		return;

	MultiplayerSettings *settings =
		*(MultiplayerSettings **)0x012ED5FC;
	Int numColors = *(Int *)((unsigned char *)settings + 0x3c);
	if (!numColors)
	{
		numColors = *(Int *)((unsigned char *)settings + 0x34);
		*(Int *)((unsigned char *)settings + 0x3c) = numColors;
	}

	_STL::vector<bool> availableColors(numColors, true);
	for (Int slotIndex = 0; slotIndex < 8; ++slotIndex)
	{
		GameSlot *slot = rva005284f0SlotAt(m_game, slotIndex);
		if (!slot || slotIndex == index)
			continue;

		Int color = *(Int *)((unsigned char *)slot + 0x0c);
		if (color >= 0 && color < numColors)
			availableColors[color] = false;
	}

	Rva005284F0Combo combo;
	rva005284f0CopyCombo(&combo, m_playerSlotCombos[index]);
	GameWindow *userData = (GameWindow *)
		rva005284f0UserData(combo.m_window);
	GameWindow *listbox = userData ?
		*(GameWindow **)((unsigned char *)userData + 8) : 0;
	Int oldCount = listbox ? rva005284f0ListEntryCount(listbox) : 0;
	Bool wasObserver = (rva005284f0ListLength(&combo) == 1);

	_STL::vector<bool> listedColors;
	listedColors.resize(numColors);
	if (listbox && oldCount == numColors - 7)
	{
		for (Int row = 0; row < oldCount; ++row)
		{
			Int color = (Int)rva005284f0ListItemData(listbox, row, 0);
			if (color >= 0 && color < numColors)
				listedColors[color] = true;
		}
	}

	if (rva005284f0SameBits(listedColors, availableColors))
	{
		rva005284f0FinishCombo(&combo);
		return;
	}
	rva005284f0ResetCombo(&combo);

	const Image *randomImage = *(const Image **)0x012F49DC;
	if ((*(Int *)0x012F49E0 & 1) == 0)
	{
		*(Int *)0x012F49E0 |= 1;
		BFMERetailAsciiString imageName((const char *)0x01106C6C);
		randomImage = rva005284f0Image(
			*(ImageCollection **)0x012F6924, imageName);
		*(const Image **)0x012F49DC = randomImage;
	}

	Int entry = rva005284f0AddImage(&combo, randomImage, 0x14, 0x14,
		*(Int *)0x012B76F4);
	rva005284f0SetItemData(&combo, entry, (void *)-1);

	GameSlot *slot = rva005284f0ConstSlotAt(m_game, index);
	if (slot && *(Int *)((unsigned char *)slot + 0x14) == -2)
		rva005284f0SetSelection(&combo, 0);

	for (Int colorIndex = 0; colorIndex < numColors; ++colorIndex)
	{
		MultiplayerColorDefinition *def =
			rva005284f0Color(settings, colorIndex);
		if (!def || !availableColors[colorIndex])
			continue;

		const Image *colorImage = *(const Image **)0x012F49D8;
		if ((*(Int *)0x012F49E0 & 2) == 0)
		{
			*(Int *)0x012F49E0 |= 2;
			BFMERetailAsciiString imageName((const char *)0x01106C5C);
			colorImage = rva005284f0Image(
				*(ImageCollection **)0x012F6924, imageName);
			*(const Image **)0x012F49D8 = colorImage;
		}

		entry = rva005284f0AddImage(&combo, colorImage, 0x14, 0x14,
			*(Int *)((unsigned char *)def + 0x10));
		rva005284f0SetItemData(&combo, entry, (void *)colorIndex);
	}

	rva005284f0SetExtent(&combo, numColors * 0x1e);
	if (wasObserver)
		rva005284f0SetSelection(&combo, 0);
	rva005284f0FinishCombo(&combo);
}
