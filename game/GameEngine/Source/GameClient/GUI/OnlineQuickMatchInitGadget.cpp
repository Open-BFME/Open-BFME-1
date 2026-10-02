// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Iinputs/reference/shims/stringinline
// stlport
#include <algorithm>
#include <vector>
#include "StringInline.h"
//
// AptOnlineQuickMatch::InitGadgets callback, retail 0x00558FB0 (244 bytes).
// The selector strings are the five OnlineQuickMatch gadget names in BFME's
// retail string table.  The callback stores each supplied window in the
// embedded gadget state and refreshes the screen's window-manager layout.

class GameWindow { public: void winGetSize(int *, int *); };

extern "C" int __cdecl strcmp(const char *left, const char *right);

class BfmeAptGameWindow
{
public:
	virtual void slot00();

	// The callback closes/re-registers the owning APT layout through the
	// window manager after each gadget is discovered.
	unsigned char m_beforeLayout[0x30];
	void *m_layout; // +0x34
	unsigned char m_afterLayout[0x08];
};

class QuickMatchPreferences
{
public:
	virtual ~QuickMatchPreferences();
	int getColor();

private:
	unsigned char m_unmodelled[0x10];
};

class Gen_004b5a80
{
public:
	void *m(int value);
};

class GameWindowManager
{
public:
	void refreshLayout(void *layout);
};

extern GameWindowManager *TheWindowManager;
extern void gadgetComboBoxReset(GameWindow *window);
void j_0003600c(void);

struct Q4Sort00483F70
{
	void *m_state;
	bool operator()(int, int) const;
};

namespace _STL
{
template <class RandomAccessIter, class Tp, class Size, class Compare>
void __introsort_loop(RandomAccessIter, RandomAccessIter, Tp *, Size, Compare);
}

typedef bool (__cdecl *RefreshLayoutScalarCompare)(int, int);
template void _STL::__insertion_sort<int *, RefreshLayoutScalarCompare>(
	int *, int *, RefreshLayoutScalarCompare);

void __cdecl bfmeSortZV(int *, int *, int *, char (__cdecl *)(int, int));

void GameWindowManager::refreshLayout(void *layout)
{
	std::vector<GameWindow *> children;
	GameWindow **childList = (GameWindow **)((char *)layout + 0x204);

	for (GameWindow *child = *childList; child != 0;
		child = *(GameWindow **)((char *)child + 0x1f8))
	{
		children.push_back(child);
	}

	int *first = (int *)children.begin();
	int *last = (int *)children.end();
	if (first != last)
	{
		int n = last - first;
		int depth;
		for (depth = 0; n != 1; n >>= 1)
			++depth;
		Q4Sort00483F70 compare = { (void *)j_0003600c };
		_STL::__introsort_loop<int *, int, int, Q4Sort00483F70>(
			first, last, (int *)0, depth * 2, compare);
		if (last - first > 16)
		{
			_STL::__insertion_sort<int *, RefreshLayoutScalarCompare>(
				first, first + 16,
				(RefreshLayoutScalarCompare)j_0003600c);
			bfmeSortZV(first + 16, last, 0,
				(char (__cdecl *)(int, int))j_0003600c);
		}
		else
			_STL::__insertion_sort<int *, RefreshLayoutScalarCompare>(
				first, last, (RefreshLayoutScalarCompare)j_0003600c);
	}

	GameWindow **link = childList;
	GameWindow *previous = 0;
	for (std::vector<GameWindow *>::iterator it = children.begin();
		it != children.end(); ++it)
	{
		GameWindow *child = *it;
		*link = child;
		*(GameWindow **)((char *)child + 0x1fc) = previous;
		previous = *link;
		link = (GameWindow **)((char *)previous + 0x1f8);
	}
	*link = 0;
}

#pragma comment(linker, "/alternatename:?refreshLayout@GameWindowManager@@QAEXPAX@Z=?j_000412c2@@YAXXZ")
#pragma comment(linker, "/alternatename:?gadgetComboBoxReset@@YAXPAVGameWindow@@@Z=?j_00007004@@YAXXZ")

class BfmeAptScreenOnlineQuickMatch : public BfmeAptGameWindow
{
public:
	void _bfme_onInitGadget(const char *name, void *argument, GameWindow *window);

private:
	QuickMatchPreferences m_preferences;
	unsigned char m_ready;
	unsigned char m_startRequested;
	unsigned char m_pad56;
	unsigned char m_pad57;
	int m_flags;
	struct GadgetState
	{
		GameWindow *m_color;
		GameWindow *m_numPlayers;
		GameWindow *m_side;
		GameWindow *m_connectionSpeed;
		GameWindow *m_ladder;
	} m_gadgets;
};

class Image;

class ImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};

extern ImageCollection *TheMappedImageCollection;

class MultiplayerColorDefinition
{
public:
	int getColor() const
	{
		return *(const int *)((const char *)this + 0x10);
	}
};

class MultiplayerSettings
{
public:
	MultiplayerColorDefinition *getColor(int which);
	int getNumColors()
	{
		if (m_numColors == 0)
			m_numColors = *(int *)((char *)this + 0x34);
		return m_numColors;
	}

private:
	unsigned char m_padding[0x3c];
	int m_numColors;
};

extern MultiplayerSettings *TheMultiplayerSettings;

class GlobalData
{
private:
	unsigned char m_padding[0x2c];

public:
	int m_xResolution;
};

extern GlobalData *TheWritableGlobalData;

class Rva004B5AA0 { public: int m(const Image *, int, int, int); };
class Rva004B5B30 { public: void set(int); };
class BfmeThing925C { public: void bfmeGo925C(); };
class BfmeThing925D { public: void bfmeGo925D(void *); };
class BfmeThing926A { public: void bfmeGo926A(void *, void *); };
class Rva00558BE0Gadget {};

class OnlineQuickMatchColorSetup : public BfmeAptGameWindow
{
public:
	void setup();
private:
	QuickMatchPreferences m_preferences;
	unsigned char m_betweenPreferencesAndGadget[0x08];
	Rva00558BE0Gadget m_gadget;
};


void BfmeAptScreenOnlineQuickMatch::_bfme_onInitGadget(
	const char *name, void *, GameWindow *window)
{
	if( window == 0 )
		return;

	if( strcmp( name, "OnlineQuickMatch::Color" ) == 0 )
	{
		((Gen_004b5a80 *)&m_gadgets)->m((int)window);
		((OnlineQuickMatchColorSetup *)this)->setup();
		m_flags |= 1;
	}
	else if( strcmp( name, "OnlineQuickMatch::NumOfPlayers" ) == 0 )
	{
		gadgetComboBoxReset( window );
		m_gadgets.m_numPlayers = window;
		m_flags |= 4;
	}
	else if( strcmp( name, "OnlineQuickMatch::Side" ) == 0 )
	{
		gadgetComboBoxReset( window );
		m_gadgets.m_side = window;
		m_flags |= 0x20;
	}
	else if( strcmp( name, "OnlineQuickMatch::ConnectionSpeed" ) == 0 )
	{
		gadgetComboBoxReset( window );
		m_gadgets.m_connectionSpeed = window;
		m_flags |= 0x40;
	}
	else if( strcmp( name, "OnlineQuickMatch::Ladder" ) == 0 )
	{
		gadgetComboBoxReset( window );
		m_gadgets.m_ladder = window;
		m_flags |= 0x80;
	}

	TheWindowManager->refreshLayout(m_layout);
}

// Retail 0x00558BE0: ILT 0x00005F3D target; complete 341-byte RET extent.
// Function-local static image initialization is required for the retail guard
// and inline-forwarding AsciiString temporary lifetime and stack allocation.
void OnlineQuickMatchColorSetup::setup()
{
	MultiplayerColorDefinition *color;
	GameWindow *window;
	int width;
	int height;
	int colorCount;

	colorCount = TheMultiplayerSettings->getNumColors();

	((BfmeThing925C *)&m_gadget)->bfmeGo925C();
	window = *(GameWindow **)&m_gadget;
	window->winGetSize(&width, &height);

	int scale = TheWritableGlobalData->m_xResolution;
	int colorWidth = (width - (scale * 0x20 / 0x400)) * 0x400 / scale;

	for (int i = 0; i < colorCount; ++i)
	{
		color = TheMultiplayerSettings->getColor(i);
		if (color != 0)
		{
			static const Image *whiteBox = TheMappedImageCollection->findImageByName(AsciiString("AptWhiteBox"));

			int row = ((Rva004B5AA0 *)&m_gadget)->m(
				whiteBox, colorWidth, 0x14, color->getColor());
			((BfmeThing926A *)&m_gadget)->bfmeGo926A((void *)row, (void *)i);
		}
	}

	((Rva004B5B30 *)&m_gadget)->set(colorCount * 0x1e);
	((BfmeThing925D *)&m_gadget)->bfmeGo925D((void *)m_preferences.getColor());
}
