// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/stringinline
// GameSpyInfo::addText, retail 0x00625570.
// The body uses m_textWindows at +0x6E0 and InGameUI::message at vtable +0x34.

#include "StringInline.h"

typedef bool Bool;
typedef int Int;
typedef int Color;

class GameWindow;

class GameSpyStagingRoom
{
public:
	Bool isInGame() const { return m_inGame; }
	Bool isGameInProgress() const { return m_inProgress; }

private:
	char m_pad[0x0C];
	Bool m_inGame;
	Bool m_inProgress;
};

extern GameSpyStagingRoom *TheGameSpyGame;

class InGameUI
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2C() = 0;
	virtual void slot30() = 0;
	virtual void message( UnicodeString message, ... );
};

extern InGameUI *TheInGameUI;

extern Int GadgetListBoxAddEntryText( GameWindow *listbox, UnicodeString text,
	Color color, Int row, Int column, Bool overwrite );
extern void GadgetListBoxSetItemData( GameWindow *listbox, void *data,
	Int row, Int column = 0 );

struct TextWindowTreeNode
{
	Int m_color;
	TextWindowTreeNode *m_parent;
	TextWindowTreeNode *m_left;
	TextWindowTreeNode *m_right;
	GameWindow *m_value;
};

class TextWindowIterator
{
public:
	TextWindowIterator( TextWindowTreeNode *node ) : m_node( node ) {}
	GameWindow *operator*() const { return m_node->m_value; }

private:
	TextWindowTreeNode *m_node;
};

class TextWindowSet
{
public:
	Bool empty() const { return m_nodeCount == 0; }

	TextWindowIterator begin() const
	{
		return TextWindowIterator( m_header->m_left );
	}

private:
	TextWindowTreeNode *m_header;
	unsigned int m_nodeCount;
	Int m_compare;
};

typedef char TextWindowSetSizeCheck[sizeof(TextWindowSet) == 12 ? 1 : -1];

class GameSpyInfo
{
public:
	virtual Int addText( UnicodeString message, Color c, GameWindow *win );

private:
	char m_pad[0x6DC];
	TextWindowSet m_textWindows;
};

Int GameSpyInfo::addText( UnicodeString message, Color c, GameWindow *win )
{
	if (TheGameSpyGame && TheGameSpyGame->isInGame() && TheGameSpyGame->isGameInProgress())
	{
		TheInGameUI->message(message);
	}

	if (!win)
	{
		if (m_textWindows.empty())
			return -1;

		win = *m_textWindows.begin();
	}

	Color color = c;
	Int index = GadgetListBoxAddEntryText(win, message, color, -1, -1, true);
	GadgetListBoxSetItemData(win, (void *)-1, index);

	return index;
}
