// cl: /DNDEBUG /MD /EHsc
// readable body of ?init@WinInstanceData@@QAEXXZ: Code/GameEngine/Source/GameClient/GUI/WinInstanceData.cpp
// readable body of ?setText@WinInstanceData@@QAEXVUnicodeString@@@Z: Code/GameEngine/Source/GameClient/GUI/WinInstanceData.cpp
// readable body of ?setTooltipText@WinInstanceData@@QAEXVUnicodeString@@@Z: Code/GameEngine/Source/GameClient/GUI/WinInstanceData.cpp
//
// WinInstanceData::init (retail 0x00499850, 596 bytes), ::setText (0x00499D60)
// and ::setTooltipText share one layout and one manager global, and each used
// to re-declare its own slice of both. init pins the whole instance-data
// layout, so the two setters' `unsigned char m_unreconstructed_00[0x19C]`
// padding is redundant here: their members are the same +0x19C and +0x1A0 that
// init writes.
//
// The manager's virtual table is the other thing that had to agree and did not
// check: the setters knew slot 9 (vtable+0x24) as newDisplayString, init knew
// slot 10 (vtable+0x28) as freeDisplayString. Distinct slots, so the two
// namings compose -- init's unnamed slot9 was the setters' newDisplayString.
//
// init: the reference's body unchanged, with its draw-data loop fully unrolled
// -- nine iterations of three states, in the reference's own order, which is
// what most of the 596 bytes are. The three strings are cleared in the
// reference's order -- label, tooltip, decorated name -- which is not their
// order in memory, and the tooltip delay is stored between the second and
// third, exactly where the reference writes it. WIN_COLOR_UNDEFINED is
// 0xFFFFFF.
//
// setText/setTooltipText: retail's two bodies are byte-identical apart from the
// member offset and their relocations. The display string is created on first
// use through the manager global, then given the text through DisplayString's
// second virtual. The by-value parameter is copied for that call and destroyed
// here at the end, which is MSVC's callee-destroys rule for value parameters.
// Private constructors on StringBase are what mangle its copy and destructor to
// ??0?$StringBase@G@@AAE@ABV0@@Z and ??1?$StringBase@G@@AAE@XZ.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

typedef UnsignedInt Color;

enum { MAX_DRAW_DATA = 9 };
enum { WIN_COLOR_UNDEFINED = 0xFFFFFF };
enum { WIN_STATUS_NONE = 0 };

class Image;
class GameWindow;
class GameFont;
class VideoBuffer;

struct ICoord2D { Int x, y; };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/WinInstanceData.h
struct WinDrawData
{
	const Image *image;
	Color color;
	Color borderColor;
};

struct WinTextDrawData
{
	Color color;
	Color borderColor;
};

class UnicodeString;

template <class T>
class StringBase
{
private:
	friend class UnicodeString;

	StringBase(const StringBase<T> &other);		///< body at 0x00888400
	~StringBase();								///< body at 0x008881D0

	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString : public StringBase<unsigned short>
{
public:
	UnicodeString(const UnicodeString &other) : StringBase<unsigned short>(other) {}
	~UnicodeString() {}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	~AsciiString();

	void clear(void);					// retail 0x00887940

private:
	char *m_text;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/DisplayString.h
class DisplayString
{
public:
	virtual void displayStringSlot0();
	virtual void setText(UnicodeString text);	// vtable +0x04
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/DisplayStringManager.h
class DisplayStringManager
{
public:
	virtual void managerSlot0();
	virtual void managerSlot1();
	virtual void managerSlot2();
	virtual void managerSlot3();
	virtual void managerSlot4();
	virtual void managerSlot5();
	virtual void managerSlot6();
	virtual void managerSlot7();
	virtual void managerSlot8();
	virtual DisplayString *newDisplayString();			// vtable +0x24
	virtual void freeDisplayString(DisplayString *string);	// vtable +0x28
};

extern DisplayStringManager *TheDisplayStringManager;		// 0x012F12CC

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/WinInstanceData.h
class WinInstanceData
{
public:
	void init(void);
	void setText(UnicodeString text);
	void setTooltipText(UnicodeString tip);

	char m_bfme_head[4];					// this+0x00, untouched
	Int m_id;						// this+0x04
	Int m_state;						// this+0x08
	UnsignedInt m_style;					// this+0x0C
	UnsignedInt m_status;					// this+0x10
	GameWindow *m_owner;					// this+0x14

	WinDrawData m_enabledDrawData[MAX_DRAW_DATA];		// this+0x18
	WinDrawData m_disabledDrawData[MAX_DRAW_DATA];		// this+0x84
	WinDrawData m_hiliteDrawData[MAX_DRAW_DATA];		// this+0xF0

	WinTextDrawData m_enabledText;				// this+0x15C
	WinTextDrawData m_disabledText;				// this+0x164
	WinTextDrawData m_hiliteText;				// this+0x16C

	char m_bfme_mid[0x17C - 0x174];				// this+0x174, untouched
	ICoord2D m_imageOffset;					// this+0x17C
	GameFont *m_font;					// this+0x184

	AsciiString m_textLabelString;				// this+0x188
	AsciiString m_decoratedNameString;			// this+0x18C
	AsciiString m_tooltipString;				// this+0x190
	char m_bfme_pad[4];					// this+0x194, untouched
	Int m_tooltipDelay;					// this+0x198

	DisplayString *m_text;					// this+0x19C
	DisplayString *m_tooltip;				// this+0x1A0
	VideoBuffer *m_videoBuffer;				// this+0x1A4
};

// ?init@WinInstanceData@@QAEXXZ
void WinInstanceData::init( void )
{
	Int i;

	// init our draw data images/colors for the states
	for( i = 0; i < MAX_DRAW_DATA; i++ )
	{

		m_enabledDrawData[ i ].image = 0;
		m_enabledDrawData[ i ].color = WIN_COLOR_UNDEFINED;
		m_enabledDrawData[ i ].borderColor = WIN_COLOR_UNDEFINED;

		m_disabledDrawData[ i ].image = 0;
		m_disabledDrawData[ i ].color = WIN_COLOR_UNDEFINED;
		m_disabledDrawData[ i ].borderColor = WIN_COLOR_UNDEFINED;

		m_hiliteDrawData[ i ].image = 0;
		m_hiliteDrawData[ i ].color = WIN_COLOR_UNDEFINED;
		m_hiliteDrawData[ i ].borderColor = WIN_COLOR_UNDEFINED;

	}  // end for i

	// initialize text colors
	m_enabledText.color					= WIN_COLOR_UNDEFINED;
	m_enabledText.borderColor		= WIN_COLOR_UNDEFINED;
	m_disabledText.color				= WIN_COLOR_UNDEFINED;
	m_disabledText.borderColor	= WIN_COLOR_UNDEFINED;
	m_hiliteText.color					= WIN_COLOR_UNDEFINED;
	m_hiliteText.borderColor		= WIN_COLOR_UNDEFINED;

	m_id = 0;
	m_state = 0;
	m_style = 0;
	m_status = WIN_STATUS_NONE;
	m_owner = 0;
	m_textLabelString.clear();
	m_tooltipString.clear();
	m_tooltipDelay = -1; ///< default value
	m_decoratedNameString.clear();

	m_imageOffset.x = 0;
	m_imageOffset.y = 0;

	// reset all data for the text display strings and font for window
	m_font = 0;
	if( m_text )
	{

		TheDisplayStringManager->freeDisplayString( m_text );
		m_text = 0;

	}  // end if
	if( m_tooltip )
	{

		TheDisplayStringManager->freeDisplayString( m_tooltip );
		m_tooltip = 0;

	}  // end if

	m_videoBuffer = 0;


}  // end init

// ?setText@WinInstanceData@@QAEXVUnicodeString@@@Z
void WinInstanceData::setText(UnicodeString text)
{
	if (m_text == 0)
	{
		m_text = TheDisplayStringManager->newDisplayString();
	}

	m_text->setText(text);
}

// ?setTooltipText@WinInstanceData@@QAEXVUnicodeString@@@Z
void WinInstanceData::setTooltipText(UnicodeString tip)
{
	if (m_tooltip == 0)
	{
		m_tooltip = TheDisplayStringManager->newDisplayString();
	}

	m_tooltip->setText(tip);
}
