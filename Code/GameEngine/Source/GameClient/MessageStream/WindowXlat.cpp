// cl: /DNDEBUG /MD /EHs-c-
// Open-BFME5: WindowXlat.cpp's rawMouseToWindowMessage, retail 0x005B9B94,
// zh_sweep packet 005b9b94.
//
// The reference body ports unchanged. What had to be established is that both
// enums it switches between survived into BFME with Zero Hour's numbering, and
// the retail jump table says they did. It covers 3..19 with three holes -- 7, 9
// and 17 -- and those are exactly MSG_RAW_MOUSE_LEFT_CLICK, the unused slot
// between the left and middle groups, and MSG_RAW_MOUSE_RIGHT_CLICK, none of
// which this switch handles. The message numbering is confirmed independently
// by message_stream_commandName.cpp, which names 3 through 19 the same way.
//
// The values the arms return pin the other enum: 24 for a mouse position, 5/6/8
// for the left group, 9/10/12 for the middle, 13/14/16 for the right, and
// 19/20 for the wheel. That is Zero Hour's GameWindowMessage exactly, counting
// GWM_NONE = 0 through GWM_MOUSE_POS = 24.
//
// Its own TU because BFME has no WindowXlat.cpp yet.

typedef int Int;

union GameMessageArgumentType
{
	Int integer;
	void *pointer;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/MessageStream.h
class GameMessage
{
public:
	enum Type
	{
		MSG_RAW_MOUSE_POSITION					= 3,
		MSG_RAW_MOUSE_LEFT_BUTTON_DOWN			= 4,
		MSG_RAW_MOUSE_LEFT_DOUBLE_CLICK			= 5,
		MSG_RAW_MOUSE_LEFT_BUTTON_UP			= 6,
		MSG_RAW_MOUSE_LEFT_DRAG					= 8,
		MSG_RAW_MOUSE_MIDDLE_BUTTON_DOWN		= 10,
		MSG_RAW_MOUSE_MIDDLE_DOUBLE_CLICK		= 11,
		MSG_RAW_MOUSE_MIDDLE_BUTTON_UP			= 12,
		MSG_RAW_MOUSE_MIDDLE_DRAG				= 13,
		MSG_RAW_MOUSE_RIGHT_BUTTON_DOWN			= 14,
		MSG_RAW_MOUSE_RIGHT_DOUBLE_CLICK		= 15,
		MSG_RAW_MOUSE_RIGHT_BUTTON_UP			= 16,
		MSG_RAW_MOUSE_RIGHT_DRAG				= 18,
		MSG_RAW_MOUSE_WHEEL						= 19
	};

	Type getType( void ) const { return m_type; }
	const GameMessageArgumentType *getArgument( Int argIndex ) const;

private:
	unsigned char m_unreconstructed_00[0x10];
	Type m_type;											///< +0x10
};

enum GameWindowMessage
{
	GWM_NONE = 0,

	GWM_CREATE,									GWM_DESTROY,
	GWM_ACTIVATE,								GWM_ENABLE,
	GWM_LEFT_DOWN,								GWM_LEFT_UP,
	GWM_LEFT_DOUBLE_CLICK,						GWM_LEFT_DRAG,
	GWM_MIDDLE_DOWN,							GWM_MIDDLE_UP,
	GWM_MIDDLE_DOUBLE_CLICK,					GWM_MIDDLE_DRAG,
	GWM_RIGHT_DOWN,								GWM_RIGHT_UP,
	GWM_RIGHT_DOUBLE_CLICK,						GWM_RIGHT_DRAG,
	GWM_MOUSE_ENTERING,							GWM_MOUSE_LEAVING,
	GWM_WHEEL_UP,								GWM_WHEEL_DOWN,
	GWM_CHAR,									GWM_SCRIPT_CREATE,
	GWM_INPUT_FOCUS,							GWM_MOUSE_POS,
	GWM_IME_CHAR,								GWM_IME_STRING
};

// ?rawMouseToWindowMessage@@YA?AW4GameWindowMessage@@PBVGameMessage@@@Z
static GameWindowMessage rawMouseToWindowMessage( const GameMessage *msg )
{
	GameWindowMessage gwm = GWM_NONE;

	switch( msg->getType() )
	{
		// ------------------------------------------------------------------------
		case GameMessage::MSG_RAW_MOUSE_POSITION:
			gwm = GWM_MOUSE_POS;
			break;

		// ------------------------------------------------------------------------
		// Strange, but true. The window stuff really doesn't care about double clicks, so just
		// treat it as a down click.. Kinda like a second click.
		case GameMessage::MSG_RAW_MOUSE_LEFT_DOUBLE_CLICK:
		case GameMessage::MSG_RAW_MOUSE_LEFT_BUTTON_DOWN:
			gwm = GWM_LEFT_DOWN;
			break;

		case GameMessage::MSG_RAW_MOUSE_LEFT_BUTTON_UP:
			gwm = GWM_LEFT_UP;
			break;

		case GameMessage::MSG_RAW_MOUSE_LEFT_DRAG:
			gwm = GWM_LEFT_DRAG;
			break;

		// ------------------------------------------------------------------------
		case GameMessage::MSG_RAW_MOUSE_MIDDLE_DOUBLE_CLICK:
		case GameMessage::MSG_RAW_MOUSE_MIDDLE_BUTTON_DOWN:
			gwm = GWM_MIDDLE_DOWN;
			break;

		case GameMessage::MSG_RAW_MOUSE_MIDDLE_BUTTON_UP:
			gwm = GWM_MIDDLE_UP;
			break;

		case GameMessage::MSG_RAW_MOUSE_MIDDLE_DRAG:
			gwm = GWM_MIDDLE_DRAG;
			break;

		// ------------------------------------------------------------------------
		case GameMessage::MSG_RAW_MOUSE_RIGHT_DOUBLE_CLICK:
		case GameMessage::MSG_RAW_MOUSE_RIGHT_BUTTON_DOWN:
			gwm = GWM_RIGHT_DOWN;
			break;

		case GameMessage::MSG_RAW_MOUSE_RIGHT_BUTTON_UP:
			gwm = GWM_RIGHT_UP;
			break;

		case GameMessage::MSG_RAW_MOUSE_RIGHT_DRAG:
			gwm = GWM_RIGHT_DRAG;
			break;

		// ------------------------------------------------------------------------
		case GameMessage::MSG_RAW_MOUSE_WHEEL:
			if( msg->getArgument( 1 )->integer > 0 )
				gwm = GWM_WHEEL_UP;
			else
				gwm = GWM_WHEEL_DOWN;
			break;

	}  // end switch

	return gwm;

}  // end rawMouseToWindowMessage

// The translator is static, so something has to reference it or the TU emits
// nothing. Retail reads its argument off the stack rather than out of a
// register, which is what a static gets once its address escapes, so this hands
// the address out rather than calling it.
typedef GameWindowMessage (*RawMouseToWindowMessageType)( const GameMessage * );

RawMouseToWindowMessageType WindowXlat_getRawMouseToWindowMessage( void )
{
	return rawMouseToWindowMessage;
}
