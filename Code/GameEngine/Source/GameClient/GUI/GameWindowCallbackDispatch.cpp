// BFME callback dispatch helpers reached by the GameWindowManager message
// forwarding methods.  These are real 22-byte bodies, not lifted assembly.
// The retail helpers first inspect an optional delegate at this+0x1dc, then
// tail-jump through the receiver's virtual slot (+8 for system dispatch).

typedef unsigned int UnsignedInt;
typedef UnsignedInt WindowMsgData;

enum WindowMsgHandledType
{
	MSG_IGNORED,
	MSG_HANDLED
};

// Honest address-derived identity: GameWindowManager's named system-message
// caller at 0x0047C9F0 reaches this ILT, and its raw 22-byte target proves only
// the forwarding layout and virtual slot.  The class owner remains unresolved.
class Rva00479210GameWindow
{
public:
	virtual WindowMsgHandledType slot00( void ) = 0;
	virtual WindowMsgHandledType slot04( void ) = 0;
	virtual WindowMsgHandledType slot08( UnsignedInt msg,
		WindowMsgData mData1, WindowMsgData mData2 ) = 0;

	WindowMsgHandledType dispatch( UnsignedInt msg,
		WindowMsgData mData1, WindowMsgData mData2 );

private:
	char m_pad0[ 0x1D8 ];
	Rva00479210GameWindow *m_forwardTarget;
};

// ?dispatch@Rva00479210GameWindow@@QAE?AW4WindowMsgHandledType@@III@Z 0x00479210
WindowMsgHandledType Rva00479210GameWindow::dispatch( UnsignedInt msg,
	WindowMsgData mData1, WindowMsgData mData2 )
{
	if( m_forwardTarget )
		return m_forwardTarget->slot08( msg, mData1, mData2 );

	return slot08( msg, mData1, mData2 );
}
