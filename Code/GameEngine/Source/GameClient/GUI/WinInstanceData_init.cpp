// cl: /DNDEBUG /MD /EHsc
// readable body of ?init@WinInstanceData@@QAEXXZ: Code/GameEngine/Source/GameClient/GUI/WinInstanceData.cpp
// Open-BFME: WinInstanceData::init, retail 0x00499850, 596 bytes.
//
// The reference's body unchanged, with its draw-data loop fully unrolled --
// nine iterations of three states, in the reference's own order, which is what
// most of the 596 bytes are.
//
// It pins the whole instance-data layout on the way past: the three
// nine-entry, twelve-byte draw arrays at +0x18, +0x84 and +0xF0, the six text
// colours from +0x15C, the id, state, style, status and owner at +0x04 through
// +0x14, the image offset and font at +0x17C, the three strings at +0x188,
// +0x18C and +0x190 with the tooltip delay at +0x198, and the two display
// strings and the video buffer at +0x19C, +0x1A0 and +0x1A4.
//
// The three strings are cleared in the reference's order -- label, tooltip,
// decorated name -- which is not their order in memory, and the tooltip delay
// is stored between the second and third, exactly where the reference writes
// it. WIN_COLOR_UNDEFINED is 0xFFFFFF.

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

class DisplayString;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/DisplayStringManager.h
class DisplayStringManager
{
public:
	virtual void slot0() = 0;
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual void slot4() = 0;
	virtual void slot5() = 0;
	virtual void slot6() = 0;
	virtual void slot7() = 0;
	virtual void slot8() = 0;
	virtual void slot9() = 0;
	virtual void freeDisplayString(DisplayString *string) = 0;	// slot 10, vtable+0x28
};

extern DisplayStringManager *TheDisplayStringManager;		// 0x012F12CC

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	~AsciiString();

	void clear(void);					// retail 0x00887940

private:
	char *m_text;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/WinInstanceData.h
class WinInstanceData
{
public:
	void init(void);

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
