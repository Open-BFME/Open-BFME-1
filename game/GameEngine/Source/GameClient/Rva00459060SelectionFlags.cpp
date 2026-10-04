// cl: /DNDEBUG /DWIN32 /D_WINDOWS /Iinputs/reference/shims/mouselayout /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// This caller only needs declarations; avoid emitting unused STL iostream data.
#define _STLP_NO_IOSTREAMS
#define Matrix4x4 Matrix4
#include "GameClient/InGameUI.h"

class Drawable;

struct BfmeDrawableListNode
{
	BfmeDrawableListNode *m_next;
	BfmeDrawableListNode *m_previous;
	Drawable *m_drawable;
};

class BfmeDrawableList
{
public:
	class const_iterator
	{
	public:
		const_iterator(BfmeDrawableListNode *node) : m_node(node) { }

		bool operator!=(const const_iterator &other) const
		{
			return m_node != other.m_node;
		}

		Drawable *operator*() const
		{
			return m_node->m_drawable;
		}

		const_iterator &operator++()
		{
			m_node = m_node->m_next;
			return *this;
		}

	private:
		BfmeDrawableListNode *m_node;
	};

	const_iterator begin() const
	{
		return const_iterator(m_node->m_next);
	}

	const_iterator end() const
	{
		return const_iterator(m_node);
	}

private:
	BfmeDrawableListNode *m_node;
};

class Object
{
public:
	bool b_001c4710() const;
	bool bfmeHasMineClearingCommand() const;
};

// Retain the witnessed virtual-slot view for the still-opaque slot BC.
class Rva00459060UI
{
public:
	#define BFME_UI_SLOT(n) virtual void slot##n() = 0;
	BFME_UI_SLOT(00) BFME_UI_SLOT(01) BFME_UI_SLOT(02) BFME_UI_SLOT(03)
	BFME_UI_SLOT(04) BFME_UI_SLOT(05) BFME_UI_SLOT(06) BFME_UI_SLOT(07)
	BFME_UI_SLOT(08) BFME_UI_SLOT(09) BFME_UI_SLOT(10) BFME_UI_SLOT(11)
	BFME_UI_SLOT(12) BFME_UI_SLOT(13) BFME_UI_SLOT(14) BFME_UI_SLOT(15)
	BFME_UI_SLOT(16) BFME_UI_SLOT(17) BFME_UI_SLOT(18) BFME_UI_SLOT(19)
	BFME_UI_SLOT(20) BFME_UI_SLOT(21) BFME_UI_SLOT(22) BFME_UI_SLOT(23)
	BFME_UI_SLOT(24) BFME_UI_SLOT(25) BFME_UI_SLOT(26) BFME_UI_SLOT(27)
	BFME_UI_SLOT(28) BFME_UI_SLOT(29) BFME_UI_SLOT(30) BFME_UI_SLOT(31)
	BFME_UI_SLOT(32) BFME_UI_SLOT(33) BFME_UI_SLOT(34) BFME_UI_SLOT(35)
	BFME_UI_SLOT(36) BFME_UI_SLOT(37) BFME_UI_SLOT(38) BFME_UI_SLOT(39)
	BFME_UI_SLOT(40) BFME_UI_SLOT(41) BFME_UI_SLOT(42) BFME_UI_SLOT(43)
	BFME_UI_SLOT(44) BFME_UI_SLOT(45) BFME_UI_SLOT(46)
	virtual void *slotBC();
	BFME_UI_SLOT(48) BFME_UI_SLOT(49) BFME_UI_SLOT(50) BFME_UI_SLOT(51)
	BFME_UI_SLOT(52) BFME_UI_SLOT(53) BFME_UI_SLOT(54) BFME_UI_SLOT(55)
	BFME_UI_SLOT(56)
	virtual void deselectDrawable(Drawable *draw) = 0;
	BFME_UI_SLOT(58) BFME_UI_SLOT(59) BFME_UI_SLOT(60) BFME_UI_SLOT(61)
	BFME_UI_SLOT(62)
	virtual const BfmeDrawableList *getAllSelectedDrawables() const = 0;
	#undef BFME_UI_SLOT
};

class Rva00459060SelectionState
{
public:
	unsigned char m_padding00[0x18];
	unsigned int m_flags;
};

extern InGameUI *TheInGameUI;
extern "C" int Rva00458FC0(bool mode);

int Rva00458FC0(bool mode)
{
	int flags = 0;
	// Retail +9 calls ILT 0x000221E2 -> 0x0043EC00 (ECX this, Bool in AL).
	if (!TheInGameUI->areSelectedObjectsControllable())
		return flags;

	const BfmeDrawableList *selected = ((Rva00459060UI *)TheInGameUI)->getAllSelectedDrawables();
	for (BfmeDrawableList::const_iterator it = selected->begin(); it != selected->end(); ++it)
	{
		Drawable *draw = *it;
		if (draw == 0)
			continue;

		Object *object = *(Object **)((char *)draw + 0xfc);
		if (object == 0)
			continue;

		if (object->b_001c4710())
			flags |= 8;
		if (object->bfmeHasMineClearingCommand())
			flags |= 0x200;
		if ((flags & 0x208) != 0)
			break;

	}
	return flags;
}

int Rva00459060(bool mode)
{
	int flags = 0x44;
	if (mode)
	{
		flags = 0x64;
	}
	Rva00459060SelectionState *state =
		(Rva00459060SelectionState *)((Rva00459060UI *)TheInGameUI)->slotBC();
	if (state != 0)
	{
		if ((state->m_flags & 0x10) != 0)
		{
			flags |= 8;
		}
		if ((state->m_flags & 0x200000) != 0)
		{
			flags |= 0x200;
		}
	}
	else
	{
		flags |= Rva00458FC0(mode);
	}
	return flags;
}
