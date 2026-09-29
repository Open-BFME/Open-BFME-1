// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport

typedef bool Bool;
typedef int Int;
typedef int Color;

#include <vector>
#include "ascii_string.h"

class GameWindow
{
public:
	void *winGetUserData(void);
};

class Image;

class ImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};

class MultiplayerColorDefinition
{
public:
	Color getColor() const
	{
		return *(const Color *)((const char *)this + 0x10);
	}
};

class MultiplayerColorList
{
public:
	Int size() const
	{
		return m_size;
	}

	Int m_size;
	char m_unmodelled[4];
};

class MultiplayerSettings
{
public:
	Int getNumColors()
	{
		if (m_numColors == 0)
			m_numColors = m_colorList.size();
		return m_numColors;
	}

	MultiplayerColorDefinition *getColor(Int which);

private:
	char m_unmodelled[0x34];
	MultiplayerColorList m_colorList;
	Int m_numColors;
};

class GameSlot
{
public:
	Int getColor() const
	{
		return *(const Int *)((const char *)this + 0x0C);
	}
	Int getPlayerTemplate() const
	{
		return *(const Int *)((const char *)this + 0x14);
	}
};

class GameInfo
{
public:
	GameSlot *getSlot(Int slot);
	const GameSlot *getConstSlot(Int slot) const;
};

extern MultiplayerSettings *TheMultiplayerSettings;
extern ImageCollection *TheMappedImageCollection;
extern Color g_012B76F4;

extern Int GadgetListBoxGetNumEntries(GameWindow *listbox);
extern void *GadgetListBoxGetItemData(GameWindow *listbox, Int row, Int column);

// STLport's vector<bool> operator==, matched as bfmeBitVectorEqual.  Its body
// is visible here as it was in the retail TU: MSVC 7.1 then sees that neither
// vector escapes, and keeps the listed-colour vector's begin iterator in
// registers across the list-box calls exactly as retail does.  noinline keeps
// the call bound to the matched symbol.
bool bfmeBitIteratorEqual(_STL::_Bit_const_iterator first,
	_STL::_Bit_const_iterator last, _STL::_Bit_const_iterator other);

__declspec(noinline) bool bfmeBitVectorEqual(const _STL::vector<bool> &first,
	const _STL::vector<bool> &second)
{
	return first.size() == second.size() &&
		bfmeBitIteratorEqual(first.begin(), first.end(), second.begin());
}

// Image combo-box adapter methods.  Each retail body is matched under an
// address-derived owner; the adapter is one GameWindow pointer copied from
// the state's combo slot (0x004B5A60) and released by an empty out-of-line
// destructor (0x004B5A70).  The image add is called directly: routing it
// through an inline wrapper moves its argument loads behind the pushes.
class Gen_004b5a60 { public: void *m(void *value); };
class Gen_004b5a70 { public: void m(); };
class BfmeThing925C { public: void bfmeGo925C(); };
class BfmeThing925D { public: void bfmeGo925D(void *value); };
class BfmeThing925E { public: Int bfmeGo925E(); };
class BfmeThing926A { public: void bfmeGo926A(void *item, void *data); };
class Rva004B5AA0 { public: Int m(const Image *image, Int height, Int width, Int color); };
class Rva004B5B30 { public: void set(Int value); };

struct Rva005284F0ComboData
{
	unsigned int m_00;
	GameWindow *m_04;
	GameWindow *m_listBox;
};

struct Rva005284F0Combo
{
	GameWindow *m_window;

	Rva005284F0Combo(void *value) { ((Gen_004b5a60 *)this)->m(value); }
	~Rva005284F0Combo() { ((Gen_004b5a70 *)this)->m(); }
	Int getLength() { return ((BfmeThing925E *)this)->bfmeGo925E(); }
	void reset() { ((BfmeThing925C *)this)->bfmeGo925C(); }
	void setItemData(Int item, Int data)
	{
		((BfmeThing926A *)this)->bfmeGo926A((void *)item, (void *)data);
	}
	void setSelected(Int item) { ((BfmeThing925D *)this)->bfmeGo925D((void *)item); }
	void setScale(Int value) { ((Rva004B5B30 *)this)->set(value); }
};

class SkirmishScreenOwner
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual Bool contains(GameInfo *game) = 0;
};

class SkirmishScreenState
{
public:
	virtual void slot00() = 0;

	Bool rebuildColorCombo005284F0(Int index);

private:
	SkirmishScreenOwner *m_owner;
	GameInfo *m_game;
	GameInfo *m_secondaryGame;
	unsigned char m_unmodelled10[0x78];
	GameWindow *m_colorCombos[8];
};

// Retail 0x005284F0, reached from matched SkirmishScreenState::apply
// (0x0052AAD0) once per slot through ILT 0x0003B1F1.  It rebuilds one slot's
// colour combo: the colours no other slot holds, compared with the list
// box's current item data, and the combo is repopulated with the
// AptRandomColor / AptWhiteBox images only when that set changed.  It returns
// whether it repopulated.  The ZH twin is GUIUtil PopulateColorComboBox; the
// method name keeps the address because no evidence names it (see
// targets/game/reverse/identity_evidence/005284f0-refreshplayerslot-pin.md).
// ?rebuildColorCombo005284F0@SkirmishScreenState@@QAE_NH@Z
Bool SkirmishScreenState::rebuildColorCombo005284F0(Int index)
{
	if (m_game && !m_owner->contains(m_game))
		m_game = 0;

	if (m_secondaryGame && !m_owner->contains(m_secondaryGame))
		m_secondaryGame = 0;

	if (!m_game)
		return false;

	Int numColors = TheMultiplayerSettings->getNumColors();
	_STL::vector<bool> availableColors(numColors, true);
	Int numAvailable = numColors;

	for (Int i = 0; i < 8; ++i)
	{
		GameSlot *slot = m_game->getSlot(i);
		if (slot && i != index && slot->getColor() >= 0
			&& slot->getColor() < numColors)
		{
			availableColors[slot->getColor()] = false;
			--numAvailable;
		}
	}

	Rva005284F0Combo combo(&m_colorCombos[index]);
	GameWindow *listBox =
		((Rva005284F0ComboData *)combo.m_window->winGetUserData())->m_listBox;
	if (listBox)
	{
		Int count = GadgetListBoxGetNumEntries(listBox);
		if (count == numAvailable + 1)
		{
			_STL::vector<bool> listedColors(numColors, false);
			for (Int row = 0; row < count; ++row)
			{
				Int color = (Int)GadgetListBoxGetItemData(listBox, row, 0);
				if (color < 0)
					continue;
				if (color >= listedColors.size())
					break;
				listedColors[color] = true;
			}

			if (bfmeBitVectorEqual(listedColors, availableColors))
				return false;
		}
	}

	Bool wasObserver = (combo.getLength() == 1);
	combo.reset();

	MultiplayerColorDefinition *def = TheMultiplayerSettings->getColor(-1);
	static const Image *randomImage =
		TheMappedImageCollection->findImageByName(AsciiString("AptRandomColor"));
	Int newIndex = ((Rva004B5AA0 *)&combo)->m(randomImage, 20, 20, g_012B76F4);
	combo.setItemData(newIndex, -1);

	if (m_game->getConstSlot(index)->getPlayerTemplate() == -2)
	{
		combo.setSelected(0);
		return true;
	}

	for (Int c = 0; c < numColors; ++c)
	{
		def = TheMultiplayerSettings->getColor(c);
		if (!def || availableColors[c] == false)
			continue;

		static const Image *colorImage =
			TheMappedImageCollection->findImageByName(AsciiString("AptWhiteBox"));
		newIndex = ((Rva004B5AA0 *)&combo)->m(colorImage, 20, 20, def->getColor());
		combo.setItemData(newIndex, c);
	}

	combo.setScale(numColors * 30);
	if (wasObserver)
		combo.setSelected(0);
	return true;
}
