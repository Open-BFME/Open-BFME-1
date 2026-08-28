// cl: /DNDEBUG /MD /EHsc
// readable body of ?processDestroyList@GameWindowManager@@IAEXXZ: Code/GameEngine/Source/GameClient/GUI/GameWindowManager.cpp
// Open-BFME: GameWindowManager::processDestroyList, retail 0x0047C0E0, 131 bytes.
//
// The reference's body unchanged, and the manager's own fields fall out of it
// in the reference's order: the destroy list at this+0x10, then the current
// mouse region, the mouse captor, the keyboard focus, the modal head and the
// grab window at +0x14, +0x18, +0x1C, +0x20 and +0x24. The list is taken and
// cleared before the loop runs, which is the whole point of the function, and
// GameWindow's own next link is +0x1F8.
//
// Four of the manager's virtuals are named off their slots and nothing else:
// winSetFocus at vtable+0xB0, winSendSystemMsg at +0xD4, winRelease at +0xE4
// and winUnsetModal at +0xF0. GWM_DESTROY is the 2 the message carries. The
// last call is the scalar deleting destructor MSVC emits for `delete`, with no
// null check because the loop already has one.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

enum { GWM_DESTROY = 2 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
class GameWindow
{
public:
	virtual ~GameWindow();					// slot 0, vtable+0x00

	char m_bfme_body[0x1F8 - 4];				// this+0x04 .. +0x1F7, untouched
	GameWindow *m_next;					// this+0x1F8
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
struct ModalWindow
{
	ModalWindow *next;
	GameWindow *window;					// this+0x04
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindowManager.h
class GameWindowManager
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
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual void slot31() = 0;
	virtual void slot32() = 0;
	virtual void slot33() = 0;
	virtual void slot34() = 0;
	virtual void slot35() = 0;
	virtual void slot36() = 0;
	virtual void slot37() = 0;
	virtual void slot38() = 0;
	virtual void slot39() = 0;
	virtual void slot40() = 0;
	virtual void slot41() = 0;
	virtual void slot42() = 0;
	virtual void slot43() = 0;
	virtual void winSetFocus(GameWindow *window) = 0;		// slot 44, vtable+0xB0
	virtual void slot45() = 0;
	virtual void slot46() = 0;
	virtual void slot47() = 0;
	virtual void slot48() = 0;
	virtual void slot49() = 0;
	virtual void slot50() = 0;
	virtual void slot51() = 0;
	virtual void slot52() = 0;
	virtual Int winSendSystemMsg(GameWindow *window, UnsignedInt msg, UnsignedInt data1, UnsignedInt data2) = 0;	// slot 53, vtable+0xD4
	virtual void slot54() = 0;
	virtual void slot55() = 0;
	virtual void slot56() = 0;
	virtual void winRelease(GameWindow *window) = 0;		// slot 57, vtable+0xE4
	virtual void slot58() = 0;
	virtual void slot59() = 0;
	virtual void winUnsetModal(GameWindow *window) = 0;		// slot 60, vtable+0xF0

protected:
	void processDestroyList(void);

	char m_slice_pad[0x10 - 4];				// retail this+0x04 .. +0x0F, untouched
	GameWindow *m_destroyList;				// this+0x10
	GameWindow *m_currMouseRgn;				// this+0x14
	GameWindow *m_mouseCaptor;				// this+0x18
	GameWindow *m_keyboardFocus;				// this+0x1C
	ModalWindow *m_modalHead;				// this+0x20
	GameWindow *m_grabWindow;				// this+0x24
};

void GameWindowManager::processDestroyList( void )
{
	GameWindow *next;
	GameWindow *doDestroy;

	//
	// we need to pass the ownership of the destroy list so
	// if, while destroying a window, we need to add other windows
	// to the destroy list it won't cause problems.
	//
	doDestroy = m_destroyList;

	// set the list to empty
	m_destroyList = 0;

	// do the destroys
	for( ; doDestroy; doDestroy = next )
	{

		next = doDestroy->m_next;

		// Check to see if this window is "special"
		if( m_mouseCaptor == doDestroy )
			winRelease( doDestroy );

		if( m_keyboardFocus == doDestroy )
			winSetFocus( 0 );

		if( (m_modalHead != 0) && (doDestroy == m_modalHead->window) )
			winUnsetModal( m_modalHead->window );

		if( m_currMouseRgn == doDestroy )
			m_currMouseRgn = 0;

		if( m_grabWindow == doDestroy )
			m_grabWindow = 0;

		// send the destroy message to the window we're about to kill
		winSendSystemMsg( doDestroy, GWM_DESTROY, 0, 0 );

		// free the memory
		if (doDestroy)
			delete doDestroy;

	}  // end for

}  // end processDestroyList
