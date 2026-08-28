// cl: /DNDEBUG /MD /EHsc
// readable body of ?clearPopupMessageData@InGameUI@@QAEXXZ: Code/GameEngine/Source/GameClient/InGameUI.cpp
// Open-BFME: InGameUI::clearPopupMessageData, retail 0x0043B890, 125 bytes.
//
// The reference's body line for line, with the one BFME change the tree
// already carries elsewhere: setGamePaused takes three arguments here, and the
// music flag reaches it inverted -- `sete cl` on the +0x19 byte -- with a
// trailing TRUE the reference has no room for.
//
// The layout is the reference's too. m_popupMessageData sits at InGameUI+0x12A8
// and is reloaded before every use, the virtual calls between them being
// enough for the compiler to have to; the message data carries pause at +0x18,
// pauseMusic at +0x19 and the layout at +0x1C behind its own vptr. Both
// deleteInstance calls are the scalar deleting destructor MSVC emits for
// `delete`, the layout's at vtable slot 1 and the message data's at slot 0,
// and destroyWindows is the layout's slot 8.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/WindowLayout.h
class WindowLayout
{
public:
	virtual void slot0() = 0;
	virtual ~WindowLayout();				// slot 1, vtable+0x04
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual void slot4() = 0;
	virtual void slot5() = 0;
	virtual void slot6() = 0;
	virtual void slot7() = 0;
	virtual void destroyWindows(void) = 0;			// slot 8, vtable+0x20
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/InGameUI.h
class PopupMessageData
{
public:
	virtual ~PopupMessageData();				// slot 0, vtable+0x00

	char m_bfme_head[0x18 - 4];				// this+0x04 .. +0x17, untouched
	Bool pause;						// this+0x18
	Bool pauseMusic;					// this+0x19
	char m_bfme_pad[0x1C - 0x1A];
	WindowLayout *layout;					// this+0x1C
};

class BfmeGameLogicPause
{
public:
	void setGamePaused(Bool pause, Int pauseInput, Bool pauseMusic);	// ILT 0x00006F50
};

extern BfmeGameLogicPause *TheGameLogic;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/InGameUI.h
class InGameUI
{
public:
	void clearPopupMessageData(void);

private:
	char m_slice_pad[0x12A8];				// retail this+0x00 .. +0x12A7, untouched
	PopupMessageData *m_popupMessageData;			// this+0x12A8
};

void InGameUI::clearPopupMessageData( void )
{
	if(!m_popupMessageData)
		return;
	if(m_popupMessageData->layout)
	{
		m_popupMessageData->layout->destroyWindows();
		delete m_popupMessageData->layout;
		m_popupMessageData->layout = 0;
	}
	if( m_popupMessageData->pause )
		TheGameLogic->setGamePaused(false, !m_popupMessageData->pauseMusic, true);
	delete m_popupMessageData;
	m_popupMessageData = 0;

}
