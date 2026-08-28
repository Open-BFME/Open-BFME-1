// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// readable body of ?processCommandTransitionUI@ControlBar@@: Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarCommandProcessing.cpp
// Open-BFME7: isolated port of ControlBarCommandProcessing.cpp's
// ControlBar::processCommandTransitionUI for retail 0x004A6520. The shared TU
// already compiles the Zero Hour body to retail's exact instruction shape --
// every branch, register and stack slot lines up -- and differs only in the
// constants, all of which are BFME drift the reference headers do not carry:
//
//   m_currentSelectedDrawable  this+0x5C   (reference: +0x58)
//   m_currContext              this+0x60   (reference: +0x5C)
//   Drawable's Object field    this+0xFC   (reference: +0x88)
//   CB_CONTEXT_MULTI_SELECT    7           (reference: 5)
//   CB_CONTEXT_OBSERVER_INFO   8           (reference: 6)
//   CB_CONTEXT_OBSERVER_LIST   9           (reference: 7)
//
// The two enum gaps and the two member offsets are what this body proves; where
// BFME's extra context values and its extra ControlBar word actually sit is not
// recoverable from one body, so nothing here claims more than the offsets the
// disassembly pins. reference/shims/controlbarlayout carries a different, older
// slice of the same class and still has the reference's enum, so this stays
// TU-scoped rather than editing that shared header.

#define NULL 0

class GameWindow;
class Object;

enum GadgetGameMessage
{
	GGM_NONE = 0
};

enum CBCommandStatus
{
	CBC_COMMAND_NOT_USED = 0,
	CBC_COMMAND_USED
};

enum ControlBarContext
{
	CB_CONTEXT_NONE = 0,
	CB_CONTEXT_MULTI_SELECT = 7,
	CB_CONTEXT_OBSERVER_INFO = 8,
	CB_CONTEXT_OBSERVER_LIST = 9
};

// Only the offset of the Object field matters here; retail reads it directly,
// so getObject() is inline in BFME too.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Drawable.h
class Drawable
{
public:
	Object *getObject( void ) const { return m_object; }

private:
	unsigned char _bfme_head[0xFC];
	Object *m_object;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class ControlBar
{
protected:
	CBCommandStatus processCommandTransitionUI( GameWindow *control, GadgetGameMessage gadgetMessage );

	// Defined elsewhere: retail reaches it through the link thunk at 0x000329D4.
	void switchToContext( ControlBarContext context, Drawable *draw );

private:
	unsigned char _bfme_head[0x5C];
	Drawable *m_currentSelectedDrawable;
	ControlBarContext m_currContext;
};

CBCommandStatus ControlBar::processCommandTransitionUI( GameWindow *control, GadgetGameMessage gadgetMessage )
{
	// sanity, we won't process messages if we have no source object
	if( m_currContext != CB_CONTEXT_MULTI_SELECT &&
			(m_currentSelectedDrawable == NULL ||
			 m_currentSelectedDrawable->getObject() == NULL) )
	{

		if( m_currContext != CB_CONTEXT_NONE &&
				m_currContext != CB_CONTEXT_OBSERVER_INFO &&
				m_currContext != CB_CONTEXT_OBSERVER_LIST)
			switchToContext( CB_CONTEXT_NONE, NULL );
		return CBC_COMMAND_NOT_USED;

	}  // end if

	return CBC_COMMAND_USED;

}
